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
	System::Void EAViewGlobeControl::EAViewGlobeControl_SizeChanged(System::Object^  sender, System::EventArgs^  e)
	{
		Instance::EAViewGlobeInit(_window);
	}
}