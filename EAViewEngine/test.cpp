#include "StdAfx.h"
#include "test.h"
#include "boost/lexical_cast.hpp"
#include "boost/format.hpp"
#include "boost/smart_ptr.hpp"

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

	void test::createTexture1D(osg::StateSet& ss)
	{
		osg::ref_ptr<osg::Image> image=new osg::Image;
		image->setImage(256,1,1,GL_RGBA,GL_RGBA,GL_UNSIGNED_BYTE,
			new unsigned char[4*256],osg::Image::USE_NEW_DELETE);
		unsigned char* ptr=image->data();
		for (unsigned int i=0;i<256;++i)
		{
			*ptr++=i;
			*ptr++=i;
			*ptr++=255;
			*ptr++=255;
		}
		osg::ref_ptr<osg::Texture1D> texture=new osg::Texture1D;
		texture->setImage(image.get());
		texture->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
		texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
		ss.setTextureAttributeAndModes(0,texture.get());
	}
	
	void test::createTexture2D(osg::StateSet& ss)
	{
		osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D;
		texture->setImage(osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Images/clockface.jpg")));
		texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
		texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
		texture->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP_TO_BORDER);
		texture->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP_TO_BORDER);
		texture->setBorderColor(osg::Vec4(1,1,0,1));
		ss.setTextureAttributeAndModes(0,texture.get());
	}

	void test::createTextureCubeMap(osg::StateSet& ss)
	{
		osg::ref_ptr<osg::TextureCubeMap> texture=new osg::TextureCubeMap;
		texture->setImage(osg::TextureCubeMap::POSITIVE_X,
			osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Cubemap_snow/posx.jpg")));
		texture->setImage(osg::TextureCubeMap::NEGATIVE_X,
			osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Cubemap_snow/negx.jpg")));
		texture->setImage(osg::TextureCubeMap::POSITIVE_Y,
			osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Cubemap_snow/posy.jpg")));
		texture->setImage(osg::TextureCubeMap::NEGATIVE_Y,
			osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Cubemap_snow/negy.jpg")));
		texture->setImage(osg::TextureCubeMap::POSITIVE_Z,
			osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Cubemap_snow/posz.jpg")));
		texture->setImage(osg::TextureCubeMap::NEGATIVE_Z,
			osgDB::readImageFile(std::string(OSGFilePath)+std::string("/Cubemap_snow/negz.jpg")));
		texture->setWrap(osg::Texture::WRAP_S,
			osg::Texture::CLAMP_TO_EDGE);
		texture->setWrap(osg::Texture::WRAP_T,
			osg::Texture::CLAMP_TO_EDGE);
		texture->setWrap(osg::Texture::WRAP_R,
			osg::Texture::CLAMP_TO_EDGE);
		texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR);
		texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
		ss.setTextureAttributeAndModes(0,texture.get());
		ss.setTextureAttributeAndModes(0,new osg::TexGen);
	}

	osg::Image* test::createCustomMipmap(unsigned int resolution)
	{
		unsigned int totalSize=0;
		unsigned int res=resolution;
		osg::Image::MipmapDataType mipmapData;
		for(unsigned int i=0;res>0;res>>=1,++i)
		{
			if (i>0)
			{
				mipmapData.push_back(totalSize);
			}
			totalSize+=res*res*4;
		}
		osg::ref_ptr<osg::Image> image=new osg::Image;
		image->setImage(resolution,resolution,1,GL_RGBA,GL_RGBA,
			GL_UNSIGNED_BYTE,
			new unsigned char[totalSize],
			osg::Image::USE_NEW_DELETE);
		image->setMipmapLevels(mipmapData);
		unsigned char* ptr=image->data();
		res=resolution;
		for(unsigned int i=0;res>0;res>>=1,++i)
		{
			for (unsigned int s=0;s<res;++s)
			{
				for (unsigned int t=0;t<res;++t)
				{
					unsigned char color=(((s&0x4)==0)^((t&0x4)==0))*255;
					*ptr++=color;*ptr++=color;*ptr++=color;
					*ptr++=255;
				}
			}
		}
		return image.release();
	}

	osg::Image* test::createInternalMipmap(unsigned int resolution)
	{
		unsigned int totalSize=resolution*resolution*4;
		osg::ref_ptr<osg::Image> image=new osg::Image;
		image->setImage(resolution,resolution,1,GL_RGBA,GL_RGBA,
			GL_UNSIGNED_BYTE,
			new unsigned char[totalSize],
			osg::Image::USE_NEW_DELETE);
		unsigned char* ptr=image->data();
		for (unsigned int s=0;s<resolution;++s)
		{
			for (unsigned int t=0;t<resolution;++t)
			{
				unsigned char color=(((s&0x4)==0)^((t&0x4)==0))*255;
				*ptr++=color;*ptr++=color;*ptr++=color;
				*ptr++=255;
			}
		}
		return image.release();
	}

	void test::createTexture2D(osg::StateSet& ss,bool useCustomizedData)
	{
		osg::ref_ptr<osg::Texture2D> texture=new osg::Texture2D;
		if (useCustomizedData)
		{
			texture->setImage(createCustomMipmap(32));
		}else
		{
			texture->setImage(createInternalMipmap(32));
		}
		texture->setFilter(osg::Texture::MIN_FILTER,
			osg::Texture::LINEAR_MIPMAP_LINEAR);
		texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
		texture->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT);
		texture->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT);
		ss.setTextureAttributeAndModes(0,texture.get());
	}
	//----------雾效果--------------------
	class FogCallback:public osg::StateSet::Callback
	{
	public:
		virtual void operator()(osg::StateSet* ss,osg::NodeVisitor* nv)
		{
			if (!ss)
			{
				return;
			}
			osg::Fog* fog=dynamic_cast<osg::Fog*>(
				ss->getAttribute(osg::StateAttribute::FOG));
			if (fog)
			{
				float start=fog->getStart();
				if (start<fog->getEnd()-5.0)
				{
					fog->setStart(start+5.0);
				}
			}
		}
	protected:
	private:
	};
	//-------在场景中使用GLSL---------
	static const char* vertSource={
		"varying vec3 normal;\n"
		"void main()\n"
		"{\n"
		"   normal=normalize(gl_NormalMatrix* gl_Normal);\n"
		"   gl_Position=ftransform();\n"
		"}\n"
	};
	static const char* fragSource={
		"uniform vec4 mainColor;\n"
		"varying vec3 normal;\n"
		"void main()\n"
		"{\n"
		"   float intensity=dot(vec3(gl_LightSource[0].position),normal);\n"
		"   if(intensity>0.95)gl_FragColor=mainColor;\n"
		"   else if(intensity>0.5)gl_FragColor=vec4(0.6,0.3,0.3,1.0);\n"
		"   else if(intensity>0.25)gl_FragColor=vec4(0.4,0.2,0.2,1.0);\n"
		"   else gl_FragColor=vec4(0.2,0.1,0.1,1.0);\n"
		"}\n"
	};
	class ColorCallback:public osg::Uniform::Callback
	{
	public:
		ColorCallback():_incRed(false){}
		virtual void operator()(osg::Uniform* uniform,osg::NodeVisitor* nv)
		{
			if (!uniform)
			{
				return;
			}
			osg::Vec4 color;
			uniform->get(color);
			if (_incRed==true)
			{
				if (color.x()<1)
				{
					color.x()+=0.01;
				}else
				{
					_incRed=false;
				}
			}else
			{
				if (color.x()>0)
				{
					color.x()-=0.01;
				}else
				{
					_incRed=true;
				}
			}
			uniform->set(color);
		}
	protected:
		bool _incRed;
	};
	void createShaders(osg::StateSet& ss)
	{
		osg::ref_ptr<osg::Shader> verShader=
			new osg::Shader(osg::Shader::VERTEX,vertSource);
		osg::ref_ptr<osg::Shader> fragShader=
			new osg::Shader(osg::Shader::FRAGMENT,fragSource);

		osg::ref_ptr<osg::Program> program=new osg::Program;
		program->addShader(verShader.get());
		program->addShader(fragShader.get());

		osg::ref_ptr<osg::Uniform> mainColor=
			new osg::Uniform("mainColor",osg::Vec4(1,0.5,0.5,1));
		mainColor->setUpdateCallback(new ColorCallback);

		ss.addUniform(mainColor.get());
		ss.setAttributeAndModes(program.get());
	}
	static void LoadShaderSource(osg::Shader* shader,const std::string& fileName)
	{
		std::string fqFileName=osgDB::findDataFile(fileName);
		if (fqFileName.length()!=0)
		{
			shader->loadShaderSourceFromFile(fqFileName.c_str());
		}
		else
		{
			osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
		}
	}
	//--------------------------------
	test::test(void)
	{
		/*_viewer=Instance::GetEAViewer();

		osg::Node*	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\tests\\boston_buildings.earth");

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

		/*osg::ref_ptr<osg::DrawPixels> bitmap1=new osg::DrawPixels;
		bitmap1->setPosition(osg::Vec3(0,0,0));
		bitmap1->setImage(osgDB::readImageFile("D:\\Program Files\\OpenSceneGraph\\data\\Images\\osg64.png"));

		osg::ref_ptr<osg::DrawPixels> bitmap2=new osg::DrawPixels;
		bitmap2->setPosition(osg::Vec3(80,0,0));
		bitmap2->setImage(osgDB::readImageFile("D:\\Program Files\\OpenSceneGraph\\data\\Images\\osg128.png"));

		osg::ref_ptr<osg::DrawPixels> bitmap3=new osg::DrawPixels;
		bitmap3->setPosition(osg::Vec3(200,0,0));
		bitmap3->setImage(osgDB::readImageFile("D:\\Program Files\\OpenSceneGraph\\data\\Images\\osg256.png"));
		bitmap3->setSubImageDimensions(64,64,128,128);
		bitmap3->setUseSubImage(true);

		osg::ref_ptr<osg::Geode> geode=new osg::Geode;
		geode->addDrawable(bitmap1.get());
		geode->addDrawable(bitmap2.get());
		geode->addDrawable(bitmap3.get());

		_viewer=Instance::GetEAViewer();
		_viewer->setSceneData(geode.get());*/

		/*osg::ref_ptr<osg::Geode> quad1=new osg::Geode;
		quad1->addDrawable(osg::createTexturedQuadGeometry(
		osg::Vec3(-3,0,-0.5),osg::Vec3(1,0,0),
		osg::Vec3(0,0,1),0,0,2,1));
		createTexture1D(*(quad1->getOrCreateStateSet()));

		osg::ref_ptr<osg::Geode> quad2=new osg::Geode;
		quad2->addDrawable(osg::createTexturedQuadGeometry(
		osg::Vec3(-0.5,0,-0.5),osg::Vec3(1,0,0),
		osg::Vec3(0,0,1),-0.1,-0.1,1.1,1.1));
		createTexture2D(*(quad2->getOrCreateStateSet()));

		osg::ref_ptr<osg::Geode> box=new osg::Geode;
		box->addDrawable(new osg::ShapeDrawable(
		new osg::Box(osg::Vec3(3,0,0),1)));
		createTextureCubeMap(*(box->getOrCreateStateSet()));

		osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(quad1.get());
		root->addChild(quad2.get());
		root->addChild(box.get());*/

		/*osg::ref_ptr<osg::Geode> quad1=new osg::Geode;
		quad1->addDrawable(osg::createTexturedQuadGeometry(
			osg::Vec3(0,0,0),osg::Vec3(1,0,0),
			osg::Vec3(0,0,1)));
		createTexture2D(*(quad1->getOrCreateStateSet()),true);
		osg::ref_ptr<osg::Geode> quad2=new osg::Geode;
		quad2->addDrawable(osg::createTexturedQuadGeometry(
			osg::Vec3(2,0,0),osg::Vec3(1,0,0),
			osg::Vec3(0,0,1)));
		createTexture2D(*(quad2->getOrCreateStateSet()),false);
		osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(quad1.get());
		root->addChild(quad2.get());*/

		/*osg::Node* model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\OpenSceneGraph-Data-3.0.0\\lz.osg");
		osg::ref_ptr<osg::Fog> fog=new osg::Fog;
		fog->setMode(osg::Fog::Mode::LINEAR);
		fog->setColor(osg::Vec4(1,1,1,1));
		fog->setStart(1);
		fog->setEnd(2000);
		osg::StateSet* ss=model->getOrCreateStateSet();
		ss->setAttributeAndModes(fog.get());
		ss->setUpdateCallback(new FogCallback);*/

		

		osg::Node* model=osgDB::readNodeFile("cow.osg");
		createShaders(*(model->getOrCreateStateSet()));

		_viewer=Instance::GetEAViewer();
		_viewer->setSceneData(model);
	}


	test::~test(void)
	{
	}

}