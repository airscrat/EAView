/********************************************************
[DateTime]:2013.8.30
[Author  ]:Mr.Huang
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
	DWORD WINAPI RenderThreadProc(LPVOID lpParameter);
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
			Object=gcnew EAViewGlobe;
			Instance::EAViewGlobeInit(_window);
			
			_viewer=Instance::GetViewer();			
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
		System::Object^ Object;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;		
		System::Windows::Forms::Panel^  _window;
		System::Windows::Forms::Label^  label1;			 
		osgViewer::Viewer* _viewer;

	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->_window = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->_window->SuspendLayout();
			this->SuspendLayout();
			// 
			// _window
			// 
			this->_window->BackColor = System::Drawing::Color::Transparent;
			this->_window->Controls->Add(this->label1);
			this->_window->Dock = System::Windows::Forms::DockStyle::Fill;
			this->_window->Location = System::Drawing::Point(0, 0);
			this->_window->Name = L"_window";
			this->_window->Size = System::Drawing::Size(250, 200);
			this->_window->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(182, 176);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"EAView 1.0";
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
			this->_window->ResumeLayout(false);
			this->_window->PerformLayout();
			this->ResumeLayout(false);

		}
	#pragma endregion

	private:		
		
		System::Void EAViewGlobeControl_Load(System::Object^  sender, System::EventArgs^  e);
		
	};
}
