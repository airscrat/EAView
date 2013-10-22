#include "StdAfx.h"
#include "EAViewFuncLib.h"

namespace EAViewEngine
{
	EAViewFuncLib::EAViewFuncLib(void)
	{
	}


	EAViewFuncLib::~EAViewFuncLib(void)
	{
	}

	std::string EAViewFuncLib::ConvertToString(System::String^ str)
	{
		int q=(int)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
		char* p=(char*)q;
		return std::string(p);
	}

}