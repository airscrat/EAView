#pragma once

namespace EAView {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for mainTest
	/// </summary>
	public ref class mainTest : public System::Windows::Forms::Form
	{
	public:
		mainTest(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainTest()
		{
			if (components)
			{
				delete components;
			}
		}
	private: EAViewEngine::EAViewEngineControl^  eaViewEngineControl1;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->eaViewEngineControl1 = (gcnew EAViewEngine::EAViewEngineControl());
			this->SuspendLayout();
			// 
			// eaViewEngineControl1
			// 
			this->eaViewEngineControl1->Location = System::Drawing::Point(12, 12);
			this->eaViewEngineControl1->Name = L"eaViewEngineControl1";
			this->eaViewEngineControl1->Size = System::Drawing::Size(260, 238);
			this->eaViewEngineControl1->TabIndex = 0;
			// 
			// mainTest
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->eaViewEngineControl1);
			this->Name = L"mainTest";
			this->Text = L"mainTest";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
