#include "stdafx.h"
#include "EAViewGlobe.h"
#include "EAHUDLayer.h"
#include "test.h"

namespace EAViewEngine
{
	EAViewGlobe::EAViewGlobe(void)
	{
		_viewer=Instance::GetEAViewer();
		
		//osg::Node*	model=osgDB::readNodeFile("D:\\Program Files\\OpenSceneGraph\\data\\lz.osgt");

		osg::ref_ptr<osg::Group> root=new osg::Group;
		//root->addChild(model);		

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
			return;
		}
		_viewer=Instance::GetEAViewer();

		osg::Node*	model=osgDB::readNodeFile(EAViewFuncLib::ConvertToString(file));

		/*osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(model);
		_viewer->setSceneData(root.get());*/
		
		osg::Node* node=_viewer->getSceneData();
		osg::Group* group = node->asGroup();
		if (group==0)
		{
			return;
		}
		int childCount=group->getNumChildren();
		//_viewer->setDone(true);//尽量早结束线程
		//Sleep(50);//等待渲染线程走完一帧
		group->removeChildren(1,childCount-1);
		group->addChild(model);
		//_viewer->setDone(false);
		/*EAHUDLayer hud;
		hud.SetHUDText("EAView 1.0");*/

		//osg::Stats* stats = _viewer->getViewerStats();
		//double frameRate=0;
		////stats->getAveragedAttribute("Frame rate",frameRate,true);
		//std::stringstream strstream;
		//strstream<<"EAView 1.0           FrameRate:"<<frameRate;
		//std::string ans=strstream.str();
		//hud.UpdateHUDText(ans);
	}


}



