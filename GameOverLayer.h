#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include <stdio.h>
#include"cocos2d.h"
#include "Scoreboard.h"

using namespace cocos2d;
using namespace std;

class GameOverLayer :public Layer
{
public:
	Scoreboard* scoreboard;
	
	Label* Score_show;

	bool init();

	Size windowSize;

	static Scene* createOverScene(Scoreboard* scoreboard2);

	void closeGame(Ref* object);

	void backToStart(Ref* object);

	CREATE_FUNC(GameOverLayer);

};
#endif /* GameOverLayer_hpp */
