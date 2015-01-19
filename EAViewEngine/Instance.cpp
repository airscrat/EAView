#include "StdAfx.h"
#include "Instance.h"


namespace EAViewEngine
{
    
	Instance::Instance(void)
	{
	}

	Instance::~Instance(void)
	{
	}

	osg::observer_ptr<osgViewer::ViewerBase> Instance::_eaview=new osgViewer::ViewerBase;

	bool Instance::EAViewGlobeInit(Control^ eaViewControl)
	{
		/*ReconfigViewer(eaViewControl);*/
		HWND hwnd = (HWND)eaViewControl->Handle.ToPointer();

		osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits(ds);
		traits->inheritedWindowData = new osgViewer::GraphicsWindowWin32::WindowData( hwnd );
		traits->setInheritedWindowPixelFormat = true;
		traits->doubleBuffer = true;
		traits->windowDecoration = true;
		traits->sharedContext = NULL;
		traits->supportsResize = true;

		RECT rect;
		::GetWindowRect( hwnd, &rect );
		traits->x = 0;
		traits->y = 0;
		traits->width = rect.right - rect.left;
		traits->height = rect.bottom - rect.top;
		
		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
		_eaview->getCamera()->setGraphicsContext( gc.get() );
		_eaview->getCamera()->setViewport( new osg::Viewport( 0, 0, traits->width, traits->height ) );
		_eaview->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f);

		_eaview->setThreadingModel(osgViewer::Viewer::DrawThreadPerContext);
		
		//_eaview->addEventHandler(new osgViewer::StatsHandler());
		_eaview->addEventHandler(new osgGA::StateSetManipulator());
		_eaview->addEventHandler(new osgViewer::ThreadingHandler());
		_eaview->setKeyEventSetsDone(0);
		_eaview->setQuitEventSetsDone(false);
		_eaview->setRunMaxFrameRate(30);

		return true;
	}

	bool Instance::EAViewGlobeTerminate()
	{
		if ( _eaview.valid() )
		{
			_eaview->setDone(true);//尽量早结束线程
			Sleep(50);//等待渲染线程走完一帧
			_eaview->stopThreading();
			_eaview = 0L;//赋值为长整型的0
		}
		
		return true;
	}

	int Instance::EAViewGlobeRun()
	{
		if (!_eaview->getCameraManipulator() && _eaview->getCamera()->getAllowEventFocus())
		{
			_eaview->setCameraManipulator(new osgGA::TrackballManipulator());
		}
		_eaview->setReleaseContextAtEndOfFrameHint(false);

		const char* run_frame_count_str = getenv("OSG_RUN_FRAME_COUNT");
		//const char* run_frame_count_str1 = getenv("OSGDIR");//这个函数取操作系统环境变量的值
		unsigned int runTillFrameNumber = run_frame_count_str==0 ? osg::UNINITIALIZED_FRAME_NUMBER : atoi(run_frame_count_str);
		//while(!_eaview->done() )//&& (_eaview->getViewerFrameStamp()->getFrameNumber()<runTillFrameNumber))
		//while(!_eaview->done() && (run_frame_count_str==0 || _eaview->getViewerFrameStamp()->getFrameNumber()<1))//runTillFrameNumber))
		
		
		
		while(_eaview.valid()&&!_eaview->done())
		{					 
			double minFrameTime = _eaview->getRunMaxFrameRate()>0.0 ? 1.0/_eaview->getRunMaxFrameRate() : 0.0;
			osg::Timer_t startFrameTick = osg::Timer::instance()->tick();
			if (minFrameTime==0.0) minFrameTime=0.02;			
			if (_eaview->getRunFrameScheme()==osgViewer::ViewerBase::FrameScheme::ON_DEMAND)
			{
				if (_eaview->checkNeedToDoFrame())
				{
					_eaview->frame();
				}
				else
				{
					// we don't need to render a frame but we don't want to spin the run loop so make sure the minimum
					// loop time is 2/100th of second, if not otherwise set, so enabling the frame microSleep below to
					// avoid consume excessive CPU resources.
					if (minFrameTime==0.0) minFrameTime=0.02;
				}
			}
			else
			{
				_eaview->frame();
			}
			// work out if we need to force a sleep to hold back the frame rate
			osg::Timer_t endFrameTick = osg::Timer::instance()->tick();
			double frameTime = osg::Timer::instance()->delta_s(startFrameTick, endFrameTick);
			if (frameTime < minFrameTime) 
				OpenThreads::Thread::microSleep(static_cast<unsigned int>(1000000.0*(minFrameTime-frameTime)));
		}		
		return 0;
	}

	bool Instance::ReconfigViewer(Control^ eaViewControl)
	{
		HWND hwnd = (HWND)eaViewControl->Handle.ToPointer();

		osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
		osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits(ds);
		traits->inheritedWindowData = new osgViewer::GraphicsWindowWin32::WindowData( hwnd );
		traits->setInheritedWindowPixelFormat = true;
		traits->doubleBuffer = true;
		traits->windowDecoration = true;
		traits->sharedContext = NULL;
		traits->supportsResize = true;

		RECT rect;
		::GetWindowRect( hwnd, &rect );
		traits->x = 0;
		traits->y = 0;
		traits->width = rect.right - rect.left;
		traits->height = rect.bottom - rect.top;

		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext( traits.get() );
		_eaview->getCamera()->setGraphicsContext( gc.get() );
		_eaview->getCamera()->setViewport( new osg::Viewport( 0, 0, traits->width, traits->height ) );
		_eaview->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f);
		return true;
	}

	osgViewer::Viewer* Instance::GetEAViewer()
	{
		return _eaview.get();
	}

	void Instance::GetEAWindowRect(int& x,int& y,int& w,int&h)
	{		
		osg::GraphicsContext* gc=_eaview->getCamera()->getGraphicsContext();
		osgViewer::GraphicsWindowWin32* window=static_cast<osgViewer::GraphicsWindowWin32*>(gc);

		if (window!=NULL&&window->valid())
		{
			window->getWindowRectangle(x,y,w,h);			
		}
		else
		{
			x=0;y=0;w=0;h=0;
		}
	}
}