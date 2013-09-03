#pragma once
#include "stdafx.h"
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
#include <string>

using namespace System;

namespace EAViewEngine
{
	public class EAViewFuncLib
	{
	public:
		EAViewFuncLib(void);
		~EAViewFuncLib(void);
		///<summary>
		///将托管的String转成std::string
		///<summary>
		static std::string ConvertToString(System::String^ str);
	};
}