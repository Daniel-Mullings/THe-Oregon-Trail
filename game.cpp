#include "HeaderFile.h"
using namespace std;


int deathscreen();
int events();
int counter();
int counter2();
int landMark();



int game()

{
    cout << endl;
    cout << endl;
    cout << "                             THE OREGON TRAIL" << endl;
    cout << endl;
    cout << "                -----------------------------------------" << endl;

    events();

    cout << "                              day : " << counter() << endl; 
    cout << "                          Weather : place holder" << endl;
    cout << "                           health : place holder" << endl;
    cout << "                             food : place holder" << endl;
    cout << "     next landmark is at 10 miles : " << landMark() << endl;
    cout << "                   miles traveled : " << counter2() << endl;
    cout << endl;
    cout << "\n   ----------------------Press any key to continue----------------------" << endl;

    system("pause");
    system("cls");

    game();
    return 0;

}

// how many turns you have taken
int counter()
{

    static int counter = 0;

    return ++counter;

}


// distance travled 
int counter2()
    {

        static int counter = 0;

        return ++counter;

    }
    
// how far the next land mark is
int landMark()
{

    int count = 10;

    return count;

}