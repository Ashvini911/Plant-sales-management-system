#pragma once

using namespace System;
using namespace System::Data;
using namespace MySql::Data::MySqlClient;

public ref class DatabaseHelper
{
private:
    String^ connectionString;

public:
    DatabaseHelper()
    {
        connectionString =
            "server=localhost;port=3306;database=plant_sales_db;uid=root;pwd=root;";
    }

    MySqlConnection^ GetConnection()
    {
        return gcnew MySqlConnection(connectionString);
    }

    // SELECT 
    DataTable^ GetData(String^ query)
    {
        MySqlConnection^ conn = GetConnection();
        MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(query, conn);
        DataTable^ table = gcnew DataTable();
        adapter->Fill(table);
        return table;
    }

    // INSERT, UPDATE, DELETE
    int Execute(MySqlCommand^ cmd)
    {
        MySqlConnection^ conn = GetConnection();
        cmd->Connection = conn;
        conn->Open();
        int rows = cmd->ExecuteNonQuery();
        conn->Close();
        return rows;
    }
};;