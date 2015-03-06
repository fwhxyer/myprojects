#include "stdafx.h"//由W意波(LuoJun)编写
#ifdef THREADCONTROL_
#pragma comment(lib,"user32.lib")
namespace LJ
{
	DWORD APIStartThread(void (*fun)(void*),void* pragma,HANDLE* pHandle)
	{
		DWORD dwThreadId;
		HANDLE h=::CreateThread(
    NULL,//NULL,使用默认安全性
    NULL,//NULL,使用与调用该函数的线程相同的栈空间大小
	//Thread1,//指定新线程的入口函数名(DWORD WINAPI 声明方法)
    (LPTHREAD_START_ROUTINE)fun,//指定新线程的入口函数名(void 声明方法)
    pragma,//向新线程传递的参数，不需要传递时设为NULL
    0,//表示新线程立即开始执行
    &dwThreadId);//保存新线程的ID
		if(pHandle)
			*pHandle = h;
		else if(h)CloseHandle(h);
		return dwThreadId;
	}

	//ThreadControl
	void ThreadControl::ThreadWait()//在进入临界区前总是等待其他线程
	{
		EnterCriticalSection(&cs);
	}
	bool ThreadControl::ThreadTry()//尝试进入临界区并立即返回，成功返回true
	{
		return TryEnterCriticalSection(&cs)!=0;
	}
	void ThreadControl::ThreadDone()//线程操作完毕，出临界区
	{
		LeaveCriticalSection(&cs);
	}

	ThreadControl::ThreadControl()//默认构造函数
		{InitializeCriticalSection(&cs);}
	ThreadControl::~ThreadControl()
	{
		DeleteCriticalSection(&cs);
	}
	bool ThreadControl::IsThreadAlive(DWORD id)//检测某线程是否存活
	{
		DWORD ExitCode;
		HANDLE hd = OpenThread(THREAD_QUERY_INFORMATION,FALSE,id);//打开线程以检验线程是否已结束
		if(hd && GetExitCodeThread(hd,&ExitCode))
		{
			if( ExitCode == STILL_ACTIVE)//线程仍在运行
			{
				CloseHandle(hd);
				return true;
			}
		}
		if(hd)CloseHandle(hd);//线程已终止
		return false;
	}
	void ThreadControl::ThreadReset()//重置线程参数
	{
		DeleteCriticalSection(&cs);
		InitializeCriticalSection(&cs);
	}
	//获取当前线程id
	DWORD ThreadControl::GetThreadID()
	{
		return (DWORD)cs.OwningThread;
	}
	int ThreadControl::GetThreadDeep()
	{
		return cs.LockCount;
	}

}
#endif