#include "SmallMushRoom.h"
#include "MushroomBullet.h"
#include "Global.h"
#include <iostream>

SmallMushRoom::SmallMushRoom(Point position, int row, int col)
{
	this->haveBullet = false;
	this->attackCol = 2;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("SmallMushRoom\\SmallMushroom.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.2);
	this->Scale = this->getImg()->getScale();
	sp->setPosition(position);
	this->setHp(5);
	this->setInterval(2000);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

void SmallMushRoom::CreateBullet()
{
	if (!this->haveBullet)
	{
		this->haveBullet = true;
		//���Ų����ӵ��Ķ���
		CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
		CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
		CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
		Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
		this->getImg()->runAction(sequence);
		//�����ӵ�
		Sprite *sp = this->getImg();
		//ֲ�����ĵ�X���ֲ꣬�����ĵ�+1/4ֲ��߶ȵ�Y����
		Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
		MushroomBullet *pb = new MushroomBullet(a, this->getRow(), 0.8, 0.5);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(SmallMushRoom::clearBullet, this));
		//���ӵ������ʱһ���������������ʱ�䣬�ز�����
		Sequence *sequence1 = Sequence::create(CCDelayTime::create(0.5), actionDone, NULL);
		this->getImg()->runAction(sequence1);
	}
}

void SmallMushRoom::Self_Animation()
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

void SmallMushRoom::clearBullet(Node * pSender)
{
	//����ʱ��
	this->setNewBirthTime();
	this->haveBullet = false;
}
