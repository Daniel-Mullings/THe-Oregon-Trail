#ifndef LEADERBOARDHANDLER_H
#define LEADERBOARDHANDLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <ctime>

class LeaderboardDataEntry{
private:
	int id;
	std::string username;
	std::string date;
	std::string time;
	int score;

	int setID();
	std::string setUsername(bool setUsername_p, int invalidUsernameCounter = 0);
	std::string setDate();
	std::string setTime();

	std::string formatDateTime(int dayOrhour_p, int monthOrminute_p, int yearOrsecond_p, int formatCode_p);
public:
	LeaderboardDataEntry(int userScore_p = 0, bool setUsername_p = false);

	int getID();
	std::string getUsername();
	std::string getDate();
	std::string getTime();
	int getScore();
};

void leaderboardDatabaseController(bool scoreSave = false, bool scoreLoad = false, LeaderboardDataEntry playerData = LeaderboardDataEntry(0));
void leaderboardDataInput(int userScore_p = 0);
void leaderboardDataOutput();

std::string formatLeaderboardRecord(int rank_p, std::string player_p, std::string date_p, std::string time_p, int score_p);
std::string formatLeaderboardField(std::string fieldEntry_p, int fieldWidth_p);
std::string formatLeaderboardField(int fieldEntry_p, int fieldWidth_p);

#endif //!LEADERBOARDHANDLER_H