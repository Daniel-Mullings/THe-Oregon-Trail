#include "TheOregonTrail_LeaderboardHandler.h"
#include "TheOregonTrail_ShopHandler.h"

int main()
{
	//defines variabales that will be used later
	const char* file = "shop.db";
	int price, amount;

	//delets current shop
	remove(file);
	//creates a new shop
	Shop_Handler::CreateDatabase(file);

	//creates a transaction
	Shop_Handler::Transaction(file);
	//displays the shop
	std::cout << "\n";
	Shop_Handler::DisplayData(file);

	return 0;
}