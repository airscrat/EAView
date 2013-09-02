#pragma once
#include "stdafx.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <Windows.h>
#include "Instance.h"

namespace EAViewEngine
{

	public ref class EAViewGlobe:public System::Object
	{
	public:
		EAViewGlobe(void);		

	private:
		osgViewer::Viewer* _viewer;
		
	};


}