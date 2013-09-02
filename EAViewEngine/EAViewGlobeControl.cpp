/********************************************************
[DateTime]:2013.8.30
[Author  ]:Mr.Huang
[Content ]:The main 3d view control,
		EAViewEngine.cpp : main project file.
/********************************************************/

#include "stdafx.h"
#include "EAViewGlobeControl.h"
#include <OpenThreads\Thread>

namespace EAViewEngine
{
	
	System::Void EAViewGlobeControl::EAViewGlobeControl_Load(System::Object^  sender, System::EventArgs^  e)
	{
		
	}

	void EAViewGlobeControl::RenderThreadProc()
	{
		Instance::EAViewGlobeRun();
	}
}