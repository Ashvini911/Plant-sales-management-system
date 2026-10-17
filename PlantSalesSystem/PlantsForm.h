#pragma once
#include "DatabaseHelper.h"

namespace PlantSalesSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	// =========================================================
	//  BillForm  -  professional bill / invoice window
	// =========================================================
	public ref class BillForm : public System::Windows::Forms::Form
	{
	public:
		BillForm(String^ customer, String^ payment, String^ cashier,
			array<String^>^ names, array<int>^ qtys, array<double>^ prices,
			double subTotal, double taxAmt, double discAmt, double totalAmt)
		{
			cGreen = System::Drawing::Color::FromArgb(22, 163, 74);
			cDark = System::Drawing::Color::FromArgb(30, 60, 40);
			cLight = System::Drawing::Color::FromArgb(220, 242, 225);
			cBg = System::Drawing::Color::FromArgb(243, 247, 243);
			cGray = System::Drawing::Color::FromArgb(110, 120, 115);
			cLine = System::Drawing::Color::FromArgb(210, 220, 212);

			custName = customer;
			payMode = payment;
			cashierName = cashier;
			itemNames = names;
			itemQtys = qtys;
			itemPrices = prices;
			sub = subTotal;
			tax = taxAmt;
			disc = discAmt;
			total = totalAmt;

			DateTime now = DateTime::Now;
			billNo = "INV-" + now.ToString("yyyyMMddHHmmss");
			billDate = now.ToString("yyyy-MM-dd  HH:mm");

			BuildUI();
		}

	private:
		// ---- data ----
		String^ custName;
		String^ payMode;
		String^ cashierName;
		String^ billNo;
		String^ billDate;
		array<String^>^ itemNames;
		array<int>^ itemQtys;
		array<double>^ itemPrices;
		double sub;
		double tax;
		double disc;
		double total;

		// ---- colors ----
		System::Drawing::Color cGreen;
		System::Drawing::Color cDark;
		System::Drawing::Color cLight;
		System::Drawing::Color cBg;
		System::Drawing::Color cGray;
		System::Drawing::Color cLine;

		// ---- helpers ----
		System::Drawing::Drawing2D::GraphicsPath^ RoundedRect(System::Drawing::Rectangle r, int radius)
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

		void Round(Control^ c, int radius)
		{
			c->Region = gcnew System::Drawing::Region(
				RoundedRect(System::Drawing::Rectangle(0, 0, c->Width, c->Height), radius));
		}

		Label^ MakeLabel(String^ text, int x, int y, int w, int h, float size, bool bold,
			System::Drawing::Color color, ContentAlignment align)
		{
			Label^ l = gcnew Label();
			l->Text = text;
			l->Location = System::Drawing::Point(x, y);
			l->Size = System::Drawing::Size(w, h);
			l->Font = gcnew System::Drawing::Font(L"Segoe UI", size,
				bold ? System::Drawing::FontStyle::Bold : System::Drawing::FontStyle::Regular);
			l->ForeColor = color;
			l->TextAlign = align;
			l->BackColor = System::Drawing::Color::Transparent;
			return l;
		}

		Button^ MakeButton(String^ text, int x, int y, int w, int h)
		{
			Button^ b = gcnew Button();
			b->Text = text;
			b->Location = System::Drawing::Point(x, y);
			b->Size = System::Drawing::Size(w, h);
			b->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			b->FlatAppearance->BorderSize = 0;
			b->UseVisualStyleBackColor = false;
			b->UseMnemonic = false;
			b->BackColor = System::Drawing::Color::White;
			b->ForeColor = cDark;
			b->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11);
			b->Cursor = System::Windows::Forms::Cursors::Hand;
			return b;
		}

		Panel^ MakeLine(int x, int y, int w)
		{
			Panel^ p = gcnew Panel();
			p->Location = System::Drawing::Point(x, y);
			p->Size = System::Drawing::Size(w, 1);
			p->BackColor = cLine;
			return p;
		}

		void AddInfoRow(Panel^ parent, String^ title, String^ value, int y)
		{
			parent->Controls->Add(MakeLabel(title, 25, y, 130, 26, 10, false, cGray, ContentAlignment::MiddleLeft));
			parent->Controls->Add(MakeLabel(value, 155, y, 300, 26, 10, true, cDark, ContentAlignment::MiddleRight));
		}

		void AddTotalRow(Panel^ parent, String^ title, String^ value, int y,
			System::Drawing::Color color)
		{
			parent->Controls->Add(MakeLabel(title, 25, y, 200, 28, 11, false, color, ContentAlignment::MiddleLeft));
			parent->Controls->Add(MakeLabel(value, 225, y, 230, 28, 11, true, color, ContentAlignment::MiddleRight));
		}

		// ---- build the bill window ----
		void BuildUI()
		{
			this->Text = L"Plant Sales - Bill";
			this->ClientSize = System::Drawing::Size(480, 720);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->BackColor = System::Drawing::Color::White;
			this->DoubleBuffered = true;

			// ----- header (green band) -----
			Panel^ header = gcnew Panel();
			header->Dock = DockStyle::Top;
			header->Height = 105;
			header->BackColor = cGreen;
			header->Controls->Add(MakeLabel(L"PLANT SALES", 0, 14, 480, 46, 22, true,
				System::Drawing::Color::White, ContentAlignment::MiddleCenter));
			header->Controls->Add(MakeLabel(L"SALES INVOICE", 0, 62, 480, 28, 11, false,
				System::Drawing::Color::FromArgb(220, 242, 225), ContentAlignment::MiddleCenter));

			// ----- bill info -----
			Panel^ info = gcnew Panel();
			info->Dock = DockStyle::Top;
			info->Height = 150;
			info->BackColor = System::Drawing::Color::White;
			AddInfoRow(info, L"Bill No", billNo, 10);
			AddInfoRow(info, L"Date", billDate, 36);
			AddInfoRow(info, L"Customer", custName, 62);
			AddInfoRow(info, L"Cashier", cashierName, 88);
			AddInfoRow(info, L"Payment", payMode, 114);
			info->Controls->Add(MakeLine(25, 147, 430));

			// ----- items table -----
			DataGridView^ grid = gcnew DataGridView();
			grid->Dock = DockStyle::Fill;
			grid->ReadOnly = true;
			grid->AllowUserToAddRows = false;
			grid->AllowUserToDeleteRows = false;
			grid->AllowUserToResizeRows = false;
			grid->AllowUserToResizeColumns = false;
			grid->RowHeadersVisible = false;
			grid->MultiSelect = false;
			grid->ScrollBars = ScrollBars::Vertical;
			grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			grid->BackgroundColor = System::Drawing::Color::White;
			grid->BorderStyle = System::Windows::Forms::BorderStyle::None;
			grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			grid->GridColor = cLine;
			grid->Font = gcnew System::Drawing::Font(L"Segoe UI", 10);
			grid->RowTemplate->Height = 34;
			grid->EnableHeadersVisualStyles = false;
			grid->ColumnHeadersHeight = 38;
			grid->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			grid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
			grid->ColumnHeadersDefaultCellStyle->BackColor = cLight;
			grid->ColumnHeadersDefaultCellStyle->ForeColor = cDark;
			grid->ColumnHeadersDefaultCellStyle->SelectionBackColor = cLight;
			grid->ColumnHeadersDefaultCellStyle->SelectionForeColor = cDark;
			grid->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10);
			grid->DefaultCellStyle->ForeColor = cDark;
			grid->DefaultCellStyle->BackColor = System::Drawing::Color::White;
			grid->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::White;
			grid->DefaultCellStyle->SelectionForeColor = cDark;

			grid->Columns->Add("item", "Item");
			grid->Columns->Add("qty", "Qty");
			grid->Columns->Add("price", "Price");
			grid->Columns->Add("amount", "Amount");

			grid->Columns[0]->FillWeight = 42;
			grid->Columns[1]->FillWeight = 12;
			grid->Columns[2]->FillWeight = 22;
			grid->Columns[3]->FillWeight = 24;
			for (int c = 1; c < 4; c++)
			{
				grid->Columns[c]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
				grid->Columns[c]->HeaderCell->Style->Alignment = DataGridViewContentAlignment::MiddleRight;
			}
			grid->Columns[1]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
			grid->Columns[1]->HeaderCell->Style->Alignment = DataGridViewContentAlignment::MiddleCenter;

			for (int i = 0; i < itemNames->Length; i++)
			{
				array<Object^>^ vals = gcnew array<Object^> {
					itemNames[i],
						itemQtys[i].ToString(),
						String::Format("{0:N2}", itemPrices[i]),
						String::Format("{0:N2}", itemPrices[i] * itemQtys[i]) };
				grid->Rows->Add(vals);
			}
			grid->ClearSelection();

			Panel^ gridHolder = gcnew Panel();
			gridHolder->Dock = DockStyle::Fill;
			gridHolder->Padding = System::Windows::Forms::Padding(20, 6, 20, 6);
			gridHolder->BackColor = System::Drawing::Color::White;
			gridHolder->Controls->Add(grid);

			// ----- totals -----
			Panel^ totals = gcnew Panel();
			totals->Dock = DockStyle::Bottom;
			totals->Height = 215;
			totals->BackColor = System::Drawing::Color::White;
			totals->Controls->Add(MakeLine(25, 0, 430));
			AddTotalRow(totals, L"Sub Total", String::Format("Rs. {0:N2}", sub), 10, cDark);
			AddTotalRow(totals, L"Tax (10%)", String::Format("Rs. {0:N2}", tax), 40, cDark);
			AddTotalRow(totals, L"Discount (5%)", String::Format("- Rs. {0:N2}", disc), 70, cGreen);

			Panel^ totalBand = gcnew Panel();
			totalBand->Location = System::Drawing::Point(20, 108);
			totalBand->Size = System::Drawing::Size(440, 54);
			totalBand->BackColor = cLight;
			totalBand->Controls->Add(MakeLabel(L"TOTAL", 14, 0, 120, 54, 14, true, cDark, ContentAlignment::MiddleLeft));
			totalBand->Controls->Add(MakeLabel(String::Format("Rs. {0:N2}", total), 140, 0, 285, 54, 18, true,
				cGreen, ContentAlignment::MiddleRight));
			Round(totalBand, 12);
			totals->Controls->Add(totalBand);

			totals->Controls->Add(MakeLabel(L"Thank you for shopping with us!", 0, 172, 480, 26, 11, true,
				cDark, ContentAlignment::MiddleCenter));

			// ----- buttons -----
			Panel^ buttons = gcnew Panel();
			buttons->Dock = DockStyle::Bottom;
			buttons->Height = 80;
			buttons->BackColor = cBg;

			Button^ btnPrint = MakeButton(L"Print", 20, 15, 210, 50);
			btnPrint->BackColor = cGreen;
			btnPrint->ForeColor = System::Drawing::Color::White;
			btnPrint->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(18, 130, 60);
			btnPrint->Click += gcnew System::EventHandler(this, &BillForm::Print_Click);
			Round(btnPrint, 12);
			buttons->Controls->Add(btnPrint);

			Button^ btnClose = MakeButton(L"Close", 250, 15, 210, 50);
			btnClose->BackColor = System::Drawing::Color::White;
			btnClose->FlatAppearance->MouseOverBackColor = cLight;
			btnClose->Click += gcnew System::EventHandler(this, &BillForm::Close_Click);
			Round(btnClose, 12);
			buttons->Controls->Add(btnClose);

			this->CancelButton = btnClose;

			// Fill first, then Bottom ones, then Top ones (last added = outermost)
			this->Controls->Add(gridHolder);
			this->Controls->Add(totals);
			this->Controls->Add(buttons);
			this->Controls->Add(info);
			this->Controls->Add(header);
		}

		// ---- events ----
		System::Void Close_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Close();
		}

		System::Void Print_Click(System::Object^ sender, System::EventArgs^ e)
		{
			try
			{
				System::Drawing::Printing::PrintDocument^ pd = gcnew System::Drawing::Printing::PrintDocument();
				pd->DocumentName = billNo;
				pd->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &BillForm::PrintPage);

				System::Windows::Forms::PrintDialog^ dlg = gcnew System::Windows::Forms::PrintDialog();
				dlg->Document = pd;
				if (dlg->ShowDialog() == System::Windows::Forms::DialogResult::OK)
					pd->Print();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not print: " + ex->Message);
			}
		}

		// draws "left ........ right" on one line, returns next y
		float DrawRow(System::Drawing::Graphics^ g, String^ left, String^ right,
			System::Drawing::Font^ f, float x, float y, float w)
		{
			g->DrawString(left, f, System::Drawing::Brushes::Black, x, y);
			System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
			sf->Alignment = System::Drawing::StringAlignment::Far;
			g->DrawString(right, f, System::Drawing::Brushes::Black,
				System::Drawing::RectangleF(x, y, w, f->GetHeight(g) + 2), sf);
			return y + f->GetHeight(g) + 4;
		}

		System::Void PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e)
		{
			System::Drawing::Graphics^ g = e->Graphics;
			System::Drawing::Font^ fTitle = gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold);
			System::Drawing::Font^ fBold = gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
			System::Drawing::Font^ fNorm = gcnew System::Drawing::Font(L"Segoe UI", 10);
			System::Drawing::Font^ fSmall = gcnew System::Drawing::Font(L"Segoe UI", 9);
			System::Drawing::Pen^ pen = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 1);

			float x = 60;
			float w = 380;
			float y = 60;

			System::Drawing::StringFormat^ center = gcnew System::Drawing::StringFormat();
			center->Alignment = System::Drawing::StringAlignment::Center;

			g->DrawString(L"PLANT SALES", fTitle, System::Drawing::Brushes::Black,
				System::Drawing::RectangleF(x, y, w, 36), center);
			y += 38;
			g->DrawString(L"SALES INVOICE", fNorm, System::Drawing::Brushes::Black,
				System::Drawing::RectangleF(x, y, w, 22), center);
			y += 32;

			g->DrawLine(pen, x, y, x + w, y);
			y += 8;
			y = DrawRow(g, L"Bill No", billNo, fNorm, x, y, w);
			y = DrawRow(g, L"Date", billDate, fNorm, x, y, w);
			y = DrawRow(g, L"Customer", custName, fNorm, x, y, w);
			y = DrawRow(g, L"Cashier", cashierName, fNorm, x, y, w);
			y = DrawRow(g, L"Payment", payMode, fNorm, x, y, w);
			y += 4;
			g->DrawLine(pen, x, y, x + w, y);
			y += 8;

			y = DrawRow(g, L"Item", L"Amount", fBold, x, y, w);
			g->DrawLine(pen, x, y, x + w, y);
			y += 6;

			for (int i = 0; i < itemNames->Length; i++)
			{
				y = DrawRow(g, itemNames[i],
					String::Format("{0:N2}", itemPrices[i] * itemQtys[i]), fNorm, x, y, w);
				g->DrawString(String::Format("   {0} x Rs. {1:N2}", itemQtys[i], itemPrices[i]),
					fSmall, System::Drawing::Brushes::Gray, x, y - 2);
				y += fSmall->GetHeight(g) + 4;
			}

			y += 2;
			g->DrawLine(pen, x, y, x + w, y);
			y += 8;

			y = DrawRow(g, L"Sub Total", String::Format("Rs. {0:N2}", sub), fNorm, x, y, w);
			y = DrawRow(g, L"Tax (10%)", String::Format("Rs. {0:N2}", tax), fNorm, x, y, w);
			y = DrawRow(g, L"Discount (5%)", String::Format("- Rs. {0:N2}", disc), fNorm, x, y, w);
			g->DrawLine(pen, x, y, x + w, y);
			y += 6;
			y = DrawRow(g, L"TOTAL", String::Format("Rs. {0:N2}", total), fBold, x, y, w);
			y += 14;

			g->DrawString(L"Thank you for shopping with us!", fNorm, System::Drawing::Brushes::Black,
				System::Drawing::RectangleF(x, y, w, 22), center);

			e->HasMorePages = false;
		}
	};

	// =========================================================
	//  PlantsForm
	// =========================================================
	public ref class PlantsForm : public System::Windows::Forms::Form
	{
	public:
		PlantsForm(String^ username, String^ userRole)
		{
			InitializeComponent();

			currentUser = username;
			role = userRole;
			db = gcnew DatabaseHelper();
			order = gcnew Dictionary<int, int>();
			currentCategory = "Flowers";
			paymentMode = "Cash";
			ownCustomerId = 0;
			ownCustomerName = "";

			cGreen = System::Drawing::Color::FromArgb(22, 163, 74);
			cDark = System::Drawing::Color::FromArgb(30, 60, 40);
			cLight = System::Drawing::Color::FromArgb(220, 242, 225);
			cBg = System::Drawing::Color::FromArgb(243, 247, 243);
			cGray = System::Drawing::Color::FromArgb(110, 120, 115);
			cLine = System::Drawing::Color::FromArgb(210, 220, 212);

			BuildUI();
			LoadCustomers();
			LoadPlants();
			RenderPlants();
			RefreshOrder();
		}

	protected:
		~PlantsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

		// ---- data ----
		DatabaseHelper^ db;
		DataTable^ plantsTable;
		Dictionary<int, int>^ order;
		String^ currentUser;
		String^ role;
		String^ currentCategory;
		String^ paymentMode;
		int ownCustomerId;
		String^ ownCustomerName;

		literal double TAX_RATE = 0.10;
		literal double DISC_RATE = 0.05;

		// ---- colors ----
		System::Drawing::Color cGreen;
		System::Drawing::Color cDark;
		System::Drawing::Color cLight;
		System::Drawing::Color cBg;
		System::Drawing::Color cGray;
		System::Drawing::Color cLine;

		// ---- controls ----
		FlowLayoutPanel^ flpCats;
		FlowLayoutPanel^ flpPlants;
		FlowLayoutPanel^ flpOrder;
		TextBox^ txtSearch;
		Label^ lblResults;
		Label^ lblSub;
		Label^ lblTax;
		Label^ lblDisc;
		Label^ lblTotal;
		Label^ lblCustomer;
		ComboBox^ cmbCustomer;
		array<Button^>^ catButtons;
		Button^ btnCash;
		Button^ btnCard;
		Button^ btnOnline;
		Button^ btnCheckout;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1300, 760);
			this->Name = L"PlantsForm";
			this->Text = L"Plant Sales - Plants";
			this->ResumeLayout(false);
		}
#pragma endregion

		// =====================================================
		//  Helpers
		// =====================================================
		System::Drawing::Drawing2D::GraphicsPath^ RoundedRect(System::Drawing::Rectangle r, int radius)
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

		void Round(Control^ c, int radius)
		{
			c->Region = gcnew System::Drawing::Region(
				RoundedRect(System::Drawing::Rectangle(0, 0, c->Width, c->Height), radius));
		}

		Label^ MakeLabel(String^ text, int x, int y, int w, int h, float size, bool bold,
			System::Drawing::Color color, ContentAlignment align)
		{
			Label^ l = gcnew Label();
			l->Text = text;
			l->Location = System::Drawing::Point(x, y);
			l->Size = System::Drawing::Size(w, h);
			l->Font = gcnew System::Drawing::Font(L"Segoe UI", size,
				bold ? System::Drawing::FontStyle::Bold : System::Drawing::FontStyle::Regular);
			l->ForeColor = color;
			l->TextAlign = align;
			l->BackColor = System::Drawing::Color::Transparent;
			return l;
		}

		Button^ MakeButton(String^ text, int x, int y, int w, int h)
		{
			Button^ b = gcnew Button();
			b->Text = text;
			b->Location = System::Drawing::Point(x, y);
			b->Size = System::Drawing::Size(w, h);
			b->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			b->FlatAppearance->BorderSize = 0;
			b->UseVisualStyleBackColor = false;
			b->UseMnemonic = false;
			b->BackColor = System::Drawing::Color::White;
			b->ForeColor = cDark;
			b->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 10);
			b->Cursor = System::Windows::Forms::Cursors::Hand;
			return b;
		}

		DataRow^ FindRow(int id)
		{
			array<DataRow^>^ r = plantsTable->Select("plantnb = " + id.ToString());
			if (r->Length > 0) return r[0];
			return nullptr;
		}

		int GetQty(int id)
		{
			if (order->ContainsKey(id)) return order[id];
			return 0;
		}

		double ComputeSubtotal()
		{
			double sub = 0;
			for each (KeyValuePair<int, int> kv in order)
			{
				DataRow^ row = FindRow(kv.Key);
				if (row != nullptr) sub += Convert::ToDouble(row["price"]) * kv.Value;
			}
			return sub;
		}

		
		System::Drawing::Image^ LoadPlantImage(String^ plantName)
		{
			try
			{
				String^ folder = System::IO::Path::Combine(Application::StartupPath, "images");
				array<String^>^ exts = gcnew array<String^> { ".jpg", ".jpeg", ".png" };

				for each (String ^ ext in exts)
				{
					String^ path = System::IO::Path::Combine(folder, plantName + ext);
					if (System::IO::File::Exists(path))
					{
						
						array<Byte>^ bytes = System::IO::File::ReadAllBytes(path);
						System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(bytes);
						return System::Drawing::Image::FromStream(ms);
					}
				}
			}
			catch (Exception^)
			{
			}
			return nullptr;
		}

		// =====================================================
		//  Build the whole screen in code
		// =====================================================
		void BuildUI()
		{
			this->Text = L"Plant Sales - Plants";
			this->BackColor = cBg;
			this->DoubleBuffered = true;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;

			// ---------- CENTER AREA ----------
			Panel^ centerPanel = gcnew Panel();
			centerPanel->Dock = DockStyle::Fill;

			flpPlants = gcnew FlowLayoutPanel();
			flpPlants->Dock = DockStyle::Fill;
			flpPlants->AutoScroll = true;
			flpPlants->BackColor = cBg;
			flpPlants->Padding = System::Windows::Forms::Padding(10);

			// "Choose Plants" header + results count
			Panel^ hdr2 = gcnew Panel();
			hdr2->Dock = DockStyle::Top;
			hdr2->Height = 50;

			Label^ lblPlantsTitle = MakeLabel(L"Choose Plants", 0, 0, 100, 50, 16, true, cDark, ContentAlignment::MiddleLeft);
			lblPlantsTitle->Dock = DockStyle::Fill;
			lblPlantsTitle->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);

			lblResults = MakeLabel(L"", 0, 0, 260, 50, 11, true, cGreen, ContentAlignment::MiddleRight);
			lblResults->Dock = DockStyle::Right;

			hdr2->Controls->Add(lblPlantsTitle);
			hdr2->Controls->Add(lblResults);

			// categories row
			flpCats = gcnew FlowLayoutPanel();
			flpCats->Dock = DockStyle::Top;
			flpCats->Height = 105;
			flpCats->Padding = System::Windows::Forms::Padding(10, 0, 0, 0);
			flpCats->BackColor = cBg;

			array<String^>^ catTitles = gcnew array<String^> {
				L"Flower\r\nBeautiful Blooms",
					L"Herbals\r\nNatural & Healthy",
					L"Indoor\r\nFor Your Home",
					L"Garden Supplies\r\n& Accessories" };
			array<String^>^ catValues = gcnew array<String^> {
				L"Flowers", L"Herbal", L"Indoor", L"Garden Supplies and Accessories" };

			catButtons = gcnew array<Button^>(4);
			for (int i = 0; i < 4; i++)
			{
				Button^ b = MakeButton(catTitles[i], 0, 0, 225, 85);
				b->Tag = catValues[i];
				b->TextAlign = ContentAlignment::MiddleLeft;
				b->Padding = System::Windows::Forms::Padding(14, 0, 0, 0);
				b->Margin = System::Windows::Forms::Padding(6);
				b->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11);
				b->Click += gcnew System::EventHandler(this, &PlantsForm::Category_Click);
				catButtons[i] = b;
				flpCats->Controls->Add(b);
			}
			SelectCategory(catButtons[0]);

			// "Choose Categories" header
			Label^ lblCatsHeader = MakeLabel(L"Choose Categories", 0, 0, 100, 50, 16, true, cDark, ContentAlignment::MiddleLeft);
			lblCatsHeader->Dock = DockStyle::Top;
			lblCatsHeader->Height = 50;
			lblCatsHeader->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);

			// top bar (search + user)
			Panel^ topBar = gcnew Panel();
			topBar->Dock = DockStyle::Top;
			topBar->Height = 70;

			txtSearch = gcnew TextBox();
			txtSearch->Location = System::Drawing::Point(15, 18);
			txtSearch->Size = System::Drawing::Size(480, 30);
			txtSearch->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
			txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			txtSearch->TextChanged += gcnew System::EventHandler(this, &PlantsForm::Search_Changed);

			Label^ lblHint = MakeLabel(L"Search for plants", 15, -2, 200, 18, 8, false, cGray, ContentAlignment::MiddleLeft);

			Label^ lblUser = MakeLabel(String::Format("Logged in: {0} ({1})", currentUser, role),
				515, 20, 380, 30, 11, true, cDark, ContentAlignment::MiddleLeft);

			topBar->Controls->Add(txtSearch);
			topBar->Controls->Add(lblHint);
			topBar->Controls->Add(lblUser);

			// add order matters for docking: Fill first, then the Top ones (last added = top-most)
			centerPanel->Controls->Add(flpPlants);
			centerPanel->Controls->Add(hdr2);
			centerPanel->Controls->Add(flpCats);
			centerPanel->Controls->Add(lblCatsHeader);
			centerPanel->Controls->Add(topBar);

			// ---------- ORDER PANEL (right) ----------
			Panel^ orderPanel = gcnew Panel();
			orderPanel->Dock = DockStyle::Right;
			orderPanel->Width = 390;
			orderPanel->BackColor = System::Drawing::Color::White;

			flpOrder = gcnew FlowLayoutPanel();
			flpOrder->Dock = DockStyle::Fill;
			flpOrder->FlowDirection = FlowDirection::TopDown;
			flpOrder->WrapContents = false;
			flpOrder->AutoScroll = true;
			flpOrder->BackColor = System::Drawing::Color::White;

			Panel^ headerPanel = gcnew Panel();
			headerPanel->Dock = DockStyle::Top;
			headerPanel->Height = 105;
			headerPanel->BackColor = cLight;
			headerPanel->Controls->Add(MakeLabel(L"Current Order", 20, 12, 340, 34, 15, true, cDark, ContentAlignment::MiddleLeft));

			cmbCustomer = gcnew ComboBox();
			cmbCustomer->Location = System::Drawing::Point(20, 58);
			cmbCustomer->Size = System::Drawing::Size(340, 30);
			cmbCustomer->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
			cmbCustomer->DropDownStyle = ComboBoxStyle::DropDownList;

			lblCustomer = MakeLabel(L"", 20, 58, 340, 30, 11, true, cDark, ContentAlignment::MiddleLeft);
			lblCustomer->Visible = false;

			headerPanel->Controls->Add(cmbCustomer);
			headerPanel->Controls->Add(lblCustomer);

			Panel^ bottomPanel = gcnew Panel();
			bottomPanel->Dock = DockStyle::Bottom;
			bottomPanel->Height = 335;
			bottomPanel->BackColor = System::Drawing::Color::White;

			bottomPanel->Controls->Add(MakeLabel(L"Sub Total", 20, 8, 180, 28, 11, false, cDark, ContentAlignment::MiddleLeft));
			lblSub = MakeLabel(L"", 200, 8, 170, 28, 11, true, cDark, ContentAlignment::MiddleRight);
			bottomPanel->Controls->Add(lblSub);

			bottomPanel->Controls->Add(MakeLabel(L"Tax (10%)", 20, 38, 180, 28, 11, false, cDark, ContentAlignment::MiddleLeft));
			lblTax = MakeLabel(L"", 200, 38, 170, 28, 11, true, cDark, ContentAlignment::MiddleRight);
			bottomPanel->Controls->Add(lblTax);

			bottomPanel->Controls->Add(MakeLabel(L"Discount (5%)", 20, 68, 180, 28, 11, false, cGreen, ContentAlignment::MiddleLeft));
			lblDisc = MakeLabel(L"", 200, 68, 170, 28, 11, true, cGreen, ContentAlignment::MiddleRight);
			bottomPanel->Controls->Add(lblDisc);

			Panel^ totalPanel = gcnew Panel();
			totalPanel->Location = System::Drawing::Point(15, 102);
			totalPanel->Size = System::Drawing::Size(360, 48);
			totalPanel->BackColor = cLight;
			totalPanel->Controls->Add(MakeLabel(L"Total", 12, 0, 100, 48, 14, true, cDark, ContentAlignment::MiddleLeft));
			lblTotal = MakeLabel(L"", 120, 0, 230, 48, 15, true, cDark, ContentAlignment::MiddleRight);
			totalPanel->Controls->Add(lblTotal);
			bottomPanel->Controls->Add(totalPanel);

			bottomPanel->Controls->Add(MakeLabel(L"Payment Mode", 20, 165, 300, 28, 12, true, cDark, ContentAlignment::MiddleLeft));

			btnCash = MakeButton(L"Cash", 15, 198, 112, 52);
			btnCard = MakeButton(L"Card", 139, 198, 112, 52);
			btnOnline = MakeButton(L"Online", 263, 198, 112, 52);
			btnCash->Click += gcnew System::EventHandler(this, &PlantsForm::Payment_Click);
			btnCard->Click += gcnew System::EventHandler(this, &PlantsForm::Payment_Click);
			btnOnline->Click += gcnew System::EventHandler(this, &PlantsForm::Payment_Click);
			bottomPanel->Controls->Add(btnCash);
			bottomPanel->Controls->Add(btnCard);
			bottomPanel->Controls->Add(btnOnline);
			SelectPayment(btnCash);

			btnCheckout = MakeButton(L"Print Bill", 15, 266, 360, 54);
			btnCheckout->BackColor = cGreen;
			btnCheckout->ForeColor = System::Drawing::Color::White;
			btnCheckout->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 13);
			btnCheckout->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(18, 130, 60);
			btnCheckout->Click += gcnew System::EventHandler(this, &PlantsForm::Checkout_Click);
			Round(btnCheckout, 12);
			bottomPanel->Controls->Add(btnCheckout);

			orderPanel->Controls->Add(flpOrder);
			orderPanel->Controls->Add(bottomPanel);
			orderPanel->Controls->Add(headerPanel);

			// ---------- SIDEBAR (left) ----------
			Panel^ sidebar = gcnew Panel();
			sidebar->Dock = DockStyle::Left;
			sidebar->Width = 120;
			sidebar->BackColor = System::Drawing::Color::White;

			array<String^>^ names = gcnew array<String^> { L"Home", L"Logout" };
			for (int i = 0; i < names->Length; i++)
			{
				Button^ b = MakeButton(names[i], 10, 20 + i * 70, 100, 60);
				bool active = (names[i] == "Plants");
				b->BackColor = active ? cLight : System::Drawing::Color::White;
				b->ForeColor = active ? cGreen : cDark;
				b->FlatAppearance->MouseOverBackColor = cLight;
				b->Click += gcnew System::EventHandler(this, &PlantsForm::Sidebar_Click);
				Round(b, 14);
				sidebar->Controls->Add(b);
			}

			// Fill first, edges after
			this->Controls->Add(centerPanel);
			this->Controls->Add(orderPanel);
			this->Controls->Add(sidebar);
		}

		// =====================================================
		//  Data loading
		// =====================================================
		void LoadPlants()
		{
			try
			{
				plantsTable = db->GetData("SELECT plantnb, name, category, price, quantity FROM plants ORDER BY name");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not load plants: " + ex->Message);
				plantsTable = gcnew DataTable();
			}
		}

		void LoadCustomers()
		{
			try
			{
				if (role == "Customer")
				{
					cmbCustomer->Visible = false;
					lblCustomer->Visible = true;

					MySqlConnection^ conn = db->GetConnection();
					conn->Open();
					MySqlCommand^ cmd = gcnew MySqlCommand(
						"SELECT c.customerid, c.username FROM customers c "
						"JOIN users u ON c.userid = u.userid WHERE u.username = @u", conn);
					cmd->Parameters->AddWithValue("@u", currentUser);
					MySqlDataReader^ rd = cmd->ExecuteReader();
					if (rd->Read())
					{
						ownCustomerId = rd->GetInt32(0);
						ownCustomerName = rd->GetString(1);
					}
					rd->Close();
					conn->Close();

					lblCustomer->Text = "Customer: " + ownCustomerName;
				}
				else
				{
					DataTable^ t = db->GetData("SELECT customerid, username FROM customers ORDER BY username");
					cmbCustomer->DataSource = t;
					cmbCustomer->DisplayMember = "username";
					cmbCustomer->ValueMember = "customerid";
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not load customers: " + ex->Message);
			}
		}

		// =====================================================
		//  Plants grid
		// =====================================================
		Panel^ MakeCard(DataRow^ row)
		{
			int id = Convert::ToInt32(row["plantnb"]);
			String^ name = row["name"]->ToString();
			double price = Convert::ToDouble(row["price"]);
			int stock = Convert::ToInt32(row["quantity"]);

			Panel^ card = gcnew Panel();
			card->Size = System::Drawing::Size(240, 240);
			card->BackColor = System::Drawing::Color::White;
			card->Margin = System::Windows::Forms::Padding(8);
			card->Tag = id;

			// ---- plant photo  ----
			Panel^ pic = gcnew Panel();
			pic->Location = System::Drawing::Point(0, 0);
			pic->Size = System::Drawing::Size(240, 115);
			pic->BackColor = cLight;

			System::Drawing::Image^ img = LoadPlantImage(name);
			if (img != nullptr)
			{
				pic->BackgroundImage = img;
				pic->BackgroundImageLayout = ImageLayout::Zoom;
			}
			else
			{
				String^ letter = (name->Length > 0) ? name->Substring(0, 1)->ToUpper() : "?";
				pic->Controls->Add(MakeLabel(letter, 0, 0, 240, 115, 40, true, cGreen, ContentAlignment::MiddleCenter));
			}
			card->Controls->Add(pic);

			card->Controls->Add(MakeLabel(name, 14, 124, 215, 26, 12, true, cDark, ContentAlignment::MiddleLeft));

			if (stock > 0)
				card->Controls->Add(MakeLabel(String::Format("In stock: {0}", stock), 14, 150, 215, 22, 9, false, cGray, ContentAlignment::MiddleLeft));
			else
				card->Controls->Add(MakeLabel(L"Out of stock", 14, 150, 215, 22, 9, true,
					System::Drawing::Color::FromArgb(200, 60, 60), ContentAlignment::MiddleLeft));

			card->Controls->Add(MakeLabel(String::Format("Rs. {0:N2}", price), 14, 188, 120, 32, 12, true, cGreen, ContentAlignment::MiddleLeft));

			Button^ btnMinus = MakeButton(L"-", 138, 190, 30, 30);
			btnMinus->BackColor = cBg;
			btnMinus->Tag = id;
			btnMinus->Click += gcnew System::EventHandler(this, &PlantsForm::PlusMinus_Click);
			card->Controls->Add(btnMinus);

			Label^ lblQty = MakeLabel(GetQty(id).ToString(), 170, 190, 28, 30, 11, true, cDark, ContentAlignment::MiddleCenter);
			lblQty->Name = "lblQty";
			card->Controls->Add(lblQty);

			Button^ btnPlus = MakeButton(L"+", 200, 190, 30, 30);
			btnPlus->BackColor = cGreen;
			btnPlus->ForeColor = System::Drawing::Color::White;
			btnPlus->Tag = id;
			btnPlus->Enabled = (stock > 0);
			btnPlus->Click += gcnew System::EventHandler(this, &PlantsForm::PlusMinus_Click);
			card->Controls->Add(btnPlus);

			Round(card, 16);
			return card;
		}

		void RenderPlants()
		{
			String^ filter;
			String^ s = txtSearch->Text->Trim()->Replace("'", "''");
			if (s != "")
				filter = "name LIKE '%" + s + "%'";
			else
				filter = "category = '" + currentCategory + "'";

			array<DataRow^>^ rows = plantsTable->Select(filter, "name ASC");

			flpPlants->SuspendLayout();
			flpPlants->Controls->Clear();
			for each (DataRow ^ row in rows)
			{
				flpPlants->Controls->Add(MakeCard(row));
			}
			flpPlants->ResumeLayout();

			lblResults->Text = String::Format("Showing {0} Results", rows->Length);
		}

		void SyncCardQty(int id)
		{
			for each (Control ^ c in flpPlants->Controls)
			{
				if (c->Tag != nullptr && safe_cast<int>(c->Tag) == id)
				{
					array<Control^>^ f = c->Controls->Find("lblQty", false);
					if (f->Length > 0) f[0]->Text = GetQty(id).ToString();
				}
			}
		}

		void ChangeQty(int id, int delta)
		{
			DataRow^ row = FindRow(id);
			if (row == nullptr) return;

			int stock = Convert::ToInt32(row["quantity"]);
			int nq = GetQty(id) + delta;
			if (nq < 0) nq = 0;
			if (nq > stock)
			{
				MessageBox::Show(String::Format("Only {0} in stock", stock));
				return;
			}
			if (nq == 0) order->Remove(id);
			else order[id] = nq;
		}

		// =====================================================
		//  Current order panel
		// =====================================================
		void RefreshOrder()
		{
			flpOrder->SuspendLayout();
			flpOrder->Controls->Clear();

			double sub = 0;
			for each (KeyValuePair<int, int> kv in order)
			{
				DataRow^ row = FindRow(kv.Key);
				if (row == nullptr) continue;

				double price = Convert::ToDouble(row["price"]);
				double line = price * kv.Value;
				sub += line;

				Panel^ p = gcnew Panel();
				p->Size = System::Drawing::Size(340, 72);
				p->BackColor = cBg;
				p->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);

				p->Controls->Add(MakeLabel(row["name"]->ToString(), 10, 6, 250, 26, 11, true, cDark, ContentAlignment::MiddleLeft));
				p->Controls->Add(MakeLabel(String::Format("{0} x Rs. {1:N2}", kv.Value, price), 10, 38, 160, 24, 10, false, cGray, ContentAlignment::MiddleLeft));
				p->Controls->Add(MakeLabel(String::Format("Rs. {0:N2}", line), 170, 38, 160, 24, 11, true, cGreen, ContentAlignment::MiddleRight));

				Button^ del = MakeButton(L"X", 290, 6, 38, 28);
				del->BackColor = System::Drawing::Color::FromArgb(250, 225, 225);
				del->ForeColor = System::Drawing::Color::FromArgb(180, 40, 40);
				del->Tag = kv.Key;
				del->Click += gcnew System::EventHandler(this, &PlantsForm::RemoveItem_Click);
				p->Controls->Add(del);

				flpOrder->Controls->Add(p);
			}
			flpOrder->ResumeLayout();

			double tax = sub * TAX_RATE;
			double disc = sub * DISC_RATE;
			double total = sub + tax - disc;

			lblSub->Text = String::Format("Rs. {0:N2}", sub);
			lblTax->Text = String::Format("Rs. {0:N2}", tax);
			lblDisc->Text = String::Format("- Rs. {0:N2}", disc);
			lblTotal->Text = String::Format("Rs. {0:N2}", total);
		}

		// =====================================================
		//  Selection styles
		// =====================================================
		void SelectCategory(Button^ sel)
		{
			for each (Button ^ b in catButtons)
			{
				bool on = (b == sel);
				b->BackColor = on ? cLight : System::Drawing::Color::White;
				b->FlatAppearance->BorderColor = on ? cGreen : cLine;
				b->FlatAppearance->BorderSize = on ? 2 : 1;
			}
			currentCategory = sel->Tag->ToString();
		}

		void SelectPayment(Button^ sel)
		{
			array<Button^>^ all = gcnew array<Button^> { btnCash, btnCard, btnOnline };
			for each (Button ^ b in all)
			{
				bool on = (b == sel);
				b->BackColor = on ? cLight : System::Drawing::Color::White;
				b->FlatAppearance->BorderColor = on ? cGreen : cLine;
				b->FlatAppearance->BorderSize = on ? 2 : 1;
			}
			paymentMode = sel->Text;
		}

		// =====================================================
		//  Event handlers
		// =====================================================
		System::Void Category_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SelectCategory(safe_cast<Button^>(sender));
			if (txtSearch->Text != "") txtSearch->Text = "";
			RenderPlants();
		}

		System::Void Search_Changed(System::Object^ sender, System::EventArgs^ e)
		{
			RenderPlants();
		}

		System::Void Payment_Click(System::Object^ sender, System::EventArgs^ e)
		{
			SelectPayment(safe_cast<Button^>(sender));
		}

		System::Void PlusMinus_Click(System::Object^ sender, System::EventArgs^ e)
		{
			Button^ b = safe_cast<Button^>(sender);
			int id = safe_cast<int>(b->Tag);
			int delta = (b->Text == "+") ? 1 : -1;

			ChangeQty(id, delta);
			SyncCardQty(id);
			RefreshOrder();
		}

		System::Void RemoveItem_Click(System::Object^ sender, System::EventArgs^ e)
		{
			Button^ b = safe_cast<Button^>(sender);
			int id = safe_cast<int>(b->Tag);
			order->Remove(id);
			SyncCardQty(id);
			RefreshOrder();
		}

		System::Void Sidebar_Click(System::Object^ sender, System::EventArgs^ e)
		{
			String^ t = safe_cast<Button^>(sender)->Text;
			if (t == "Home") this->Close();
			else if (t == "Logout") Application::Restart();
			else if (t != "Plants") MessageBox::Show(t + " page is coming soon");
		}

		int GetCustomerId()
		{
			if (role == "Customer") return ownCustomerId;
			if (cmbCustomer->SelectedValue == nullptr) return -1;
			return Convert::ToInt32(cmbCustomer->SelectedValue);
		}

		System::Void Checkout_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (order->Count == 0)
			{
				MessageBox::Show("Please add at least one plant to the order");
				return;
			}

			int customerId = GetCustomerId();
			if (customerId <= 0)
			{
				MessageBox::Show("Please select a customer first");
				return;
			}

			String^ custName = (role == "Customer") ? ownCustomerName : cmbCustomer->Text;

			double sub = ComputeSubtotal();
			double tax = sub * TAX_RATE;
			double disc = sub * DISC_RATE;
			double total = sub + tax - disc;
			double factor = 1.0 + TAX_RATE - DISC_RATE;

			// items for the bill window
			List<String^>^ billNames = gcnew List<String^>();
			List<int>^ billQtys = gcnew List<int>();
			List<double>^ billPrices = gcnew List<double>();

			MySqlConnection^ conn = db->GetConnection();
			MySqlTransaction^ tx = nullptr;
			bool saved = false;

			try
			{
				conn->Open();
				tx = conn->BeginTransaction();

				for each (KeyValuePair<int, int> kv in order)
				{
					DataRow^ row = FindRow(kv.Key);
					String^ name = row["name"]->ToString();
					double price = Convert::ToDouble(row["price"]);
					double lineTotal = Math::Round(price * kv.Value * factor, 2);

					MySqlCommand^ c1 = gcnew MySqlCommand(
						"INSERT INTO sales (customerid, plantnb, quantity, total) VALUES (@c, @p, @q, @t)", conn, tx);
					c1->Parameters->AddWithValue("@c", customerId);
					c1->Parameters->AddWithValue("@p", kv.Key);
					c1->Parameters->AddWithValue("@q", kv.Value);
					c1->Parameters->AddWithValue("@t", lineTotal);
					c1->ExecuteNonQuery();

					MySqlCommand^ c2 = gcnew MySqlCommand(
						"UPDATE plants SET quantity = quantity - @q WHERE plantnb = @p AND quantity >= @q", conn, tx);
					c2->Parameters->AddWithValue("@q", kv.Value);
					c2->Parameters->AddWithValue("@p", kv.Key);
					if (c2->ExecuteNonQuery() != 1)
						throw gcnew Exception("Not enough stock for " + name);

					billNames->Add(name);
					billQtys->Add(kv.Value);
					billPrices->Add(price);
				}

				tx->Commit();
				saved = true;
			}
			catch (Exception^ ex)
			{
				if (tx != nullptr) tx->Rollback();
				MessageBox::Show("Could not complete the sale: " + ex->Message);
			}
			finally
			{
				conn->Close();
			}

			if (!saved) return;

			// ---- show the professional bill window (centered) ----
			BillForm^ bf = gcnew BillForm(custName, paymentMode, currentUser,
				billNames->ToArray(), billQtys->ToArray(), billPrices->ToArray(),
				sub, tax, disc, total);
			bf->ShowDialog(this);

			order->Clear();
			LoadPlants();
			RenderPlants();
			RefreshOrder();
		}
	};
}