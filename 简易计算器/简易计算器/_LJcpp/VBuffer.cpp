#include "stdafx.h"
#ifdef VBUFFER_
namespace LJ
{
	unsigned VBuffer::DefaultSize = 10240;//Ĭ����10k�Ļ����
	VBuffer::VBuffer(unsigned int size)//����һ����СΪsize�ֽڵĻ����
		:VArray<unsigned char>(size,(unsigned char*)0),
		readingPosition(0),writingPosition(0),sizeBefore(0),sizeAfter(0),sizeBeforeMinimum(size/4),
		isReading(false),isWriting(false),isResizing(false),isRollbacking(false),readNothing(false),writeNothing(false)
	{	}
	VBuffer::~VBuffer()//����������
	{
	}
	//����������С������������������
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
		//���Ĺ��̲���Ҫͬ������Ϊ��ʱ����������������
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
	//����������С���������ݣ����ö�дλ�ã�
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
		VArray<unsigned char>::ResizeAndDestroy(size);//���Ĺ��̲���Ҫͬ������Ϊ��ʱ����������������
		readingPosition=0;
		writingPosition=0;
		sizeBefore=0;
		sizeAfter=0;
		isResizing = false;
		if(sizeBeforeMinimum>size/2)sizeBeforeMinimum=size/2;
		return size;
	}
	//����Ԥ���ĺ��˿ռ�
	void VBuffer::SetMinimumSizeBefore(unsigned int size)
	{
		if(size<=(unsigned int)Length/2)sizeBeforeMinimum = size;
	}
	//���ó������С��Ĳ���
	void VBuffer::Reset()//���õ�����С�ı�ǣ��ų��д
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
		//����
		readingPosition=0;//���Ĺ��̲���Ҫͬ������Ϊ��ʱ����������������
		writingPosition=0;
		sizeBefore=0;
		sizeAfter=0;
		isResizing = false;
	}
	//��ȡ������ȡ�ֽ���
	unsigned int VBuffer::GetReadable()const
	{
		return sizeAfter;
	}
	//��ȡ�����д���ֽ���
	unsigned int VBuffer::GetWriteable()const
	{
		const_cast<VBuffer*>(this)->tc.ThreadWait();
		unsigned int tmp = Length -  sizeAfter - sizeBeforeMinimum;
		tmp = (tmp>Length-sizeAfter-sizeBefore)?tmp:(Length-sizeAfter-sizeBefore);
		const_cast<VBuffer*>(this)->tc.ThreadDone();
		return tmp;
	}
	//��λ�û���,����ʵ�ʻ��˵��ֽ���
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
		if(size>sizeBefore)size = sizeBefore;//���Ĺ��̲���Ҫͬ������Ϊ��ʱ����������������
		readingPosition -= size;
		sizeBefore -= size;
		sizeAfter += size;

		isRollbacking = false;
		return size;
	}
	//��λ��ǰ��,����ʵ��ǰ�����ֽ���
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
		isReading = true;//���ö��������
		tc.ThreadDone();
START2:;
		while(isWriting)Sleep(0);//�ȴ�д�������
		tc.ThreadWait();//���Ĺ�����Ҫͬ������Ϊ��ʱд�����п����ڽ���
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
	//����ȡһ���ֽ��������ݣ��ɹ���ȡʱ����ȡλ�ý���֮���ƣ����ݲ���ʱ��һֱ�ȴ�
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
		isReading = true;//���ö��������
		tc.ThreadDone();
		int tmp,i=0;
		unsigned char* pdata=new unsigned char[size];
		while(i<(int)size)
		{
			if(!sizeAfter)//�޿ɶ�����,�ȴ�д��
			{
				if(isRollbacking || isResizing)goto End;
				readNothing = true;
				Sleep(1);
				continue;
			}
			readNothing = false;
			tmp = sizeAfter;
			if(tmp>(int)size-i)tmp = size-i;

			if(((readingPosition%Length)+Length)%Length+tmp>=Length)//������Χ
				tmp = Length - ((readingPosition%Length)+Length)%Length;
			XBase::Memory::Copy(pdata+i,pData+((readingPosition%Length)+Length)%Length,tmp);
			i+=tmp;

START2:;
			readNothing = true;
			while(isWriting && !writeNothing)Sleep(0);//�ȴ�д�������
			tc.ThreadWait();//���Ĺ�����Ҫͬ������Ϊ��ʱд�����п����ڽ���
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
End:;//������ȡ
		readNothing = false;
		isReading = false;//������ȡ
		return XArray<unsigned char>(i,pdata);
	}
	XArray<unsigned char> VBuffer::GetBefore(unsigned int size)//��ǰ��ȡһ���ֽ��������ݣ��ɹ���ȡʱ����ȡλ�ý���֮ǰ�ƣ����ݲ���ʱ��һֱ�ȴ�
	{
		START1:;
		tc.ThreadWait();
		if(isReading || isResizing || isRollbacking)
		{
			tc.ThreadDone();
			Sleep(1);
			goto START1;
		}
		isReading = true;//���ö��������
		tc.ThreadDone();
		int tmp,i=size;
		unsigned char* pdata=new unsigned char[size];
		while(i>0)
		{
			if(!sizeBefore)//�޿ɶ�����,�ȴ�д��
			{
				if(isRollbacking || isResizing)goto End;
				readNothing = true;
				Sleep(1);
				continue;
			}
			readNothing = false;
			tmp = sizeBefore;
			if(tmp>i)tmp = i;

			if(((readingPosition%Length)+Length)%Length<=tmp)//������Χ
				tmp = Length - ((readingPosition%Length)+Length)%Length;
			i-=tmp;
			memcpy_s(pdata+i,tmp,pData+((readingPosition%Length)+Length)%Length,tmp);

START2:;
			while(isWriting && !writeNothing)Sleep(0);//�ȴ�д�������
			tc.ThreadWait();//���Ĺ�����Ҫͬ������Ϊ��ʱд�����п����ڽ���
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
End:;//������ȡ
		readNothing = false;
		isReading = false;//������ȡ
		if(i)
		{
			memmove_s(pdata,size-i,pdata+i,size-i);
		}
		return XArray<unsigned char>(size-i,pdata);
	}


}
#endif