#include "Help.h"
#include "StartLayer.h"

Scene* HelpLayer::createHelpScene()
{
	Scene* helpscene = Scene::create();

	HelpLayer* help = HelpLayer::create();

	helpscene->addChild(help);

	return helpscene;
}

bool HelpLayer::init()
{
	if (Layer::init())
	{
		windowSize = getContentSize();

		Sprite* helpImg = Sprite::create("help.png");

		helpImg->setAnchorPoint(Vec2(0, 1));

		helpImg->setPosition(Vec2(0, windowSize.height));

		this->addChild(helpImg);

		Sprite* normal = Sprite::create("closeN.jpg");
		Sprite* selected = Sprite::create("closeS.jpg");

		MenuItemSprite* overBtn = MenuItemSprite::create(normal, selected, CC_CALLBACK_1(HelpLayer::closeGame, this));
		Menu* list_over = Menu::create(overBtn, NULL);

		list_over->setPosition(Vec2(windowSize.width / 5, windowSize.height / 11));

		this->addChild(list_over);

		Sprite* normal_back = Sprite::create("backN.jpg");
		Sprite* selected_back = Sprite::create("backS.jpg");

		MenuItemSprite* backBtn = MenuItemSprite::create(normal_back, selected_back, CC_CALLBACK_1(HelpLayer::backToStart, this));
		Menu* list_back = Menu::create(backBtn, NULL);

		list_back->setPosition(Vec2(windowSize.width / 1.35, windowSize.height / 11));

		this->addChild(list_back);

		return true;
	}

	return false;
}
void HelpLayer::closeGame(Ref* object)
{

}
void HelpLayer::backToStart(Ref* object)
{
	TransitionRotoZoom* anmation = TransitionRotoZoom::create(1, StartLayer::createGameStartScene());
	Director::getInstance()->replaceScene(anmation);
}