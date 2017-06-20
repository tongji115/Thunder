#include "Player.h"
#include "TOTAL_DEFINE.h"
USING_NS_CC;

Player* Player::creatWithPicture(const char* PictureName)
{
	Player* player = new Player();

	if (player&&player->initWithFile(PictureName)) {                                     //ȷ��ָ����ڲ���ͼƬ����
		player->autorelease();
		player->setAnchorPoint(Vec2(0.5, 0.5));     //����ê����ͼƬ������
		player->setTag(FRIEND);


		auto body = PhysicsBody::createCircle(player->getContentSize().width/4);                                       
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0xFFFFFFFF);

		player->setPhysicsBody(body);                                                   //����ҷɻ�һ�����������塱
		return player;
	}

	CC_SAFE_DELETE(player);                                                            //��ͼƬʱ��Ĳ���
	return NULL;
}

