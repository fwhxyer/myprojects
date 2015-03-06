#include "stdafx.h"
#ifdef VBUFFER_
namespace LJ
{
	unsigned VBuffer::DefaultSize = 10240;//默认是10k的缓冲块
	VBuffer::VBuffer(unsigned int size)//创建一个大小为size字节的缓存块
		:VArray<unsigned char>(size,(unsigned char*)0),
		readingPosition(0),writingPosition(0),sizeBefore(0),sizeAfter(0),sizeBeforeMinimum(size/4),
		isReading(false),isWriting(false),isResizing(false),isRollbacking(false),readNothing(false),writeNothing(false)
	{	}
	VBuffer::~VBuffer()//虚析构函数
	{
	}
	//调整缓存块大小并尽量保存向后的数据
	unsigned int VBuffer::Resize(unsigned int size)
	{
START:;
		tc.ThreadWait();
		if(isResizing)
		{
			tc.ThreadDone();
			Sleep(0);
			goto START;
		}
		tc.ThreadDone();
		while(isReading || isWriting || isRollbacking)Sleep(0);
		//更改过程不需要同步，因为此时其它操作都被挂起
		VArray<unsigned char> pdata(size);
		unsigned int tmp = Length?Length-(readingPosition%Length+Length)%Length:0;
		if(tmp>sizeAfter)tmp = sizeAfter;
		if(tmp>size)tmp = size;
		Memory::Copy(pdata,pData+(readingPosition%Length+Length)%Length,tmp);
		sizeAfter = size<sizeAfter?size:sizeAfter;
		if(tmp<sizeAfter)
		{
			Memory::Copy(pdata+tmp,pData+((readingPosition+tmp)%Length+Length)%Length,sizeAfter-tmp);
		}
		writingPosition = sizeAfter;
		readingPosition = 0;
		sizeBefore = 0;
		VArray<unsigned char>::SwapWith(pdata);
		isResizing = false;
		if(sizeBeforeMinimum>size/2)sizeBeforeMinimum=size/2;
		return size;
	}
	//调整缓存块大小并销毁数据（重置读写位置）
	unsigned int VBuffer::ResizeAndDestroy(unsigned int size)
	{
START:;
		tc.ThreadWait();
		if(isResizing)
		{
			tc.ThreadDone();
			Sleep(0);
			goto START;
		}
		tc.ThreadDone();
		while(isReading || isWriting || isRollbacking)Sleep(0);
		VArray<unsigned char>::ResizeAndDestroy(size);//更改过程不需要同步，因为此时其它操作都被挂起
		readingPosition=0;
		writingPosition=0;
		sizeBefore=0;
		sizeAfter=0;
		isResizing = false;
		if(sizeBeforeMinimum>size/2)sizeBeforeMinimum=size/2;
		return size;
	}
	//设置预留的后退空间
	void VBuffer::SetMinimumSizeBefore(unsigned int size)
	{
		if(size<=(unsigned int)Length/2)sizeBeforeMinimum = size;
	}
	//重置除缓存大小外的参数
	void VBuffer::Reset()//采用调整大小的标记，排斥读写
	{
START:;
		tc.ThreadWait();
		if(isResizing)
		{
			tc.ThreadDone();
			Sleep(0);
			goto START;
		}
		tc.ThreadDone();
		while(isReading || isWriting || isRollbacking)Sleep(0);
		//操作
		readingPosition=0;//更改过程不需要同步，因为此时其它操作都被挂起
		writingPosition=0;
		sizeBefore=0;
		sizeAfter=0;
		isResizing = false;
	}
	//获取可向后读取字节数
	unsigned int VBuffer::GetReadable()const
	{
		return sizeAfter;
	}
	//获取可向后写入字节数
	unsigned int VBuffer::GetWriteable()const
	{
		const_cast<VBuffer*>(this)->tc.ThreadWait();
		unsigned int tmp = Length -  sizeAfter - sizeBeforeMinimum;
		tmp = (tmp>Length-sizeAfter-sizeBefore)?tmp:(Length-sizeAfter-sizeBefore);
		const_cast<VBuffer*>(this)->tc.ThreadDone();
		return tmp;
	}
	//读位置回退,返回实际回退的字节数
	unsigned int VBuffer::Rollback(unsigned int size)
	{
START:;
		tc.ThreadWait();
		if(isRollbacking || isResizing)
		{
			tc.ThreadDone();
			Sleep(0);
			goto START;
		}
		isRollbacking = true;
		tc.ThreadDone();
		while(isWriting || isReading)Sleep(0);
		if(size>sizeBefore)size = sizeBefore;//更改过程不需要同步，因为此时其它操作都被挂起
		readingPosition -= size;
		sizeBefore -= size;
		sizeAfter += size;

		isRollbacking = false;
		return size;
	}
	//读位置前进,返回实际前进的字节数
	unsigned int VBuffer::Skip(unsigned int size)
	{
START1:;
		tc.ThreadWait();
		if(isReading || isResizing || isRollbacking)
		{
			tc.ThreadDone();
			Sleep(0);
			goto START1;
		}
		isReading = true;//采用读操作标记
		tc.ThreadDone();
START2:;
		while(isWriting)Sleep(0);//等待写操作完成
		tc.ThreadWait();//更改过程需要同步，因为此时写操作有可能在进行
		if(isWriting)
		{
			tc.ThreadDone();
			goto START2;
		}
		if(size>sizeAfter)size = sizeAfter;
		readingPosition += size;
		sizeBefore += size;
		sizeAfter -= size;
		isReading = false;
		tc.ThreadDone();
		return size;
	}
	//向后读取一定字节数的内容，成功读取时，读取位置将随之后移，内容不足时将一直等待
	XArray<unsigned char> VBuffer::GetAfter(unsigned int size)
	{
START1:;
		tc.ThreadWait();
		if(isReading || isResizing || isRollbacking)
		{
			tc.ThreadDone();
			Sleep(1);
			goto START1;
		}
		isReading = true;//采用读操作标记
		tc.ThreadDone();
		int tmp,i=0;
		unsigned char* pdata=new unsigned char[size];
		while(i<(int)size)
		{
			if(!sizeAfter)//无可读内容,等待写入
			{
				if(isRollbacking || isResizing)goto End;
				readNothing = true;
				Sleep(1);
				continue;
			}
			readNothing = false;
			tmp = sizeAfter;
			if(tmp>(int)size-i)tmp = size-i;

			if(((readingPosition%Length)+Length)%Length+tmp>=Length)//超出范围
				tmp = Length - ((readingPosition%Length)+Length)%Length;
			XBase::Memory::Copy(pdata+i,pData+((readingPosition%Length)+Length)%Length,tmp);
			i+=tmp;

START2:;
			readNothing = true;
			while(isWriting && !writeNothing)Sleep(0);//等待写操作完成
			tc.ThreadWait();//更改过程需要同步，因为此时写操作有可能在进行
			if(isWriting && !writeNothing)
			{
				tc.ThreadDone();
				goto START2;
			}
			readingPosition += tmp;
			sizeBefore += tmp;
			sizeAfter -= tmp;
			tc.ThreadDone();
		}
End:;//结束读取
		readNothing = false;
		isReading = false;//结束读取
		return XArray<unsigned char>(i,pdata);
	}
	XArray<unsigned char> VBuffer::GetBefore(unsigned int size)//向前读取一定字节数的内容，成功读取时，读取位置将随之前移，内容不足时将一直等待
	{
		START1:;
		tc.ThreadWait();
		if(isReading || isResizing || isRollbacking)
		{
			tc.ThreadDone();
			Sleep(1);
			goto START1;
		}
		isReading = true;//采用读操作标记
		tc.ThreadDone();
		int tmp,i=size;
		unsigned char* pdata=new unsigned char[size];
		while(i>0)
		{
			if(!sizeBefore)//无可读内容,等待写入
			{
				if(isRollbacking || isResizing)goto End;
				readNothing = true;
				Sleep(1);
				continue;
			}
			readNothing = false;
			tmp = sizeBefore;
			if(tmp>i)tmp = i;

			if(((readingPosition%Length)+Length)%Length<=tmp)//超出范围
				tmp = Length - ((readingPosition%Length)+Length)%Length;
			i-=tmp;
			memcpy_s(pdata+i,tmp,pData+((readingPosition%Length)+Length)%Length,tmp);

START2:;
			while(isWriting && !writeNothing)Sleep(0);//等待写操作完成
			tc.ThreadWait();//更改过程需要同步，因为此时写操作有可能在进行
			if(isWriting && !writeNothing)
			{
				tc.ThreadDone();
				goto START2;
			}
			readingPosition -= tmp;
			sizeBefore -= tmp;
			sizeAfter += tmp;
			tc.ThreadDone();
		}
End:;//结束读取
		readNothing = false;
		isReading = false;//结束读取
		if(i)
		{
			memmove_s(pdata,size-i,pdata+i,size-i);
		}
		return XArray<unsigned char>(size-i,pdata);
	}


}
#endif