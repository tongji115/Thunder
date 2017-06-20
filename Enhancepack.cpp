#include "Enhancepack.h"
#include "cocos2d.h"
#include "TOTAL_DEFINE.h"

USING_NS_CC;

Enhancepack* Enhancepack::createEnhancepack(const char * Name, int type)
{
	Enhancepack*  enhancepack = new Enhancepack();
	if (enhancepack && enhancepack->initWithFile(Name))
	{
		enhancepack->Type = type;

		enhancepack->setContentSize(Size(20, 20));
		enhancepack->setAnchorPoint(Vec2(0.5, 0.5));
		enhancepack->setTag(ENHANCE_PACK);

		auto body = PhysicsBody::createBox(enhancepack->getContentSize());
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x00);
		body->setContactTestBitmask(COLLISION_TRUE);
		enhancepack->setPhysicsBody(body);

		enhancepack->schedule(schedule_selector(Enhancepack::update_Enhancepack_delete), 5, kRepeatForever, 0);

		return enhancepack;
	}
	CC_SAFE_DELETE(enhancepack);
	return nullptr;
}

void Enhancepack::Enhancepackmove()
{
	auto move_1 = MoveBy::create(1, Vec2(-100, -100));
	auto move_2 = MoveBy::create(1, Vec2(200, -100));
	auto move_3 = MoveBy::create(1, Vec2(-200, -100));
	//auto actionMoveDone = CallFuncN::create([&](Ref* sender) {
	//this->removeFromParent();
	//});
	auto movement = Sequence::create(move_1, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		move_3, move_2,
		NULL);

	this->runAction(movement);
}

void Enhancepack::update_Enhancepack_delete(float dt)
{
	Point p = this->getPosition();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (p.y<0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParentAndCleanup(true);
	}
}