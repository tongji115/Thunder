#ifndef LIFE_BAR_
#define LIFE_BAR_

#include "cocos2d.h"
#include "TOTAL_DEFINE.h"
class Lifebar :public std::vector<cocos2d::Sprite*>
{
public:
	int Lifenum;

	std::string Filename;

	static Lifebar * createLifebar(const char* Name, int lifenum);

	void PlaceLifebar(cocos2d::Point p,cocos2d::Node* Paraent);

	void reduceLife();

	void addLife();

	const cocos2d::Vec2 distance = cocos2d::Vec2(20, 0);

	
};

#endif
