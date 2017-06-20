#ifndef _CHAPTER¢ò_H_
#define _CHAPTER¢ò_H_

#include "cocos2d.h"
#include "Player.h"
#include "Lifebar.h"
#include "Scoreboard.h"
#include "SimpleAudioEngine.h"
#include "RollingLayer.h"
using namespace::cocos2d;
using namespace::std;
using namespace::CocosDenshion;


class Chapter2: public Layer
{
public:
	Player*  player;
	Lifebar* lifebar;
	Menu* play;
	bool musicOn = true;
    Scoreboard* scoreboard;
    Label* Score_show;
	Size visibleSize;

	std::vector<bool> recorder = { 0,0,0,0,0,0,0 };

	void onEnter();

	int player_bullet_type = NORMAL_BULLET;

	//º¯ÊýÇø
	static Scene* creatChapter2(int Lifenum2,Scoreboard* scoreboard2);
	bool init();
	
	void update(float dt) override;

	void updateEnemey(float dt); 
	void updateEnemey2(float dt);
	void updateEnemey3(float dt);
	void updateEnemey4(float dt);
	void updateEnemey5(float dt);
	void updateEnemey6(float dt);

	void updateEnhancepack(float dt);
	void update_set_player_normal(float dt);
	void checkmove();
	void backToStart(Ref* object);
	void stop(Ref* object);
	void ContinueGame(Ref* object);
	void CheckHp(float time);
	void stopmusic(Ref* object);


	CREATE_FUNC(Chapter2);

};

#endif