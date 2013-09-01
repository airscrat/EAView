#include "stdafx.h"
#include "EAViewGlobe.h"
#include <Windows.h>

namespace EAViewEngine
{
	EAViewGlobe::EAViewGlobe(void)
	{	
		_viewer=Instance::GetViewer();
	}
}



