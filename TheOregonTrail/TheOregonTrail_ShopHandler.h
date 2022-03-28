#ifndef SHOPHANDLER_H
#define SHOPHANDLER_H

//C++ standard library - https://en.cppreference.com/w/cpp/header/iostream - input/output using terminal
#include <iostream>
//C++ standard library - https://en.cppreference.com/w/cpp/string/basic_string - stores data as string datatype
#include <string>
//C++ standard library - https://en.cppreference.com/w/cpp/container/vector - stores data in a dynamically sized array
#include <vector>
//SQLITE - third party library - https://sqlite.org/download.html - used to store and query data in database format
#include <SQLite/sqlite3.h>


//Pre-defining functions to be given content later in the .cpp file
namespace Shop
{
	float quantity;
	float balance;

	//Callback functions
	int DisplayCallback(void* NotUsed, int total, char** value, char** column);
	int ItemCallback(void* NotUsed, int total, char** value, char** column);

	//Functions to handle SQL Queries
	//inserts row to sql table
	void InsertRow(const char* file, std::string id, std::string item, std::string quantity, std::string price);
	//creates a database and populates it with data
	void CreateDatabase(const char* file);
	//retrieves all the data from inside the database
	void DisplayData(const char* file);
	//updates the stock for a given item by a given amount
	void UpdateItem(const char* file, std::string item, int amount);

	//Function to handle a transaction
	void Transaction(const char* file);


}
#endif //SHOPHANDLER_H