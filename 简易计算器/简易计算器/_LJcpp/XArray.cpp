#include "stdafx.h"
#ifdef XARRAY_
namespace LJ
{

	//复制方法(针对性强)
	void VArrayCopyMethod(const char* pSource, char* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(char));
	}
	void VArrayCopyMethod(const short* pSource, short* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(short));
	}
	void VArrayCopyMethod(const WCHAR* pSource, WCHAR* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(WCHAR));
	}
	void VArrayCopyMethod(const int* pSource, int* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(int));
	}
	void VArrayCopyMethod(const long* pSource, long* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(long));
	}
	void VArrayCopyMethod(const long long* pSource, long long* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(long long));
	}
	void VArrayCopyMethod(const unsigned char* pSource, unsigned char* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(unsigned char));
	}
	void VArrayCopyMethod(const unsigned short* pSource, unsigned short* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(unsigned short));
	}
	void VArrayCopyMethod(const unsigned int* pSource, unsigned int* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(unsigned int));
	}
	void VArrayCopyMethod(const unsigned long* pSource, unsigned long* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(unsigned long));
	}
	void VArrayCopyMethod(const unsigned long long* pSource, unsigned long long* pDestination, unsigned long size)
	{
		XBase::Memory::Copy(pDestination,pSource,size*sizeof(unsigned long long));
	}
	void VArrayDefaultConstructMethod(char*,unsigned long){}
	void VArrayDefaultConstructMethod(signed char*,unsigned long){}
	void VArrayDefaultConstructMethod(unsigned char*,unsigned long){}
	void VArrayDefaultConstructMethod(short*,unsigned long){}
	void VArrayDefaultConstructMethod(unsigned short*,unsigned long){}
	void VArrayDefaultConstructMethod(int*,unsigned long){}
	void VArrayDefaultConstructMethod(unsigned int*,unsigned long){}
	void VArrayDefaultConstructMethod(long*,unsigned long){}
	void VArrayDefaultConstructMethod(unsigned long*,unsigned long){}
	void VArrayDefaultConstructMethod(long long*,unsigned long){}
	void VArrayDefaultConstructMethod(unsigned long long*,unsigned long){}
	void VArrayDeconstructMethod(char*,unsigned long){}
	void VArrayDeconstructMethod(signed char*,unsigned long){}
	void VArrayDeconstructMethod(unsigned char*,unsigned long){}
	void VArrayDeconstructMethod(short*,unsigned long){}
	void VArrayDeconstructMethod(unsigned short*,unsigned long){}
	void VArrayDeconstructMethod(int*,unsigned long){}
	void VArrayDeconstructMethod(unsigned int*,unsigned long){}
	void VArrayDeconstructMethod(long*,unsigned long){}
	void VArrayDeconstructMethod(unsigned long*,unsigned long){}
	void VArrayDeconstructMethod(long long*,unsigned long){}
	void VArrayDeconstructMethod(unsigned long long*,unsigned long){}

}
#endif