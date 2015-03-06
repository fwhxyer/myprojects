#include "stdafx.h"//��W�Ⲩ(LuoJun)��д
#ifdef THREADCONTROL_
#pragma comment(lib,"user32.lib")
namespace LJ
{
	DWORD APIStartThread(void (*fun)(void*),void* pragma,HANDLE* pHandle)
	{
		DWORD dwThreadId;
		HANDLE h=::CreateThread(
    NULL,//NULL,ʹ��Ĭ�ϰ�ȫ��
    NULL,//NULL,ʹ������øú������߳���ͬ��ջ�ռ��С
	//Thread1,//ָ�����̵߳���ں�����(DWORD WINAPI ��������)
    (LPTHREAD_START_ROUTINE)fun,//ָ�����̵߳���ں�����(void ��������)
    pragma,//�����̴߳��ݵĲ���������Ҫ����ʱ��ΪNULL
    0,//��ʾ���߳�������ʼִ��
    &dwThreadId);//�������̵߳�ID
		if(pHandle)
			*pHandle = h;
		else if(h)CloseHandle(h);
		return dwThreadId;
	}

	//ThreadControl
	void ThreadControl::ThreadWait()//�ڽ����ٽ���ǰ���ǵȴ������߳�
	{
		EnterCriticalSection(&cs);
	}
	bool ThreadControl::ThreadTry()//���Խ����ٽ������������أ��ɹ�����true
	{
		return TryEnterCriticalSection(&cs)!=0;
	}
	void ThreadControl::ThreadDone()//�̲߳�����ϣ����ٽ���
	{
		LeaveCriticalSection(&cs);
	}

	ThreadControl::ThreadControl()//Ĭ�Ϲ��캯��
		{InitializeCriticalSection(&cs);}
	ThreadControl::~ThreadControl()
	{
		DeleteCriticalSection(&cs);
	}
	bool ThreadControl::IsThreadAlive(DWORD id)//���ĳ�߳��Ƿ���
	{
		DWORD ExitCode;
		HANDLE hd = OpenThread(THREAD_QUERY_INFORMATION,FALSE,id);//���߳��Լ����߳��Ƿ��ѽ���
		if(hd && GetExitCodeThread(hd,&ExitCode))
		{
			if( ExitCode == STILL_ACTIVE)//�߳���������
			{
				CloseHandle(hd);
				return true;
			}
		}
		if(hd)CloseHandle(hd);//�߳�����ֹ
		return false;
	}
	void ThreadControl::ThreadReset()//�����̲߳���
	{
		DeleteCriticalSection(&cs);
		InitializeCriticalSection(&cs);
	}
	//��ȡ��ǰ�߳�id
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