#pragma once
#define VBUFFER_
#include "XArray.h"

namespace LJ
{
	//�����,�ṩ����д��ͬ��
	class VBuffer:public VArray<unsigned char>
	{
		//�߳�ͬ������
		ThreadControl tc;
		//��ֹ���ƹ���
		VBuffer(const VBuffer&){}
		//��ֹ��ֵ����
		void operator=(const VBuffer&){}
	protected:
		//���µĶ�ȡ��λ�ã�%Length�͵õ������ȡλ�ã�
		long long readingPosition;
		//���µ�д���λ�ã�%Length�͵õ�����д��λ�ã�
		long long writingPosition;
		//��ǰ��ȡ�ռ䣨��Զ�ȡλ�ö��ԣ�
		unsigned int sizeBefore;
		//Ԥ����ǰ��ȡ�ռ䣬Ĭ��Ϊ����Bufferʹ�Ĵ�С��1/4
		unsigned int sizeBeforeMinimum;
		//����ȡ�ռ䣨��Զ�ȡλ�ö��ԣ�
		unsigned int sizeAfter;
		//�Ƿ����ڶ�ȡ����Ҫͬ����������Ҫ����ͣ������С�����˲���
		bool isReading;
		//�Ƿ�����д�룬д�����Ҫ����ͣ������С�����˲���
		bool isWriting;
		//���������������ݿɶ�����
		bool readNothing;
		//д�������������ݿ�д����
		bool writeNothing;
		//�Ƿ����ڵ�����С��������С����Ҫ����ͣ��������
		bool isResizing;
		//�Ƿ����ڻ��ˣ����˹���Ҫ����ͣ��д����
		bool isRollbacking;
	public:
		//Ĭ�ϻ����С
		static unsigned int DefaultSize;
		//����һ����СΪsize�ֽڵĻ����
		VBuffer(unsigned int size=DefaultSize);
		//����������
		virtual ~VBuffer();
		//���ó������С��Ĳ���
		virtual void Reset();
		//����������С���ֽڣ�
		virtual unsigned int Resize(unsigned int size);
		//����������С���ֽڣ�
		virtual unsigned int ResizeAndDestroy(unsigned int size);
		//����Ԥ���ĺ��˿ռ䣬���ܳ����ܿռ��һ�룬������Сʱ�������ܿռ����֮һ��������
		void SetMinimumSizeBefore(unsigned int);
		//��ȡ�ɶ�ȡ�ֽ���
		unsigned int GetReadable()const;
		//��ȡ��д���ֽ���
		unsigned int GetWriteable()const;
		//��λ�û���,����ʵ�ʻ��˵��ֽ���
		unsigned int Rollback(unsigned);
		//��λ��ǰ��,����ʵ��ǰ�����ֽ���
		unsigned int Skip(unsigned);
		//����ȡһ���ֽ��������ݣ��ɹ���ȡʱ����ȡλ�ý���֮���ƣ����ݲ���ʱ��һֱ�ȴ�
		XArray<unsigned char> GetAfter(unsigned int );
		//��ǰ��ȡһ���ֽ��������ݣ��ɹ���ȡʱ����ȡλ�ý���֮ǰ�ƣ����ݲ���ʱ��һֱ�ȴ�
		XArray<unsigned char> GetBefore(unsigned int );
		//���д��һ�����ݣ����޷�д����һֱ�ȴ�������ʵ��д������
		template<typename T>unsigned int PutAfter(const XArray<T>&);
		//��ǰд��һ�����ݣ����޷�д����һֱ�ȴ�
		template<typename T>unsigned int PutBefore(const XArray<T>&);
	};
	//���д��һ�����ݣ����޷�д����һֱ�ȴ�
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
		isWriting = true;//����д�������
		tc.ThreadDone();
		int tmp,i=0;
		while(i<size)
		{
			tc.ThreadWait();
			if(sizeBeforeMinimum+sizeAfter>=(unsigned int)Length && sizeBefore+sizeAfter>=(unsigned int)Length)//�޿�д����,�ȴ���ȡ
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

			if(((writingPosition%Length)+Length)%Length+tmp>=Length)//������Χ
				tmp = Length - ((writingPosition%Length)+Length)%Length;
START2:;
			tc.ThreadWait();//��ȡ������Ҫͬ������Ϊ��ʱ�������п��ܶ����ݸĶ�
			if(isReading && !readNothing)//�ȴ����������
			{
				tc.ThreadDone();
				Sleep(0);
				goto START2;
			}
			if(sizeBefore+tmp+sizeAfter>(unsigned int)Length)sizeBefore -= tmp;//���д��ǰ�ȼ��ٿ���ǰ��ȡ����
			tc.ThreadDone();

			XBase::Memory::Copy(pData+((writingPosition%Length)+Length)%Length,((const unsigned char*)(const void*)xArray)+i,tmp);
			i+=tmp;

START3:
			writeNothing = true;
			tc.ThreadWait();//���Ĺ�����Ҫͬ������Ϊ��ʱд�����п����ڽ���
			if(isReading && !readNothing)//�ȴ����������
			{
				tc.ThreadDone();
				Sleep(0);
				goto START3;
			}
			writingPosition += tmp;
			sizeAfter += tmp;
			tc.ThreadDone();
		}
End:;//������ȡ
		writeNothing = false;
		isWriting = false;//������ȡ
		return i;
	}
	//��ǰд��һ�����ݣ����޷�д����һֱ�ȴ�
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
		isWriting = true;//����д�������
		tc.ThreadDone();
		int tmp,i=size;
		while(i>0)
		{
			tc.ThreadWait();
			if(sizeBeforeMinimum+sizeBefore>=Length && sizeBefore+sizeAfter>=Length)//�޿�д����,�ȴ���ȡ
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

			if(((writingPosition%Length)+Length)%Length<tmp)//������Χ
				tmp = ((writingPosition%Length)+Length)%Length;

START2:;
			tc.ThreadWait();//��ȡ������Ҫͬ������Ϊ��ʱ�������п��ܶ����ݸĶ�
			if(isReading && !readNothing)//�ȴ����������
			{
				tc.ThreadDone();
				Sleep(0);
				goto START2;
			}
			if(sizeBefore+tmp+sizeAfter>Length)sizeAfter -= tmp;//��ǰд��ǰ�ȼ��ٿ�����ȡ����
			tc.ThreadDone();

			i-=tmp;
			memcpy_s(pData+((writingPosition%Length)+Length)%Length,tmp,((const unsigned char*)xArray)+i,tmp);

START3:;
			tc.ThreadWait();//���Ĺ�����Ҫͬ������Ϊ��ʱд�����п����ڽ���
			if(isReading && !readNothing)//�ȴ����������
			{
				tc.ThreadDone();
				Sleep(0);
				goto START3;
			}
			writingPosition -= tmp;
			sizeBefore += tmp;
			tc.ThreadDone();
		}
End:;//������ȡ
		writeNothing = false;
		isWriting = false;//������ȡ
		return size-i;
	}

}