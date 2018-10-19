#pragma once
#include "cocos2d.h"
#include "Global.h"
#include "PotatoBullet.h"
#include <iostream>
USING_NS_CC;

PotatoBullet::PotatoBullet(Point position):Bullet(position,50,0)
{
	Sprite *sp = Sprite::create("sword1.png");
	//�ܲ��ܸı��С
	this->setImg(sp);
	sp->setScale(0.3);
	sp->retain();
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScaleX() / 2, position.y);
	this->addLayer(sp);
	
	readyBullet.push_back(this);
}

void PotatoBullet::move()
{
}

void PotatoBullet::clear(Node * pSender)
{
	pSender->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
}

void PotatoBullet::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

void PotatoBullet::Hit_Animation(TestZombie * zombie)
{
	//��ը��
	std::cout << "�ӵ�������ʬ" << std::endl;
	Sprite* sp = this->getImg();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}	clearNode(this->getImg());
}