#ifndef _HELP_H_
#define _HELP_H_

#include <stdio.h>
#include"cocos2d.h"

using namespace cocos2d;
using namespace std;

class HelpLayer :public Layer
{
public:

	bool init();

	Size windowSize;

	static Scene* createHelpScene();

	void closeGame(Ref* object);

	void backToStart(Ref* object);

	CREATE_FUNC(HelpLayer);

};

#endif