#pragma once
#include "DatabaseHelper.h"
#include "DashboardForm.h"
#include "RegisterForm.h"

namespace PlantSalesSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			ApplyTheme();
		}

	protected:
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Panel^ pnlCard;
	private: System::Windows::Forms::Label^ lblUsername;
	private: System::Windows::Forms::Label^ lblPassword;
	private: System::Windows::Forms::TextBox^ txtUsername;
	private: System::Windows::Forms::TextBox^ txtPassword;
	private: System::Windows::Forms::Button^ btnLogin;
	private: System::Windows::Forms::Button^ btnRegister;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoginForm::typeid));
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->pnlCard = (gcnew System::Windows::Forms::Panel());
			this->lblUsername = (gcnew System::Windows::Forms::Label());
			this->lblPassword = (gcnew System::Windows::Forms::Label());
			this->txtUsername = (gcnew System::Windows::Forms::TextBox());
			this->txtPassword = (gcnew System::Windows::Forms::TextBox());
			this->btnLogin = (gcnew System::Windows::Forms::Button());
			this->btnRegister = (gcnew System::Windows::Forms::Button());
			this->pnlCard->SuspendLayout();
			this->SuspendLayout();
			this->lblTitle->AutoSize = true;
			this->lblTitle->BackColor = System::Drawing::Color::Transparent;
			this->lblTitle->Location = System::Drawing::Point(70, 30);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(157, 16);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Plant Sales Management";
			this->pnlCard->Controls->Add(this->btnRegister);
			this->pnlCard->Controls->Add(this->lblUsername);
			this->pnlCard->Controls->Add(this->lblPassword);
			this->pnlCard->Controls->Add(this->txtUsername);
			this->pnlCard->Controls->Add(this->txtPassword);
			this->pnlCard->Controls->Add(this->btnLogin);
			this->pnlCard->Location = System::Drawing::Point(70, 90);
			this->pnlCard->Name = L"pnlCard";
			this->pnlCard->Size = System::Drawing::Size(680, 430);
			this->pnlCard->TabIndex = 1;
			this->lblUsername->AutoSize = true;
			this->lblUsername->Location = System::Drawing::Point(60, 66);
			this->lblUsername->Name = L"lblUsername";
			this->lblUsername->Size = System::Drawing::Size(70, 16);
			this->lblUsername->TabIndex = 0;
			this->lblUsername->Text = L"Username";
			this->lblPassword->AutoSize = true;
			this->lblPassword->Location = System::Drawing::Point(60, 146);
			this->lblPassword->Name = L"lblPassword";
			this->lblPassword->Size = System::Drawing::Size(67, 16);
			this->lblPassword->TabIndex = 1;
			this->lblPassword->Text = L"Password";
			this->txtUsername->Location = System::Drawing::Point(220, 60);
			this->txtUsername->Name = L"txtUsername";
			this->txtUsername->Size = System::Drawing::Size(400, 22);
			this->txtUsername->TabIndex = 0;
			this->txtPassword->Location = System::Drawing::Point(220, 140);
			this->txtPassword->Name = L"txtPassword";
			this->txtPassword->Size = System::Drawing::Size(400, 22);
			this->txtPassword->TabIndex = 1;
			this->txtPassword->UseSystemPasswordChar = true;
			this->btnLogin->Location = System::Drawing::Point(200, 220);
			this->btnLogin->Name = L"btnLogin";
			this->btnLogin->Size = System::Drawing::Size(280, 62);
			this->btnLogin->TabIndex = 2;
			this->btnLogin->Text = L"Login";
			this->btnLogin->UseVisualStyleBackColor = false;
			this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
			this->btnRegister->Location = System::Drawing::Point(180, 310);
			this->btnRegister->Name = L"btnRegister";
			this->btnRegister->Size = System::Drawing::Size(320, 62);
			this->btnRegister->TabIndex = 3;
			this->btnRegister->Text = L"New Customer\?";
			this->btnRegister->UseVisualStyleBackColor = false;
			this->btnRegister->Click += gcnew System::EventHandler(this, &LoginForm::btnRegister_Click);
			this->AcceptButton = this->btnLogin;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1000, 640);
			this->Controls->Add(this->pnlCard);
			this->Controls->Add(this->lblTitle);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"LoginForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Plant Sales - Login";
			this->pnlCard->ResumeLayout(false);
			this->pnlCard->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
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

	private: void StyleButton(Button^ b, System::Drawing::Color back, System::Drawing::Color fore, System::Drawing::Color hover)
	{
		b->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		b->FlatAppearance->BorderSize = 0;
		b->FlatAppearance->MouseOverBackColor = hover;
		b->BackColor = back;
		b->ForeColor = fore;
		b->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 15);
		b->Cursor = System::Windows::Forms::Cursors::Hand;
		Round(b, 16);
	}

	private: void ApplyTheme()
	{
		System::Drawing::Color darkGreen = System::Drawing::Color::FromArgb(47, 79, 53);
		System::Drawing::Color midGreen = System::Drawing::Color::FromArgb(63, 107, 71);
		System::Drawing::Color lightGreen = System::Drawing::Color::FromArgb(221, 232, 213);
		System::Drawing::Color hoverGreen = System::Drawing::Color::FromArgb(200, 218, 190);

		this->DoubleBuffered = true;
		this->BackColor = System::Drawing::Color::FromArgb(245, 241, 230);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		this->MaximizeBox = true;
		this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->Resize += gcnew System::EventHandler(this, &LoginForm::LoginForm_Resize);

		lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 26);
		lblTitle->ForeColor = darkGreen;

		pnlCard->BackColor = System::Drawing::Color::FromArgb(250, 247, 239);
		Round(pnlCard, 28);

		array<Label^>^ labels = gcnew array<Label^> { lblUsername, lblPassword };
		for each (Label ^ l in labels)
		{
			l->Font = gcnew System::Drawing::Font(L"Segoe UI", 15);
			l->ForeColor = darkGreen;
		}

		array<TextBox^>^ boxes = gcnew array<TextBox^> { txtUsername, txtPassword };
		for each (TextBox ^ t in boxes)
		{
			t->Font = gcnew System::Drawing::Font(L"Segoe UI", 15);
			t->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		}

		StyleButton(btnLogin, midGreen, System::Drawing::Color::White, darkGreen);
		StyleButton(btnRegister, lightGreen, darkGreen, hoverGreen);

		CenterLayout();
	}

	private: void CenterLayout()
	{
		int w = this->ClientSize.Width;
		int h = this->ClientSize.Height;
		int gap = 25;
		int top = (h - (lblTitle->Height + gap + pnlCard->Height)) / 2;
		if (top < 10) top = 10;

		lblTitle->Left = (w - lblTitle->Width) / 2;
		lblTitle->Top = top;
		pnlCard->Left = (w - pnlCard->Width) / 2;
		pnlCard->Top = lblTitle->Bottom + gap;
	}

	private: System::Void LoginForm_Resize(System::Object^ sender, System::EventArgs^ e)
	{
		CenterLayout();
	}

	private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (txtUsername->Text->Trim() == "" || txtPassword->Text == "")
		{
			MessageBox::Show("Please enter username and password");
			return;
		}

		try
		{
			DatabaseHelper^ db = gcnew DatabaseHelper();
			MySqlConnection^ conn = db->GetConnection();
			conn->Open();

			MySqlCommand^ cmd = gcnew MySqlCommand(
				"SELECT role FROM users WHERE username=@u AND password=@p", conn);
			cmd->Parameters->AddWithValue("@u", txtUsername->Text->Trim());
			cmd->Parameters->AddWithValue("@p", txtPassword->Text);

			Object^ result = cmd->ExecuteScalar();
			conn->Close();

			if (result != nullptr)
			{
				DashboardForm^ dash = gcnew DashboardForm(
					txtUsername->Text->Trim(), result->ToString());
				this->Hide();
				System::Windows::Forms::DialogResult r = dash->ShowDialog();

				if (r == System::Windows::Forms::DialogResult::Retry)
				{
					txtUsername->Text = "";
					txtPassword->Text = "";
					txtUsername->Focus();
					this->Show();
				}
				else
				{
					this->Close();
				}
			}
			else
			{
				MessageBox::Show("Invalid username or password");
			}
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Error: " + ex->Message);
		}
	}

	private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e)
	{
		RegisterForm^ reg = gcnew RegisterForm();
		reg->ShowDialog();
	}
	};
}