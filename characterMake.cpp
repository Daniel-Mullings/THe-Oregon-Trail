#include "HeaderFile.h"

using namespace std;


int game();

int characterMake()
{
	
	char name[50];
	
	cout << endl;
	cout << endl;
	cout << "                             THE OREGON TRAIL" << endl;
	cout << endl;
	cout << "                -----------------------------------------" << endl;
	cout <<      "                       Enter your characters name: " << endl;
	cout <<      "                                 ";

	cin >> name;


	system("cls");

	cout << endl;
	cout << endl;
	cout <<      "                            Hello " << name << endl;
	cout <<      "              -----------------------------------------" << endl;
	cout <<      "                  Are you ready to go on the trail" << endl;
	cout <<      "                              " << name << endl;
	cout <<      " " << endl;
	cout <<      "----------------------Press any key to continue----------------------" << endl;

	
	
	_getch();
	system("cls");



	game();

	return name[50];
	
}

