#include "riceShooter.h"
#include "Global.h"
#include "riceBullet.h"
#include <iostream>

riceShooter::riceShooter(Point position, int row)
{
	this->setRow(row);
	Sprite*sp = Sprite::create("riceShooter.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
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
	//Q弹效果
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
	//蒙上一层红
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
			//放大，准备放子弹
			CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
			CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
			CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
			Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
			sp->runAction(sequence);
			//子弹以及僵尸的坐标
			Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
			//Point b = readyZombies.at(i)->getImg()->getPosition();
			//产生子弹
			Bullet *pb = new riceBullet(a, readyZombies.at(i), this->getRow());
			setNewBirthTime();
		}
	}
}

void riceShooter::clear(Node * pSender)
{

	pSender->removeFromParent();
}
