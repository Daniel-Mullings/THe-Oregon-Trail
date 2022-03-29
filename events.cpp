#include "HeaderFile.h"
using namespace std;


int deathscreen();
int main();
int games();



int events()
{

    string line;
    vector<string> lines;

    srand(time(0));

    ifstream file("QUESTION.txt");

    int total_lines = 0;
    while (getline(file, line))
    {
        total_lines++;
        lines.push_back(line);
    }

    int random_number = rand() % total_lines;

    cout << "           " << lines[random_number] << endl;
    cout << "                -----------------------------------------" << endl;

    /// ... died of Dysentery.
    if (random_number == 0)
    {

        cout << "" << endl;
        cout << "               THIS IS VERY SAD LOOKS LIKE YOUR DEAD NOW :(" << endl;
        cout << "                -----------------------------------------" << endl;

        deathscreen();
        return 0;
    } 

    /// Snake Bite!
    else if (random_number == 1)
    {
        int random_chance = rand() % 2;

        if (random_chance == 0)
        {
            cout << "               THIS IS VERY SAD LOOKS LIKE YOUR DEAD NOW :(" << endl;
            cout << "                -----------------------------------------" << endl;

            deathscreen();
            return 0;

        }

        else if (random_chance == 1)
        {
            cout << "                THIS IS VERY GOOD LOOKS LIKE YOUR NOT DEAD." << endl;
            cout << "                   WATCH OUT NEXT TIME YOU SILLY BILLY." << endl;
            cout << "                -----------------------------------------" << endl;

            return 0;
        }

        return 0;
    }

    /// Broke Arm.
    else if (random_number == 2)
    {

        int random_chance = rand() % 100;

        if (random_chance > 75)
        {

            cout << "               THIS IS VERY SAD LOOKS LIKE YOUR DEAD NOW :(" << endl;
            cout << "                -----------------------------------------" << endl;

            deathscreen();
            return 0;

        }

        else if (random_chance < 75)
        {

            cout << "               THIS IS VERY GOOD LOOKS LIKE YOUR NOT DEAD." << endl;
            cout << "                  WATCH OUT NEXT TIME YOU SILLY BILLY." << endl;
            cout << "                -----------------------------------------" << endl;

            return 0;

        }

        return 0;

    }

    /// Thunder Storm!!!
    else if (random_number == 3)
    {

        cout << "                 THUNDER STORM. YIKES! LET'S KEEP MOVING." << endl;
        cout << "                -----------------------------------------" << endl;

        return 0;

    }

    /// TRAIL DIVIDEDS HERE. YOU MAY:
    else if (random_number == 4)
    {

        cout << "                       A. GO DOWN THE LEFT PATH" << endl;
        cout << "                       B. GO DOWN THE RIGHT PATH" << endl;
        cout << "                -----------------------------------------" << endl;

        string input;

        cout << "                       Enter your input A or B : ";
        cin >> input;
        cout << endl;
        cout << "                -----------------------------------------" << endl;

        if (input == "A")
        {
            cout << endl;
            cout << "                -----------------------------------------" << endl;
            cout << "               THIS IS VERY SAD LOOKS LIKE YOUR DEAD NOW :(" << endl;
            cout << "                -----------------------------------------" << endl;

            deathscreen();
            return 0;

        }

        else if (input == "B")
        {
            cout << "" << std::endl;
            cout << "                -----------------------------------------" << endl;
            cout << "                  LOOKS LIKE YOU HAVE CHOSEN THE RIGHT PATH." << endl;
            cout << "                        DO YOU GET IT, IT'S A FUNNY." << endl;
            cout << "                -----------------------------------------" << endl;

            return 0;

        }

        return 0;
    }

    /// WOW, A NORMAL DAY. THIS IS TO QUITE? TO QUITE!
    else if (random_number == 5)
    {

        cout << "                     .... AM I BEING FOLLOWED" << endl;
        cout << "                -----------------------------------------" << endl;

        return 0;

    }

    /// Chicken
    else if (random_number == 5)
    {
     
    cout << "                          .... POOP" << endl;
    cout << "                -----------------------------------------" << endl;

    return 0;

    }

}



