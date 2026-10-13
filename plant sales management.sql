-- Plant Sales Management System : run this whole file in MySQL Workbench
CREATE DATABASE IF NOT EXISTS plant_sales_db;
USE plant_sales_db;

CREATE TABLE IF NOT EXISTS plants (
  plant_id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  category VARCHAR(50) NOT NULL,         
  price DECIMAL(10,2) NOT NULL,
  stock int NOT NULL;

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

INSERT INTO customers (name, phone, address)
VALUES
('Nimal Perera', '0711234567', 'Avissawella'),
('Kamal Silva', '0772345678', 'Colombo'),
('Amali Fernando', '0753456789', 'Kegalle'),
('Saman Kumara', '0764567890', 'Ratnapura'),
('Dilani Jayasuriya', '0725678901', 'Kandy');


INSERT INTO plants (name, category, price, stock)
VALUES   
('Rose', 'Flowers', 500.00, 50),
('Jasmine', 'Flowers', 350.00, 40),
('Orchid', 'Flowers', 1200.00, 20),
('Sunflower', 'Flowers', 450.00, 35),
('Lily', 'Flowers', 650.00, 25),

('Money Plant', 'Indoor', 450.00, 40),
('Aloe Vera', 'Indoor', 350.00, 30),
('Snake Plant', 'Indoor', 750.00, 20),
('Peace Lily', 'Indoor', 850.00, 15),
('Spider Plant', 'Indoor', 400.00, 25),

('Mint', 'Herbal Plants', 150.00, 40),
('Curry Leaves', 'Herbal Plants', 200.00, 35),
('Basil', 'Herbal Plants', 180.00, 30),
('Gotu Kola', 'Herbal Plants', 120.00, 50),
('Lemongrass', 'Herbal Plants', 160.00, 30),

('Watering Can', 'Garden Supplies and Accessories', 850.00, 15),
('Plant Spray Bottle', 'Garden Supplies and Accessories', 300.00, 25),
('Clay Pot', 'Garden Supplies and Accessories', 350.00, 40),
('Decorative Pot', 'Garden Supplies and Accessories', 900.00, 20),
('Hanging Basket', 'Garden Supplies and Accessories', 650.00, 15),
('Plant Labels', 'Garden Supplies and Accessories', 120.00, 50);


