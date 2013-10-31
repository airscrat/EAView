#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/io_utils>
#include <osg/TriangleFunctor>
#include <osg/Drawable>
#include <osg/DrawPixels>
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

