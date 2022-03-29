#include "HeaderFile.h"
using namespace std;

int characterMake();

int deathscreen()
{

	cout << endl;
	cout << endl;
	cout << "Thank you for playing this game ur score will be posted in the leaderboard" << endl;
	cout << "      Now reload the game and you can go for another game ;)" << endl;
	cout << "" << endl;
	cout << "  ----------------------Press any key to continue----------------------" << endl;

	_getch();
	system("cls");

	exit(3);
	return 3;
}