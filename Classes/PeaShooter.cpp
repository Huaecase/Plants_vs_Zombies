#include "PeaShooter.h"
#include "PeaBullet.h"
#include "Global.h"
#include <iostream>

//相当于init
PeaShooter::PeaShooter(Point position,int row,int col) 
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("peaShooter.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.25);
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

PeaShooter::PeaShooter() 
{
}
bool PeaShooter::isWorking()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : readyZombies)
	{
		if (this->getRow() == x->getRow() && x->getImg()->getPositionX() < visibleSize.width&&x->getImg()->getPositionX()>this->getImg()->getPositionX())
		{
			return true;
		}
	}
	return false;
}
void PeaShooter::work()
{
	if (isWorking())
	{
		CreateBullet();
	}
		
}


void PeaShooter::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void PeaShooter::Self_Animation()
{
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
void PeaShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite *sp = this->getImg();
	//植物中心点X坐标，植物中心点+1/4植物高度的Y坐标
	Point a = ccp(sp->getPositionX() , sp->getContentSize().height*sp->getScaleY()/ 4 + sp->getPositionY());
	Bullet *pb = new PeaBullet(a,this->getRow());
	setNewBirthTime();
}

