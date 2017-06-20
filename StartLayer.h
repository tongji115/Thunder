#ifndef StartLayer_hpp
#define StartLayer_hpp

#include <stdio.h>
#include"cocos2d.h"

using namespace cocos2d;
using namespace std;

class StartLayer :public Layer
{
public:

	static Scene* createGameStartScene();

	bool init();

	Size windowSize;

	void startAction(Ref* object);
	void helpAction(Ref* object);
	void closeAction(Ref* object);

	CREATE_FUNC(StartLayer);
};

#endif /* StartLayer_hpp */