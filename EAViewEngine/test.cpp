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
	//--------------------------------
	class AttributePrinter:public osg::Drawable::AttributeFunctor
	{
	public:
		typedef osg::Drawable::AttributeType AttributeType;
		inline const char* getTypeName(AttributeType type)
		{
			static const char* typeNames[]=
			{
				"Vertices","Weights","Normals","Colors",
				"Fog Coords","Sencondary Colors","Attribute6","Attribute7",
				"Texture Coords 0","Texture Coords 1","Texture Coords 2",
				"Texture Coordinates 3","Texture Coords 4",
				"Texture Coords 5","Texture Coords 6","Texture Coords 7"
			};
			return typeNames[type];
		}
		template<typename T>
		void printInfo(AttributeType type,unsigned int size,T* front)
		{
			std::cout<<"***"<<getTypeName(type)<<":"<<size<<std::endl;
			for (unsigned int i=0;i<size;++i)
			{
				std::cout<<"("<<*(front+i)<<");";
			}
			std::cout<<std::endl<<std::endl;
		}
		virtual void apply(AttributeType type,unsigned int size,float* front)
		{
			printInfo(type,size,front);
		}
		virtual void apply(AttributeType type,unsigned int size,osg::Vec2* front)
		{
			printInfo(type,size,front);
		}
		virtual void apply(AttributeType type,unsigned int size,osg::Vec3* front)
		{
			printInfo(type,size,front);
		}
		virtual void apply(AttributeType type,unsigned int size,osg::Vec4* front)
		{
			printInfo(type,size,front);
		}
	};
	class TrianglePrinter
	{
	public:
		TrianglePrinter()
		{
			std::cout<<"***Triangles***"<<std::endl;
		}
		void operator()(const osg::Vec3& v1,const osg::Vec3& v2,
			const osg::Vec3& v3,bool)const
		{
			std::cout<<"("<<v1<<");("<<v2<<");("<<v3<<")***"<<std::endl;
		}
	};

	class FindGeomtryVisitor:public osg::NodeVisitor
	{
	public:
		FindGeomtryVisitor():osg::NodeVisitor(TraversalMode::TRAVERSE_ALL_CHILDREN){}
		virtual void apply(osg::Node& node)
		{
			traverse(node);
		}
		virtual void apply(osg::Geode& node)
		{
			for (unsigned int i=0;i<node.getNumDrawables();++i)
			{
				osg::Drawable* drawable=node.getDrawable(i);
				if (!drawable)
				{
					continue;
				}
				std::cout<<"["<<drawable->libraryName()
					<<"::"<<drawable->className()<<"]"<<std::endl;
				AttributePrinter attrPrinter;
				drawable->accept(attrPrinter);
				osg::TriangleFunctor<TrianglePrinter> triPrinter;
				drawable->accept(triPrinter);

				std::cout<<std::endl;
			}
			traverse(node);
		}
	};
	

	//------------------------------------
	test::test(void)
	{
		/*_viewer=Instance::GetEAViewer();

		osg::Node*	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\lz.osgt");

		osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(model);		

		_viewer->setSceneData(root.get());*/

		
		/*_viewer=Instance::GetEAViewer();
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
		_viewer->setSceneData(geode.get());*/

		/*osg::Node* model=osgDB::readNodeFile("cow.osg");
		FindGeomtryVisitor fgv;
		if (model)
		{
			model->accept(fgv);
		}*/

		osg::ref_ptr<osg::DrawPixels> bitmap1=new osg::DrawPixels;
		bitmap1->setPosition(osg::Vec3(0,0,0));
		bitmap1->setImage(osgDB::readImageFile("Images/osg64.png"));

		osg::ref_ptr<osg::DrawPixels> bitmap2=new osg::DrawPixels;
		bitmap2->setPosition(osg::Vec3(80,0,0));
		bitmap2->setImage(osgDB::readImageFile("Images/osg128.png"));

		osg::ref_ptr<osg::DrawPixels> bitmap3=new osg::DrawPixels;
		bitmap3->setPosition(osg::Vec3(200,0,0));
		bitmap3->setImage(osgDB::readImageFile("Images/osg256.png"));
		bitmap3->setSubImageDimensions(64,64,128,128);
		bitmap3->setUseSubImage(true);

		osg::ref_ptr<osg::Geode> geode=new osg::Geode;
		geode->addDrawable(bitmap1.get());
		geode->addDrawable(bitmap2.get());
		geode->addDrawable(bitmap3.get());

		_viewer->setSceneData(geode.get());
	}


	test::~test(void)
	{
	}

}