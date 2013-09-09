#include "stdafx.h"
#include "EAViewGlobe.h"


namespace EAViewEngine
{
	EAViewGlobe::EAViewGlobe(void)
	{	
		_viewer=Instance::GetViewer();

		osg::Node*	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\cessnafire.osgt");

		osg::ref_ptr<osg::PositionAttitudeTransform> pat=
			new osg::PositionAttitudeTransform;
		pat->addChild(model);

		_viewer->setSceneData(pat.get());
		
	}

	void EAViewGlobe::LoadOSGModel(System::String^ file)//string file)
	{	
		if (file=="")
		{
			file="D:\\Program Files\\OpenSceneGraph\\data\\cessnafire.osgt";
		}
		_viewer=Instance::GetViewer();

		osg::Node*	model=osgDB::readNodeFile(EAViewFuncLib::ConvertToString(file));

		osg::ref_ptr<osg::PositionAttitudeTransform> pat=
			new osg::PositionAttitudeTransform;
		pat->addChild(model);
		_viewer->setSceneData(pat.get());
		
	}


}



