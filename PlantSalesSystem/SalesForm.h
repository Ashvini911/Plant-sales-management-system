#pragma once
#include "DatabaseHelper.h"
#include "PlantsForm.h"

namespace PlantSalesSystem {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	public ref class SalesForm : public System::Windows::Forms::Form
	{
	public:
		SalesForm(String^ username, String^ userRole)
		{
			InitializeComponent();

			currentUser = username;
			role = userRole;
			db = gcnew DatabaseHelper();

			cGreen = System::Drawing::Color::FromArgb(22, 163, 74);
			cDark = System::Drawing::Color::FromArgb(30, 60, 40);
			cLight = System::Drawing::Color::FromArgb(220, 242, 225);
			cBg = System::Drawing::Color::FromArgb(243, 247, 243);
			cGray = System::Drawing::Color::FromArgb(110, 120, 115);
			cLine = System::Drawing::Color::FromArgb(210, 220, 212);

			BuildUI();
			LoadSales();
		}

	protected:
		~SalesForm()
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
		String^ currentUser;
		String^ role;

		// ---- colors ----
		System::Drawing::Color cGreen;
		System::Drawing::Color cDark;
		System::Drawing::Color cLight;
		System::Drawing::Color cBg;
		System::Drawing::Color cGray;
		System::Drawing::Color cLine;

		// ---- controls ----
		TextBox^ txtSearch;
		DateTimePicker^ dtFrom;
		DateTimePicker^ dtTo;
		DataGridView^ grid;
		Label^ lblResults;
		Label^ lblTotalSales;
		Label^ lblCount;
		Label^ lblItems;
		Button^ btnRefresh;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1300, 760);
			this->Name = L"SalesForm";
			this->Text = L"Plant Sales - Sales";
			this->ResumeLayout(false);
		}
#pragma endregion

		// =====================================================
		//  Helpers (same style as PlantsForm)
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

		// small summary card (title on top, big value below). Returns the value label
		Label^ MakeStatCard(Panel^ parent, String^ title, int x)
		{
			Panel^ card = gcnew Panel();
			card->Location = System::Drawing::Point(x, 8);
			card->Size = System::Drawing::Size(300, 90);
			card->BackColor = System::Drawing::Color::White;

			card->Controls->Add(MakeLabel(title, 16, 8, 270, 26, 10, false, cGray, ContentAlignment::MiddleLeft));
			Label^ value = MakeLabel(L"", 16, 36, 270, 44, 20, true, cGreen, ContentAlignment::MiddleLeft);
			card->Controls->Add(value);

			Round(card, 16);
			parent->Controls->Add(card);
			return value;
		}

		// =====================================================
		//  Build the whole screen in code
		// =====================================================
		void BuildUI()
		{
			this->Text = L"Plant Sales - Sales";
			this->BackColor = cBg;
			this->DoubleBuffered = true;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;

			// ---------- CENTER AREA ----------
			Panel^ centerPanel = gcnew Panel();
			centerPanel->Dock = DockStyle::Fill;

			// ----- table (Fill) -----
			grid = gcnew DataGridView();
			grid->Dock = DockStyle::Fill;
			grid->ReadOnly = true;
			grid->AllowUserToAddRows = false;
			grid->AllowUserToDeleteRows = false;
			grid->AllowUserToResizeRows = false;
			grid->RowHeadersVisible = false;
			grid->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
			grid->MultiSelect = false;
			grid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
			grid->BackgroundColor = System::Drawing::Color::White;
			grid->BorderStyle = System::Windows::Forms::BorderStyle::None;
			grid->CellBorderStyle = DataGridViewCellBorderStyle::SingleHorizontal;
			grid->GridColor = cLine;
			grid->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
			grid->RowTemplate->Height = 38;
			grid->EnableHeadersVisualStyles = false;
			grid->ColumnHeadersHeight = 44;
			grid->ColumnHeadersBorderStyle = DataGridViewHeaderBorderStyle::None;
			grid->ColumnHeadersDefaultCellStyle->BackColor = cLight;
			grid->ColumnHeadersDefaultCellStyle->ForeColor = cDark;
			grid->ColumnHeadersDefaultCellStyle->SelectionBackColor = cLight;
			grid->ColumnHeadersDefaultCellStyle->SelectionForeColor = cDark;
			grid->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 11);
			grid->DefaultCellStyle->ForeColor = cDark;
			grid->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::FromArgb(200, 235, 210);
			grid->DefaultCellStyle->SelectionForeColor = cDark;
			grid->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(248, 252, 248);

			// table holder gives some padding around the grid
			Panel^ gridHolder = gcnew Panel();
			gridHolder->Dock = DockStyle::Fill;
			gridHolder->Padding = System::Windows::Forms::Padding(15, 5, 15, 15);
			gridHolder->Controls->Add(grid);

			// ----- filter bar -----
			Panel^ filterBar = gcnew Panel();
			filterBar->Dock = DockStyle::Top;
			filterBar->Height = 70;

			filterBar->Controls->Add(MakeLabel(L"Search (customer / plant)", 15, 2, 260, 18, 8, false, cGray, ContentAlignment::MiddleLeft));
			txtSearch = gcnew TextBox();
			txtSearch->Location = System::Drawing::Point(15, 24);
			txtSearch->Size = System::Drawing::Size(320, 30);
			txtSearch->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
			txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			txtSearch->TextChanged += gcnew System::EventHandler(this, &SalesForm::Filter_Changed);
			filterBar->Controls->Add(txtSearch);

			filterBar->Controls->Add(MakeLabel(L"From", 355, 2, 100, 18, 8, false, cGray, ContentAlignment::MiddleLeft));
			dtFrom = gcnew DateTimePicker();
			dtFrom->Format = DateTimePickerFormat::Short;
			dtFrom->Location = System::Drawing::Point(355, 24);
			dtFrom->Size = System::Drawing::Size(140, 30);
			dtFrom->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
			dtFrom->Value = DateTime::Today.AddYears(-1);
			dtFrom->ValueChanged += gcnew System::EventHandler(this, &SalesForm::Filter_Changed);
			filterBar->Controls->Add(dtFrom);

			filterBar->Controls->Add(MakeLabel(L"To", 510, 2, 100, 18, 8, false, cGray, ContentAlignment::MiddleLeft));
			dtTo = gcnew DateTimePicker();
			dtTo->Format = DateTimePickerFormat::Short;
			dtTo->Location = System::Drawing::Point(510, 24);
			dtTo->Size = System::Drawing::Size(140, 30);
			dtTo->Font = gcnew System::Drawing::Font(L"Segoe UI", 11);
			dtTo->Value = DateTime::Today;
			dtTo->ValueChanged += gcnew System::EventHandler(this, &SalesForm::Filter_Changed);
			filterBar->Controls->Add(dtTo);

			btnRefresh = MakeButton(L"Refresh", 670, 20, 110, 36);
			btnRefresh->BackColor = cGreen;
			btnRefresh->ForeColor = System::Drawing::Color::White;
			btnRefresh->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(18, 130, 60);
			btnRefresh->Click += gcnew System::EventHandler(this, &SalesForm::Refresh_Click);
			Round(btnRefresh, 10);
			filterBar->Controls->Add(btnRefresh);

			lblResults = MakeLabel(L"", 0, 0, 260, 70, 11, true, cGreen, ContentAlignment::MiddleRight);
			lblResults->Dock = DockStyle::Right;
			filterBar->Controls->Add(lblResults);

			// ----- summary cards -----
			Panel^ statsPanel = gcnew Panel();
			statsPanel->Dock = DockStyle::Top;
			statsPanel->Height = 108;
			statsPanel->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);
			lblTotalSales = MakeStatCard(statsPanel, L"Total Sales (Rs.)", 15);
			lblCount = MakeStatCard(statsPanel, L"Number of Sales", 330);
			lblItems = MakeStatCard(statsPanel, L"Items Sold", 645);

			// ----- header + top bar -----
			Label^ lblSalesTitle = MakeLabel(L"Sales History", 0, 0, 100, 50, 16, true, cDark, ContentAlignment::MiddleLeft);
			lblSalesTitle->Dock = DockStyle::Top;
			lblSalesTitle->Height = 50;
			lblSalesTitle->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);

			Panel^ topBar = gcnew Panel();
			topBar->Dock = DockStyle::Top;
			topBar->Height = 50;
			topBar->Controls->Add(MakeLabel(String::Format("Logged in: {0} ({1})", currentUser, role),
				15, 10, 500, 30, 11, true, cDark, ContentAlignment::MiddleLeft));

			// add order matters for docking: Fill first, then the Top ones (last added = top-most)
			centerPanel->Controls->Add(gridHolder);
			centerPanel->Controls->Add(filterBar);
			centerPanel->Controls->Add(statsPanel);
			centerPanel->Controls->Add(lblSalesTitle);
			centerPanel->Controls->Add(topBar);

			// ---------- SIDEBAR (left) ----------
			Panel^ sidebar = gcnew Panel();
			sidebar->Dock = DockStyle::Left;
			sidebar->Width = 120;
			sidebar->BackColor = System::Drawing::Color::White;

			array<String^>^ names = gcnew array<String^> {
				L"Home", L"Logout" };

			for (int i = 0; i < names->Length; i++)
			{
				Button^ b = MakeButton(names[i], 10, 20 + i * 70, 100, 60);
				bool active = (names[i] == "Sales");
				b->BackColor = active ? cLight : System::Drawing::Color::White;
				b->ForeColor = active ? cGreen : cDark;
				b->FlatAppearance->MouseOverBackColor = cLight;
				b->Click += gcnew System::EventHandler(this, &SalesForm::Sidebar_Click);
				Round(b, 14);
				sidebar->Controls->Add(b);
			}

			// Fill first, edges after
			this->Controls->Add(centerPanel);
			this->Controls->Add(sidebar);
		}

		// =====================================================
		//  Data loading
		// =====================================================
		void LoadSales()
		{
			try
			{
				String^ s = txtSearch->Text->Trim()->Replace("'", "''");
				String^ from = dtFrom->Value.ToString("yyyy-MM-dd");
				String^ to = dtTo->Value.AddDays(1).ToString("yyyy-MM-dd"); // include the whole "To" day

				String^ sql =
					"SELECT s.sales_id AS 'Sale ID', s.sale_date AS 'Date', "
					"c.username AS 'Customer', p.name AS 'Plant', "
					"s.quantity AS 'Qty', s.total AS 'Total (Rs.)' "
					"FROM sales s "
					"JOIN customers c ON s.customerid = c.customerid "
					"JOIN plants p ON s.plantnb = p.plantnb "
					"WHERE s.sale_date >= '" + from + "' AND s.sale_date < '" + to + "' ";

				if (s != "")
					sql += "AND (c.username LIKE '%" + s + "%' OR p.name LIKE '%" + s + "%') ";

				sql += "ORDER BY s.sale_date DESC, s.sales_id DESC";

				DataTable^ t = db->GetData(sql);
				grid->DataSource = t;

				// column look
				if (grid->Columns->Count >= 6)
				{
					grid->Columns[0]->FillWeight = 60;
					grid->Columns[1]->FillWeight = 130;
					grid->Columns[1]->DefaultCellStyle->Format = "yyyy-MM-dd  HH:mm";
					grid->Columns[2]->FillWeight = 150;
					grid->Columns[3]->FillWeight = 150;
					grid->Columns[4]->FillWeight = 50;
					grid->Columns[4]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
					grid->Columns[5]->FillWeight = 100;
					grid->Columns[5]->DefaultCellStyle->Format = "N2";
					grid->Columns[5]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
				}

				// summary
				double sum = 0;
				int items = 0;
				for each (DataRow ^ row in t->Rows)
				{
					sum += Convert::ToDouble(row["Total (Rs.)"]);
					items += Convert::ToInt32(row["Qty"]);
				}
				lblTotalSales->Text = String::Format("Rs. {0:N2}", sum);
				lblCount->Text = t->Rows->Count.ToString();
				lblItems->Text = items.ToString();
				lblResults->Text = String::Format("Showing {0} Results", t->Rows->Count);
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not load sales: " + ex->Message);
			}
		}

		// =====================================================
		//  Event handlers
		// =====================================================
		System::Void Filter_Changed(System::Object^ sender, System::EventArgs^ e)
		{
			LoadSales();
		}

		System::Void Refresh_Click(System::Object^ sender, System::EventArgs^ e)
		{
			LoadSales();
		}

		System::Void Sidebar_Click(System::Object^ sender, System::EventArgs^ e)
		{
			String^ t = safe_cast<Button^>(sender)->Text;

			if (t == "Home")
			{
				this->Close();
			}
			else if (t == "Logout")
			{
				Application::Restart();
			}
		}
	};
}