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
#include <osg/Fog>
#include <osg/Program>
#include <osgDB/FileUtils>
#include <osg/Camera>
#include <osg/View>
#include <osg/Switch>
#include <osgGA/GUIEventHandler>
#include <osgga/GUIEventAdapter>
#include <osgga/SphericalManipulator>
#include "Instance.h"
//#include <boost/property_tree/xml_parser.hpp>
#include <osgManipulator/CommandManager>
#include <osgManipulator/TranslateAxisDragger>

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
		osg::Camera* createBirdsEye(const osg::BoundingSphere& bs);
		osg::Texture* createRttTexture(int texWidth,int texHeight);
		osg::Camera* createRttCamera(int texWidth,int texHeight,
			const osg::BoundingSphere& bs);
	};
}
