#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <osg/io_utils>
#include <osg/MatrixTransform>
#include <osgViewer/Renderer>
#include <osg/PolygonMode>
#include <osg/Geometry>
#include <osgGA/GUIEventHandler>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgViewer/Renderer>
#include <osgText/Text>
#include <osg/State>
#include <osg/Drawable>


namespace EAViewEngine
{
	class ViewStatsHandler : public osgGA::GUIEventHandler
	{
	public:
		ViewStatsHandler();
		~ViewStatsHandler();
		enum StatsType
		{
			NO_STATS = 0,
			FRAME_RATE = 1,
			VIEWER_STATS = 2,
			CAMERA_SCENE_STATS = 3,
			VIEWER_SCENE_STATS = 4,
			LAST = 5
		};
		void setKeyEventTogglesOnScreenStats(int key) { _keyEventTogglesOnScreenStats = key; }
		int getKeyEventTogglesOnScreenStats() const { return _keyEventTogglesOnScreenStats; }
		void setKeyEventPrintsOutStats(int key) { _keyEventPrintsOutStats = key; }
		int getKeyEventPrintsOutStats() const { return _keyEventPrintsOutStats; }
		void setKeyEventToggleVSync(int key) { _keyEventToggleVSync = key; }
		int getKeyEventToggleVSync() const { return _keyEventToggleVSync; }
		double getBlockMultiplier() const { return _blockMultiplier; }
		void reset();
		osg::Camera* getCamera() { return _camera.get(); }
		const osg::Camera* getCamera() const { return _camera.get(); }
		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
		/** Get the keyboard and mouse usage of this manipulator.*/
		virtual void getUsage(osg::ApplicationUsage& usage) const;
		/** This allows the user to register additional stats lines that will
		be added to the graph. The stats for these will be gotten from the
		viewer (viewer->getViewerStats()). The stats can be displayed in
		either or all of the following ways:
		- A numeric time beside the stat name
		Requires that an elapsed time be recorded in the viewer's stats
		for the "timeTakenName".
		- A bar in the top bar graph
		Requires that two times (relative to the viewer's start tick) be
		recorded in the viewer's stats for the "beginTimeName" and
		"endTimeName".
		- A line in the bottom graph
		Requires that an elapsed time be recorded in the viewer's stats
		for the "timeTakenName" and that the value be used as an average.
		If you don't want a numeric value and a line in the bottom line
		graph for your value, pass the empty string for timeTakenName. If
		you don't want a bar in the graph, pass the empty string for
		beginTimeName and endTimeName.
		@param label The label to be displayed to identify the line in the stats.
		@param textColor Will be used for the text label, the numeric time and the bottom line graph.
		@param barColor Will be used for the bar in the top bar graph.
		@param timeTakenName The name to be queried in the viewer stats for the numeric value (also used for the bottom line graph).
		@param multiplier The multiplier to apply to the numeric value before displaying it in the stats.
		@param average Whether to use the average value of the numeric value.
		@param averageInInverseSpace Whether to average in inverse space (used for frame rate).
		@param beginTimeName The name to be queried in the viewer stats for the begin time for the top bar graph.
		@param endTimeName The name to be queried in the viewer stats for the end time for the top bar graph.
		@param maxValue The value to use as maximum in the bottom line graph. Stats will be clamped between 0 and that value, and it will be the highest visible value in the graph.
		*/
		void addUserStatsLine(const std::string& label, const osg::Vec4& textColor, const osg::Vec4& barColor,
			const std::string& timeTakenName, float multiplier, bool average, bool averageInInverseSpace,
			const std::string& beginTimeName, const std::string& endTimeName, float maxValue);
		void removeUserStatsLine(const std::string& label);
	protected:
		void setUpHUDCamera(osgViewer::ViewerBase* viewer);
		void setWindowSize(int width, int height);
		osg::Geometry* createBackgroundRectangle(const osg::Vec3& pos, const float width, const float height, osg::Vec4& color);
		osg::Geometry* createGeometry(const osg::Vec3& pos, float height, const osg::Vec4& colour, unsigned int numBlocks);
		osg::Geometry* createFrameMarkers(const osg::Vec3& pos, float height, const osg::Vec4& colour, unsigned int numBlocks);
		osg::Geometry* createTick(const osg::Vec3& pos, float height, const osg::Vec4& colour, unsigned int numTicks);
		void createTimeStatsLine(const std::string& lineLabel, osg::Vec3 pos,
			const osg::Vec4& textColor, const osg::Vec4& barColor, osg::Stats* viewerStats, osg::Stats* stats,
			const std::string& timeTakenName, float multiplier, bool average, bool averageInInverseSpace,
			const std::string& beginTimeName, const std::string& endTimeName);
		void createCameraTimeStats(osg::Vec3& pos, bool acquireGPUStats, osg::Stats* viewerStats, osg::Camera* camera);
		void setUpScene(osgViewer::ViewerBase* viewer);
		void updateThreadingModelText();

		int _keyEventTogglesOnScreenStats;
		int _keyEventPrintsOutStats;
		int _keyEventToggleVSync;
		int _statsType;
		bool _initialized;
		osg::ref_ptr<osg::Camera> _camera;
		osg::ref_ptr<osg::Switch> _switch;
		osg::ref_ptr<osg::Geode> _statsGeode;
		osgViewer::ViewerBase::ThreadingModel _threadModel;
		osg::ref_ptr<osgText::Text> _threadModelText;
		unsigned int _frameRateChildNum;
		unsigned int _viewerChildNum;
		unsigned int _cameraSceneChildNum;
		unsigned int _viewerSceneChildNum;
		unsigned int _numBlocks;
		double _blockMultiplier;
		float _statsWidth;
		float _statsHeight;
		std::string _font;
		float _startBlocks;
		float _leftPos;
		float _characterSize;
		float _lineHeight;
		struct UserStatsLine
		{
			std::string label;
			osg::Vec4 textColor;
			osg::Vec4 barColor;
			std::string timeTakenName;
			float multiplier;
			bool average;
			bool averageInInverseSpace;
			std::string beginTimeName;
			std::string endTimeName;
			float maxValue;
			UserStatsLine(const std::string& label_, const osg::Vec4& textColor_, const osg::Vec4& barColor_,
				const std::string& timeTakenName_, float multiplier_, bool average_, bool averageInInverseSpace_,
				const std::string& beginTimeName_, const std::string& endTimeName_, float maxValue_)
				: label(label_), textColor(textColor_), barColor(barColor_),
				timeTakenName(timeTakenName_), multiplier(multiplier_), average(average_), averageInInverseSpace(averageInInverseSpace_),
				beginTimeName(beginTimeName_), endTimeName(endTimeName_), maxValue(maxValue_)
			{
			}
		};
		typedef std::vector<UserStatsLine> UserStatsLines;
		UserStatsLines _userStatsLines;
	};
}