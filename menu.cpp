#include "HeaderFile.h"
using namespace std;


int events();
int characterMake();



int menu()
{
    system("color A");
    
    cout << endl;
    cout << endl;
    cout << "                  WELCOME  TO THE OREGON TRAIL " << endl;
    cout << endl;
    cout << "           ----------------------------------------- " << endl;
    cout << "                             BY " << endl;
    cout << endl;
    cout << "    Daniel Mullings | Josh Marsh | Luke Harrison | Jacob Wilson" << endl;
    cout << endl;
    cout << "\n   ----------------------Press any key to continue----------------------" << endl;

    _getch();
    system("cls");

    int choice;    
    const int PLAYTRAIL_CHOICE = 1,
        HOWTOPLAY_CHOICE = 2,
        LEADERBOARD_CHOICE = 3,
        QUIT_CHOICE = 4;

    cout << endl;
    cout << endl;
    cout << "                         THE OREGON TRAIL " << endl;
    cout << endl;
    cout << "           ----------------------------------------- " << endl;
    cout << "                      1. TRAVEL THE TRAIL\n";
    cout << "                      2. LEARN ABOUT THE TRAIL\n";
    cout << "                      3. LEADERBOARDS\n";
    cout << "                      4. Quit the program\n\n";
    cout << "---------------Enter your choice between 1 through 4---------------";

    cin >> choice;

    system("cls");

    cout << fixed << showpoint << setprecision(2);

    if (choice == PLAYTRAIL_CHOICE)
    {

       characterMake();

    }

    else if (choice == HOWTOPLAY_CHOICE)
    {

        // Page 1
        cout << endl;
        cout << endl;
        cout << "                             THE OREGON TRAIL" << endl;
        cout << endl;
        cout << "                -----------------------------------------" << endl;
        cout << endl;
        cout << "                      Try taking a journey by" << endl;
        cout << "                      covered wagon across 2000" << endl;
        cout << "                      miles of plains, rivers, and" << endl;
        cout << "                      mountains. Try! On the" << endl;
        cout << "                      plains, will you slosh your" << endl;
        cout << "                      oxen through mud and" << endl;
        cout << "                      water-filled ruts or will you" << endl;
        cout << "                      plod through dust six inches deep?" << endl;
        cout << endl;
        cout << "\n   ----------------------Press any key to continue----------------------" << endl;

        _getch();
        system("cls");

        //page 2
        cout << endl;
        cout << endl;
        cout << "                             THE OREGON TRAIL" << endl;
        cout << endl;
        cout << "                -----------------------------------------" << endl;
        cout << endl;
        cout << "                      How will you cross the rivers?" << endl;
        cout << "                      If you have money, you might" << endl;
        cout << "                      take a ferry (if there is a" << endl;
        cout << "                      ferry). Or, you can ford the" << endl;
        cout << "                      river and hope you and your" << endl;
        cout << "                      wagon aren't swallowed alive!" << endl;
        cout << endl;

        cout << "\n   ----------------------Press any key to continue----------------------" << endl;

        _getch();
        system("cls");

        //Page 3
        cout << endl;
        cout << endl;
        cout << "                             THE OREGON TRAIL" << endl;
        cout << endl;
        cout << "                -----------------------------------------" << endl;
        cout << endl;
        cout << "                      What about supplies? Well, if" << endl;
        cout << "                      you're low on food you can" << endl;
        cout << "                      hunt. You might get a buffalo..." << endl;
        cout << "                      you might. And there are" << endl;
        cout << "                      bear in the mountains." << endl;
        cout << endl;
        cout << "\n   ----------------------Press any key to continue----------------------" << endl;

        _getch();
        system("cls");

        //Page 4
        cout << endl;
        cout << endl;
        cout << "                             THE OREGON TRAIL" << endl;
        cout << endl;
        cout << "                -----------------------------------------" << endl;
        cout << endl;
        cout << "                      At the Dalles, you can try " << endl;
        cout << "                      navigating the Columbia River, " << endl;
        cout << "                      but if running the rapids with" << endl;
        cout << "                      a makeshift raft makes you" << endl;
        cout << "                      queasy, better take the Barlow" << endl;
        cout << "                      Road." << std::endl;
        cout << endl;
        cout << "\n   ----------------------Press any key to continue----------------------" << endl;

        _getch();
        system("cls");

        menu();

    }

    else if (choice == LEADERBOARD_CHOICE)
    {
        cout << endl;
        cout << endl;


        cout << "\n----------------------Press any key to continue----------------------" << endl;

        _getch();
        system("cls");

        menu();

    }

    else if (choice == QUIT_CHOICE)
    {
    cout << endl;
    cout << endl;
    cout << "Program ending.\n";

    }
    else
    {

    cout << endl;
    cout << endl;
    cout << "\t\t   The valid choices are 1 through 4.\n\n";
    cout << "";

    system("Pause");

        system("cls");

        menu();
    }
    return 0;

}
