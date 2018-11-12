#include "iceCabbage.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

iceCabbage::iceCabbage(Point position, int row, int col)
{
	this->thisIsEnd = false;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("IceCabbage\\IceCabbage.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	this->position = position;
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(0);
	//��ӵ�ֲ��㣨��ʾ��
	addLayer(sp);
	readyPlants.push_back(this);
}

void iceCabbage::thisDie()
{
	//÷ܽ����
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//÷ܽ����ͱ�ѩ�����ϳɶ���
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::Effect, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);
	sp->runAction(sequence);
}

void iceCabbage::Effect(Node * pSender)
{
	//�Ѿɾ����Ƴ�
	this->getImg()->removeFromParent();
	this->setHp(-1);
	//Ч������
	creatSprite();
}

void iceCabbage::creatSprite()
{
	///��ը����
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "IceCabbage\\Boom%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("IceCabbage\\Boom1.png"));
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(Point(this->position.x, this->position.y));
	addLayer(sp);
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::clear, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
	///��ը����
	//ȫͼ��ʬ����
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		if (zombie->hasHead())
		{
			if (judgeIsDriving(zombie))
			{
				//�涯��
				drivingOut = zombie->getImg()->getActionManager()->getActionByTag(DrivingOut,zombie->getImg());
				drivingOut->retain();
				zombie->getImg()->getActionManager()->removeActionByTag(DrivingOut, zombie->getImg());
			}
			zombie->getDebuff()->push_back(Freezing);
			Point freezePoint = zombie->getImg()->getPosition();

			//����һ�㵭��ɫ
			CCActionInterval * tintto2 = CCTintTo::create(0.5, 0, 255, 255);
			zombie->getImg()->runAction(tintto2);
			//��ʬֹͣ����
			zombie->Stop_Animation();

			//������������
			char str[100] = { 0 };
			Vector<SpriteFrame*> allframe;
			for (int i = 1; i <= 16; i++)
			{
				sprintf(str, "IceCabbage\\ice%d.png", i);
				//һ�������ּ��ط���
				auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
				auto frame = sprite->getSpriteFrame();
				allframe.pushBack(frame);
			}
			Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
			auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("IceCabbage\\ice16.png"));
			sp->setPosition(Point(freezePoint.x + 5, freezePoint.y + 5));
			sp->retain();
			sp->setScale(1.4);
			EntityLayer* bl = EntityLayer::getInstance();
			bl->addChild(sp, zombie->getRow() * 3 - 1);
			//����ʱ��
			CCDelayTime* delayTime = CCDelayTime::create(3);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::clearIceSprite, this, sp, zombie));
			Sequence *sequence = Sequence::create(Animate::create(an), delayTime, actionDone, NULL);
			sp->runAction(sequence);

		}
	}
}

bool iceCabbage::judgeIsDriving(Zombie* zombie)
{
	for (int i = 0; i < zombie->getDebuff()->size(); i++)
	{
		if (zombie->getDebuff()->at(i) == DrivingOut)
		{
			return true;
		}
	}
	return false;
}

void iceCabbage::zombieRun(Node * pSender,Zombie* zombie)
{
	zombie->Move();
	zombie->setMeeting(false);
}

void iceCabbage::clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie)
{
	iceSprite->removeFromParent();
	//�Ƴ�debuff
	for (int i = 0; i < zombie->getDebuff()->size(); i++)
	{
		if (zombie->getDebuff()->at(i) == Freezing)
		{
			zombie->getDebuff()->erase(zombie->getDebuff()->begin() + i);
			break;
		}
	}
	//�����ʬ����ɫ����
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	zombie->getImg()->runAction(tintto2);
	//���֮ǰ�б�����
	if (judgeIsDriving(zombie))
	{
		//ִ�л��ж�����
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(iceCabbage::zombieRun, this, zombie));
		Sequence *sequence = Sequence::create((Sequence*)drivingOut, actionDone, NULL);
		zombie->getImg()->runAction(sequence);
	}
	else
	{
		//����ֱ����
		zombieRun(this->getImg(), zombie);
	}
}