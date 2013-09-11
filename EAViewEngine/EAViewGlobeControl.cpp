/********************************************************
[DateTime]:2013.8.30
[Author  ]:Mr.Huang
[Content ]:The main 3d view control,
		EAViewEngine.cpp : main project file.
/********************************************************/

#include "stdafx.h"
#include "EAViewGlobeControl.h"


namespace EAViewEngine
{
	
	System::Void EAViewGlobeControl::EAViewGlobeControl_Load(System::Object^  sender, System::EventArgs^  e)
	{
		/*HANDLE hThread1=CreateThread(NULL,0,RenderThreadProc,NULL,0,NULL);
		CloseHandle(hThread1);*/

		_beginthread(RenderThreadStart,0,NULL);
	}

	//渲染的线程，全局函数
	DWORD WINAPI RenderThreadProc(LPVOID lpParameter)
	{
		Instance::EAViewGlobeRun();
		return 0;
	}

	void RenderThreadStart(void*)
	{
		Instance::EAViewGlobeRun();
	}

	
}