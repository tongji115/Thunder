#ifndef _BULLET_H_
#define _BULLET_H_

#include "TOTAL_DEFINE.h"
#include "cocos2d.h"
class Bullet :public cocos2d::Sprite
{
public:
	cocos2d::Node* bullet_parent;

	cocos2d::Vec2 bulletVelocity = cocos2d::Vec2(0, 1000);

	int bulletType;

	static Bullet* createBullet(const char * Name, int Side, cocos2d::Vec2 velocity);                //Éè¶¨×Óµ¯Íâ¹Û£¬µØ·½»¹ÊÇÓÑ·½£¬ÒÔ¼°ËÙ¶È£¬×¢ÒâËÙ¶ÈÊÇ¸ö¶þÎ¬Ê¸Á¿
																									 //ËÙ¶ÈÔÚÒ»Ç§×óÓÒ±È½ÏÃ÷ÏÔ

	void bulletShootFrom(cocos2d::Node* p,int Type);

	void update_bullet(float dt);

	void update_laser(float dt);

};

#endif