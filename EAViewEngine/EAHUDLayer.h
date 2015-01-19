/********************************************************
[DateTime]:2013.9.10
[Author  ]:Mr.Huang
[Email   ]:hsq2013(at)foxmail(dot)com
[Content ]:set a HUD layer
/********************************************************/
#pragma once
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/Point>
#include <osgText/Text>
#include <osg/ShapeDrawable>
//#include <osg/CameraNode>
#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osgViewer/api/Win32/GraphicsWindowWin32>

#include <iostream>
#include <sstream>
#include <tchar.h>
#include "Instance.h"

using namespace std;

namespace EAViewEngine
{
	public class EAHUDLayer
	{
	public:
		EAHUDLayer();
		bool SetHUDText(const std::string& text);
		//bool UpdateHUDText(const std::string& inText);
	protected:
	private:		
		osgViewer::Viewer* _eaview;
		osg::ref_ptr<osgText::Text> m_text;
		osg::ref_ptr<osg::Geode> CreatePanel();
		bool _valid;
	};
}
