#include "Lifebar.h"
#include "cocos2d.h"
#include "TOTAL_DEFINE.h"

USING_NS_CC;

Lifebar * Lifebar::createLifebar(const char* Name, int lifenum)
{
	Lifebar* lifebar = new Lifebar();
	int counter = 0;
	Sprite* sprite;
	if (lifebar && lifenum)
	{
		lifebar->Lifenum = lifenum;
		for (int i = 0; i<lifenum;i++)
		{
			lifebar->Filename = Name;
			sprite = Sprite::create(Name);
			if (sprite)
			{
				sprite->setContentSize(Size(25, 25));
				lifebar->push_back(sprite);
				counter++;
			}
		}

			return lifebar;
	}

	delete lifebar;
	return nullptr;
}

void Lifebar::PlaceLifebar(Point p,Node* Paraent)
{
	if (Lifenum && this->at(0))
	{
		Paraent->addChild(this->at(0));
		this->at(0)->setPosition(p);
		for (int i = 0; i < Lifenum - 1; i++)
		{
			this->at(i)->getParent()->addChild(this->at(i+1));
			this->at(i + 1)->setPosition(this->at(i)->getPosition() + distance);
		}
	}
}

void Lifebar::addLife()
{
	if (Lifenum)
	{
		auto p = this->at(Lifenum - 1)->getPosition();
		auto sprite = Sprite::create(Filename);
		this->at(Lifenum - 1)->getParent()->addChild(sprite);
		sprite->setContentSize(Size(25, 25));
		sprite->setPosition(p + distance);
		Lifenum++;
		this->push_back(sprite);
	}
}

void Lifebar::reduceLife()
{
	if (this->Lifenum)
	{
		this->at(Lifenum - 1)->removeFromParent();
		this->pop_back();
		this->Lifenum--;
	}
}