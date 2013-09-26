#include "StdAfx.h"
#include "EAHUDLayer.h"


namespace EAViewEngine
{

	//--------------下面为鼠标求交的一个案例--------------------
	EAHUDLayer::EAHUDLayer()
	{
		_viewer=Instance::GetEAViewer();
		_valid=false;
	}

	osg::ref_ptr<osg::Geode> EAHUDLayer::CreatePanel()  
	{
		//beging  
		//画一个矩形模拟HUD面板  
		osg::ref_ptr<osg::Geometry> panelGeom = new osg::Geometry;  
		osg::ref_ptr<osg::Geode> panelGeode = new osg::Geode;  
		osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;  
		//确定框的大小

		vertexArray->push_back(osg::Vec3(0,0,-1));  
		vertexArray->push_back(osg::Vec3(1366,0,-1));  
		vertexArray->push_back(osg::Vec3(1366,40,-1));  
		vertexArray->push_back(osg::Vec3(0,40,-1));  

		osg::ref_ptr<osg::Vec4Array> colorArray = new osg::Vec4Array;  
		colorArray->push_back(osg::Vec4(0.1f, 0.2f, 0.4f, 0.8f));  

		osg::ref_ptr<osg::DrawElementsUInt> panelUnit = new osg::DrawElementsUInt(osg::PrimitiveSet::POLYGON,0);  
		panelUnit->push_back(0);  
		panelUnit->push_back(1);  
		panelUnit->push_back(2);  
		panelUnit->push_back(3);  

		osg::ref_ptr<osg::Vec3Array> normalArray = new osg::Vec3Array;  
		normalArray->push_back(osg::Vec3(0.0f,0.0f,1.0f));  

		osg::ref_ptr<osg::Vec2Array> textrueIndex = new osg::Vec2Array;  
		textrueIndex->push_back(osg::Vec2(0.0f,0.0f));  
		textrueIndex->push_back(osg::Vec2(1.0f,0.0f));  
		textrueIndex->push_back(osg::Vec2(1.0f,1.0f));  
		textrueIndex->push_back(osg::Vec2(0.0f,1.0f));  

		panelGeom->setVertexArray(vertexArray.get());  
		panelGeom->setNormalArray(normalArray.get());  
		panelGeom->setNormalBinding(osg::Geometry::BIND_OVERALL);  
		panelGeom->setColorArray(colorArray.get());  
		panelGeom->setColorBinding(osg::Geometry::BIND_OVERALL);  
		panelGeom->setTexCoordArray(0,textrueIndex.get());  
		panelGeom->addPrimitiveSet(panelUnit.get());  

		panelGeode->addDrawable(panelGeom.get());  
		//end  

		//begin  
		//载入纹理  
		osg::ref_ptr<osg::Texture2D> HUDTexture = new osg::Texture2D;  
		HUDTexture->setDataVariance(osg::Object::DYNAMIC);  
		osg::ref_ptr<osg::Image> HUDImage = osgDB::readImageFile("D:\\Program Files\\OpenSceneGraph\\data\\Images\\skymap.jpg");  
		HUDTexture->setImage(HUDImage.get());  
		osg::ref_ptr<osg::StateSet> HUDStateSet = new osg::StateSet;  
		HUDStateSet->setTextureAttributeAndModes(0,HUDTexture.get());  
		HUDStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);  
		HUDStateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);  
		HUDStateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);  
		HUDStateSet->setRenderBinDetails(11, "RenderBin");  
		panelGeode->setStateSet(HUDStateSet.get());  
		//end  
		return panelGeode;  
	}  

	bool EAHUDLayer::SetHUDText(const std::string& inText)
	{
		/*
		//begin  
		//this block intend to create a label with text "tank #1" and displayed in the scene  
		osg::ref_ptr<osgText::Text> tankLabel = new osgText::Text();  
		osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;  

		tankLabel->setCharacterSize(2);  
		//tankLabel->setFont("D:\\OSG\\osg2.9\\OpenSceneGraph2.9.5\\data\\fonts\\times.ttf");  
		tankLabel->setText("tank #1");  
		tankLabel->setAxisAlignment(osgText::Text::SCREEN);  
		tankLabel->setDrawMode(osgText::Text::TEXT);  

		tankLabel->setAlignment(osgText::Text::CENTER_CENTER);  
		tankLabel->setPosition( osg::Vec3(0,0,4) );  
		tankLabel->setColor( osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f) );  
		textGeode->addDrawable(tankLabel.get());  
		tankXForm->addChild(textGeode.get());  
		//end  
		*/

		osg::ref_ptr<osg::Group> root = _viewer->getSceneData()->asGroup();  
		osg::ref_ptr<osg::Geode> panelGeode = CreatePanel();
		//begin  
		//裁剪一个矩形，用来承装文字，并且不随场景的变化而变化  
		osg::ref_ptr<osg::Projection> HUDProjection = new osg::Projection;  
		HUDProjection->setMatrix(osg::Matrix::ortho2D(0,1366,0,768));  
		osg::ref_ptr<osg::MatrixTransform> HUDViewMatrix = new osg::MatrixTransform;  
		HUDViewMatrix->setMatrix(osg::Matrix::identity());  
		HUDViewMatrix->setReferenceFrame(osg::Transform::ABSOLUTE_RF); 
		HUDViewMatrix->addChild(panelGeode.get());
		HUDProjection->addChild(HUDViewMatrix.get());  
		//end  

		//begin  
		m_text = new osgText::Text; 
		m_text->setCharacterSize(30);  
		m_text->setFont("D:\\Program Files\\OpenSceneGraph\\data\\Fonts\\simhei.ttf");
		m_text->setText(inText);  
		m_text->setAlignment(osgText::Text::CENTER_CENTER);  
		m_text->setAxisAlignment(osgText::Text::SCREEN);  
		m_text->setPosition(osg::Vec3(100,20,-1.5));  
		m_text->setColor(osg::Vec4(199, 77, 15, 1));  
		panelGeode->addDrawable(m_text.get());
		//end
		root->addChild(HUDProjection.get());  
		/*root->addChild(tankXForm.get());  
		root->addChild(landTankNode.get());  */
		_viewer->setSceneData(root.get());
		_valid=true;
		return true;
	}

	//bool EAHUDLayer::UpdateHUDText(const std::string& inText)
	//{
	//	if (m_text!=NULL&&_valid)
	//	{
	//		m_text->setText(inText);
	//		m_text->update();
	//		return true;
	//	}
	//	return false;
	//}
}
