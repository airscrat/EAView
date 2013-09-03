#pragma once
#include "stdafx.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <Windows.h>
#include "Instance.h"
#include "IEAViewGlobe.h"
#include "EAViewFuncLib.h"

namespace EAViewEngine
{

	public ref class EAViewGlobe:public System::Object//,IEAViewGlobe
	{
	public:
		EAViewGlobe(void);		
		void LoadOSGModel(System::String^ file);//string file);
	private:
		osgViewer::Viewer* _viewer;
		
	};


}