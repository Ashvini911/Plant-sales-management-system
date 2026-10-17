#pragma once
#include "DatabaseHelper.h"

namespace PlantSalesSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	public ref class RegisterForm : public System::Windows::Forms::Form
	{
	public:
		
		property String^ RegisteredUsername;

		RegisterForm(void)
		{
			InitializeComponent();
			ApplyTheme();
		}

	protected:
		~RegisterForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^ pnlCard;
	private: System::Windows::Forms::Label^ lblHeading;
	private: System::Windows::Forms::Panel^ pnlLine;
	private: System::Windows::Forms::Label^ lblName;
	private: System::Windows::Forms::Label^ lblPhone;
	private: System::Windows::Forms::Label^ lblAddress;
	private: System::Windows::Forms::Label^ lblUsername;
	private: System::Windows::Forms::Label^ lblPassword;
	private: System::Windows::Forms::Label^ lblConfirm;
	private: System::Windows::Forms::TextBox^ txtName;
	private: System::Windows::Forms::TextBox^ txtPhone;
	private: System::Windows::Forms::TextBox^ txtAddress;
	private: System::Windows::Forms::TextBox^ txtUsername;
	private: System::Windows::Forms::TextBox^ txtPassword;
	private: System::Windows::Forms::TextBox^ txtConfirm;
	private: System::Windows::Forms::Button^ btnRegister;
	private: System::Windows::Forms::Button^ btnBack;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(RegisterForm::typeid));
			this->pnlCard = (gcnew System::Windows::Forms::Panel());
			this->lblHeading = (gcnew System::Windows::Forms::Label());
			this->pnlLine = (gcnew System::Windows::Forms::Panel());
			this->lblName = (gcnew System::Windows::Forms::Label());
			this->txtName = (gcnew System::Windows::Forms::TextBox());
			this->lblPhone = (gcnew System::Windows::Forms::Label());
			this->txtPhone = (gcnew System::Windows::Forms::TextBox());
			this->lblAddress = (gcnew System::Windows::Forms::Label());
			this->txtAddress = (gcnew System::Windows::Forms::TextBox());
			this->lblUsername = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->lblConfirm = (gcnew System::Windows::Forms::Label());
			this->txtConfirm = (gcnew System::Windows::Forms::TextBox());
			this->btnRegister = (gcnew System::Windows::Forms::Button());
			this->btnBack = (gcnew System::Windows::Forms::Button());
			this->pnlCard->SuspendLayout();
			this->SuspendLayout();
			// 
			// pnlCard
			// 
			this->pnlCard->Controls->Add(this->lblHeading);
			this->pnlCard->Controls->Add(this->pnlLine);
			this->pnlCard->Controls->Add(this->lblName);
			this->pnlCard->Controls->Add(this->txtName);
			this->pnlCard->Controls->Add(this->lblPhone);
			this->pnlCard->Controls->Add(this->txtPhone);
			this->pnlCard->Controls->Add(this->lblAddress);
			this->pnlCard->Controls->Add(this->txtAddress);
			this->pnlCard->Controls->Add(this->lblUsername);
			this->pnlCard->Controls->Add(this->txtUsername);
			this->pnlCard->Controls->Add(this->lblPassword);
			this->pnlCard->Controls->Add(this->txtPassword);
			this->pnlCard->Controls->Add(this->lblConfirm);
			this->pnlCard->Controls->Add(this->txtConfirm);
			this->pnlCard->Controls->Add(this->btnRegister);
			this->pnlCard->Controls->Add(this->btnBack);
			this->pnlCard->Location = System::Drawing::Point(100, 40);
			this->pnlCard->Name = L"pnlCard";
			this->pnlCard->Size = System::Drawing::Size(560, 625);
			this->pnlCard->TabIndex = 0;
			// 
			// lblHeading
			// 
			this->lblHeading->AutoSize = true;
			this->lblHeading->Location = System::Drawing::Point(35, 22);
			this->lblHeading->Name = L"lblHeading";
			this->lblHeading->Size = System::Drawing::Size(98, 16);
			this->lblHeading->TabIndex = 0;
			this->lblHeading->Text = L"Create Account";
			// 
			// pnlLine
			// 
			this->pnlLine->Location = System::Drawing::Point(35, 82);
			this->pnlLine->Name = L"pnlLine";
			this->pnlLine->Size = System::Drawing::Size(490, 2);
			this->pnlLine->TabIndex = 1;
			// 
			// lblName
			// 
			this->lblName->AutoSize = true;
			this->lblName->Location = System::Drawing::Point(35, 105);
			this->lblName->Name = L"lblName";
			this->lblName->Size = System::Drawing::Size(68, 16);
			this->lblName->TabIndex = 2;
			this->lblName->Text = L"Full Name";
			// 
			// txtName
			// 
			this->txtName->Location = System::Drawing::Point(35, 131);
			this->txtName->Name = L"txtName";
			this->txtName->Size = System::Drawing::Size(490, 22);
			this->txtName->TabIndex = 0;
			// 
			// lblPhone
			// 
			this->lblPhone->AutoSize = true;
			this->lblPhone->Location = System::Drawing::Point(35, 179);
			this->lblPhone->Name = L"lblPhone";
			this->lblPhone->Size = System::Drawing::Size(46, 16);
			this->lblPhone->TabIndex = 3;
			this->lblPhone->Text = L"Phone";
			// 
			// txtPhone
			// 
			this->txtPhone->Location = System::Drawing::Point(35, 205);
			this->txtPhone->Name = L"txtPhone";
			this->txtPhone->Size = System::Drawing::Size(490, 22);
			this->txtPhone->TabIndex = 1;
			// 
			// lblAddress
			// 
			this->lblAddress->AutoSize = true;
			this->lblAddress->Location = System::Drawing::Point(35, 253);
			this->lblAddress->Name = L"lblAddress";
			this->lblAddress->Size = System::Drawing::Size(58, 16);
			this->lblAddress->TabIndex = 4;
			this->lblAddress->Text = L"Address";
			// 
			// txtAddress
			// 
			this->txtAddress->Location = System::Drawing::Point(35, 279);
			this->txtAddress->Name = L"txtAddress";
			this->txtAddress->Size = System::Drawing::Size(490, 22);
			this->txtAddress->TabIndex = 2;
			// 
			// lblUsername
			// 
			this->lblUsername->AutoSize = true;
			this->lblUsername->Location = System::Drawing::Point(35, 327);
			this->lblUsername->Name = L"lblUsername";
			this->lblUsername->Size = System::Drawing::Size(70, 16);
			this->lblUsername->TabIndex = 5;
			this->lblUsername->Text = L"Username";
			// 
			// txtUsername
			// 
			this->txtUsername->Location = System::Drawing::Point(35, 353);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(490, 22);
			this->txtUsername->TabIndex = 3;
			// 
			// lblPassword
			// 
			this->lblPassword->AutoSize = true;
			this->lblPassword->Location = System::Drawing::Point(35, 401);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(67, 16);
			this->lblPassword->TabIndex = 6;
			this->lblPassword->Text = L"Password";
			// 
			// txtPassword
			// 
			this->txtPassword->Location = System::Drawing::Point(35, 427);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(490, 22);
			this->txtPassword->TabIndex = 4;
			this->txtPassword->UseSystemPasswordChar = true;
			// 
			// lblConfirm
			// 
			this->lblConfirm->AutoSize = true;
			this->lblConfirm->Location = System::Drawing::Point(35, 475);
			this->lblConfirm->Name = L"lblConfirm";
			this->lblConfirm->Size = System::Drawing::Size(115, 16);
			this->lblConfirm->TabIndex = 7;
			this->lblConfirm->Text = L"Confirm Password";
			// 
			// txtConfirm
			// 
			this->txtConfirm->Location = System::Drawing::Point(35, 501);
			this->txtConfirm->Name = L"txtConfirm";
			this->txtConfirm->Size = System::Drawing::Size(490, 22);
			this->txtConfirm->TabIndex = 5;
			this->txtConfirm->UseSystemPasswordChar = true;
			// 
			// btnRegister
			// 
			this->btnRegister->Location = System::Drawing::Point(35, 555);
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->Size = System::Drawing::Size(240, 46);
			this->btnRegister->TabIndex = 6;
			this->btnRegister->Text = L"Register";
			this->btnRegister->UseVisualStyleBackColor = false;
			this->btnRegister->Click += gcnew System::EventHandler(this, &RegisterForm::btnRegister_Click);
			// 
			// btnBack
			// 
			this->btnBack->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnBack->Location = System::Drawing::Point(285, 555);
			this->btnBack->Name = L"btnBack";
			this->btnBack->Size = System::Drawing::Size(240, 46);
			this->btnBack->TabIndex = 7;
			this->btnBack->Text = L"Back to Login";
			this->btnBack->UseVisualStyleBackColor = false;
			this->btnBack->Click += gcnew System::EventHandler(this, &RegisterForm::btnBack_Click);
			// 
			// RegisterForm
			// 
			this->AcceptButton = this->btnRegister;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->CancelButton = this->btnBack;
			this->ClientSize = System::Drawing::Size(900, 700);
			this->Controls->Add(this->pnlCard);
			this->Name = L"RegisterForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Plant Sales - Register";
			this->pnlCard->ResumeLayout(false);
			this->pnlCard->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Drawing::Drawing2D::GraphicsPath^ RoundedRect(System::Drawing::Rectangle r, int radius)
	{
		int d = radius * 2;
		System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();
		path->AddArc(r.X, r.Y, d, d, 180, 90);
		path->AddArc(r.Right - d, r.Y, d, d, 270, 90);
		path->AddArc(r.Right - d, r.Bottom - d, d, d, 0, 90);
		path->AddArc(r.X, r.Bottom - d, d, d, 90, 90);
		path->CloseFigure();
		return path;
	}

	private: void Round(Control^ c, int radius)
	{
		c->Region = gcnew System::Drawing::Region(
			RoundedRect(System::Drawing::Rectangle(0, 0, c->Width, c->Height), radius));
	}

	private: void ApplyTheme()
	{
		System::Drawing::Color darkGreen = System::Drawing::Color::FromArgb(47, 79, 53);
		System::Drawing::Color midGreen = System::Drawing::Color::FromArgb(63, 107, 71);
		System::Drawing::Color lightGreen = System::Drawing::Color::FromArgb(221, 232, 213);
		System::Drawing::Color lineGreen = System::Drawing::Color::FromArgb(170, 200, 165);
		System::Drawing::Color cream = System::Drawing::Color::FromArgb(245, 241, 230);
		System::Drawing::Color cardColor = System::Drawing::Color::FromArgb(250, 247, 239);

		this->DoubleBuffered = true;
		this->BackColor = cream;
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;

		// Full screen
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		this->MaximizeBox = true;
		this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
		this->Resize += gcnew System::EventHandler(this, &RegisterForm::RegisterForm_Resize);
		this->Load += gcnew System::EventHandler(this, &RegisterForm::RegisterForm_Resize);

		pnlCard->BackColor = cardColor;
		Round(pnlCard, 24);

		lblHeading->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 24);
		lblHeading->ForeColor = darkGreen;
		pnlLine->BackColor = lineGreen;

		array<Label^>^ labels = gcnew array<Label^> { lblName, lblPhone, lblAddress, lblUsername, lblPassword, lblConfirm };
		for each (Label ^ l in labels)
		{
			l->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
			l->ForeColor = darkGreen;
		}

		array<TextBox^>^ boxes = gcnew array<TextBox^> { txtName, txtPhone, txtAddress, txtUsername, txtPassword, txtConfirm };
		for each (TextBox ^ t in boxes)
		{
			t->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
			t->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		}

		// Register button 
		btnRegister->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnRegister->FlatAppearance->BorderSize = 0;
		btnRegister->FlatAppearance->MouseOverBackColor = darkGreen;
		btnRegister->BackColor = midGreen;
		btnRegister->ForeColor = System::Drawing::Color::White;
		btnRegister->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12);
		btnRegister->Cursor = System::Windows::Forms::Cursors::Hand;
		Round(btnRegister, 14);

		// Back button 
		btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnBack->FlatAppearance->BorderSize = 0;
		btnBack->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(200, 218, 190);
		btnBack->BackColor = lightGreen;
		btnBack->ForeColor = darkGreen;
		btnBack->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12);
		btnBack->Cursor = System::Windows::Forms::Cursors::Hand;
		Round(btnBack, 14);

		CenterLayout();
	}

	private: void CenterLayout()
	{
		int left = (this->ClientSize.Width - pnlCard->Width) / 2;
		int top = (this->ClientSize.Height - pnlCard->Height) / 2;
		if (top < 10) top = 10;
		pnlCard->Left = left;
		pnlCard->Top = top;
	}

	private: System::Void RegisterForm_Resize(System::Object^ sender, System::EventArgs^ e)
	{
		CenterLayout();
	}

		   // ---------- Back to Login ----------
	private: System::Void btnBack_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

		   // ---------- Register ----------
	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ name = txtName->Text->Trim();
		String^ phone = txtPhone->Text->Trim();
		String^ address = txtAddress->Text->Trim();
		String^ user = txtUsername->Text->Trim();
		String^ pass = txtPassword->Text;

		if (name == "" || user == "" || pass == "")
		{
			MessageBox::Show("Full Name, Username and Password are required");
			return;
		}
		if (phone != "" && !System::Text::RegularExpressions::Regex::IsMatch(phone, "^[0-9]{10}$"))
		{
			MessageBox::Show("Phone number must be 10 digits (example: 0771234567)");
			return;
		}
		if (pass->Length < 4)
		{
			MessageBox::Show("Password must be at least 4 characters");
			return;
		}
		if (pass != txtConfirm->Text)
		{
			MessageBox::Show("Passwords do not match");
			return;
		}

		DatabaseHelper^ db = gcnew DatabaseHelper();
		MySqlConnection^ conn = db->GetConnection();
		MySqlTransaction^ tx = nullptr;

		try
		{
			conn->Open();
			tx = conn->BeginTransaction();

			
			MySqlCommand^ c1 = gcnew MySqlCommand(
				"INSERT INTO users (username, password, role) VALUES (@u, @p, 'Customer')", conn, tx);
			c1->Parameters->AddWithValue("@u", user);
			c1->Parameters->AddWithValue("@p", pass);
			c1->ExecuteNonQuery();
			int newUserId = (int)c1->LastInsertedId;

			
			MySqlCommand^ c2 = gcnew MySqlCommand(
				"INSERT INTO customers (username, phone, address, userid) VALUES (@n, @ph, @a, @uid)", conn, tx);
			c2->Parameters->AddWithValue("@n", name);
			c2->Parameters->AddWithValue("@ph", phone);
			c2->Parameters->AddWithValue("@a", address);
			c2->Parameters->AddWithValue("@uid", newUserId);
			c2->ExecuteNonQuery();

			tx->Commit();

			RegisteredUsername = user;
			MessageBox::Show("Registered successfully! You can now log in.");
			this->Close();
		}
		catch (MySqlException^ ex)
		{
			if (tx != nullptr) tx->Rollback();
			if (ex->Number == 1062)
				MessageBox::Show("That username is already taken");
			else
				MessageBox::Show("Error: " + ex->Message);
		}
		catch (Exception^ ex)
		{
			if (tx != nullptr) tx->Rollback();
			MessageBox::Show("Error: " + ex->Message);
		}
		finally
		{
			conn->Close();
		}
	}
	};
}