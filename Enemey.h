#ifndef ENEMY_H_
#define ENEMEY_H_

#include "cocos2d.h"
#include "Bullet.h"
class Enemey :public cocos2d::Sprite
{

public:
	int EnemeyTypes;

	static Enemey* createEnemey(const char* PictureName, int Types);

	void enemeyRun();

	void enemeyRepeatShoot();

	void updateshoot(float dt);

	void updatedelete(float dt);

};

#endif