// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//DisableThreadLibraryCalls(hModule);
		//CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)初始化, NULL, 0, NULL));
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)初始化, NULL, 0, NULL);
		
		初始化();  //用ce注入不能创建线程,否则闪退
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}



