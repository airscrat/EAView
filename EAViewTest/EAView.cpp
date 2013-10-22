// EAView.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "vld.h"
#include <osgDB\ReadFile>
#include <osgViewer\Viewer>
#include <iostream>
#include <osg/Node>
#include <osg/io_utils>
#include <osg/PositionAttitudeTransform>

#include <osgGA/TrackballManipulator>
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

class GeodeParent
{
public:	
	GeodeParent(){}
	void SetGeode(osg::Geode * geode){_geode=geode;}
	osg::Geode * GetGeode(){return _geode.get();}
protected:
	osg::ref_ptr<osg::Geode> _geode;
};

class InfoVisitor:public osg::NodeVisitor
{

public:
	InfoVisitor():osg::NodeVisitor(TRAVERSE_ALL_CHILDREN),_indent(0){}
	virtual void apply(osg::Node& node)
	{
		for(int i=0;i<_indent;++i)
			std::cout<<"   ";
		std::cout<<"["<<_indent+1<<"]"<<node.libraryName()
			<<"::"<<node.className()<<std::endl;
		_indent++;
		traverse(node);
		_indent--;
	}

	virtual void apply(osg::Geode& node)
	{
		for (int i=0;i<_indent;++i)
		{
			std::cout<<"  ";
		}
		std::cout<<"["<<_indent+1<<"]"<<node.libraryName()
			<<"::"<<node.className()<<std::endl;
		for (unsigned int n=0;n<node.getNumDrawables();++n)
		{
			osg::Drawable *drawable=node.getDrawable(n);
			if(!drawable)continue;
			for (int i=0;i<_indent;++i)
			{
				for (int i=0;i<_indent;++i)
				{
					std::cout<<"  ";
				}
				std::cout<<drawable->libraryName()<<"::"
					<<drawable->className()<<std::endl;
			}
			_indent++;
			traverse(node);
			_indent--;
		}
	
	}

protected:
	int _indent;
};

class RotateCallback:public osg::NodeCallback
{
public:
	RotateCallback():_rotateZ(0){}
	virtual void operator()(osg::Node* node,osg::NodeVisitor* nv)
	{
		osg::PositionAttitudeTransform* pat=dynamic_cast<osg::PositionAttitudeTransform*>(node);
		if(pat)
		{
			osg::Quat quat(osg::DegreesToRadians(_rotateZ),osg::Z_AXIS);
			pat->setAttitude(quat);
			_rotateZ+=1.0;
		}
		traverse(node,nv); 
	}
protected:
	double _rotateZ;
};

class InfoCallback:public osg::NodeCallback
{
public:
	virtual void operator()(osg::Node* node,osg::NodeVisitor* nv)
	{
		osg::PositionAttitudeTransform* pat=
			dynamic_cast<osg::PositionAttitudeTransform*>(node);
		if(pat)
		{
			double angle=0.0;
			osg::Vec3 axis;
			pat->getAttitude().getRotate(angle,axis);
			std::cout<<"Node is rotation around the("
				<<axis<<")axis,"
				<<osg::RadiansToDegrees(angle)
				<<"degrees"<<std::endl;
			traverse(node,nv);

		}
	}
};

// Derive a class from NodeCallback to manipulate a
//   MatrixTransform object's matrix.
class RotateCB : public osg::NodeCallback
{
public:
	RotateCB() : _angle( 0. ) {}

	virtual void operator()( osg::Node* node,
		osg::NodeVisitor* nv )
	{
		// Normally, check to make sure we have an update
		//   visitor, not necessary in this simple example.
		osg::MatrixTransform* mtLeft =
			dynamic_cast<osg::MatrixTransform*>( node );
		osg::Matrix mR, mT;
		mT.makeTranslate( -6., 0., 0. );
		mR.makeRotate( _angle, osg::Vec3( 0., 0., 1. ) );
		mtLeft->setMatrix( mR * mT );

		// Increment the angle for the next from.
		_angle += 0.01;

		// Continue traversing so that OSG can process
		//   any other nodes with callbacks.
		traverse( node, nv );
	}

protected:
	double _angle;
};

// Create the scene graph. This is a Group root node with two
//   MatrixTransform children, which multiply parent a single
//   Geode loaded from the cow.osg model file.
osg::ref_ptr<osg::Node>	createScene()
{
	// Load the cow model.
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile( "D:\\Program Files\\OpenSceneGraph\\data\\cow.osgt" );
	if (!cow.valid())
	{
		osg::notify( osg::FATAL ) << "Unable to load data file. Exiting." << std::endl;
		return NULL;
	}
	// Data variance is STATIC because we won't modify it.
	cow->setDataVariance( osg::Object::STATIC );

	// Create a MatrixTransform to display the cow on the left.
	osg::ref_ptr<osg::MatrixTransform> mtLeft =
		new osg::MatrixTransform;
	mtLeft->setName( "Left Cow\nDYNAMIC" );
	// Set data variance to DYNAMIC to let OSG know that we
	//   will modify this node during the update traversal.
	mtLeft->setDataVariance( osg::Object::DYNAMIC );
	// Set the update callback.
	mtLeft->setUpdateCallback( new RotateCB );
	osg::Matrix m;
	m.makeTranslate( -6.f, 0.f, 0.f );
	mtLeft->setMatrix( m );
	mtLeft->addChild( cow.get() );

	// Create a MatrixTransform to display the cow on the right.
	osg::ref_ptr<osg::MatrixTransform> mtRight =
		new osg::MatrixTransform;
	mtRight->setName( "Right Cow\nSTATIC" );
	// Data variance is STATIC because we won't modify it.
	mtRight->setDataVariance( osg::Object::STATIC );
	m.makeTranslate( 6.f, 0.f, 0.f );
	mtRight->setMatrix( m );
	mtRight->addChild( cow.get() );

	// Create the Group root node.
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->setName( "Root Node" );
	// Data variance is STATIC because we won't modify it.
	root->setDataVariance( osg::Object::STATIC );
	root->addChild( mtLeft.get() );
	root->addChild( mtRight.get() );

	return root.get();
}

osg::Transform* createAutoTransform(double posX,osg::Node* model)
{
	osg::ref_ptr<osg::AutoTransform> at=new osg::AutoTransform;
	at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_AXIS);
	at->setPosition(osg::Vec3(posX,0,0));
	at->addChild(model);
	return at.release();
}
osg::Transform* createMatrixTransform(double posX,double rotateZ,osg::Node* model)
{
	osg::ref_ptr<osg::MatrixTransform> mt=new osg::MatrixTransform;
	mt->setMatrix(osg::Matrix::rotate(rotateZ,osg::Z_AXIS)
		*osg::Matrix::translate(posX,0,0));
	mt->addChild(model);
	return mt.release();
}
osg::Transform* createPositionAttitudeTransform(double posX,double rotateZ,osg::Node* model)
{
	osg::ref_ptr<osg::PositionAttitudeTransform> pat=
		new osg::PositionAttitudeTransform;
	pat->setPosition(osg::Vec3(posX,0,0));
	pat->setAttitude(osg::Quat(rotateZ,osg::Z_AXIS));
	pat->addChild(model);
	return pat.release();
}

class CessnaCallback:public osg::NodeCallback
{
public:
	static const int _fireStartFrame=120;
	virtual void operator()(osg::Node* node,osg::NodeVisitor* nv)
	{
		//这个地方必须用dynamic_cast，作为与c#里的 as 类似。但要求被转换的node的Node类中有虚函数
		osg::Switch* cessnaSwitch=dynamic_cast<osg::Switch*>(node);
		if (cessnaSwitch&&nv)
		{
			const osg::FrameStamp* frameStamp=nv->getFrameStamp();
			if (frameStamp)
			{
				if (_fireStartFrame<frameStamp->getFrameNumber())
				{
					cessnaSwitch->setValue(0,false);
					cessnaSwitch->setValue(1,true);
				}
			}
		}
		traverse(node,nv);
	}
protected:
private:
};

osg::Drawable* createHouseWall()
{
	//House vertices
	char* p=new char[1];
	osg::ref_ptr<osg::Vec3Array> vertices=new osg::Vec3Array;
	vertices->push_back(osg::Vec3(0,0,4));
	vertices->push_back(osg::Vec3(0,0,0));
	vertices->push_back(osg::Vec3(6,0,4));
	vertices->push_back(osg::Vec3(6,0,0));
	vertices->push_back(osg::Vec3(6,4,4));
	vertices->push_back(osg::Vec3(6,4,0));
	vertices->push_back(osg::Vec3(0,4,4));
	vertices->push_back(osg::Vec3(0,4,0));
	vertices->push_back(osg::Vec3(0,0,4));
	vertices->push_back(osg::Vec3(0,0,0));

	//House normals
	osg::ref_ptr<osg::Vec3Array> normals=new osg::Vec3Array(10);
	(*normals)[0].set(-0.707,-0.707,0);
	(*normals)[1].set(-0.707,-0.707,0);
	(*normals)[2].set(-0.707,0.707,0);
	(*normals)[3].set(0.707,-0.707,0);
	(*normals)[4].set(0.707,0.707,0);
	(*normals)[5].set(0.707,0.707,0);
	(*normals)[6].set(-0.707,0.707,0);
	(*normals)[7].set(-0.707,0.707,0);
	(*normals)[8].set(-0.707,-0.707,0);
	(*normals)[9].set(-0.707,-0.707,0);

	//House texture coordinates
	osg::ref_ptr<osg::Vec2Array> texcoords=new osg::Vec2Array(10);
	(*texcoords)[0].set(0,1);
	(*texcoords)[0].set(0,0);
	(*texcoords)[0].set(0.3,1);
	(*texcoords)[0].set(0.3,0);
	(*texcoords)[0].set(0.5,1);
	(*texcoords)[0].set(0.5,0);
	(*texcoords)[0].set(0.8,1);
	(*texcoords)[0].set(0.8,0);
	(*texcoords)[0].set(1,1);
	(*texcoords)[0].set(1,0);

	//Create wall geometry
	osg::ref_ptr<osg::Geometry> houseWall=new osg::Geometry;
	houseWall->setVertexArray(vertices.get());
	houseWall->setTexCoordArray(0,texcoords.get());
	houseWall->setNormalArray(normals.get());
	houseWall->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	houseWall->addPrimitiveSet(
		new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP,0,10));
	houseWall->getOrCreateStateSet()->setTextureAttributeAndModes(
		0,new osg::Texture2D(osgDB::readImageFile("D:\\Program Files\\OpenSceneGraph\\data\\Images\\road.png")));
	return houseWall.release();
}
osg::Drawable* createHouseRoof()
{
	//House vertices
	osg::ref_ptr<osg::Vec3Array> vertices=new osg::Vec3Array;
	vertices->push_back(osg::Vec3(-0.2,-0.5,3.5));
	vertices->push_back(osg::Vec3(6.2,-0.5,3.5));
	vertices->push_back(osg::Vec3(0.8,2,6));
	vertices->push_back(osg::Vec3(5.2,2,6));
	vertices->push_back(osg::Vec3(-0.2,4.5,3.5));
	vertices->push_back(osg::Vec3(6.2,4.5,3.5));

	//Roof primitives
	osg::ref_ptr<osg::DrawArrays> roof=
		new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP,0,6);
	osg::ref_ptr<osg::DrawElementsUInt> roofSide=
		new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES,6);
	(*roofSide)[0]=0;
	(*roofSide)[1]=2;
	(*roofSide)[2]=4;
	(*roofSide)[3]=5;
	(*roofSide)[4]=3;
	(*roofSide)[5]=1;
	//Color
	osg::ref_ptr<osg::Vec4Array> colors=new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.25,0,0,1));
	//Create roof geometry
	osg::ref_ptr<osg::Geometry> houseRoof=new osg::Geometry;
	houseRoof->setVertexArray(vertices.get());
	houseRoof->setColorArray(colors.get());
	houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
	houseRoof->addPrimitiveSet(roof.get());
	houseRoof->addPrimitiveSet(roofSide.get());
	osgUtil::SmoothingVisitor smv;
	smv.smooth(*houseRoof);
	return houseRoof.release();
}
//int _tmain(int argc, _TCHAR* argv[])
int _tmain(int argc, char** argv)
{
	/*osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile("E:\\wz_model\\smgc\\smgc\\x\\smgc_grass.x"));

	return viewer.run();*/

	/*osg::ref_ptr<osg::Geode> geode1=new osg::Geode();
	osg::ref_ptr<osg::Geode> geode2=new osg::Geode;
	GeodeParent geodeParent;
	geodeParent.SetGeode(geode1);
	std::cout<<"count11:"<<geode1->referenceCount()<<std::endl;
	std::cout<<"count21:"<<geode2->referenceCount()<<std::endl;
	geodeParent.SetGeode(geode2);
	std::cout<<"count12:"<<geode1->referenceCount()<<std::endl;
	std::cout<<"count22:"<<geode2->referenceCount()<<std::endl;
	int a;
	std::cin>>a;
	return 0;*/

	/*osg::ArgumentParser arguments(&argc,argv);
	osg::Node * root=osgDB::readNodeFiles(arguments);
	if(!root)
		root=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\axes.osgt");

	InfoVisitor infoVistor;
	if(root)root->accept(infoVistor);
	int a;
	std::cin>>a;
	return 0;*/


	//osg::ArgumentParser arguments(&argc,argv);
	//osg::Node* model=osgDB::readNodeFiles(arguments);
	//if(!model)
	//{
	//	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\cow.osgt");
	//}
	//osg::ref_ptr<osg::PositionAttitudeTransform> pat=
	//	new osg::PositionAttitudeTransform;
	//pat->addChild(model);
	//pat->setUpdateCallback(new RotateCallback);
	//pat->addUpdateCallback(new InfoCallback);
	//osgViewer::Viewer viewer;
	//viewer.setSceneData(pat.get());
	//return viewer.run();


	////--------------空间变换节点--------------------
	//// Create the viewer and set its scene data to our scene
	////   graph created above.
	//osgViewer::Viewer viewer;
	//viewer.setSceneData( createScene().get() );
	//if (!viewer.getSceneData())
	//	return 1;

	//// Set the clear color to something other than chalky blue.
	///*viewer.getCamera()->setClearColor(
	//	osg::Vec4( 1., 1., 1., 1. ) );*/

	//// Loop and render. OSG calls RotateCB::operator()
	////   during the update traversal.
	//return viewer.run();

	//--------------------------------
//	osg::ArgumentParser arguments(&argc,argv);
//	osg::Node* model=osgDB::readNodeFiles(arguments);
//	if(!model)
//	{
//		model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\axes.osgt");
//	}
//	osg::ref_ptr<osg::Group> root=new osg::Group;
//	root->addChild(createMatrixTransform(-5,osg::PI_4,model));
//	root->addChild(createAutoTransform(0,model));
//	root->addChild(createPositionAttitudeTransform(5,-osg::PI_4,model));
//	osgViewer::Viewer viewer;
//	viewer.setSceneData(root.get());
//	return viewer.run();

	//---------------开关节点------------
	/*osg::ref_ptr<osg::Switch> root=new osg::Switch;
	root->addChild(osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\cessna.osg"),true);
	root->addChild(osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\cessnafire.osg"),false);
	root->setUpdateCallback(new CessnaCallback);

	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();*/

	//---------------使用LOD节点---------
	//osg::Node* model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\robot.osg");
	//float r=model->getBound().radius();

	//osg::ref_ptr<osg::LOD> root=new osg::LOD;
	//
	//root->addChild(osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\dumptruck.osg"),r*7,FLT_MAX);
	//root->addChild(osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\cow.osg"),r*3,r*7);
	//root->addChild(model,0,r*3);

	//osgViewer::Viewer viewer;
	//viewer.setSceneData(root.get());
	//return viewer.run();

	////-------------节点代理--------------
	//osg::ArgumentParser arg(&argc,argv);
	//osg::ref_ptr<osg::ProxyNode>root=new osg::ProxyNode;
	//unsigned int childrenNo=0;
	//for (int i=1;i<arg.argc();++i)
	//{
	//	if (arg.isString(i))
	//	{
	//		root->setFileName(childrenNo++,arg[i]);
	//	}
	//}
	//if (!root->getNumFileNames())
	//{
	//	root->setFileName(0,"D:\\Program Files\\OpenSceneGraph\\data\\cow.osg");
	//}
	//osgViewer::Viewer viewer;
	//viewer.setSceneData(root.get());
	//return viewer.run();

	//------------简易房屋---------------
	osg::ref_ptr<osg::Geode> geode=new osg::Geode;
	geode->addDrawable(createHouseWall());
	geode->addDrawable(createHouseRoof());	
	osgViewer::Viewer viewer;
	viewer.setSceneData(geode.get());
	return viewer.run();

}

