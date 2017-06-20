#include "Player.h"
#include "TOTAL_DEFINE.h"
USING_NS_CC;

Player* Player::creatWithPicture(const char* PictureName)
{
	Player* player = new Player();

	if (player&&player->initWithFile(PictureName)) {                                     //确定指针存在并且图片存在
		player->autorelease();
		player->setAnchorPoint(Vec2(0.5, 0.5));     //设置锚点在图片的中央
		player->setTag(FRIEND);


		auto body = PhysicsBody::createCircle(player->getContentSize().width/4);                                       
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0xFFFFFFFF);

		player->setPhysicsBody(body);                                                   //给玩家飞机一个“物理身体”
		return player;
	}

	CC_SAFE_DELETE(player);                                                            //无图片时候的操作
	return NULL;
}

