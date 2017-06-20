#include "StartLayer.h"
#include "RollingLayer.h"
#include "Help.h"

bool StartLayer::init()
{

	if (Layer::init())
	{

		this->windowSize = this->getContentSize();

		Sprite* StartImg = Sprite::create("StartImg.jpg");
		StartImg->setAnchorPoint(Vec2(0, 1));
		StartImg->setPosition(Vec2(0, windowSize.height));

		this->addChild(StartImg);

		Sprite* normal_close = Sprite::create("closeN.jpg");
		Sprite* selected_close = Sprite::create("closeS.jpg");

		MenuItemSprite* closeBtn = MenuItemSprite::create(normal_close, selected_close, CC_CALLBACK_1(StartLayer::closeAction, this));
		Menu* list_close = Menu::create(closeBtn, NULL);

		list_close->setPosition(Vec2(this->windowSize.width / 2, this->windowSize.height / 3.5));

		this->addChild(list_close);

		Sprite* normal = Sprite::create("StartBtnN.png");
		Sprite* selected = Sprite::create("StartBtnS.png");

		MenuItemSprite* startBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(StartLayer::startAction, this));
		Menu* list = Menu::create(startBtn, NULL);

		list->setPosition(Vec2(this->windowSize.width / 2, this->windowSize.height / 2));

		this->addChild(list);

		Sprite* helpN = Sprite::create("helpN.png");
		Sprite* helpS = Sprite::create("helpS.png");

		MenuItemSprite* helpBtn = MenuItemSprite::create(helpN, helpS, CC_CALLBACK_1(StartLayer::helpAction, this));
		Menu* list_help = Menu::create(helpBtn, NULL);

		list_help->setPosition(Vec2(this->windowSize.width / 2, this->windowSize.height / 5));

		this->addChild(list_help);

		return true;
	}

	return false;
}

Scene* StartLayer::createGameStartScene()
{
	Scene* start = Scene::create();

	StartLayer* start_m = StartLayer::create();

	start->addChild(start_m);

	return start;
}

void StartLayer::startAction(Ref* object)
{
	Director* dic = Director::getInstance();

	TransitionRotoZoom* roto = TransitionRotoZoom::create(1, RollingScene::createScene());

	dic->replaceScene(roto);
}

void StartLayer::helpAction(Ref* object)
{
	Director::getInstance()->replaceScene(HelpLayer::createHelpScene());
}

void StartLayer::closeAction(Ref* object)
{
	CCDirector::sharedDirector()->end();
	exit(0);
}