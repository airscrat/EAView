#include "StdAfx.h"
#include "test.h"

namespace EAViewEngine
{
	class DynamicLineCallback:public osg::Drawable::UpdateCallback
	{
	public:
		DynamicLineCallback():_angle(0){}
		virtual void update(osg::NodeVisitor* nv,osg::Drawable* drawable)
		{
			osg::Geometry* geom=dynamic_cast<osg::Geometry*>(drawable);
			if (!geom)return;
			osg::Vec3Array* vertices=
				dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
			if (vertices)
			{
				for (osg::Vec3Array::iterator itr=vertices->begin();
					itr!=vertices->end()-1;++itr)
				{
					itr->set(*(itr+1));//for what?
				}
				_angle+=0.1;
				osg::Vec3& pt=vertices->back();
				pt.set(10*cos(_angle),0,10*sin(_angle));
				vertices->dirty();
			}
		}
	protected:
		float _angle;
	};




	//------------------------------------
	test::test(void)
	{
		/*_viewer=Instance::GetEAViewer();

		osg::Node*	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\lz.osgt");

		osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(model);		

		_viewer->setSceneData(root.get());*/


		_viewer=Instance::GetEAViewer();
		osg::ref_ptr<osg::Vec3Array> vertices=new osg::Vec3Array(10);
		for (unsigned int i=0;i<10;++i)
		{
			(*vertices)[i].set(float(i),0,0);
		}
		osg::ref_ptr<osg::Geometry> lineGeom=new osg::Geometry;
		lineGeom->setVertexArray(vertices.get());
		lineGeom->addPrimitiveSet(
			new osg::DrawArrays(osg::DrawArrays::LINE_STRIP,0,10));
		lineGeom->setInitialBound(osg::BoundingBox(osg::Vec3(-10,-10,-10),
			osg::Vec3(10,10,10)));
		lineGeom->setUpdateCallback(new DynamicLineCallback);
		lineGeom->setUseDisplayList(false);
		lineGeom->setUseVertexBufferObjects(true);

		osg::ref_ptr<osg::Geode> geode=new osg::Geode;
		geode->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		geode->getOrCreateStateSet()->setAttribute(new osg::LineWidth(2));
		geode->addDrawable(lineGeom.get());
		_viewer->setSceneData(geode.get());
	}


	test::~test(void)
	{
	}

}