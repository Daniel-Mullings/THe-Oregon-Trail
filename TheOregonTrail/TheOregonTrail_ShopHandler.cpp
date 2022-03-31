#include "TheOregonTrail_ShopHandler.h"

//defines variables that will be used in the program
float quantity = 1.0;
float balance = 10.0;

//recieves the data from the database to be outputted to the command window
int Shop_Handler::DisplayCallback(void* NotUsed, int total, char** value, char** column)
{
	int counter = 0;

	//loops through the data that has been pulled from the SELECT query and displays the data
	for (int i = 0; i < total; i++) {
		std::cout << value[i];
		counter++;

		//if statement to make the data more readable in the command window
		if (counter == 1)
		{
			std::cout << ")  ";
		}
		else if (counter == 2 || counter == 3)
		{
			std::cout << "  ";
		}
	}
	std::cout << std::endl;

	return 0;
}

//recieves the quantity from the database to be used in the rest of the program
int Shop_Handler::ItemCallback(void* NotUsed, int total, char** value, char** column)
{
	//sets the quantity to the value pulled from the table
	quantity = atof(value[0]);

	return 0;
}


//inserts a row into the SQL table, given the values
void Shop_Handler::InsertRow(const char* file, std::string id, std::string item, std::string quantity, std::string price)
{
	//connects to the sql database
	sqlite3* db;
	char* errMsg = 0;

	//opens the database
	sqlite3_open(file, &db);

	//sql query to insert the data using the given values
	std::string sql = "INSERT INTO Stock ('ID', 'ITEM', 'PRICE', 'QUANTITY') VALUES (" + id + ", '" + item + "', " + quantity + ", " + price + ");";
	//executes the query
	sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

	//closes the database
	sqlite3_close(db);
}

//creates the SQL table and fills it with data
void Shop_Handler::CreateDatabase(const char* file)
{
	//connects to the sql database
	sqlite3* db;
	char* errMsg = 0;

	//opens the database
	sqlite3_open(file, &db);

	//sql query to create the Stock table
	std::string sql = "CREATE TABLE IF NOT EXISTS Stock("
		"Id			INT NOY NULL, "
		"Item		TEXT NOT NULL, "
		"Price		INT NOT NULL, "
		"Quantity	INT NOT NULL);";
	//exectues the query
	sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

	//populates the table with example data
	InsertRow(file, "0", "apple", "1.5", "20");
	InsertRow(file, "1", "cart", "10", "5");
	InsertRow(file, "2", "horse", "25", "2");
	InsertRow(file, "3", "medicine", "3", "15");

	//closes the database
	sqlite3_close(db);
}

//outputs the contents of the database to the command window
void Shop_Handler::DisplayData(const char* file)
{
	//connects to the sql database
	sqlite3* db;
	char* errMsg = 0;

	//opens the database
	sqlite3_open(file, &db);

	//shows the user their current balance
	std::cout << "Balance: $" << balance << std::endl;
	//displays the collumn names to the command window
	std::cout << "ID  Item  Price  Quantity" << std::endl;

	//sql query to pull all the data from the 
	std::string sql = "SELECT * FROM Stock ORDER BY ID;";
	//executes the query
	sqlite3_exec(db, sql.c_str(), DisplayCallback, 0, &errMsg);

	//closes the database
	sqlite3_close(db);
}

//updates the stock of a given item by a given amount
void Shop_Handler::UpdateItem(const char* file, std::string item, int amount)
{
	//connects to the sql database
	sqlite3* db;
	char* errMsg = 0;

	//opens the database
	sqlite3_open(file, &db);

	//sql query to change the quantity of the given item by the given amount
	std::string sql = "UPDATE Stock SET Quantity = Quantity -" + std::to_string(amount) + " WHERE Item = '" + item + "';";
	//executes the query
	sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

	//closes the sql database
	sqlite3_close(db);
}

//handles the transaction of buying something from the database
void Shop_Handler::Transaction(const char* file)
{
	//connects sql database
	sqlite3* db;
	std::string sql;
	char* errMsg = 0;
	//creates variables to be filled later
	std::string item;
	float totalPrice, amount;

	//shows the user the current items they can buy
	DisplayData(file);

	//takes inputs for the item and quantity they wish to buy
	std::cout << "\nWhich item would you like to buy? ";
	std::cin >> item;
	std::cout << "How many would you like? ";
	std::cin >> amount;

	//opens the sql database
	sqlite3_open(file, &db);

	//sql query to get the current stock for the requested item
	sql = "SELECT Quantity FROM Stock WHERE Item = '" + item + "';";
	//executes the query
	sqlite3_exec(db, sql.c_str(), ItemCallback, 0, &errMsg);

	//closes the database
	sqlite3_close(db);

	//if there is enough stock for the transaction
	if (quantity >= amount)
	{
		//reopens the database
		sqlite3_open(file, &db);

		//sql query to get the price of the chosen item
		sql = "SELECT Price FROM Stock WHERE Item = '" + item + "';";
		//executes the query
		sqlite3_exec(db, sql.c_str(), ItemCallback, 0, &errMsg);

		//closes the database
		sqlite3_close(db);

		//calculates the total price the user has to pay
		totalPrice = (amount * quantity);
		//tells the user how much they owe
		std::cout << "Valid Quantity, This will cost: $";
		printf("%.2f", totalPrice);
		std::cout << std::endl;

		//checks if the user has sufficient funds to make the transaction
		if (totalPrice > balance)
		{
			//informs uses they lack funds for their transaction
			std::cout << "Insufficent Funds, Transaction Voided" << std::endl;
		}
		else
		{
			//updates the users balance
			balance -= totalPrice;
			//updates the stock of the chosen item
			UpdateItem(file, item, amount);
		}
	}
	//if there is not enough stock for the transaction
	else
	{
		//tells the user there isnt enough stock for their purchase
		std::cout << "Insufficient stock for transaction, please enter a valid quantity" << std::endl;
	}
}