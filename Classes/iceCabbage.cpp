#include "iceCabbage.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>
iceCabbage::iceCabbage(Point position, int row)
{
	this->setRow(row);
	Sprite*sp = Sprite::create("IceCabbage\\IceCabbage.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	this->position = position;
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	//��ӵ�ֲ��㣨��ʾ��
	addLayer(sp);
	//��������die
	Die();
}

bool iceCabbage::isWorking()
{
	return true;
}

void iceCabbage::work()
{
}

void iceCabbage::Die()
{
	//÷ܽ����
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//÷ܽ����ͱ�ѩ�����ϳɶ���
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::iceWorld, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);

	sp->runAction(sequence);
}

void iceCabbage::iceWorld(Node *pSender)
{
	//�Ѿɾ����Ƴ�
	this->getImg()->removeFromParent();
	//�����ͼ���Ǳ�ѩ
	Point minPointInX = readyZombies.at(0)->getImg()->getPosition();
	for (int i = 1; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getImg()->getPositionX() < minPointInX.x)
		{
			minPointInX = readyZombies.at(i)->getImg()->getPosition();
		}
	}
	//�����ͼ���Ǳ�ѩ

	//ʹ��ʬ����
	for (int i = 0; i < readyZombies.size(); i++)
	{
		std::cout << "���Ὡʬ" << std::endl;
		freezeZombie(readyZombies.at(i));
	}
}

void iceCabbage::freezeZombie(Zombie* zombie)
{
	Point freezePoint = zombie->getImg()->getPosition();
	float scale = zombie->getImg()->getScale();
	//����һ�㵭��ɫ
	CCActionInterval * tintto2 = CCTintTo::create(3, 0, 255, 255);
	zombie->getImg()->runAction(tintto2);
	zombie->getImg()->getActionManager()->removeAllActionsByTag(Animation_Tag, zombie->getImg());
	
	//������������
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 16; i++)
	{
		sprintf(str, "IceCabbage\\ice%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);

	Sprite*sp = Sprite::create("IceCabbage\\ice16.png");
	sp->setPosition(freezePoint);
	sp->retain();
	sp->setScale(1.4);
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, 100);
	//����ʱ��
	CCDelayTime* delayTime = CCDelayTime::create(3);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::clearIceSprite, this, sp, zombie));
	Sequence *sequence = Sequence::create(Animate::create(an), delayTime, actionDone, NULL);
	sp->runAction(sequence);
}

void iceCabbage::Attacked()
{
}

void iceCabbage::CreateBullet()
{
}

void iceCabbage::clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie)
{
	iceSprite->removeFromParent();
	//�����ʬ����ɫ����
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	zombie->getImg()->runAction(tintto2);
	//��ʬ�ָ��ж�
	zombie->Move();
}

void iceCabbage::clear(Node * pSender)
{
	pSender->removeFromParent();
}
