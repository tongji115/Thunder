#include "Bullet.h"
#include"cocos2d.h"
#include"TOTAL_DEFINE.h"
USING_NS_CC;

Bullet* Bullet::createBullet(const char * Name, int Side, Vec2 velocity)
{
	Bullet*bullet = new Bullet();
	if (bullet&&bullet->initWithFile(Name))
	{

		bullet->autorelease();
		bullet->setContentSize(Size(50, 50));
		bullet->setAnchorPoint(Vec2(0.5, 0.5));
		bullet->bulletVelocity = velocity;

		bullet->bulletType = Side;

		return bullet;

	}
	CC_SAFE_DELETE(bullet);
	return nullptr;

}


void Bullet::bulletShootFrom(Node* p,int Type)
{
	this->setPosition(p->getPosition());
	bullet_parent = p;
	this->unscheduleUpdate();
	this->setVisible(true);
	switch (Type)
	{
	case 1:
		this->schedule(schedule_selector(Bullet::update_bullet));
		break;
	case 2:
		this->schedule(schedule_selector(Bullet::update_laser));
		break;
	}



}

void Bullet::update_bullet(float dt)
{
	auto body = PhysicsBody::createCircle(5);


	if (bulletType == FRIEND)
	{
		this->setTag(MY_BULLET);
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x00);
		body->setContactTestBitmask(COLLISION_TRUE);                                                   //µÐ·½»úÌåµÄ½Ó´¥ÑÚÂëÒ²ÊÇ0x02
	}
	else
	{
		this->setTag(ENEMEY_BULLET);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x00);
		body->setContactTestBitmask(0x01);                                                  //ÎÒ·½»úÌåµÄÑÚÂëÊÇ0x01
	}

	this->setPhysicsBody(body);

	this->setPosition(Vec2(this->getPosition() + bulletVelocity*dt));
	Point p = this->getPosition();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (p.y>visibleSize.height || p.y<0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParentAndCleanup(true);
	}

}

void Bullet::update_laser(float dt)
{
	auto body = PhysicsBody::createBox(this->getContentSize());


	if (bulletType == FRIEND)
	{
		this->setTag(MY_BULLET);
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x00);
		body->setContactTestBitmask(COLLISION_TRUE);                                                   //µÐ·½»úÌåµÄ½Ó´¥ÑÚÂëÒ²ÊÇ0x02
	}
	else
	{
		this->setTag(ENEMEY_BULLET);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x00);
		body->setContactTestBitmask(0x01);                                                  //ÎÒ·½»úÌåµÄÑÚÂëÊÇ0x01
	}

	this->setPhysicsBody(body);

	this->getPhysicsBody()->createBox(this->getContentSize());
	this->setAnchorPoint(Vec2(0.5, 0));
	this->setPosition(Vec2(bullet_parent->getPositionX() ,this->getPositionY()+bulletVelocity.y*dt));
	Point p = this->getPosition();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (p.y>visibleSize.height|| p.y<0)
	{
		this->setVisible(false);
		this->unscheduleUpdate();
		this->removeFromParentAndCleanup(true);
	}
}