#ifndef LEADERBOARDHANDLER_H
#define LEADERBOARDHANDLER_H

//C++ STANDARD LIBRARY - https://en.cppreference.com/w/cpp/header/iostream - USED TO INPUT/OUTPUT TO/FROM TERMINAL
#include <iostream>
//C++ STANDARD LIBRARY - https://en.cppreference.com/w/cpp/string/basic_string - USED STORE DATA AS STRING DATATYPE
#include <string>
//C++ STANDARD LIBRARY - https://en.cppreference.com/w/cpp/io/basic_stringstream - USED TO CONCATENATE STRINGS
#include <sstream>
//C++ STANDARD LIBRARY - https://en.cppreference.com/w/cpp/container/vector - USED TO STORE A RECORDS FIELDS FROM THE SQL DATABASE IN DYANAMICALLY SIZED ARRAY AT RUNTIME
#include <vector>
//C++ STANDARD LIBRARY - https://en.cppreference.com/w/cpp/header/random - USED FOR MERSENNE TWISTER PRNG TO GERNATE RANDOM NUMBER FOR SQLITE DATABSE PRIMARY KEY
#include <random>
//C++ STANDARD LIBRARY - https://en.cppreference.com/w/cpp/header/ctime - USED TO GET SYSTEM DATE AND TIME
#include <ctime>

//SQLITE - THIRD PARTY LIBRARY - https://sqlite.org/download.html - USED TO STORE LEADERBOARD AS DATABASE
#include "SQLite/sqlite3.h"

namespace Leaderboard_Handler 
{
	//|---FUNCTIONS BELOW FOR USE INSIDE OF TheOregonTrail_LeaderboardHandler.cpp---|
	//RETRIVES AND STORES PLAYER DATA TO BE PARSED INTO SQLITE DATABASE Leaderboard.db
	class LeaderboardDataEntry {
	private:
		int id;
		std::string player_name;
		std::string date;
		std::string time;
		int score;

		int setID();
		std::string setPlayerName(bool p_setPlayerName, int p_invalidUsernameCounter = 0);
		std::string setDate();
		std::string setTime();

		std::string formatDateTime(int p_dayOrhour_p, int p_monthOrminute, int p_yearOrsecond, int p_formatCode);
	public:
		//Default Constructor
		LeaderboardDataEntry(int p_userScore = 0, bool p_setPlayerName = false);

		int getID();
		std::string getPlayerName();
		std::string getDate();
		std::string getTime();
		int getScore();
	};

	//RETRIVES RECORDS FROM SQL DATABASE AND PRINTS THEM TO TERMINAL
	int callback(void* NotUsed, int argc, char** argv, char** azColName);
	//HANDLES CREATION/OPENING AND READ/WRITE FROM/TO SQL DATABASE
	void leaderboardDatabaseController(bool p_scoreSave = false, bool p_scoreLoad = false, LeaderboardDataEntry p_playerData = LeaderboardDataEntry(0));

	//TAKES RANK, PLAYER, DATE, TIME AND SCORE AS std::string
	//RETURNS RANK, PLAYER, DATE, TIME AND SCORE AS std::string IN CENTRE ALIGNED COLUMNS w/ BORDERS
	std::string formatLeaderboardRecord(std::string p_rank, std::string p_player, std::string p_date, std::string p_time, std::string p_score);
	
	//TAKES FIELD ENTRY (From record in SQLite Database Leaderboard.db) AS std::string AND COLUMN WIDTH AS (Width of Column when Leaderboard Printed to Terminal) int
	//RETURNS FIELD ENTRY AS std::string CENTER ALIGNED TO COLUMN w/ WHITESPACE AS PADDING 
	std::string formatLeaderboardField(std::string p_fieldEntry, int p_columnWidth);
	
	//TAKES NOTICE MESSAGE AS std::string, NOTICE CODE (0 = True, 1 = False, 2 = Success, 3 = Fail, 4 = N/A, 5 = CUSTOM NOTICE STATUS) AS int and CUSTOM NOTICE STATUS std::string
	void formatNotice(std::string p_notice, int p_noticeCode, std::string p_noticeStatus = "");



	//|---FUNCTIONS BELOW FOR USE OUTSIDE OF TheOregonTrail_LeaderboardHandler.cpp---|
	//TAKES USERS SCORE AS TYPE int AND WRITES IT TO NEW RECORD IN SQLITE DATABASE Leaderboard.db w/ ID AS TYPE int AND PLAYER, DATE, TIME AS TYPE std::string
	void leaderboardDataInput(int p_userScore = 0);
	//READS SQLITE DATABASE Leaderboard.db RECORDS AND PRINTS THEM TO CONSOLE
	void leaderboardDataOutput();
}
#endif //!LEADERBOARDHANDLER_H