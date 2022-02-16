#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>

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

int LeaderboardDataEntry::setID()
{
	return recordIDGen(prng);
}
std::string LeaderboardDataEntry::setUsername(bool setUsername_p)
{
	if (setUsername_p) 
	{
		std::string usernameInput{ "" };
		std::cout << "Enter your name: ";
		std::getline(std::cin, usernameInput);
		std::cout << std::endl;

		return usernameInput;
	}
	else
		return "";
}
std::string LeaderboardDataEntry::setDate()
{
	return "";
}
std::string LeaderboardDataEntry::setTime()
{
	return "";
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