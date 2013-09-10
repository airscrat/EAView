/********************************************************
[DateTime]:2013.8.30
[Author  ]:Mr.Huang
[Content ]:this class provide some static functions
/********************************************************/
#pragma once
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osg/PositionAttitudeTransform>


using namespace System::Windows::Forms;

namespace EAViewEngine
{
	//all of members and functions in this class is static
	public class Instance
	{
	private:
		/// <summary>
		/// this member is private,we can call GetViewer() to get it's pointer*/
		/// <summary>
		static osg::observer_ptr<osgViewer::Viewer> _viewer;
	public:
		Instance(void);
		~Instance(void);
		/// <summary>
		/// init viewer on a control in .net
		/// </summary>
		static bool EAViewGlobeInit(Control^ eaViewControl);
		/// <summary>
		/// terminate viewer's render thread.
		/// </summary>
		static bool EAViewGlobeTerminate();
		/// <summary>
		/// start viewer's render thread.
		/// </summary>
		static int EAViewGlobeRun();
		/// <summary>
		/// reconfig viewer's parameters.
		/// </summary>
		static bool ReconfigViewer(Control^ eaViewControl);
		/// <summary>
		/// get the globe viewer.
		/// </summary>
		static osgViewer::Viewer* GetViewer();		
	};
}
