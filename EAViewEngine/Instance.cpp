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

	osg::observer_ptr<osgViewer::Viewer> Instance::_viewer=new osgViewer::Viewer;

	bool Instance::EAViewGlobeInit(Control^ eaViewControl)
	{
		ReconfigViewer(eaViewControl);
		_viewer->setThreadingModel(osgViewer::Viewer::DrawThreadPerContext);
		
		_viewer->addEventHandler(new osgViewer::StatsHandler());
		_viewer->addEventHandler(new osgGA::StateSetManipulator());
		_viewer->addEventHandler(new osgViewer::ThreadingHandler());
		_viewer->setKeyEventSetsDone(0);
		_viewer->setQuitEventSetsDone(false);
		
		//static_cast<osgViewer::ViewerBase*>(_viewer.get())->run();
		return true;
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
		_viewer->getCamera()->setGraphicsContext( gc.get() );
		_viewer->getCamera()->setViewport( new osg::Viewport( 0, 0, traits->width, traits->height ) );
		_viewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f);
		return true;
	}

	osgViewer::Viewer* Instance::GetViewer()
	{
		return _viewer.get();
	}
}