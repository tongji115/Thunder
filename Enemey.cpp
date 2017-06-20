#include "Enemey.h"
#include "TOTAL_DEFINE.h"
#include "cocos2d.h"

USING_NS_CC;

Enemey* Enemey::createEnemey(const char * PictureNames, int Types)
{
	Enemey* enemey = new Enemey();
	if (enemey&&enemey->initWithFile(PictureNames))
	{
		
		enemey->EnemeyTypes = Types;

		enemey->autorelease();
		enemey->setAnchorPoint(Vec2(0.5, 0.5));
		enemey->setTag(ENEMEY);


		auto body = PhysicsBody::createCircle(enemey->getContentSize().width/4);
		body->setCategoryBitmask(0x02);
		body->setCollisionBitmask(0x00);
		body->setContactTestBitmask(COLLISION_TRUE);

		enemey->setPhysicsBody(body);

		enemey->schedule(schedule_selector(Enemey::updatedelete), 0.5, kRepeatForever, 0);

		return enemey;

	}

	CC_SAFE_DELETE(enemey);
	return nullptr;
	
}




void Enemey::enemeyRun()
{
	//设置不同敌人的运行轨迹
	switch (EnemeyTypes)
	{
	case 1: {
		auto move_1 = MoveBy::create(1, Vec2(-100, -100));
		auto move_2 = MoveBy::create(1, Vec2(200, -100));
		auto move_3 = MoveBy::create(1, Vec2(-200, -100));
		//auto actionMoveDone = CallFuncN::create([&](Ref* sender) {
		//this->removeFromParent();
		//}); 
		auto movement_unit = Sequence::create(move_3, move_2, NULL);
		auto movement = RepeatForever::create(movement_unit);
		this->runAction(movement);
		//
		break;
	}
	case 2: {//左边画弧的敌机

			 //设置贝塞尔曲线参数  
		ccBezierConfig tr0;
		tr0.endPosition = Vec2(-10, 200);//终点  
		tr0.controlPoint_1 = Vec2(250, 400);//控制点1  
		tr0.controlPoint_2 = Vec2(180, 300);//控制点2  


		ActionInterval* bezierForward = BezierTo::create(3.f, tr0);//创建运行的贝塞尔曲线  
		ActionInterval *forwardBy = RotateBy::create(3.f, 180);     // 第二个参数：如果是正数则是顺时针，否则逆时针   
		Spawn* spawn = Spawn::create(bezierForward, forwardBy, NULL);//创建合成动作  

		this->runAction(spawn);
		break;
	}
	case 3: {//一组自上而下的飞机（三个左边那架）

		auto visibleSize = Director::getInstance()->getVisibleSize();

		float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素  
		float flyLen = visibleSize.height;
		float realFlyDuration = flyLen / flyVelocity; //飞行时间

		auto move = MoveBy::create(realFlyDuration, Vec2(0, -visibleSize.height - 100));

		this->runAction(move);


		break;
	}
	case 4: {//一组自上而下的飞机（三个中间那架）

		auto visibleSize = Director::getInstance()->getVisibleSize();

		float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素  
		float flyLen = visibleSize.height;
		float realFlyDuration = flyLen / flyVelocity; //飞行时间

		auto move = MoveBy::create(realFlyDuration, Vec2(0, -visibleSize.height - 100));

		this->runAction(move);

		break;
	}
	case 5: {//一组自上而下的飞机（三个右边那架）

		auto visibleSize = Director::getInstance()->getVisibleSize();

		float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素  
		float flyLen = visibleSize.height;
		float realFlyDuration = flyLen / flyVelocity; //飞行时间

		auto move = MoveBy::create(realFlyDuration, Vec2(0, -visibleSize.height - 100));

		this->runAction(move);

		break;
	}
	case 6: {//从右上角出现朝着自己飞机飞的敌机
		auto visibleSize = Director::getInstance()->getVisibleSize();

		//计算自己飞机和对角点连起的线与边界的角度
		float x = this->getParent()->getChildByTag(FRIEND)->getPosition().x;
		float y = this->getParent()->getChildByTag(FRIEND)->getPosition().y;
		float a = visibleSize.width - x;
		float b = visibleSize.height - y;
		// 弧度转角度  
		float radians = atanf(a / b);
		float mDegree = CC_RADIANS_TO_DEGREES(radians);
		this->setRotation(180 + mDegree);
		//敌机的最终位置
		float endX = visibleSize.width - (visibleSize.height + 10)*a / b;
		float endY = -10;
		//计算飞行时间  
		float flyVelocity = 600;//运行速度，可以自己控制，每秒所走的像素  
		float flyLen = sqrt((visibleSize.width - endX)*(visibleSize.width - endX) + (visibleSize.height - endY)*(visibleSize.height - endY));
		float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间 

		auto move = MoveTo::create(realFlyDuration, Point(endX, endY));

		this->runAction(move);

		break;
	}
	case 7: {//掉下来的石头
		auto visibleSize=Director::getInstance()->getVisibleSize();

		auto move = MoveBy::create(3, Vec2(0, -visibleSize.height-5));

		auto action = EaseSineIn::create(move);
		 
		this->runAction(action);
	}
	case 8: {//打不死且与屏幕同步滚动的飞机
		auto visibleSize = Director::getInstance()->getVisibleSize();

		auto move = MoveBy::create(15, Point(0, -visibleSize.height));

		this->runAction(move);
	}
	}
}




void Enemey::updateshoot(float dt)
{

	switch (EnemeyTypes)
	{
	case 1: {
		auto bullet = Bullet::createBullet("bullet_2.png", ENEMEY, Vec2(0, -500));
		this->getParent()->addChild(bullet, 1);
		bullet->bulletShootFrom(this, 1);
		break;
	}
	case 2:
	case 3: {
		auto bullet = Bullet::createBullet("bullet_2.png", ENEMEY, Vec2(0, -500));
		this->getParent()->addChild(bullet, 1);
		bullet->bulletShootFrom(this, 1);
		break;
	}
	case 4: {
		auto bullet = Bullet::createBullet("bullet_2.png", ENEMEY, Vec2(0, -500));
		this->getParent()->addChild(bullet, 1);
		bullet->bulletShootFrom(this, 1);
		break;
	}
	case 5: {
		auto bullet = Bullet::createBullet("bullet_2.png", ENEMEY, Vec2(0, -500));
		this->getParent()->addChild(bullet, 1);
		bullet->bulletShootFrom(this, 1);
		break;
	}
	case 6: 
		break;
	}
}


void Enemey::enemeyRepeatShoot()
{
	this->schedule(schedule_selector(Enemey::updateshoot), 0.2, 10, 0);
}

void Enemey::updatedelete(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (this->getPositionY() > visibleSize.height
		|| this->getPositionX() > visibleSize.width
		|| this->getPositionX() < 0
		|| this->getPositionY() < 0)
	{
		this->stopAllActions();
		this->removeFromParentAndCleanup(true);
	}
}