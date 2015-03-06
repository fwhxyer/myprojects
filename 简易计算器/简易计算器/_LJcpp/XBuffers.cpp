#include"stdafx.h"
#ifdef XBUFFERS_
namespace LJ
{
	namespace IO
	{
		//��ĳ����ȡ�̹߳���
		void IBuffers::HangReading(XThread xt)
		{
			xt.Suspend();
			queueReadingTasks.Enqueue(xt);
		}
		//��ĳ��д���̹߳���
		void IBuffers::HangWriting(XThread xt)
		{
			xt.Suspend();
			queueWritingTasks.Enqueue(xt);
		}
		//Ĭ�Ϲ��캯��
		IBuffers::IBuffers(int maxAlreadyRead)
			:IIO(true,true),
			AlreadyReadBytes(0),UnReadBytes(0),
			maxUnReadBytes(DefaultMaxUnReadBytes),maxUnReadCount(DefaultMaxUnReadCount),maxAreadyReadBytes(DefaultMaxAreadyReadBytes),maxAreadyReadCount(maxAlreadyRead)
		{}
		//��ȡδ��ȡ������
		int IBuffers::GetUnReadCount()const
		{
			return queueUnRead.Length;
		}
		//��ȡ�Ѷ�ȡ��������
		int IBuffers::GetAlreadyReadCount()const
		{
			return queueAlreadyRead.Length;
		}
		//���һ�����鵽������У�ֱ�����ã������ݸ��ƹ��̣�,�����������������ò�������һֱ�ȴ�
		void IBuffers::Add(const XArray<unsigned char>& r)
		{
			int countWaiting(0);
Start:;
			tc.ThreadWait();
			if(UnReadBytes>=maxUnReadBytes || UnReadCount>=maxUnReadCount)
			{
				tc.ThreadDone();
				++countWaiting;
				if(countWaiting>5){XThread(this,&IBuffers::HangWriting,XThread::Current);countWaiting = 0;}//����
				Sleep(1);
				goto Start;
			}
			queueUnRead.Enqueue(r);//��ӵ�δ��ȡ����
			const_cast<long long&>(UnReadBytes)+=r.Length;
			IncreaseOut(r.Length);
			if(queueUnRead.Length==1)firstUnReadBytes = r.Length;
			while(queueReadingTasks.Length>0)queueReadingTasks.Dequeue().Resume();
			tc.ThreadDone();
		}
		//�첽���һ�����鵽������У�ֱ�����ã������ݸ��ƹ��̣�������һ��������Ӷ���������
		XTask IBuffers::BeginAdd(const XArray<unsigned char>& r)
		{
			XTask tmp(XActions(XDelegates(this,&IBuffers::Add),r));
			tmp.Begin();
			return tmp;
		}
		//��Buffersδ��������ȡ��һ�����飨�����CopyTo����������и��ƹ��̣������û�пɶ����飬�ò�����һֱ�ȴ�
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
			if(maxAreadyReadBytes>0 && maxAreadyReadCount>0)//�����Ѷ�ȡ����
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
		//�첽ȡ��һ�����飨�����CopyTo����������и��ƹ��̣�������һ������ȡ������������,ȡ�������ݿ��������ж����ķ���ֵ�õ�
		XTask IBuffers::BeginGet()
		{
			XTask tmp(XDelegates(this,&IBuffers::Get).MakeAction());
			tmp.Begin();
			return tmp;
		}
		//��Buffers��δ��ȡ������ȡһ�����飨ֱ�����ã��޸��ƹ��̣���Get������ͬ���÷�������ʹ�Ѷ�ȡ�����仯�����û�пɶ����飬�ò�������������һ��������
		XArray<unsigned char> IBuffers::Peek()
		{
			tc.ThreadWait();
			XArray<unsigned char> tmp;
			if(queueUnRead.Length>0)
			{
				tmp = queueUnRead.Peek();
				if(firstUnReadBytes<tmp.Length)//��CopyTo����ʱ�������·�����������
					tmp = tmp.SubArray(tmp.Length-firstUnReadBytes,firstUnReadBytes,Reference);//����һ���������ʵ����飬�����齫�ǲ���ȫ��
			}
			tc.ThreadDone();
			return tmp;
		}
		//ȡ���ݵ�ָ��������(�и��ƹ��̣���������)�����ض�ȡ���ֽ���
		int IBuffers::CopyTo(XArray<unsigned char> ra)
		{
			return CopyTo(ra,ra.Length);
		}
		//ȡһ���ֽ��������ݵ�ָ��������(�и��ƹ���)�����ض�ȡ���ֽ���
		int IBuffers::CopyTo(XArray<unsigned char> ra,int length)
		{
			if(length>ra.Length)throw XException(COR_E_INDEXOUTOFRANGE);
			int bytesCopy=0;
			int countWaiting=0;
Start:;
			tc.ThreadWait();
			if(queueUnRead.Length==0)//û�пɶ����ݽ����µȴ�
			{
				tc.ThreadDone();
				++countWaiting;
				if(countWaiting>5){XThread(this,&IBuffers::HangReading,XThread::Current);countWaiting=0;}//�̹߳���
				Sleep(1);
				goto Start;
			}
			for(;;)
			{
				XArray<unsigned char> tmp = queueUnRead.Peek();//��̽��һ������
				if(firstUnReadBytes>length-bytesCopy)//���ݹ���
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
				if(maxAreadyReadBytes>0 && maxAreadyReadCount>0)//�����Ѷ�ȡ����
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
		//����������δ�����ݿ���(Ĭ��ֵ)
		int IBuffers::DefaultMaxUnReadCount = 1024;
		//����������δ���ֽ���(Ĭ��ֵ)
		long long IBuffers::DefaultMaxUnReadBytes=0x100000000;
		//�����������Ѷ����ݿ���(Ĭ��ֵ)
		int IBuffers::DefaultMaxAreadyReadCount=0;
		//�����������Ѷ��ֽ���(Ĭ��ֵ)
		long long IBuffers::DefaultMaxAreadyReadBytes=0x100000000;


		//���һ�����鵽������У�ֱ�����ã������ݸ��ƹ��̣�,�����������������ò�������һֱ�ȴ�
		void XBuffers::Add(const XArray<unsigned char>& r)
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			reinterpret_cast<IBuffers*&>(pObject)->Add(r);
		}
		//�첽���һ�����鵽������У�ֱ�����ã������ݸ��ƹ��̣�������һ��������Ӷ���������
		XTask XBuffers::BeginAdd(const XArray<unsigned char>& r)
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->BeginAdd(r);
		}
		//��Buffers��ȡ��һ�����飨ֱ�����ã��޸��ƹ��̣������û�пɶ����飬�ò�����һֱ�ȴ�
		XArray<unsigned char> XBuffers::Get()
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->Get();
		}
		//�첽ȡ��һ�����飨ֱ�����ã��޸��ƹ��̣�������һ������ȡ������������,ȡ�������ݿ��������ж����ķ���ֵ�õ�
		XTask XBuffers::BeginGet()
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->BeginGet();
		}
		//��Buffers��ȡһ�����飨ֱ�����ã��޸��ƹ��̣���Get������ͬ���÷�������ʹ�Ѷ�ȡ�����仯�����û�пɶ����飬�ò�������������һ��������
		XArray<unsigned char> XBuffers::Peek()
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->Peek();
		}
		//ȡ���ݵ�ָ��������(�и��ƹ��̣���������)�����ض�ȡ���ֽ���
		int XBuffers::CopyTo(XArray<unsigned char> ra)
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->CopyTo(ra);
		}
		//ȡһ���ֽ��������ݵ�ָ��������(�и��ƹ���)�����ض�ȡ���ֽ���
		int XBuffers::CopyTo(XArray<unsigned char> ra,int length)
		{
			if(IsNull())throw XException("���ԶԿ�����ִ�в�����",E_POINTER);
			return reinterpret_cast<IBuffers*&>(pObject)->CopyTo(ra,length);
		}

	}
}
#endif