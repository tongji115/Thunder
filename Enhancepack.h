#ifndef  _ENHANCE_PACK_
#define _ENHANCE_PACK_

#include "cocos2d.h"
#include "TOTAL_DEFINE.h"
class Enhancepack :public cocos2d::Sprite
{
public:
	static Enhancepack* createEnhancepack(const char* Name,int type);
	void Enhancepackmove();
	int Type;
	void update_Enhancepack_delete(float dt);
};
#endif 
