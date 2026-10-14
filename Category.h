#pragma once

namespace PlantSalesManagementSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Category
	/// </summary>
	public ref class Category : public System::Windows::Forms::Form
	{
	public:
		Category(void)
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
		~Category()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::FlowLayoutPanel^ flpCategories;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::FlowLayoutPanel^ panelRight;
	private: System::Windows::Forms::Label^ label2;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->flpCategories = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->panelRight = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->flpCategories->SuspendLayout();
			this->panelRight->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(238, 29);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Choose Categories";
			// 
			// flpCategories
			// 
			this->flpCategories->AutoScroll = true;
			this->flpCategories->BackColor = System::Drawing::Color::White;
			this->flpCategories->Controls->Add(this->button2);
			this->flpCategories->Controls->Add(this->button3);
			this->flpCategories->Controls->Add(this->button4);
			this->flpCategories->Controls->Add(this->button1);
			this->flpCategories->Location = System::Drawing::Point(6, 50);
			this->flpCategories->Name = L"flpCategories";
			this->flpCategories->Size = System::Drawing::Size(1098, 422);
			this->flpCategories->TabIndex = 1;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(3, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(186, 66);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Flower Plant";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Category::Category_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(195, 3);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(186, 66);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Herbs Plant";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Category::Category_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(387, 3);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(189, 66);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Indoor Plant";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Category::Category_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(582, 3);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(232, 66);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Garden Supplies / Accessories";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Category::Category_Click);
			// 
			// panelRight
			// 
			this->panelRight->Controls->Add(this->label2);
			this->panelRight->Dock = System::Windows::Forms::DockStyle::Right;
			this->panelRight->Location = System::Drawing::Point(1113, 0);
			this->panelRight->Name = L"panelRight";
			this->panelRight->Size = System::Drawing::Size(254, 540);
			this->panelRight->TabIndex = 6;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(3, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(145, 25);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Current Order";
			// 
			// Category
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1367, 540);
			this->Controls->Add(this->flpCategories);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panelRight);
			this->Name = L"Category";
			this->Text = L"Category";
			this->flpCategories->ResumeLayout(false);
			this->panelRight->ResumeLayout(false);
			this->panelRight->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	
}

private: System::Void Category_Click(System::Object^ sender, System::EventArgs^ e) {
	for each (Control ^ c in flpCategories->Controls) {
		if (dynamic_cast<Button^>(c) != nullptr) {
			c->BackColor = Color::White;
			c->ForeColor = Color::Black;
		}
	}
	Button^ clickKaraEka = safe_cast<Button^>(sender);
	clickKaraEka->BackColor = Color::FromArgb(34, 197, 94);
	clickKaraEka->ForeColor = Color::White;
}
	 

};
}

