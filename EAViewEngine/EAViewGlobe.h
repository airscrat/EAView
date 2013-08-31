#pragma once
#include "stdafx.h"
#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgViewer/View>
#include <osgViewer/api/Win32/GraphicsWindowWin32>
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
//#include <osg/io_utils>
//#include <osg/Version>
//#include <osg/DisplaySettings>
//#include <osg/GLObjects>
//#include <osgDB/ReadFile>
//#include <osgDB/FileUtils>
//#include <osgDB/FileNameUtils>
//#include <osgGA/TrackballManipulator>
//#include <osgGA/FlightManipulator>
//#include <osgGA/DriveManipulator>
//#include <osgGA/KeySwitchMatrixManipulator>
//#include <osgGA/TerrainManipulator>
//#include <osgGA/SphericalManipulator>
//#include <osgViewer/api/Win32/GraphicsWindowWin32>
//#include <OpenThreads/Thread>
//
//#include <sstream>
//#include <iostream>
//
//#include <windows.h>
//#include <windowsx.h>
//
//#include <string.h>
//#include <atlconv.h>


namespace EAViewEngine
{
	//struct EAViewGlobeCallback;
	public ref class EAViewGlobe//:public osg::Referenced, public OpenThreads::Thread 
	{
	public:
		EAViewGlobe(void);
	
		bool EAViewGlobeInit(System::Windows::Forms::Panel^ eaViewControl);

	private:
		osgViewer::Viewer* _viewer;
	//	class EventCallback
	//	{
	//	public:
	//		virtual void handleEvent(const std::string &target, const std::string &eventName, const std::string &data) = 0;
	//	};

	//	EAViewGlobe(void);
	//	virtual void init(void* window);

	//	void setEventCallback(EventCallback* eventCallback) { _eventCallback = eventCallback; }

	//	virtual void run();
	//	virtual int cancel();

	//	osg::CoordinateSystemNode* getCoordinateSystemsNode() {return _csn.get();}

	//	CommandQueue* getCommandQueue() {return _commandQueue.get();}

	//	osgViewer::View* getView() {return _viewer.get();}

	//	osg::Group* getRoot() {return _root.get();}

	//	/*osgEarth::Map* getMap() { return _mapNode.get() ? _mapNode->getMap() : 0L; }

	//	osgEarth::MapNode* getMapNode() { return _mapNode.get(); }*/

	//	SelectionSet* getSelectionSet() { return _selectionSet.get(); }

	//	//osgEarth::Util::EarthManipulator* selectEarthManipulator();
	//	//GodziWebControl::FirstPersonManipulator* selectFirstPersonManipulator();

	//	void toggleStats();
	//	void cyclePolygonMode();

	//	void setMapFile(const std::string &mapFile);

	//	void showSkyNode();
	//	void setSkyDateTime(int year, int month, int day, double timeUTC);

	//	void toggleNavDisplay(bool visible);

	//	float getVerticalScale();
	//	void setVerticalScale(float verticalScale);

	//	float getSampleRatio();
	//	void setSampleRatio(float sampleRatio);

	//	void latLongHeightToXYZ(double lat, double lon, double height, double &x, double &y, double &z);
	//	void xyzToLatLongHeight(double x, double y, double z, double &lat, double &lon, double &height);

	//	//osgEarth::Util::Viewpoint getViewpoint();

	//	LRESULT handleNativeWindowingEvent( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

	//	void addCommandFactory(CommandFactory* factory);

	//	std::string handleCommand(const std::string &command, const std::string &args, bool block);

	//	void postEvent(const std::string &target, const std::string &eventName, const std::string &data);

	//	void requestRefresh() { _refreshRequested = true; }

	//private:

	//	osg::ref_ptr<MapControlMapCallback> _mapCallback;
	//	osg::Vec4 _clearColor;

	//	osg::ref_ptr<osgViewer::Viewer> _viewer;
	//	osg::ref_ptr<osg::Group> _root;

	//	osg::ref_ptr<osgViewer::StatsHandler> _statsHandler;
	//	osg::ref_ptr<osgGA::StateSetManipulator> _stateSetManipulator;

	//	osg::ref_ptr<osg::CoordinateSystemNode> _csn;
	//	osg::ref_ptr<osgTerrain::Terrain> _terrain;

	//	osg::ref_ptr<GodziWebControl::CommandQueue> _commandQueue;

	//	osg::ref_ptr<osgEarth::Util::SkyNode> _skyNode;
	//	osgEarth::Util::FeatureManipTool* _manipTool;
	//	osg::ref_ptr<osgEarth::Util::Controls::LabelControl> _manipLabel;

	//	HWND _hwnd;
	//	WNDPROC _previousWindowProcedure;
	//	bool _paintRequested;
	//	bool _refreshRequested;

	//	//osg::ref_ptr<osg::Node> _rootNode;
	//	osg::ref_ptr<osgEarth::MapNode> _mapNode;

	//	typedef std::vector< osg::ref_ptr<CommandFactory> > CommandFactoryList;
	//	CommandFactoryList _commandFactories;

	//	EventCallback* _eventCallback;

	//	osg::ref_ptr<SelectionSet> _selectionSet;
		
	};


}