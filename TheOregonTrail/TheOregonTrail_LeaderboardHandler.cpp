#define _CRT_SECURE_NO_WARNINGS

#include "TheOregonTrail_LeaderboardHandler.h"
#include "SQLite/sqlite3.h"

//PRNG
std::mt19937 prng{static_cast<std::mt19937::result_type>(std::time(nullptr))};
std::uniform_int_distribution<> recordIDGen{ 0,  1000000};

//Class Function Definitions
LeaderboardDataEntry::LeaderboardDataEntry(int userScore_p, bool setUsername_p) 
{
	id = setID();
	username = setUsername(setUsername_p);
	date = setDate();
	time = setTime();
	score = userScore_p;
} //Default Constructor
std::string LeaderboardDataEntry::formatDateTime(int dayOrhour_p, int monthOrminute_p, int yearOrsecond_p, int formatCode_p)
{
	std::stringstream formattedDateTime{ "" };

	std::string dayOrHour_str{ std::to_string(dayOrhour_p) };
	std::string monthOrminute_str{ std::to_string(monthOrminute_p) };
	std::string yearOrsecond_str{ std::to_string(yearOrsecond_p) };

	if (dayOrHour_str.length() == 1)
		dayOrHour_str.insert(0, "0");
	if (monthOrminute_str.length() == 1)
		monthOrminute_str.insert(0, "0");
	if (yearOrsecond_str.length() == 1)
		yearOrsecond_str.insert(0, "0");

	if (formatCode_p == 0)
		formattedDateTime << dayOrHour_str << "/" << monthOrminute_str << "/" << yearOrsecond_str;
	else if (formatCode_p == 1)
		formattedDateTime << dayOrHour_str << ":" << monthOrminute_str << ":" << yearOrsecond_str;


	return formattedDateTime.str();
}

int LeaderboardDataEntry::setID()
{
	return recordIDGen(prng);
}
std::string LeaderboardDataEntry::setUsername(bool setUsername_p, int invalidUsernameCounter_p)
{
	if (setUsername_p)
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "PLAYER SCOREBOARD DETAILS" << std::endl;
		std::cout << "-------------------------" << std::endl;

		int invalidUsernameCounter{ 0 };
		std::string usernameIn;

		while (invalidUsernameCounter <= 2)
		{
			std::cout << "(MAX: 24 CHARACTERS, ATTEMPT: " << invalidUsernameCounter + 1 << "/3)" << std::endl;
			std::cout << "Enter your name: ";

			std::getline(std::cin, usernameIn);

			if (usernameIn.length() == 0 || usernameIn.length() > 24)
			{
				std::cout << "\nInvalid Username\n" << std::endl;
				invalidUsernameCounter += 1;
			}
			else
			{
				std::cout << "\nNOTICE: USERNAME ENTRY SAVED!\n" << std::endl;
				return usernameIn;
			}
		}

		std::stringstream invalidUsername{ "" };
		invalidUsername << "INVAL_UNAME@" << id << '>';

		std::cout << "NOTICE: MAXIMUM ATTEMPTS REACHED!" << std::endl;
		std::cout << "NOTICE: SETTING DEFAULT USERNAME: SUCCESS" << std::endl;
		std::cout << "NOTICE: DEFAULT USERNAME:         <INVAL_UNAME@" << id << ">\n" << std::endl;
		return invalidUsername.str();
	}
	return "";
}
std::string LeaderboardDataEntry::setDate()
{
	// current date/time based on current system
	time_t now = std::time(0);
	tm* ltm = std::localtime(&now);

	//Print various components of tm structure.
	int year{ 1900 + ltm->tm_year };
	int month{ 1 + ltm->tm_mon };
	int day{ ltm->tm_mday };
	
	return formatDateTime(day, month, year, 0);
}
std::string LeaderboardDataEntry::setTime()
{
	// current date/time based on current system
	time_t now = std::time(0);
	tm* ltm = localtime(&now);

	//Print various components of tm structure.
	std::ostringstream time{ "" };

	int hours{ ltm->tm_hour };
	int minutes{ ltm->tm_min };
	int seconds{ ltm->tm_sec };

	return formatDateTime(hours, minutes, seconds, 1);
}

int LeaderboardDataEntry::getID() 
{
	return id;
}
std::string LeaderboardDataEntry::getUsername()
{
	return username;
}
std::string LeaderboardDataEntry::getDate()
{
	return date;
}
std::string LeaderboardDataEntry::getTime()
{
	return time;
}
int LeaderboardDataEntry::getScore()
{
	return score;
}



int callback(void* NotUsed, int argc, char** argv, char** azColName) 
{
	return 0;
}
void leaderboardDatabaseController(bool scoreSave, bool scoreLoad, LeaderboardDataEntry playerData)
{
	//Pointer to SQLite connection
	sqlite3* database;
	std::string sqlQuery{ "" };

	// Save any error messages
	char* zErrMsg = 0;

	//Save the connection result
	int sqlDatabaseFile{0};
	sqlDatabaseFile = sqlite3_open("Leaderboard.db", &database);

	//Test if there was an error
	if (sqlDatabaseFile)
		std::cout << "NOTICE: Database Load State: FAIL: " << sqlite3_errmsg(database) << std::endl;
	else
		std::cout << "NOTICE: Database Load State: SUCCESS" << std::endl;

	//Save SQL to create a table
	sqlQuery = "CREATE TABLE Scores ("\
		"ID		INT		PRIMARY KEY     NOT NULL," \
		"Player STRING					NOT NULL," \
		"Date	STRING					NOT NULL," \
		"Time	STRING					NOT NULL," \
		"Score	INT						NOT NULL);";

	// Run the SQL (convert the string to a C-String with c_str() )
	sqlDatabaseFile = sqlite3_exec(database, sqlQuery.c_str(), callback, 0, &zErrMsg);

	//Insert Player Score As Record
	if (scoreSave)
	{
		//CODE TO SAVE RECORD TO DATABASE
		std::ostringstream SQLQuery_recordInsert;
		SQLQuery_recordInsert << "INSERT INTO Scores ('ID', 'Player', 'Date', 'Time', 'Score') VALUES ('" << playerData.getID() << "', '" << playerData.getUsername() << "', '"
																								 << playerData.getDate() << "', '" << playerData.getTime() << "', '" 
																								 << playerData.getScore() << "');";

		sqlQuery = SQLQuery_recordInsert.str();
		sqlDatabaseFile = sqlite3_exec(database, sqlQuery.c_str(), callback, 0, &zErrMsg);

		std::cout << "NOTICE: Score Save State:    SUCCESS" << std::endl;
		
	}
	else
		std::cout << "NOTICE: Score Save State:    FAIL" << std::endl;
	
	//Display All Player Score Records
	if (scoreLoad)
	{
		sqlQuery = "SELECT * FROM Scores ORDER BY Score";
		sqlDatabaseFile = sqlite3_exec(database, sqlQuery.c_str(), callback, 0, &zErrMsg);

	}
	else
		std::cout << "NOTICE: Score Load State:    FAIL" << std::endl;

	//Close the connection
	sqlite3_close(database);
}
void leaderboardDataInput(int userScore_p)
{
	LeaderboardDataEntry playerData(userScore_p, true);
	leaderboardDatabaseController(true, false, playerData);
}
void leaderboardDataOutput()
{
	std::cout << "-----------------------------------------------------------------------" << std::endl
		<< "|   RANK   |         PLAYER         |   DATE   |   TIME   |   SCORE   |" << std::endl
		<< "-----------------------------------------------------------------------" << std::endl;

	leaderboardDatabaseController(false, true);
}

std::string formatLeaderboardField(std::string fieldEntry_p, int fieldWidth_p)
{
	int whiteSpace = fieldWidth_p - fieldEntry_p.length();

	if (fieldEntry_p.length() % 2 == 0)
	{
		fieldEntry_p.insert(0, std::string((whiteSpace / 2), ' '));
		fieldEntry_p.insert(fieldEntry_p.length(), std::string((whiteSpace / 2), ' '));
	}
	else
	{
		fieldEntry_p.insert(0, std::string(((whiteSpace + 1) / 2), ' '));
		fieldEntry_p.insert(fieldEntry_p.length(), std::string(((whiteSpace - 1) / 2), ' '));
	}
	return fieldEntry_p;
}
std::string formatLeaderboardField(int fieldEntry_p, int fieldWidth_p)
{
	std::string fieldEntry = std::to_string(fieldEntry_p);
	int whiteSpace = fieldWidth_p - fieldEntry.length();

	if (fieldEntry.length() % 2 == 0)
	{
		fieldEntry.insert(0, std::string((whiteSpace / 2), ' '));
		fieldEntry.insert(fieldEntry.length(), std::string((whiteSpace / 2), ' '));
	}
	else
	{
		fieldEntry.insert(0, std::string(((whiteSpace + 1) / 2), ' '));
		fieldEntry.insert(fieldEntry.length(), std::string(((whiteSpace - 1) / 2), ' '));
	}
	return fieldEntry;
}
std::string formatLeaderboardRecord(int rank_p, std::string player_p, std::string date_p, std::string time_p, int score_p)
{
	std::string formattedLeaderboardRecord{ '|' + formatLeaderboardField(rank_p, 10) + '|' + formatLeaderboardField(player_p, 24)
										  + '|' + formatLeaderboardField(date_p, 10) + '|' + formatLeaderboardField(time_p, 10) + '|' + formatLeaderboardField(score_p, 11) + " |" };

	return formattedLeaderboardRecord;
}