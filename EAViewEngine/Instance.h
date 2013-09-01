
#pragma once
#include "stdafx.h"
#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/View>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Node>
#include <osg/io_utils>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osg/Camera>
#include <osg/NodeCallback>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Notify>
#include <osg/AutoTransform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/Switch>
#include <osg/ProxyNode>
#include <osg/Texture2D>
#include <osgUtil/SmoothingVisitor>
#include <osg/Geometry>
#include <osg/Geode>
#include <Windows.h>

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
		static bool EAViewGlobeInit(Control^ eaViewControl);
		static bool ReconfigViewer(Control^ eaViewControl);
		static osgViewer::Viewer* GetViewer();
	};
}
