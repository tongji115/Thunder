#ifndef SCORE_BOARD_H_
#define SCORE_BOARD_H_



#include <string>

class Scoreboard : public std::string {
public:
	static Scoreboard* creatScoreboard();
	void Scoreboard_add_num(std::string num);
};


#endif 