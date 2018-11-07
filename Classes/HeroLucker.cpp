#include "HeroLucker.h"
#include "Global.h"
#include "HeroLuckerBullet.h"
#include <iostream>

HeroLucker::HeroLucker(Point position, int row, int col)
{
	this->position = position;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("HeroLucker\\HeroLucker.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(8000);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

void HeroLucker::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
}

void HeroLucker::CreateBullet()
{
	//���Ų����ӵ��Ķ���
	CCScaleBy * scaleup = CCScaleBy::create(0.1f, 0.8f, 0.8f);
	CCScaleBy * scaledown = CCScaleBy::create(0.1f, 1.5625f, 1.5625f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 0.8f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		Point a = zombie->getImg()->getPosition();
		HeroLuckerBullet *pb = new HeroLuckerBullet(a, zombie->getRow());
	}
	setNewBirthTime();
}

void HeroLucker::Self_Animation()
{
	//Q��Ч��
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	CCActionInterval * moveBy = CCMoveBy::create(1, ccp(7, 0));
	CCActionInterval * actionmoveback = moveBy->reverse();
	CCFiniteTimeAction * spawn1 = CCSpawn::create(sequence1, moveBy, NULL);
	CCFiniteTimeAction * spawn2 = CCSpawn::create(sequence1, actionmoveback, NULL);
	Sequence *sequence2 = Sequence::create(spawn1, spawn2, NULL);
	sp->runAction(CCRepeatForever::create(sequence2));
}

void HeroLucker::clearBullet(Node * pSender, HeroLuckerBullet * bp)
{
	//�����ӵ�
	bp->getImg()->removeFromParent();
	bp->clear(bp->getImg());
	//����ʱ��
	this->setNewBirthTime();
}
