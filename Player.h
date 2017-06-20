#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
class Player :public cocos2d::Sprite
{

public: 
	static Player* creatWithPicture(const char* PictureName);                       //创建PLayer Static的目的是为了可以在没有实例的时候就调用这个“构造”函数


};
#endif
