#pragma once
#include "stdafx.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <Windows.h>
#include "Instance.h"
#include "IEAViewGlobe.h"

namespace EAViewEngine
{

	public ref class EAViewGlobe:public System::Object//,IEAViewGlobe
	{
	public:
		EAViewGlobe(void);		

	private:
		osgViewer::Viewer* _viewer;
		
	};


}