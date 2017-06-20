#include "ChapterⅡ.h"
#include "Player.h"
#include "Bullet.h"
#include "TOTAL_DEFINE.h"
#include "Enemey.h"
#include "Lifebar.h"
#include "Enhancepack.h"
#include "StartLayer.h"
#include "GameOverLayer.h"
#include "Scoreboard.h"
#include "RollingLayer.h"

Scene* Chapter2::creatChapter2(int Lifenum2, Scoreboard* scoreboard2)
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	PhysicsWorld* phyworld = scene->getPhysicsWorld();
	phyworld->setGravity(Vect(0, 0));

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto layer = Chapter2::create();


	

	layer->scoreboard = Scoreboard::creatScoreboard();

	layer->scoreboard =scoreboard2;
	layer->Score_show = Label::create("hello", "Arial", 45);
	layer->Score_show->setPosition(Vec2(666, 1566));
	layer->Score_show->setString(*layer->scoreboard);
	layer->Score_show->setColor(ccc3(255, 140, 0));
	layer->addChild(layer->Score_show, 8);

	layer->lifebar = Lifebar::createLifebar("hahaha.png", Lifenum2);
	layer->lifebar->PlaceLifebar(Point(10, visibleSize.height - 10), layer);

	scene->addChild(layer);
	return scene;
}

bool Chapter2::init()
{
	if (Layer::init())
	{
		visibleSize = Director::getInstance()->getVisibleSize();

		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		SimpleAudioEngine::getInstance()->playBackgroundMusic("Alone.mp3",true);

		

		auto rolling_1_1 = MoveTo::create(15, Point(0, -visibleSize.height));
		auto rolling_1_2 = MoveTo::create(15, Point(0, 0));
		auto rolling_2_1 = MoveTo::create(15, Point(0, 0));
		auto rolling_2_2 = MoveTo::create(15, Point(0, -visibleSize.height));

		auto jump_1 = MoveTo::create(0, Point(origin.x, origin.y + visibleSize.height));
		auto jump_2 = MoveTo::create(0, Point(origin.x, origin.y + visibleSize.height));

		auto rolling_1_combine = Sequence::create(rolling_1_1, jump_1, rolling_1_2, NULL);
		auto rolling_2_combine = Sequence::create(rolling_2_1, rolling_2_2, jump_2, NULL);

		auto rolling_1_repeat = RepeatForever::create(rolling_1_combine);
		auto rolling_2_repeat = RepeatForever::create(rolling_2_combine);

		auto layer_rolling_1 = Sprite::create("Chapter2.jpg");//修改需要的背景
		layer_rolling_1->setContentSize(Size(800, 1600));
		layer_rolling_1->setAnchorPoint(Vec2(0, 0));
		layer_rolling_1->setPosition(origin);
		layer_rolling_1->runAction(rolling_1_repeat);


		auto layer_rolling_2 = Sprite::create("Chapter2.jpg");
		layer_rolling_2->setContentSize(Size(800, 1600));
		layer_rolling_2->setAnchorPoint(Vec2(0, 0));
		layer_rolling_2->setPosition(Vec2(origin.x, origin.y + 1600));
		layer_rolling_2->runAction(rolling_2_repeat);
		this->addChild(layer_rolling_1, 0);
		this->addChild(layer_rolling_2, 0);

	


		player = Player::creatWithPicture("player2.png");
		player->setPosition(Vec2(visibleSize.width / 2, 0));
		this->addChild(player, 2);

		Sprite*backN = Sprite::create("backBtn.png");
		Sprite*backS = Sprite::create("backBtnS.png");

		MenuItemSprite* backBtn = MenuItemSprite::create(backN, backS, CC_CALLBACK_1(Chapter2::backToStart, this));
		Menu* list_back = Menu::create(backBtn, NULL);

		list_back->setAnchorPoint(Vec2(0, 1));
		list_back->setPosition(770, 100);

		this->addChild(list_back, 10);

		Sprite*stopN = Sprite::create("StopN.png");
		Sprite*stopS = Sprite::create("StopS.png");

		MenuItemSprite* stopBtn = MenuItemSprite::create(stopN, stopS, CC_CALLBACK_1(Chapter2::stop, this));
		Menu* list_stop = Menu::create(stopBtn, NULL);

		list_stop->setAnchorPoint(Vec2(0, 1));
		list_stop->setPosition(770, 300);

		this->addChild(list_stop, 10);

		Sprite*stopmusicN = Sprite::create("StopMusicN.png");
		Sprite*stopmusicS = Sprite::create("StopMusicS.png");

		MenuItemSprite* stopmusicBtn = MenuItemSprite::create(stopmusicN, stopmusicS, CC_CALLBACK_1(Chapter2::stopmusic, this));
		Menu* list_stopmusic = Menu::create(stopmusicBtn, NULL);

		list_stopmusic->setAnchorPoint(Vec2(0, 1));
		list_stopmusic->setPosition(770, 400);

		this->addChild(list_stopmusic, 10);


		//auto enemey = Enemey::createEnemey("Enemey_1.png", 1);

		//enemey->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));

		//this->addChild(enemey, 1);

		//enemey->enemeyRun();
		//enemey->enemeyRepeatShoot();

		schedule(schedule_selector(Chapter2::update), 0.1, kRepeatForever, 0);
		
		schedule(schedule_selector(Chapter2::updateEnemey), 2, kRepeatForever, 0);
		schedule(schedule_selector(Chapter2::updateEnemey2), 0.5, 1, 4);
		schedule(schedule_selector(Chapter2::updateEnemey3), 8, 1, 8);
		schedule(schedule_selector(Chapter2::updateEnemey4), 0.5, 10, 10);
		schedule(schedule_selector(Chapter2::updateEnemey5), 8, kRepeatForever, 0);
		schedule(schedule_selector(Chapter2::updateEnemey6), 10, kRepeatForever, 0);

		schedule(schedule_selector(Chapter2::updateEnhancepack), 10, kRepeatForever, 0);
		schedule(schedule_selector(Chapter2::CheckHp), 0.1);

		return true;
	}
	return false;
}

void Chapter2::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			recorder[0] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			recorder[1] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			recorder[2] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			recorder[3] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			recorder[4] = 1;
			break;

		}

	};

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			recorder[0] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			recorder[1] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			recorder[2] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			recorder[3] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			recorder[4] = 0;
			break;

		}
	};

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [&](PhysicsContact &contact)
	{
		auto spriteA = contact.getShapeA()->getBody()->getNode();
		auto spriteB = contact.getShapeB()->getBody()->getNode();

		Node* enemeytemp = nullptr;
		if (spriteA->getTag() == MY_BULLET && spriteB->getTag() == ENEMEY)
		{
			if (!spriteA->isVisible() || !spriteB->isVisible())
			{
				return false;
			}
			spriteA->setVisible(false);
			spriteB->setVisible(false);
			spriteB->unschedule(schedule_selector(Enemey::updateshoot));
			scoreboard->Scoreboard_add_num("100");
			Score_show->setString(*scoreboard);


		}

		if (spriteA->getTag() == ENEMEY && spriteB->getTag() == MY_BULLET)
		{
			if (!spriteA->isVisible() || !spriteB->isVisible())
			{
				return false;
			}
			spriteB->setVisible(false);
			spriteA->setVisible(false);
			spriteA->unschedule(schedule_selector(Enemey::updateshoot));
			scoreboard->Scoreboard_add_num("100");
			Score_show->setString(*scoreboard);

		}

		if ((spriteA->getTag() == ENEMEY_BULLET || spriteA->getTag() == ENEMEY) && spriteB->getTag() == FRIEND)
		{
			if (!spriteA->isVisible() || !spriteB->isVisible())
			{
				return false;
			}
			spriteA->setVisible(false);
			lifebar->reduceLife();
		}

		if ((spriteB->getTag() == ENEMEY_BULLET || spriteB->getTag() == ENEMEY) && spriteA->getTag() == FRIEND)
		{
			if (!spriteA->isVisible() || !spriteB->isVisible())
			{
				return false;
			}
			spriteB->setVisible(false);
			lifebar->reduceLife();
		}

		if (spriteA && spriteB && spriteB->getTag() == FRIEND && spriteA->getTag() == ENHANCE_PACK)
		{
			if (!spriteA->isVisible() || !spriteB->isVisible())
			{
				return false;
			}
			Enhancepack* enhancepack = (Enhancepack*)spriteA;

			switch (enhancepack->Type)
			{
			case HEALTH_PACK:
				lifebar->addLife();
				break;
			case WEAPON_PACK_1:
				player_bullet_type = WEAPON_PACK_1;
				break;
			case WEAPON_PACK_2:
				player_bullet_type = WEAPON_PACK_2;
				break;
			}

			enhancepack->setVisible(false);
			this->unschedule(schedule_selector(Chapter2::update_set_player_normal));
			this->schedule(schedule_selector(Chapter2::update_set_player_normal), 3, 1, 0);

		}

		if (spriteA->getTag() == FRIEND && spriteB->getTag() == ENHANCE_PACK)
		{
			if (!spriteA->isVisible() || !spriteB->isVisible())
			{
				return false;
			}
			Enhancepack* enhancepack = (Enhancepack*)spriteB;

			switch (enhancepack->Type)
			{
			case HEALTH_PACK:
				lifebar->addLife();
				break;
			case WEAPON_PACK_1:
				player_bullet_type = WEAPON_PACK_1;
				break;
			case WEAPON_PACK_2:
				player_bullet_type = WEAPON_PACK_2;
				break;
			}

			enhancepack->setVisible(false);
			this->unschedule(schedule_selector(Chapter2::update_set_player_normal));
			this->schedule(schedule_selector(Chapter2::update_set_player_normal), 3, 1, 0);
		}
		return true;
	};





	_eventDispatcher = Director::getInstance()->getEventDispatcher();

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Chapter2::update(float dt) {
	checkmove();
}

void Chapter2::checkmove()
{



	if (recorder[0]) {
		auto flipxAction = FlipX::create(false); player->runAction(flipxAction);
		if (player->getPositionX() <= 150)
		{
			auto move_left = MoveTo::create(0.1, Point(50, player->getPositionY()));
			player->runAction(move_left);
		}
		else
		{
			auto move_left = MoveTo::create(0.1, Point(player->getPositionX() - 100, player->getPositionY()));
			player->runAction(move_left);
		}
	}

	if (recorder[1]) {
		auto flipxAction = FlipX::create(true); player->runAction(flipxAction);
		if (player->getPositionX() >= visibleSize.width - 150)
		{
			auto move_right = MoveTo::create(0.1, Vec2(visibleSize.width - 50, player->getPositionY()));
			player->runAction(move_right);
		}
		else
		{
			auto move_right = MoveTo::create(0.1, Vec2(player->getPositionX() + 100, player->getPositionY()));
			player->runAction(move_right);
		}
	}

	if (recorder[2]) {
		auto flipxAction = FlipY::create(false); player->runAction(flipxAction);
		if (player->getPositionY() >= visibleSize.height - 150)
		{
			auto move_up = MoveTo::create(0.1, Point(player->getPositionX(), visibleSize.height - 50));
			player->runAction(move_up);
		}
		else
		{
			auto move_up = MoveTo::create(0.1, Point(player->getPositionX(), player->getPositionY() + 100));
			player->runAction(move_up);
		}
	}

	if (recorder[3]) {
		auto flipxAction = FlipY::create(true); player->runAction(flipxAction);
		if (player->getPositionY() <= 150)
		{
			auto move_down = MoveTo::create(0.1, Point(player->getPositionX(), 50));
			player->runAction(move_down);
		}
		else
		{
			auto move_down = MoveTo::create(0.1, Point(player->getPositionX(), player->getPositionY() - 100));
			player->runAction(move_down);
		}
	}
	if (recorder[4]) {

		if (player_bullet_type == NORMAL_BULLET)
		{
			auto bullet = Bullet::createBullet("bullet_1.png", FRIEND, Vec2(0, 500));

			this->addChild(bullet, 1);

			bullet->bulletShootFrom(player, 1);
		}
		else if (player_bullet_type == WEAPON_PACK_1) {


			auto bullet_1 = Bullet::createBullet("bullet_3.png", FRIEND, Vec2(-100, 500));
			auto bullet_2 = Bullet::createBullet("bullet_5.png", FRIEND, Vec2(0, 500));
			auto bullet_3 = Bullet::createBullet("bullet_6.png", FRIEND, Vec2(100, 500));

			this->addChild(bullet_1, 1);
			this->addChild(bullet_2, 1);
			this->addChild(bullet_3, 1);

			bullet_1->bulletShootFrom(player, 1);
			bullet_2->bulletShootFrom(player, 1);
			bullet_3->bulletShootFrom(player, 1);
		}
		else if (player_bullet_type == WEAPON_PACK_2) {
			auto bullet = Bullet::createBullet("bullet_7.png", FRIEND, Vec2(0, 250));
			auto visibleSize = Director::getInstance()->getVisibleSize();
			bullet->setContentSize(Size(25, 50));
			bullet->bulletShootFrom(player, 2);

			this->addChild(bullet, 1);
		}

	}
}


void Chapter2::updateEnemey(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto enemey = Enemey::createEnemey("Enemey_1.png", 1);
	enemey->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height - 100));
	this->addChild(enemey, 1);


	enemey->enemeyRun();
	if (enemey->isVisible())
		enemey->schedule(schedule_selector(Enemey::updateshoot), 0.1, 20, 0);

}

void Chapter2::updateEnemey2(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto enemey2 = Enemey::createEnemey("Enemey_2.png", 2);
	enemey2->setRotation(270);
	enemey2->setPosition(Vec2(0, 800));
	enemey2->setScale(1);

	this->addChild(enemey2, 2);

	enemey2->enemeyRun();


}

void Chapter2::updateEnemey3(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto enemy1 = Enemey::createEnemey("Enemey_3.png", 3);
	auto enemy2 = Enemey::createEnemey("Enemey_3.png", 4);
	auto enemy3 = Enemey::createEnemey("Enemey_3.png", 5);
	//出发位置
	enemy1->setPosition(Vec2(visibleSize.width / 4, visibleSize.height));
	enemy2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 100));
	enemy3->setPosition(Vec2(visibleSize.width / 4 * 3, visibleSize.height));
	//调节比例
	enemy1->setScale(0.8);
	enemy2->setScale(0.8);
	enemy3->setScale(0.8);

	this->addChild(enemy1, 1);
	this->addChild(enemy2, 1);
	this->addChild(enemy3, 1);

	enemy1->enemeyRun();
	enemy2->enemeyRun();
	enemy3->enemeyRun();

	if (enemy1->isVisible())
		enemy1->schedule(schedule_selector(Enemey::updateshoot), 0.1, 20, 0);
	if (enemy2->isVisible())
		enemy2->schedule(schedule_selector(Enemey::updateshoot), 0.1, 20, 0);
	if (enemy3->isVisible())
		enemy3->schedule(schedule_selector(Enemey::updateshoot), 0.1, 20, 0);
}

void Chapter2::updateEnemey4(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//敌机在右上角
	auto enemy1 = Enemey::createEnemey("Enemey_4.png", 6);
	enemy1->setPosition(Vec2(visibleSize.width, visibleSize.height));
	enemy1->setScale(0.8);

	this->addChild(enemy1, 1);

	enemy1->enemeyRun();

}

void Chapter2::updateEnemey5(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto stone = Enemey::createEnemey("stone_1.png", 7);
	stone->setPosition(Vec2((rand_0_1()*visibleSize.width), visibleSize.height + 30));
	stone->setScale(0.5);

	this->addChild(stone, 1);

	stone->enemeyRun();

}

void Chapter2::updateEnemey6(float dt)
{//碉堡似的飞机（打不死且与屏幕同步滚动）
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto enemy = Enemey::createEnemey("Enemey_5.png", 8);
	enemy->setPosition(Vec2((rand_0_1()*visibleSize.width), visibleSize.height));
	enemy->setScale(0.8);
	enemy->setTag(FRIEND);

 	this->addChild(enemy, 1);

	enemy->enemeyRun();
}

void Chapter2::updateEnhancepack(float dt)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();

	srand((unsigned)time(NULL));
	auto enhancepack = Enhancepack::createEnhancepack("blood.png", 1);
	int Ram = random(1, 3);
	if (Ram == 1)
		enhancepack = Enhancepack::createEnhancepack("blood.png", Ram);
	else if (Ram == 2)
		enhancepack = Enhancepack::createEnhancepack("weapon1.png", Ram);
	else
		enhancepack = Enhancepack::createEnhancepack("weapon2.png", Ram);


	this->addChild(enhancepack);
	enhancepack->setPosition(Point(random(50, (int)visibleSize.width - 50), random(300, (int)visibleSize.height - 50)));
	enhancepack->Enhancepackmove();
}

void Chapter2::update_set_player_normal(float dt)
{
	player_bullet_type = NORMAL_BULLET;
}

void Chapter2::backToStart(Ref* object)
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	TransitionRotoZoom* anmation = TransitionRotoZoom::create(1, StartLayer::createGameStartScene());
	Director::getInstance()->replaceScene(anmation);
}

void Chapter2::stop(Ref* object)
{
	Vector<Node*>vec = getChildren();
	for (auto i : vec)
		i->pause();
	pause();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	Sprite* playN = Sprite::create("ContinueN.png");
	Sprite* playS = Sprite::create("ContinueS.png");

	MenuItemSprite* continueBtn = MenuItemSprite::create(playN, playS, CC_CALLBACK_1(Chapter2::ContinueGame, this));
	play = Menu::create(continueBtn, NULL);

	play->setAnchorPoint(Vec2(0, 1));
	play->setPosition(400, 500);

	this->addChild(play);
}

void Chapter2::ContinueGame(Ref* object)
{
	Vector<Node*>vec = getChildren();
	for (auto i : vec)
		i->resume();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	removeChild(play);

	resume();
}

void Chapter2::CheckHp(float time)
{
	if (lifebar->Lifenum == 0)
	{
		Director::getInstance()->replaceScene(GameOverLayer::createOverScene(scoreboard));
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void Chapter2::stopmusic(Ref* object)
{
	MenuItemSprite* btn = (MenuItemSprite*)object;
	if (musicOn)
	{
		musicOn = false;
		btn->setNormalImage(Sprite::create("StopMusicS.png"));
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		musicOn = true;
		btn->setNormalImage(Sprite::create("StopMusicN.png"));
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}