#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include "Instance.h"

#pragma once

namespace EAViewEngine
{
	class test
	{
	public:
		test(void);
		~test(void);
	private:
		osgViewer::Viewer* _viewer;
	};
}

