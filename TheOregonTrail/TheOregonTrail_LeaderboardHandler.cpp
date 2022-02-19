#define _CRT_SECURE_NO_WARNINGS

#include "TheOregonTrail_LeaderboardHandler.h"

//STORES RANK FOR EACH LEADERBOARD ENTRY
int rank_counter{ 0 };

//PSEUDO RANDOM NUMBER GENERATOR, GENERATE PRIMARY KEY FOR RECORDS IN SQLITE DATABASE Leaderboard.db
std::mt19937 prng{static_cast<std::mt19937::result_type>(std::time(nullptr))};
std::uniform_int_distribution<> recordIDGen{ 0,  9999999};

//CLASS FUNCTIONS
Leaderboard_Handler::LeaderboardDataEntry::LeaderboardDataEntry(int p_userScore, bool p_setPlayerName)
{
	id = setID();
	player_name = setPlayerName(p_setPlayerName);
	date = setDate();
	time = setTime();
	score = p_userScore;
}
std::string Leaderboard_Handler::LeaderboardDataEntry::formatDateTime(int p_dayOrhour, int p_monthOrminute, int p_yearOrsecond, int p_formatCode)
{
	std::stringstream formattedDateTime{ "" };

	std::string dayOrHour_str{ std::to_string(p_dayOrhour) };
	std::string monthOrminute_str{ std::to_string(p_monthOrminute) };
	std::string yearOrsecond_str{ std::to_string(p_yearOrsecond) };

	if (dayOrHour_str.length() == 1)
		dayOrHour_str.insert(0, "0");
	if (monthOrminute_str.length() == 1)
		monthOrminute_str.insert(0, "0");
	if (yearOrsecond_str.length() == 1)
		yearOrsecond_str.insert(0, "0");

	if (p_formatCode == 0)
		formattedDateTime << dayOrHour_str << "/" << monthOrminute_str << "/" << yearOrsecond_str;
	else if (p_formatCode == 1)
		formattedDateTime << dayOrHour_str << ":" << monthOrminute_str << ":" << yearOrsecond_str;

	//RETURN FORMATTED DATA OR TIME (DD:MM:YYYY, HH:MM:SS)
	return formattedDateTime.str();
}

int Leaderboard_Handler::LeaderboardDataEntry::setID()
{
	//RETURNS RANDOMLY GENERATED NUMBER
	return recordIDGen(prng);
}
std::string Leaderboard_Handler::LeaderboardDataEntry::setPlayerName(bool p_setPlayerName, int invalidUsernameCounterp_)
{
	if (p_setPlayerName)
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "PLAYER SCOREBOARD DETAILS" << std::endl;
		std::cout << "-------------------------" << std::endl;

		int invalidPlayerNameCounter{ 0 };
		std::string playerNameIn;

		while (invalidPlayerNameCounter <= 2)
		{
			std::cout << "\n(MAX: 24 CHARACTERS, ATTEMPT: " << invalidPlayerNameCounter + 1 << "/3)" << std::endl;
			std::cout << "Enter your name: ";

			std::getline(std::cin, playerNameIn);

			if (playerNameIn.length() == 0 || playerNameIn.length() > 24)
			{
				std::cout << "Invalid Username!" << std::endl;
				invalidPlayerNameCounter += 1;
			}
			else
			{
				std::cout << std::endl;
				Leaderboard_Handler::formatNotice("PLAYER NAME ENTRY SAVE STATE", 2);
				std::cout << std::endl;
				
				//RETURNS INPUTTED PLAYER NAME
				return playerNameIn;
			}
		}
		std::stringstream invalidPlayerName{ "" };
		invalidPlayerName << "<INVAL_UNAME@" << id << '>';

		std::cout << std::endl;
		Leaderboard_Handler::formatNotice("MAXIMUM ATTEMPTS REACHED", 0);
		Leaderboard_Handler::formatNotice("SETTING DEFAULT USERNAME", 2);
		Leaderboard_Handler::formatNotice("DEFAULT USERNAME", 5, invalidPlayerName.str());
		std::cout << std::endl;

		//RETURNS PLACEHOLDER PLAYER NAME "<INVAL_UNAME@ID#>"
		return invalidPlayerName.str();
	}
	//RETURNS EMPTY PLAYER NAME
	return "";
}
std::string Leaderboard_Handler::LeaderboardDataEntry::setDate()
{
	//CURRENT DATE/TIME ON CURRENT SYSTEM
	time_t now = std::time(0);
	tm* ltm = std::localtime(&now);

	//COMPONENTS OF tm STRUCTURE
	int year{ 1900 + ltm->tm_year };
	int month{ 1 + ltm->tm_mon };
	int day{ ltm->tm_mday };
	
	//RETURNS DATE AS "DD/MM/YYYY"
	return formatDateTime(day, month, year, 0);
}
std::string Leaderboard_Handler::LeaderboardDataEntry::setTime()
{
	//CURRENT DATE/TIME ON CURRENT SYSTEM
	time_t now = std::time(0);
	tm* ltm = localtime(&now);

	//COMPONENTS OF tm STRUCTURE
	int hours{ ltm->tm_hour };
	int minutes{ ltm->tm_min };
	int seconds{ ltm->tm_sec };

	//RETURNS TIME AS "HH:MM:SS"
	return formatDateTime(hours, minutes, seconds, 1);
}

int Leaderboard_Handler::LeaderboardDataEntry::getID()
{
	return id;
}
std::string Leaderboard_Handler::LeaderboardDataEntry::getPlayerName()
{
	return player_name;
}
std::string Leaderboard_Handler::LeaderboardDataEntry::getDate()
{
	return date;
}
std::string Leaderboard_Handler::LeaderboardDataEntry::getTime()
{
	return time;
}
int Leaderboard_Handler::LeaderboardDataEntry::getScore()
{
	return score;
}

//SQLITE DATABASE INTERFACE FUNCTIONS
int Leaderboard_Handler::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	std::vector<std::string> record;

	for (int counter = 0; counter < argc; counter++)
	{
		record.push_back(argv[counter]);
		if (counter != 0 && (counter % 4) == 0)
		{
			rank_counter += 1;
			std::cout << Leaderboard_Handler::formatLeaderboardRecord(std::to_string(rank_counter), record[1], record[2], record[3], record[4]);
			record.clear();
		}
	}
	return 0;
}
void Leaderboard_Handler::leaderboardDatabaseController(bool p_scoreSave, bool p_scoreLoad, Leaderboard_Handler::LeaderboardDataEntry p_playerData)
{
	/*
	REFERENCE (LINE NUMBERS: #, #):

	ONLINE TUTORIAL - https://videlais.com/2018/12/12/c-with-sqlite3-part-1-downloading-and-compiling/ - SQLITE DATABASE: HOW TO CREATE TABLES, INSERT AND SELECT DATA
	*/

	//POINTER TO SQLITE CONNECTION
	sqlite3* database;
	std::string sqlQuery{ "" };

	//SAVE CONNECTION RESULT
	int sqlDatabaseFile{ 0 };
	sqlDatabaseFile = sqlite3_open("Leaderboard.db", &database);

	//SAVE ERROR MESSAGES
	char* zErrMsg{ 0 };

	//SQL QUERY (Create Table within SQLite Database Leaderboard.db)
	sqlQuery = "CREATE TABLE Scores ("\
		"ID		INT		PRIMARY KEY     NOT NULL," \
		"Player STRING					NOT NULL," \
		"Date	STRING					NOT NULL," \
		"Time	STRING					NOT NULL," \
		"Score	INT						NOT NULL);";

	//EXECUTE SQL QUERY (CONVERT std::string TO C-STRING WITH c_str())
	sqlDatabaseFile = sqlite3_exec(database, sqlQuery.c_str(), callback, 0, &zErrMsg);

	//INSERT PLAYER SCORE/DETAILS AS RECORD
	if (p_scoreSave)
	{
		std::ostringstream SQLQuery_recordInsert{ "" };
		SQLQuery_recordInsert << "INSERT INTO Scores ('ID', 'Player', 'Date', 'Time', 'Score') VALUES ('" << p_playerData.getID() << "', '" << p_playerData.getPlayerName() << "', '"
																										  << p_playerData.getDate() << "', '" << p_playerData.getTime() << "', '"
																										  << p_playerData.getScore() << "');";

		sqlQuery = SQLQuery_recordInsert.str();
		sqlDatabaseFile = sqlite3_exec(database, sqlQuery.c_str(), callback, 0, &zErrMsg);
	}
	
	//RETRIVE ALL PLAYER SCORES/DETAILS BY SCORE HIGH TO LOW, PLAYER A TO Z
	if (p_scoreLoad)
	{
		sqlQuery = "SELECT * FROM Scores ORDER BY Score DESC, Player ASC";
		sqlDatabaseFile = sqlite3_exec(database, sqlQuery.c_str(), callback, 0, &zErrMsg);
	}

	//CLOSE SQLITE CONNECTION
	sqlite3_close(database);
}

//SQLITE DATABASE DATA FORMATTING FUNCTIONS
std::string Leaderboard_Handler::formatLeaderboardField(std::string p_fieldEntry, int p_columnWidth)
{
	int whitespace_padding{ p_columnWidth - int(p_fieldEntry.length()) };

	if (p_fieldEntry.length() % 2 == 0)
	{
		p_fieldEntry.insert(0, std::string((whitespace_padding / 2), ' '));
		p_fieldEntry.insert(p_fieldEntry.length(), std::string((whitespace_padding / 2), ' '));
	}
	else
	{
		p_fieldEntry.insert(0, std::string(((whitespace_padding + 1) / 2), ' '));
		p_fieldEntry.insert(p_fieldEntry.length(), std::string(((whitespace_padding - 1) / 2), ' '));
	}

	//RETURNS FIELD FROM RECORD CENTER ALIGNED w/ WHITESPACE AS PADDING
	return p_fieldEntry;
}
std::string Leaderboard_Handler::formatLeaderboardRecord(std::string p_rank, std::string p_player, std::string p_date, std::string p_time, std::string p_score)
{
	std::string formattedLeaderboardRecord{ '|' + formatLeaderboardField(p_rank, 10) + '|' + formatLeaderboardField(p_player, 24)
										  + '|' + formatLeaderboardField(p_date, 10) + '|' + formatLeaderboardField(p_time, 10) + '|' + formatLeaderboardField(p_score, 11) + " |\n" };

	//RETURNS FIELDS FROM RECORD FORMATTED AS "| RANK | PLAYER | DATE | TIME | SCORE |"
	return formattedLeaderboardRecord;
}

//PRINTS FORMATTED NOTICES
void Leaderboard_Handler::formatNotice(std::string p_notice, int p_noticeCode, std::string p_noticeStatus)
{
	int whitespace{ 35 - int(p_notice.length()) };

	p_notice.insert(p_notice.end(), whitespace, '.');
	p_notice.insert(0, "NOTICE: ");

	switch (p_noticeCode)
	{
	case 0:
		p_notice.append(": TRUE");
		break;
	case 1:
		p_notice.append(": FALSE");
		break;
	case 2:
		p_notice.append(": SUCCESS");
		break;
	case 3:
		p_notice.append(": FAIL");
		break;
	case 4:
		p_notice.append(": N/A");
		break;
	case 5:
		p_notice.append(": " + p_noticeStatus);
		break;
	default:
		break;
	}
	std::cout << p_notice << '\n';
}

//SQLITE DATABASE I/O FUNCTIONS
void Leaderboard_Handler::leaderboardDataInput(int p_userScore)
{
	LeaderboardDataEntry playerData(p_userScore, true);
	leaderboardDatabaseController(true, false, playerData);
}
void Leaderboard_Handler::leaderboardDataOutput()
{
	std::cout << "-----------------------------------------------------------------------" << std::endl
			  << "|                             LEADERBOARD                             |" << std::endl
			  << "-----------------------------------------------------------------------" << std::endl
			  << "|   RANK   |         PLAYER         |   DATE   |   TIME   |   SCORE   |" << std::endl
			  << "-----------------------------------------------------------------------" << std::endl;

	leaderboardDatabaseController(false, true);

	std::cout << "-----------------------------------------------------------------------" << std::endl;

	std::cout << std::endl;
	formatNotice("LEADERBOARD LOADED", 2);
	std::cout << std::endl;
}