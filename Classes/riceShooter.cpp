#include "riceShooter.h"
#include "Global.h"
#include "riceBullet.h"
#include <iostream>

riceShooter::riceShooter(Point position, int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("riceShooter.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool riceShooter::isWorking()
{
	return true;
}

void riceShooter::work()
{
	CreateBullet();
}

void riceShooter::Die()
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

void riceShooter::Self_Animation()
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

void riceShooter::Attacked()
{
	//����һ���
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void riceShooter::CreateBullet()
{
	Sprite *sp = this->getImg();
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getRow() == this->getRow())
		{
			//�Ŵ�׼�����ӵ�
			CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
			CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
			CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
			Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
			sp->runAction(sequence);
			//�ӵ��Լ���ʬ������
			Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
			//Point b = readyZombies.at(i)->getImg()->getPosition();
			//�����ӵ�
			Bullet *pb = new riceBullet(a, readyZombies.at(i), this->getRow());
			setNewBirthTime();
		}
	}
}

void riceShooter::clear(Node * pSender)
{

	pSender->removeFromParent();
}
