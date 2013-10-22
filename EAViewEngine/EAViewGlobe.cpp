#include "stdafx.h"
#include "EAViewGlobe.h"
#include "EAHUDLayer.h"
#include "test.h"
#include "vld.h"

namespace EAViewEngine
{
	EAViewGlobe::EAViewGlobe(void)
	{
		_viewer=Instance::GetEAViewer();
		
		osg::Node*	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\lz.osgt");

		osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(model);		

		_viewer->setSceneData(root.get());
		
		EAHUDLayer hud;
		hud.SetHUDText("EAView 1.0");	
		//---------------
		test test;

		
	}

	void EAViewGlobe::LoadOSGModel(System::String^ file)//string file)
	{	
		if (file=="")
		{
			file="D:\\Program Files\\OpenSceneGraph\\data\\lz.osgt";
		}
		_viewer=Instance::GetEAViewer();

		osg::Node*	model=osgDB::readNodeFile(EAViewFuncLib::ConvertToString(file));

		osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(model);
		_viewer->setSceneData(root.get());

		EAHUDLayer hud;
		hud.SetHUDText("EAView 1.0");

		//osg::Stats* stats = _viewer->getViewerStats();
		//double frameRate=0;
		////stats->getAveragedAttribute("Frame rate",frameRate,true);
		//std::stringstream strstream;
		//strstream<<"EAView 1.0           FrameRate:"<<frameRate;
		//std::string ans=strstream.str();
		//hud.UpdateHUDText(ans);
	}


}



