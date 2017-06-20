#include "GameOverLayer.h"
#include "StartLayer.h"
#include "RollingLayer.h"

Scene* GameOverLayer::createOverScene(Scoreboard* scoreboard2)
{
	Scene* overscene = Scene::create();

	GameOverLayer* gameover = GameOverLayer::create();

	gameover->scoreboard = scoreboard2;
	gameover->Score_show = Label::create("hello", "Arial", 45);
	gameover->Score_show->setPosition(Vec2(366, 666));
	auto i =gameover->scoreboard->begin();
	Scoreboard *score=new Scoreboard;

	for (;i!= gameover->scoreboard->end();i++)
	{
		if (*i != '0')
		{
			for (; i != gameover->scoreboard->end(); i++)
				score->push_back(*i);
			break;
		}
		else if (i + 1 == gameover->scoreboard->end())
			score->push_back('0');
	}
	gameover->scoreboard = score;
	gameover->Score_show->setString("You only get "+*score+" scores");
	gameover->Score_show->setColor(ccc3(199, 21, 133));
	gameover->addChild(gameover->Score_show, 8);
	
	overscene->addChild(gameover);

	delete score;

	return overscene;
}

bool GameOverLayer::init()
{
	if (Layer::init())
	{
		windowSize = getContentSize();

		Sprite* overImg = Sprite::create("over.jpg");

		overImg->setAnchorPoint(Vec2(0, 1));

		overImg->setPosition(Vec2(0, windowSize.height));

		this->addChild(overImg);

		Label* show_score = Label::create();

		Sprite* normal = Sprite::create("closeN.jpg");
		Sprite* selected = Sprite::create("closeS.jpg");

		MenuItemSprite* overBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(GameOverLayer::closeGame, this));
		Menu* list_over = Menu::create(overBtn, NULL);

		list_over->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));

		this->addChild(list_over);

		Sprite* normal_back = Sprite::create("backN.jpg");
		Sprite* selected_back = Sprite::create("backS.jpg");

		MenuItemSprite* backBtn = MenuItemSprite::create(normal_back, selected_back, CC_CALLBACK_1(GameOverLayer::backToStart, this));
		Menu* list_back = Menu::create(backBtn, NULL);

		list_back->setPosition(Vec2(windowSize.width / 2, windowSize.height / 3));

		this->addChild(list_back);

		return true;
	}

	return false;
}
void GameOverLayer::closeGame(Ref* object)
{
	CCDirector::sharedDirector()->end();
	exit(0);
}
void GameOverLayer::backToStart(Ref* object)
{
	TransitionRotoZoom* anmation = TransitionRotoZoom::create(1, StartLayer::createGameStartScene());
	Director::getInstance()->replaceScene(anmation);
}