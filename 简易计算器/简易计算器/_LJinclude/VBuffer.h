#pragma once
#define VBUFFER_
#include "XArray.h"

namespace LJ
{
	//缓存块,提供读和写的同步
	class VBuffer:public VArray<unsigned char>
	{
		//线程同步控制
		ThreadControl tc;
		//禁止复制构造
		VBuffer(const VBuffer&){}
		//禁止赋值运算
		void operator=(const VBuffer&){}
	protected:
		//最新的读取点位置（%Length就得到具体读取位置）
		long long readingPosition;
		//最新的写入点位置（%Length就得到具体写入位置）
		long long writingPosition;
		//向前读取空间（相对读取位置而言）
		unsigned int sizeBefore;
		//预留的前读取空间，默认为创建Buffer使的大小的1/4
		unsigned int sizeBeforeMinimum;
		//向后读取空间（相对读取位置而言）
		unsigned int sizeAfter;
		//是否正在读取，需要同步，读过程要求暂停调整大小、回退操作
		bool isReading;
		//是否正在写入，写入过程要求暂停调整大小、回退操作
		bool isWriting;
		//读操作遇上无内容可读现象
		bool readNothing;
		//写操作遇上无内容可写现象
		bool writeNothing;
		//是否正在调整大小，调整大小过程要求暂停其他操作
		bool isResizing;
		//是否正在回退，回退过程要求暂停读写操作
		bool isRollbacking;
	public:
		//默认缓冲大小
		static unsigned int DefaultSize;
		//创建一个大小为size字节的缓存块
		VBuffer(unsigned int size=DefaultSize);
		//虚析构函数
		virtual ~VBuffer();
		//重置除缓存大小外的参数
		virtual void Reset();
		//调整缓存块大小（字节）
		virtual unsigned int Resize(unsigned int size);
		//调整缓存块大小（字节）
		virtual unsigned int ResizeAndDestroy(unsigned int size);
		//设置预留的后退空间，不能超过总空间的一半，调整大小时将按照总空间二分之一予以限制
		void SetMinimumSizeBefore(unsigned int);
		//获取可读取字节数
		unsigned int GetReadable()const;
		//获取可写入字节数
		unsigned int GetWriteable()const;
		//读位置回退,返回实际回退的字节数
		unsigned int Rollback(unsigned);
		//读位置前进,返回实际前进的字节数
		unsigned int Skip(unsigned);
		//向后读取一定字节数的内容，成功读取时，读取位置将随之后移，内容不足时将一直等待
		XArray<unsigned char> GetAfter(unsigned int );
		//向前读取一定字节数的内容，成功读取时，读取位置将随之前移，内容不足时将一直等待
		XArray<unsigned char> GetBefore(unsigned int );
		//向后写入一段数据，若无法写完则一直等待，返回实际写入数量
		template<typename T>unsigned int PutAfter(const XArray<T>&);
		//向前写入一段数据，若无法写完则一直等待
		template<typename T>unsigned int PutBefore(const XArray<T>&);
	};
	//向后写入一段数据，若无法写完则一直等待
	template<typename T> unsigned int VBuffer::PutAfter(const XArray<T>&xArray)
	{
		if(!xArray.Length)return 0; 
		int size = xArray.GetLengthOfBytes();
START1:;
		tc.ThreadWait();
		if(isWriting || isResizing || isRollbacking)
		{
			tc.ThreadDone();
			Sleep(1);
			goto START1;
		}
		if(writingPosition<=readingPosition && sizeAfter)writingPosition = readingPosition+sizeAfter;
		isWriting = true;//采用写操作标记
		tc.ThreadDone();
		int tmp,i=0;
		while(i<size)
		{
			tc.ThreadWait();
			if(sizeBeforeMinimum+sizeAfter>=(unsigned int)Length && sizeBefore+sizeAfter>=(unsigned int)Length)//无可写内容,等待读取
			{
				tc.ThreadDone();
				if(isRollbacking || isResizing)goto End;
				writeNothing = true;
				Sleep(1);
				continue;
			}
			writeNothing = false;
			if(sizeBefore+sizeAfter>=(unsigned int)Length)tmp = Length-sizeAfter-sizeBeforeMinimum;
			else tmp = Length - sizeBefore;
			tc.ThreadDone();
			if(tmp>size-i)tmp = size-i;

			if(((writingPosition%Length)+Length)%Length+tmp>=Length)//超出范围
				tmp = Length - ((writingPosition%Length)+Length)%Length;
START2:;
			tc.ThreadWait();//获取过程需要同步，因为此时读操作有可能对数据改动
			if(isReading && !readNothing)//等待读操作完成
			{
				tc.ThreadDone();
				Sleep(0);
				goto START2;
			}
			if(sizeBefore+tmp+sizeAfter>(unsigned int)Length)sizeBefore -= tmp;//向后写入前先减少可向前读取部分
			tc.ThreadDone();

			XBase::Memory::Copy(pData+((writingPosition%Length)+Length)%Length,((const unsigned char*)(const void*)xArray)+i,tmp);
			i+=tmp;

START3:
			writeNothing = true;
			tc.ThreadWait();//更改过程需要同步，因为此时写操作有可能在进行
			if(isReading && !readNothing)//等待读操作完成
			{
				tc.ThreadDone();
				Sleep(0);
				goto START3;
			}
			writingPosition += tmp;
			sizeAfter += tmp;
			tc.ThreadDone();
		}
End:;//结束读取
		writeNothing = false;
		isWriting = false;//结束读取
		return i;
	}
	//向前写入一段数据，若无法写完则一直等待
	template<typename T>unsigned int VBuffer::PutBefore(const XArray<T>&xArray)
	{
		if(xArray.Length==0)return 0; 
		int size = xArray.GetLengthOfByte();
START1:;
		tc.ThreadWait();
		if(isWriting || isResizing || isRollbacking)
		{
			tc.ThreadDone();
			Sleep(1);
			goto START1;
		}
		if(writingPosition>=readingPosition && sizeBefore)writingPosition = readingPosition-sizeBefore;
		isWriting = true;//采用写操作标记
		tc.ThreadDone();
		int tmp,i=size;
		while(i>0)
		{
			tc.ThreadWait();
			if(sizeBeforeMinimum+sizeBefore>=Length && sizeBefore+sizeAfter>=Length)//无可写内容,等待读取
			{
				tc.ThreadDone();
				if(isRollbacking || isResizing)goto End;
				writeNothing = true;
				Sleep(1);
				continue;
			}
			writeNothing = false;
			if(sizeBefore+sizeAfter>=Length)tmp = Length-sizeBefore-sizeBeforeMinimum;
			else tmp = Length - sizeBefore;
			tc.ThreadDone();
			if(tmp>i)tmp = i;

			if(((writingPosition%Length)+Length)%Length<tmp)//超出范围
				tmp = ((writingPosition%Length)+Length)%Length;

START2:;
			tc.ThreadWait();//获取过程需要同步，因为此时读操作有可能对数据改动
			if(isReading && !readNothing)//等待读操作完成
			{
				tc.ThreadDone();
				Sleep(0);
				goto START2;
			}
			if(sizeBefore+tmp+sizeAfter>Length)sizeAfter -= tmp;//向前写入前先减少可向后读取部分
			tc.ThreadDone();

			i-=tmp;
			memcpy_s(pData+((writingPosition%Length)+Length)%Length,tmp,((const unsigned char*)xArray)+i,tmp);

START3:;
			tc.ThreadWait();//更改过程需要同步，因为此时写操作有可能在进行
			if(isReading && !readNothing)//等待读操作完成
			{
				tc.ThreadDone();
				Sleep(0);
				goto START3;
			}
			writingPosition -= tmp;
			sizeBefore += tmp;
			tc.ThreadDone();
		}
End:;//结束读取
		writeNothing = false;
		isWriting = false;//结束读取
		return size-i;
	}

}