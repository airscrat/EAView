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
		/*pat->setUpdateCallback(new RotateCallback);
		pat->addUpdateCallback(new InfoCallback);*/

		_viewer->setSceneData(pat.get());
		
	}
}



