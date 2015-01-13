#include "stdafx.h"
#include "EAViewGlobe.h"
#include "EAHUDLayer.h"
#include "test.h"

namespace EAViewEngine
{
	EAViewGlobe::EAViewGlobe(void)
	{
		_viewer=Instance::GetEAViewer();
		osg::ref_ptr<osg::Group> root=new osg::Group;
		_viewer->setSceneData(root.get());
		EAViewInit();
		EAGroupDataReset();
		//---------------
		test test;

		
	}

	bool EAViewGlobe::EAViewInit()
	{
		//show hud logo
		EAHUDLayer hud;
		hud.SetHUDText("EAView 1.0");
		//remove statshandler
		osgViewer::View::EventHandlers handlers = 
			_viewer->getEventHandlers();
		for (osgViewer::View::EventHandlers::iterator itr=handlers.begin();
			itr!=handlers.end();++itr)
		{
			osgViewer::StatsHandler* statsHandler = dynamic_cast<osgViewer::StatsHandler*>((*itr).get());
			if (statsHandler!=0)
			{
				_viewer->removeEventHandler(statsHandler);
			}
		}
		
		return true;
	}

	osg::Group* EAViewGlobe::EAGroupDataReset()
	{
		osg::Node* node=_viewer->getSceneData();
		osg::Group* group = node->asGroup();
		if (group==0)
		{
			return NULL;
		}
		int childCount=group->getNumChildren();

		group->removeChildren(1,childCount-1);
		
		return group;
	}

	void EAViewGlobe::LoadOSGModel(System::String^ file)//string file)
	{	
		if (file=="")
		{
			return;
		}

		osg::Node*	model=osgDB::readNodeFile(EAViewFuncLib::ConvertToString(file));

		/*osg::ref_ptr<osg::Group> root=new osg::Group;
		root->addChild(model);
		_viewer->setSceneData(root.get());*/
		
		osg::Group* group=EAGroupDataReset();
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

	void EAViewGlobe::LoadProject(System::String^ file)
	{
	}
}



