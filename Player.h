#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
class Player :public cocos2d::Sprite
{

public: 
	static Player* creatWithPicture(const char* PictureName);                       //����PLayer Static��Ŀ����Ϊ�˿�����û��ʵ����ʱ��͵�����������족����


};
#endif
