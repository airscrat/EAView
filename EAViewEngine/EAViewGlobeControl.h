/********************************************************
[DateTime]:2013.8.30
[Author  ]:Mr.Huang
[Email   ]:hsq2013(at)foxmail(dot)com
[Content ]:The main 3d view control
/********************************************************/
#include <stdlib.h>
#include "Instance.h"
#include "EAViewGlobe.h"
#include <windows.h>
#include <process.h>
//#include <iostream.h>
#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace EAViewEngine {

	/// <summary>
	/// Summary for EAViewGlobeControl
	/// </summary>
	//[ToolboxBitmap(EAViewGlobeControl::typeid)]//,"EAViewGlobeControl.bmp")]//the icon
	//DWORD WINAPI RenderThreadProc(LPVOID lpParameter);
	void RenderThreadStart(void*);
	public ref class EAViewGlobeControl : public System::Windows::Forms::UserControl
	{
	public:
		//friend class EAViewGlobe;
		EAViewGlobeControl(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//		
			
			Instance::EAViewGlobeInit(_window);
			Object=gcnew EAViewGlobe;
			_viewer=Instance::GetEAViewer();	
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EAViewGlobeControl()
		{
			Instance::EAViewGlobeTerminate();
			if (components)
			{
				delete components;
			}			
		}

	public:
		/// <summary>
		/// get a class EAViewGlobe instance
		/// </summary>
		System::Object^ Object;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;		
		System::Windows::Forms::Panel^  _window;

		osgViewer::Viewer* _viewer;

	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->_window = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// _window
			// 
			this->_window->BackColor = System::Drawing::Color::Transparent;
			this->_window->Dock = System::Windows::Forms::DockStyle::Fill;
			this->_window->Location = System::Drawing::Point(0, 0);
			this->_window->Name = L"_window";
			this->_window->Size = System::Drawing::Size(250, 200);
			this->_window->TabIndex = 1;
			// 
			// EAViewGlobeControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->_window);
			this->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->Name = L"EAViewGlobeControl";
			this->Size = System::Drawing::Size(250, 200);
			this->Load += gcnew System::EventHandler(this, &EAViewGlobeControl::EAViewGlobeControl_Load);
			this->ResumeLayout(false);

		}
	#pragma endregion

	private:		
		/// <summary>
		/// this is a event to triger the osg render thread
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		System::Void EAViewGlobeControl_Load(System::Object^  sender, System::EventArgs^  e);		
	};
}
