#include"stdafx.h"
#ifdef XBUFFERS_
namespace LJ
{
	namespace IO
	{
		//将某个读取线程挂起
		void IBuffers::HangReading(XThread xt)
		{
			xt.Suspend();
			queueReadingTasks.Enqueue(xt);
		}
		//将某个写入线程挂起
		void IBuffers::HangWriting(XThread xt)
		{
			xt.Suspend();
			queueWritingTasks.Enqueue(xt);
		}
		//默认构造函数
		IBuffers::IBuffers(int maxAlreadyRead)
			:IIO(true,true),
			AlreadyReadBytes(0),UnReadBytes(0),
			maxUnReadBytes(DefaultMaxUnReadBytes),maxUnReadCount(DefaultMaxUnReadCount),maxAreadyReadBytes(DefaultMaxAreadyReadBytes),maxAreadyReadCount(maxAlreadyRead)
		{}
		//获取未读取数组数
		int IBuffers::GetUnReadCount()const
		{
			return queueUnRead.Length;
		}
		//获取已读取的数组数
		int IBuffers::GetAlreadyReadCount()const
		{
			return queueAlreadyRead.Length;
		}
		//添加一个数组到缓存队列（直接引用，无数据复制过程）,如果缓存队列已满，该操作将会一直等待
		void IBuffers::Add(const XArray<unsigned char>& r)
		{
			int countWaiting(0);
Start:;
			tc.ThreadWait();
			if(UnReadBytes>=maxUnReadBytes || UnReadCount>=maxUnReadCount)
			{
				tc.ThreadDone();
				++countWaiting;
				if(countWaiting>5){XThread(this,&IBuffers::HangWriting,XThread::Current);countWaiting = 0;}//挂起
				Sleep(1);
				goto Start;
			}
			queueUnRead.Enqueue(r);//添加到未读取队列
			const_cast<long long&>(UnReadBytes)+=r.Length;
			IncreaseOut(r.Length);
			if(queueUnRead.Length==1)firstUnReadBytes = r.Length;
			while(queueReadingTasks.Length>0)queueReadingTasks.Dequeue().Resume();
			tc.ThreadDone();
		}
		//异步添加一个数组到缓存队列（直接引用，无数据复制过程），返回一个包含添加动作的任务
		XTask IBuffers::BeginAdd(const XArray<unsigned char>& r)
		{
			XTask tmp(XActions(XDelegates(this,&IBuffers::Add),r));
			tmp.Begin();
			return tmp;
		}
		//从Buffers未读数据中取出一个数组（如果与CopyTo混用则可能有复制过程），如果没有可读数组，该操作将一直等待
		XArray<unsigned char> IBuffers::Get()
		{
			int countWaiting(0);
Start:;
			tc.ThreadWait();
			if(queueUnRead.Length==0)
			{
				tc.ThreadDone();
				++countWaiting;
				if(countWaiting>5){XThread(this,&IBuffers::HangReading,XThread::Current);countWaiting=0;}
				Sleep(1);
				goto Start;
			}
			XArray<unsigned char> tmp(queueUnRead.Dequeue());
			const_cast<long long&>(UnReadBytes)-=firstUnReadBytes;
			if(maxAreadyReadBytes>0 && maxAreadyReadCount>0)//放入已读取队列
			{
				queueAlreadyRead.Enqueue(tmp);
				const_cast<long long&>(AlreadyReadBytes)+=firstUnReadBytes;
				while(queueAlreadyRead.Length>0 && (AlreadyReadBytes>maxAreadyReadBytes || AlreadyReadCount>maxAreadyReadCount))
				{
					const_cast<long long&>(AlreadyReadBytes)-=queueAlreadyRead.Dequeue().Length;
				}
			}
			if(firstUnReadBytes<tmp.Length)tmp = tmp.SubArray(tmp.Length-firstUnReadBytes,firstUnReadBytes);
			IncreaseIn(firstUnReadBytes);
			if(queueUnRead.Length>0)firstUnReadBytes=queueUnRead.Peek().Length;
			if(UnReadBytes<maxUnReadBytes && UnReadCount<maxUnReadCount)while(queueWritingTasks.Length>0)queueWritingTasks.Dequeue().Resume();
			tc.ThreadDone();
			return tmp;
		}
		//异步取出一个数组（如果与CopyTo混用则可能有复制过程），返回一个包含取出动作的任务,取出的数据可在任务中动作的返回值得到
		XTask IBuffers::BeginGet()
		{
			XTask tmp(XDelegates(this,&IBuffers::Get).MakeAction());
			tmp.Begin();
			return tmp;
		}
		//从Buffers的未读取队列中取一个数组（直接引用，无复制过程）与Get方法不同，该方法不会使已读取数量变化。如果没有可读数组，该操作将立即返回一个空数组
		XArray<unsigned char> IBuffers::Peek()
		{
			tc.ThreadWait();
			XArray<unsigned char> tmp;
			if(queueUnRead.Length>0)
			{
				tmp = queueUnRead.Peek();
				if(firstUnReadBytes<tmp.Length)//与CopyTo混用时，将导致返回引用数组
					tmp = tmp.SubArray(tmp.Length-firstUnReadBytes,firstUnReadBytes,Reference);//返回一个引用性质的数组，该数组将是不安全的
			}
			tc.ThreadDone();
			return tmp;
		}
		//取数据到指定数组中(有复制过程，填满数组)，返回读取的字节数
		int IBuffers::CopyTo(XArray<unsigned char> ra)
		{
			return CopyTo(ra,ra.Length);
		}
		//取一定字节数的数据到指定数组中(有复制过程)，返回读取的字节数
		int IBuffers::CopyTo(XArray<unsigned char> ra,int length)
		{
			if(length>ra.Length)throw XException(COR_E_INDEXOUTOFRANGE);
			int bytesCopy=0;
			int countWaiting=0;
Start:;
			tc.ThreadWait();
			if(queueUnRead.Length==0)//没有可读数据将导致等待
			{
				tc.ThreadDone();
				++countWaiting;
				if(countWaiting>5){XThread(this,&IBuffers::HangReading,XThread::Current);countWaiting=0;}//线程挂起
				Sleep(1);
				goto Start;
			}
			for(;;)
			{
				XArray<unsigned char> tmp = queueUnRead.Peek();//试探第一个数据
				if(firstUnReadBytes>length-bytesCopy)//数据过多
				{
					tmp.CopyTo(ra,tmp.Length-firstUnReadBytes,bytesCopy,firstUnReadBytes);
					firstUnReadBytes -= length-bytesCopy;
					const_cast<long long&>(UnReadBytes)-=length-bytesCopy;
					const_cast<long long&>(AlreadyReadBytes)+=length-bytesCopy;
					IncreaseIn(length-bytesCopy);
					goto End;
				}
				tmp.CopyTo(ra,0,0,firstUnReadBytes);
				bytesCopy+= firstUnReadBytes;
				queueUnRead.Dequeue();
				const_cast<long long&>(UnReadBytes)-=firstUnReadBytes;
				IncreaseIn(firstUnReadBytes);
				if(maxAreadyReadBytes>0 && maxAreadyReadCount>0)//放入已读取队列
				{
					queueAlreadyRead.Enqueue(tmp);
					const_cast<long long&>(AlreadyReadBytes)+=firstUnReadBytes;
					while(queueAlreadyRead.Length>0 && (AlreadyReadBytes>maxAreadyReadBytes || AlreadyReadCount>maxAreadyReadCount))
					{
						const_cast<long long&>(AlreadyReadBytes)-=queueAlreadyRead.Dequeue().Length;
					}
				}
				else const_cast<long long&>(AlreadyReadBytes)=0;
				if(queueUnRead.Length>0)firstUnReadBytes = queueUnRead.Peek().Length;
				else
				{
					if(bytesCopy<length){tc.ThreadDone();goto Start;}
					goto End;
				}
			}
End:;
			if(UnReadBytes<maxUnReadBytes && UnReadCount<maxUnReadCount)while(queueWritingTasks.Length>0)queueWritingTasks.Dequeue().Resume();
			tc.ThreadDone();
			return bytesCopy;
		}
		//最大允许保存的未读数据块数(默认值)
		int IBuffers::DefaultMaxUnReadCount = 1024;
		//最大允许保存的未读字节数(默认值)
		long long IBuffers::DefaultMaxUnReadBytes=0x100000000;
		//最大允许保存的已读数据块数(默认值)
		int IBuffers::DefaultMaxAreadyReadCount=0;
		//最大允许保存的已读字节数(默认值)
		long long IBuffers::DefaultMaxAreadyReadBytes=0x100000000;


		//添加一个数组到缓存队列（直接引用，无数据复制过程）,如果缓存队列已满，该操作将会一直等待
		void XBuffers::Add(const XArray<unsigned char>& r)
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			reinterpret_cast<IBuffers*&>(pObject)->Add(r);
		}
		//异步添加一个数组到缓存队列（直接引用，无数据复制过程），返回一个包含添加动作的任务
		XTask XBuffers::BeginAdd(const XArray<unsigned char>& r)
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->BeginAdd(r);
		}
		//从Buffers中取出一个数组（直接引用，无复制过程），如果没有可读数组，该操作将一直等待
		XArray<unsigned char> XBuffers::Get()
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->Get();
		}
		//异步取出一个数组（直接引用，无复制过程），返回一个包含取出动作的任务,取出的数据可在任务中动作的返回值得到
		XTask XBuffers::BeginGet()
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->BeginGet();
		}
		//从Buffers中取一个数组（直接引用，无复制过程）与Get方法不同，该方法不会使已读取数量变化。如果没有可读数组，该操作将立即返回一个空引用
		XArray<unsigned char> XBuffers::Peek()
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->Peek();
		}
		//取数据到指定数组中(有复制过程，填满数组)，返回读取的字节数
		int XBuffers::CopyTo(XArray<unsigned char> ra)
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->CopyTo(ra);
		}
		//取一定字节数的数据到指定数组中(有复制过程)，返回读取的字节数
		int XBuffers::CopyTo(XArray<unsigned char> ra,int length)
		{
			if(IsNull())throw XException("尝试对空引用执行操作。",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->CopyTo(ra,length);
		}

	}
}
#endif