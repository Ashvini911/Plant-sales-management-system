#pragma once
#include "PlantsForm.h"
#include "SalesForm.h"
#include "CustomersForm.h"

namespace PlantSalesSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class DashboardForm : public System::Windows::Forms::Form
	{
	public:
		DashboardForm(String^ username, String^ role)
		{
			InitializeComponent();
			ApplyTheme();

			currentUser = username;
			currentRole = role;
			limited = (role == "Customer");

			lblUser->Text = "Logged in as " + username + " | Role: " + role;

			if (limited)
			{
				btnSales->Visible = false;
				btnCustomers->Visible = false;
			}

			LayoutCard();
		}

	protected:
		~DashboardForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Panel^ pnlCard;
	private: System::Windows::Forms::Label^ lblWelcome;
	private: System::Windows::Forms::Label^ lblUser;
	private: System::Windows::Forms::Panel^ pnlLine;
	private: System::Windows::Forms::Button^ btnPlants;
	private: System::Windows::Forms::Button^ btnSales;
	private: System::Windows::Forms::Button^ btnCustomers;
	private: System::Windows::Forms::Button^ btnBack;
	private: System::Windows::Forms::Button^ activeButton;

	private: String^ currentUser;
	private: String^ currentRole;
	private: bool limited;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(DashboardForm::typeid));
			this->pnlCard = (gcnew System::Windows::Forms::Panel());
			this->lblWelcome = (gcnew System::Windows::Forms::Label());
			this->lblUser = (gcnew System::Windows::Forms::Label());
			this->pnlLine = (gcnew System::Windows::Forms::Panel());
			this->btnPlants = (gcnew System::Windows::Forms::Button());
			this->btnSales = (gcnew System::Windows::Forms::Button());
			this->btnCustomers = (gcnew System::Windows::Forms::Button());
			this->pnlCard->SuspendLayout();
			this->SuspendLayout();
			this->pnlCard->Controls->Add(this->lblWelcome);
			this->pnlCard->Controls->Add(this->lblUser);
			this->pnlCard->Controls->Add(this->pnlLine);
			this->pnlCard->Controls->Add(this->btnPlants);
			this->pnlCard->Controls->Add(this->btnSales);
			this->pnlCard->Controls->Add(this->btnCustomers);
			this->pnlCard->Location = System::Drawing::Point(97, 75);
			this->pnlCard->Name = L"pnlCard";
			this->pnlCard->Size = System::Drawing::Size(920, 400);
			this->pnlCard->TabIndex = 0;
			this->lblWelcome->AutoSize = true;
			this->lblWelcome->Location = System::Drawing::Point(45, 26);
			this->lblWelcome->Name = L"lblWelcome";
			this->lblWelcome->Size = System::Drawing::Size(68, 16);
			this->lblWelcome->TabIndex = 0;
			this->lblWelcome->Text = L"Welcome!";
			this->lblUser->AutoSize = true;
			this->lblUser->Location = System::Drawing::Point(48, 88);
			this->lblUser->Name = L"lblUser";
			this->lblUser->Size = System::Drawing::Size(67, 16);
			this->lblUser->TabIndex = 1;
			this->lblUser->Text = L"Logged in";
			this->pnlLine->Location = System::Drawing::Point(45, 128);
			this->pnlLine->Name = L"pnlLine";
			this->pnlLine->Size = System::Drawing::Size(830, 2);
			this->pnlLine->TabIndex = 2;
			this->btnPlants->Location = System::Drawing::Point(45, 195);
			this->btnPlants->Name = L"btnPlants";
			this->btnPlants->Size = System::Drawing::Size(260, 140);
			this->btnPlants->TabIndex = 3;
			this->btnPlants->Text = L"Plants";
			this->btnPlants->UseVisualStyleBackColor = false;
			this->btnSales->Location = System::Drawing::Point(335, 195);
			this->btnSales->Name = L"btnSales";
			this->btnSales->Size = System::Drawing::Size(260, 140);
			this->btnSales->TabIndex = 4;
			this->btnSales->Text = L"Sales";
			this->btnSales->UseVisualStyleBackColor = false;
			this->btnCustomers->Location = System::Drawing::Point(625, 195);
			this->btnCustomers->Name = L"btnCustomers";
			this->btnCustomers->Size = System::Drawing::Size(260, 140);
			this->btnCustomers->TabIndex = 5;
			this->btnCustomers->Text = L"Customers";
			this->btnCustomers->UseVisualStyleBackColor = false;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1100, 580);
			this->Controls->Add(this->pnlCard);
			this->Name = L"DashboardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Plant Sales - Dashboard";
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
		System::Drawing::Color lineGreen = System::Drawing::Color::FromArgb(170, 200, 165);
		System::Drawing::Color lightGreen = System::Drawing::Color::FromArgb(221, 232, 213);

		this->DoubleBuffered = true;
		this->BackColor = System::Drawing::Color::FromArgb(245, 241, 230);
		this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;

		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		this->MaximizeBox = true;
		this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
		this->Resize += gcnew System::EventHandler(this, &DashboardForm::DashboardForm_Resize);
		this->Load += gcnew System::EventHandler(this, &DashboardForm::DashboardForm_Resize);

		pnlCard->BackColor = System::Drawing::Color::FromArgb(238, 244, 232);
		Round(pnlCard, 28);

		lblWelcome->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 30);
		lblWelcome->ForeColor = darkGreen;
		lblUser->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
		lblUser->ForeColor = midGreen;
		pnlLine->BackColor = lineGreen;

		array<Button^>^ navButtons = gcnew array<Button^> { btnPlants, btnSales, btnCustomers };
		for each (Button ^ b in navButtons)
		{
			b->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			b->FlatAppearance->BorderSize = 0;
			b->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 18);
			b->Cursor = System::Windows::Forms::Cursors::Hand;
			Round(b, 18);
			b->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &DashboardForm::OutlineButton_Paint);
			b->Click += gcnew System::EventHandler(this, &DashboardForm::NavButton_Click);
		}

		btnBack = gcnew Button();
		btnBack->Text = L"Back to Login";
		btnBack->Size = System::Drawing::Size(200, 46);
		btnBack->Top = 28;
		btnBack->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		btnBack->FlatAppearance->BorderSize = 0;
		btnBack->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(200, 218, 190);
		btnBack->UseVisualStyleBackColor = false;
		btnBack->BackColor = lightGreen;
		btnBack->ForeColor = darkGreen;
		btnBack->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12);
		btnBack->Cursor = System::Windows::Forms::Cursors::Hand;
		Round(btnBack, 14);
		btnBack->Click += gcnew System::EventHandler(this, &DashboardForm::BackButton_Click);
		pnlCard->Controls->Add(btnBack);

		SetActive(nullptr);
		LayoutCard();
		CenterLayout();
	}

		   // Centers the visible nav buttons inside the card with equal gaps
	private: void LayoutCard()
	{
		int w = pnlCard->Width;

		array<Button^>^ shown;
		if (limited)
			shown = gcnew array<Button^> { btnPlants };
		else
			shown = gcnew array<Button^> { btnPlants, btnSales, btnCustomers };

		int gap = 30;
		int bw = btnPlants->Width;
		int totalW = shown->Length * bw + (shown->Length - 1) * gap;
		int x = (w - totalW) / 2;

		for each (Button ^ b in shown)
		{
			b->Left = x;
			b->Top = 195;
			x += bw + gap;
		}

		pnlLine->Left = 45;
		pnlLine->Width = w - 90;
		btnBack->Left = w - btnBack->Width - 45;
	}

	private: void SetActive(Button^ active)
	{
		System::Drawing::Color darkGreen = System::Drawing::Color::FromArgb(47, 79, 53);
		System::Drawing::Color midGreen = System::Drawing::Color::FromArgb(63, 107, 71);
		System::Drawing::Color btnLight = System::Drawing::Color::FromArgb(252, 253, 250);
		System::Drawing::Color btnHover = System::Drawing::Color::FromArgb(226, 238, 220);

		activeButton = active;

		array<Button^>^ navButtons = gcnew array<Button^> { btnPlants, btnSales, btnCustomers };
		for each (Button ^ b in navButtons)
		{
			if (b == active)
			{
				b->BackColor = midGreen;
				b->ForeColor = System::Drawing::Color::White;
				b->FlatAppearance->MouseOverBackColor = darkGreen;
			}
			else
			{
				b->BackColor = btnLight;
				b->ForeColor = darkGreen;
				b->FlatAppearance->MouseOverBackColor = btnHover;
			}
			b->Invalidate();
		}
	}

	private: System::Void OutlineButton_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		Button^ b = safe_cast<Button^>(sender);
		if (b == activeButton) return;

		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;
		System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(110, 150, 115), 2);
		e->Graphics->DrawPath(pen,
			RoundedRect(System::Drawing::Rectangle(1, 1, b->Width - 3, b->Height - 3), 18));
	}

		   // ===== Plants / Sales / Customers open here =====
	private: System::Void NavButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Button^ clicked = safe_cast<Button^>(sender);
		SetActive(clicked);

		if (clicked == btnPlants)
		{
			PlantsForm^ f = gcnew PlantsForm(currentUser, currentRole);
			this->Hide();
			f->ShowDialog();
			this->Show();
			SetActive(nullptr);
		}
		else if (clicked == btnSales)
		{
			SalesForm^ f = gcnew SalesForm(currentUser, currentRole);
			this->Hide();
			f->ShowDialog();
			this->Show();
			SetActive(nullptr);
		}
		else if (clicked == btnCustomers)
		{
			CustomersForm^ f = gcnew CustomersForm(currentUser, currentRole);
			this->Hide();
			f->ShowDialog();
			this->Show();
			SetActive(nullptr);
		}
	}

	private: System::Void BackButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->DialogResult = System::Windows::Forms::DialogResult::Retry;
	}

	private: void CenterLayout()
	{
		pnlCard->Left = (this->ClientSize.Width - pnlCard->Width) / 2;
		pnlCard->Top = (this->ClientSize.Height - pnlCard->Height) / 2;
	}

	private: System::Void DashboardForm_Resize(System::Object^ sender, System::EventArgs^ e)
	{
		CenterLayout();
	}
	};
}