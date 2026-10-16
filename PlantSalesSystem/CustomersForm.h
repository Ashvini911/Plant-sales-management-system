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

	public ref class CustomersForm : public System::Windows::Forms::Form
	{
	public:
		CustomersForm(String^ username, String^ userRole)
		{
			InitializeComponent();

			currentUser = username;
			role = userRole;
			db = gcnew DatabaseHelper();
			selectedId = 0;

			cGreen = System::Drawing::Color::FromArgb(22, 163, 74);
			cDark = System::Drawing::Color::FromArgb(30, 60, 40);
			cLight = System::Drawing::Color::FromArgb(220, 242, 225);
			cBg = System::Drawing::Color::FromArgb(243, 247, 243);
			cGray = System::Drawing::Color::FromArgb(110, 120, 115);
			cLine = System::Drawing::Color::FromArgb(210, 220, 212);

			BuildUI();
			LoadCustomers();
		}

	protected:
		~CustomersForm()
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
		int selectedId;

		// ---- colors ----
		System::Drawing::Color cGreen;
		System::Drawing::Color cDark;
		System::Drawing::Color cLight;
		System::Drawing::Color cBg;
		System::Drawing::Color cGray;
		System::Drawing::Color cLine;

		// ---- controls ----
		TextBox^ txtSearch;
		DataGridView^ grid;
		Label^ lblResults;
		Label^ lblTotalCust;
		Label^ lblAccounts;
		Label^ lblSpent;
		Label^ lblMode;
		TextBox^ txtName;
		TextBox^ txtPhone;
		TextBox^ txtAddress;
		Button^ btnRefresh;
		Button^ btnAdd;
		Button^ btnUpdate;
		Button^ btnDelete;
		Button^ btnClear;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1300, 760);
			this->Name = L"CustomersForm";
			this->Text = L"Plant Sales - Customers";
			this->ResumeLayout(false);
		}
#pragma endregion

		// =====================================================
		//  Helpers (same style as PlantsForm / SalesForm)
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

		TextBox^ MakeInput(int y)
		{
			TextBox^ t = gcnew TextBox();
			t->Location = System::Drawing::Point(20, y);
			t->Size = System::Drawing::Size(340, 30);
			t->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
			t->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			return t;
		}

		String^ Esc(String^ s)
		{
			return s->Replace("\\", "\\\\")->Replace("'", "''");
		}

		// =====================================================
		//  Build the whole screen in code
		// =====================================================
		void BuildUI()
		{
			this->Text = L"Plant Sales - Customers";
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
			grid->CellClick += gcnew DataGridViewCellEventHandler(this, &CustomersForm::Grid_CellClick);

			Panel^ gridHolder = gcnew Panel();
			gridHolder->Dock = DockStyle::Fill;
			gridHolder->Padding = System::Windows::Forms::Padding(15, 5, 15, 15);
			gridHolder->Controls->Add(grid);

			// ----- filter bar -----
			Panel^ filterBar = gcnew Panel();
			filterBar->Dock = DockStyle::Top;
			filterBar->Height = 70;

			filterBar->Controls->Add(MakeLabel(L"Search (name / phone / address)", 15, 2, 300, 18, 8, false, cGray, ContentAlignment::MiddleLeft));
			txtSearch = gcnew TextBox();
			txtSearch->Location = System::Drawing::Point(15, 24);
			txtSearch->Size = System::Drawing::Size(380, 30);
			txtSearch->Font = gcnew System::Drawing::Font(L"Segoe UI", 12);
			txtSearch->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			txtSearch->TextChanged += gcnew System::EventHandler(this, &CustomersForm::Filter_Changed);
			filterBar->Controls->Add(txtSearch);

			btnRefresh = MakeButton(L"Refresh", 415, 20, 110, 36);
			btnRefresh->BackColor = cGreen;
			btnRefresh->ForeColor = System::Drawing::Color::White;
			btnRefresh->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(18, 130, 60);
			btnRefresh->Click += gcnew System::EventHandler(this, &CustomersForm::Refresh_Click);
			Round(btnRefresh, 10);
			filterBar->Controls->Add(btnRefresh);

			lblResults = MakeLabel(L"", 0, 0, 260, 70, 11, true, cGreen, ContentAlignment::MiddleRight);
			lblResults->Dock = DockStyle::Right;
			filterBar->Controls->Add(lblResults);

			// ----- summary cards -----
			Panel^ statsPanel = gcnew Panel();
			statsPanel->Dock = DockStyle::Top;
			statsPanel->Height = 108;
			lblTotalCust = MakeStatCard(statsPanel, L"Total Customers", 15);
			lblAccounts = MakeStatCard(statsPanel, L"Registered Accounts", 330);
			lblSpent = MakeStatCard(statsPanel, L"Total Spent (Rs.)", 645);

			// ----- header + top bar -----
			Label^ lblTitle = MakeLabel(L"Customers", 0, 0, 100, 50, 16, true, cDark, ContentAlignment::MiddleLeft);
			lblTitle->Dock = DockStyle::Top;
			lblTitle->Height = 50;
			lblTitle->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);

			Panel^ topBar = gcnew Panel();
			topBar->Dock = DockStyle::Top;
			topBar->Height = 50;
			topBar->Controls->Add(MakeLabel(String::Format("Logged in: {0} ({1})", currentUser, role),
				15, 10, 500, 30, 11, true, cDark, ContentAlignment::MiddleLeft));

			// add order matters for docking: Fill first, then the Top ones (last added = top-most)
			centerPanel->Controls->Add(gridHolder);
			centerPanel->Controls->Add(filterBar);
			centerPanel->Controls->Add(statsPanel);
			centerPanel->Controls->Add(lblTitle);
			centerPanel->Controls->Add(topBar);

			// ---------- DETAILS PANEL (right) ----------
			Panel^ detailPanel = gcnew Panel();
			detailPanel->Dock = DockStyle::Right;
			detailPanel->Width = 390;
			detailPanel->BackColor = System::Drawing::Color::White;

			Panel^ headerPanel = gcnew Panel();
			headerPanel->Dock = DockStyle::Top;
			headerPanel->Height = 105;
			headerPanel->BackColor = cLight;
			headerPanel->Controls->Add(MakeLabel(L"Customer Details", 20, 12, 340, 34, 15, true, cDark, ContentAlignment::MiddleLeft));
			lblMode = MakeLabel(L"New customer", 20, 58, 340, 30, 11, true, cGreen, ContentAlignment::MiddleLeft);
			headerPanel->Controls->Add(lblMode);
			detailPanel->Controls->Add(headerPanel);

			detailPanel->Controls->Add(MakeLabel(L"Full Name", 20, 125, 340, 22, 10, false, cGray, ContentAlignment::MiddleLeft));
			txtName = MakeInput(150);
			detailPanel->Controls->Add(txtName);

			detailPanel->Controls->Add(MakeLabel(L"Phone (10 digits)", 20, 200, 340, 22, 10, false, cGray, ContentAlignment::MiddleLeft));
			txtPhone = MakeInput(225);
			detailPanel->Controls->Add(txtPhone);

			detailPanel->Controls->Add(MakeLabel(L"Address", 20, 275, 340, 22, 10, false, cGray, ContentAlignment::MiddleLeft));
			txtAddress = MakeInput(300);
			detailPanel->Controls->Add(txtAddress);

			btnAdd = MakeButton(L"Add Customer", 20, 365, 340, 50);
			btnAdd->BackColor = cGreen;
			btnAdd->ForeColor = System::Drawing::Color::White;
			btnAdd->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12);
			btnAdd->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(18, 130, 60);
			btnAdd->Click += gcnew System::EventHandler(this, &CustomersForm::Add_Click);
			Round(btnAdd, 12);
			detailPanel->Controls->Add(btnAdd);

			btnUpdate = MakeButton(L"Update Selected", 20, 428, 340, 50);
			btnUpdate->BackColor = cLight;
			btnUpdate->ForeColor = cDark;
			btnUpdate->Font = gcnew System::Drawing::Font(L"Segoe UI Semibold", 12);
			btnUpdate->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(200, 230, 208);
			btnUpdate->Click += gcnew System::EventHandler(this, &CustomersForm::Update_Click);
			Round(btnUpdate, 12);
			detailPanel->Controls->Add(btnUpdate);

			btnDelete = MakeButton(L"Delete Selected", 20, 491, 165, 50);
			btnDelete->BackColor = System::Drawing::Color::FromArgb(250, 225, 225);
			btnDelete->ForeColor = System::Drawing::Color::FromArgb(180, 40, 40);
			btnDelete->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(245, 205, 205);
			btnDelete->Click += gcnew System::EventHandler(this, &CustomersForm::Delete_Click);
			Round(btnDelete, 12);
			detailPanel->Controls->Add(btnDelete);

			btnClear = MakeButton(L"Clear", 195, 491, 165, 50);
			btnClear->BackColor = cBg;
			btnClear->FlatAppearance->MouseOverBackColor = cLight;
			btnClear->Click += gcnew System::EventHandler(this, &CustomersForm::Clear_Click);
			Round(btnClear, 12);
			detailPanel->Controls->Add(btnClear);

			// ---------- SIDEBAR (left) ----------
			Panel^ sidebar = gcnew Panel();
			sidebar->Dock = DockStyle::Left;
			sidebar->Width = 120;
			sidebar->BackColor = System::Drawing::Color::White;

			array<String^>^ names = gcnew array<String^> { L"Home", L"Logout" };
			for (int i = 0; i < names->Length; i++)
			{
				Button^ b = MakeButton(names[i], 10, 20 + i * 70, 100, 60);
				b->BackColor = System::Drawing::Color::White;
				b->ForeColor = cDark;
				b->FlatAppearance->MouseOverBackColor = cLight;
				b->Click += gcnew System::EventHandler(this, &CustomersForm::Sidebar_Click);
				Round(b, 14);
				sidebar->Controls->Add(b);
			}

			// Fill first, edges after
			this->Controls->Add(centerPanel);
			this->Controls->Add(detailPanel);
			this->Controls->Add(sidebar);
		}

		// =====================================================
		//  Data loading
		// =====================================================
		void LoadCustomers()
		{
			try
			{
				String^ s = Esc(txtSearch->Text->Trim());

				String^ sql =
					"SELECT c.customerid AS 'ID', c.username AS 'Name', "
					"IFNULL(c.phone,'') AS 'Phone', IFNULL(c.address,'') AS 'Address', "
					"IF(c.userid IS NULL,'No','Yes') AS 'Account', "
					"COUNT(s.sales_id) AS 'Purchases', "
					"IFNULL(SUM(s.total),0) AS 'Total Spent (Rs.)' "
					"FROM customers c "
					"LEFT JOIN sales s ON s.customerid = c.customerid ";

				if (s != "")
					sql += "WHERE (c.username LIKE '%" + s + "%' OR c.phone LIKE '%" + s +
					"%' OR c.address LIKE '%" + s + "%') ";

				sql += "GROUP BY c.customerid, c.username, c.phone, c.address, c.userid "
					"ORDER BY c.username";

				DataTable^ t = db->GetData(sql);
				grid->DataSource = t;

				if (grid->Columns->Count >= 7)
				{
					grid->Columns[0]->FillWeight = 40;
					grid->Columns[1]->FillWeight = 150;
					grid->Columns[2]->FillWeight = 100;
					grid->Columns[3]->FillWeight = 130;
					grid->Columns[4]->FillWeight = 70;
					grid->Columns[5]->FillWeight = 70;
					grid->Columns[5]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
					grid->Columns[6]->FillWeight = 100;
					grid->Columns[6]->DefaultCellStyle->Format = "N2";
					grid->Columns[6]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
				}

				double spent = 0;
				int accounts = 0;
				for each (DataRow ^ row in t->Rows)
				{
					spent += Convert::ToDouble(row["Total Spent (Rs.)"]);
					if (row["Account"]->ToString() == "Yes") accounts++;
				}

				lblTotalCust->Text = t->Rows->Count.ToString();
				lblAccounts->Text = accounts.ToString();
				lblSpent->Text = String::Format("Rs. {0:N2}", spent);
				lblResults->Text = String::Format("Showing {0} Results", t->Rows->Count);
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not load customers: " + ex->Message);
			}
		}

		void ClearForm()
		{
			selectedId = 0;
			txtName->Text = "";
			txtPhone->Text = "";
			txtAddress->Text = "";
			lblMode->Text = "New customer";
			grid->ClearSelection();
		}

		bool ValidateInputs()
		{
			String^ name = txtName->Text->Trim();
			String^ phone = txtPhone->Text->Trim();

			if (name == "")
			{
				MessageBox::Show("Full Name is required");
				return false;
			}
			if (phone != "" && !System::Text::RegularExpressions::Regex::IsMatch(phone, "^[0-9]{10}$"))
			{
				MessageBox::Show("Phone number must be 10 digits (example: 0771234567)");
				return false;
			}
			return true;
		}

		// =====================================================
		//  Event handlers
		// =====================================================
		System::Void Filter_Changed(System::Object^ sender, System::EventArgs^ e)
		{
			LoadCustomers();
		}

		System::Void Refresh_Click(System::Object^ sender, System::EventArgs^ e)
		{
			LoadCustomers();
		}

		System::Void Clear_Click(System::Object^ sender, System::EventArgs^ e)
		{
			ClearForm();
		}

		System::Void Grid_CellClick(System::Object^ sender, DataGridViewCellEventArgs^ e)
		{
			if (e->RowIndex < 0) return;

			DataGridViewRow^ r = grid->Rows[e->RowIndex];
			selectedId = Convert::ToInt32(r->Cells[0]->Value);
			txtName->Text = r->Cells[1]->Value->ToString();
			txtPhone->Text = r->Cells[2]->Value->ToString();
			txtAddress->Text = r->Cells[3]->Value->ToString();
			lblMode->Text = String::Format("Editing customer #{0}", selectedId);
		}

		System::Void Add_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!ValidateInputs()) return;

			String^ phone = txtPhone->Text->Trim();
			String^ address = txtAddress->Text->Trim();

			MySqlConnection^ conn = db->GetConnection();
			try
			{
				conn->Open();
				MySqlCommand^ cmd = gcnew MySqlCommand(
					"INSERT INTO customers (username, phone, address) VALUES (@n, @p, @a)", conn);
				cmd->Parameters->AddWithValue("@n", txtName->Text->Trim());
				if (phone == "") cmd->Parameters->AddWithValue("@p", DBNull::Value);
				else cmd->Parameters->AddWithValue("@p", phone);
				if (address == "") cmd->Parameters->AddWithValue("@a", DBNull::Value);
				else cmd->Parameters->AddWithValue("@a", address);
				cmd->ExecuteNonQuery();

				MessageBox::Show("Customer added successfully");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not add customer: " + ex->Message);
				return;
			}
			finally
			{
				conn->Close();
			}

			ClearForm();
			LoadCustomers();
		}

		System::Void Update_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (selectedId <= 0)
			{
				MessageBox::Show("Please select a customer from the table first");
				return;
			}
			if (!ValidateInputs()) return;

			String^ phone = txtPhone->Text->Trim();
			String^ address = txtAddress->Text->Trim();

			MySqlConnection^ conn = db->GetConnection();
			try
			{
				conn->Open();
				MySqlCommand^ cmd = gcnew MySqlCommand(
					"UPDATE customers SET username=@n, phone=@p, address=@a WHERE customerid=@id", conn);
				cmd->Parameters->AddWithValue("@n", txtName->Text->Trim());
				if (phone == "") cmd->Parameters->AddWithValue("@p", DBNull::Value);
				else cmd->Parameters->AddWithValue("@p", phone);
				if (address == "") cmd->Parameters->AddWithValue("@a", DBNull::Value);
				else cmd->Parameters->AddWithValue("@a", address);
				cmd->Parameters->AddWithValue("@id", selectedId);
				cmd->ExecuteNonQuery();

				MessageBox::Show("Customer updated successfully");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Could not update customer: " + ex->Message);
				return;
			}
			finally
			{
				conn->Close();
			}

			ClearForm();
			LoadCustomers();
		}

		System::Void Delete_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (selectedId <= 0)
			{
				MessageBox::Show("Please select a customer from the table first");
				return;
			}
			if (txtName->Text->Trim() == "Walk-in Customer")
			{
				MessageBox::Show("The Walk-in Customer record cannot be deleted");
				return;
			}

			if (MessageBox::Show("Delete this customer?", "Confirm",
				MessageBoxButtons::YesNo, MessageBoxIcon::Question) != System::Windows::Forms::DialogResult::Yes)
				return;

			MySqlConnection^ conn = db->GetConnection();
			MySqlTransaction^ tx = nullptr;
			try
			{
				conn->Open();

				// customers who already bought something cannot be deleted
				MySqlCommand^ chk = gcnew MySqlCommand(
					"SELECT COUNT(*) FROM sales WHERE customerid=@id", conn);
				chk->Parameters->AddWithValue("@id", selectedId);
				int salesCount = Convert::ToInt32(chk->ExecuteScalar());
				if (salesCount > 0)
				{
					MessageBox::Show("This customer has sales records and cannot be deleted");
					return;
				}

				// find linked login account (if any)
				MySqlCommand^ q = gcnew MySqlCommand(
					"SELECT userid FROM customers WHERE customerid=@id", conn);
				q->Parameters->AddWithValue("@id", selectedId);
				Object^ uid = q->ExecuteScalar();

				tx = conn->BeginTransaction();

				MySqlCommand^ d1 = gcnew MySqlCommand(
					"DELETE FROM customers WHERE customerid=@id", conn, tx);
				d1->Parameters->AddWithValue("@id", selectedId);
				d1->ExecuteNonQuery();

				if (uid != nullptr && uid != DBNull::Value)
				{
					MySqlCommand^ d2 = gcnew MySqlCommand(
						"DELETE FROM users WHERE userid=@u", conn, tx);
					d2->Parameters->AddWithValue("@u", Convert::ToInt32(uid));
					d2->ExecuteNonQuery();
				}

				tx->Commit();
				MessageBox::Show("Customer deleted");
			}
			catch (Exception^ ex)
			{
				if (tx != nullptr) tx->Rollback();
				MessageBox::Show("Could not delete customer: " + ex->Message);
				return;
			}
			finally
			{
				conn->Close();
			}

			ClearForm();
			LoadCustomers();
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