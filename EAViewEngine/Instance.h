/********************************************************
[DateTime]:2013.9.10
[Author  ]:Mr.Huang
[Email   ]:hsq2013(at)foxmail(dot)com
[Content ]:this class provide some static functions
/********************************************************/
#pragma once
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include "EAHUDLayer.h"
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
		static osg::observer_ptr<osgViewer::Viewer> _eaview;
		static bool _isPause;
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
		/// set viewer's render thread frame pause.
		/// </summary>
		static bool EAViewGlobeSetPause(bool isPause);
		/// <summary>
		/// reconfig viewer's parameters.
		/// </summary>
		static bool ReconfigViewer(Control^ eaViewControl);
		/// <summary>
		/// get the globe viewer.
		/// </summary>
		static osgViewer::Viewer* GetEAViewer();
		/// <summary>
		/// get the window's position and size
		/// </summary>
		static void GetEAWindowRect(int& x,int& y,int& w,int&h);
	};
}
