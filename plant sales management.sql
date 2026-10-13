-- Plant Sales Management System : run this whole file in MySQL Workbench
CREATE DATABASE IF NOT EXISTS plant_sales_db;
USE plant_sales_db;

CREATE TABLE IF NOT EXISTS plants (
  plant_id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  category VARCHAR(50) NOT NULL,         
  price DECIMAL(10,2) NOT NULL);

CREATE TABLE IF NOT EXISTS customers (
  customer_id INT AUTO_INCREMENT PRIMARY KEY,
  username VARCHAR(100) NOT NULL,
  phone VARCHAR(20),
  address VARCHAR(200)
);

CREATE TABLE IF NOT EXISTS sales (
  sale_id INT AUTO_INCREMENT PRIMARY KEY,
  customer_id INT NOT NULL,
  plant_id INT NOT NULL,
  quantity INT NOT NULL,
  total DECIMAL(10,2) NOT NULL,
  sale_date DATETIME DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (customer_id) REFERENCES customers(customer_id),
  FOREIGN KEY (plant_id) REFERENCES plants(plant_id)
);


