#include <osg/LineWidth>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/io_utils>
#include <osg/TriangleFunctor>
#include <osg/Drawable>
#include <osg/DrawPixels>
#include <osg/Texture1D>
#include <osg/Texture2D>
#include <osg/TextureCubeMap>
#include <osg/TexGen>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include "Instance.h"

#pragma once
#define OSGFilePath "D:/Program Files/OpenSceneGraph/OpenSceneGraph-Data-3.0.0"

namespace EAViewEngine
{
	class test
	{
	public:
		test(void);
		~test(void);
	private:
		osgViewer::Viewer* _viewer;		
		void createTexture1D(osg::StateSet& ss);
		void createTexture2D(osg::StateSet& ss);
		void createTextureCubeMap(osg::StateSet& ss);
		osg::Image* createCustomMipmap(unsigned int resolution);
		osg::Image* createInternalMipmap(unsigned int resolution);
		void createTexture2D(osg::StateSet& ss,bool useCustomizedData);
	};
}

