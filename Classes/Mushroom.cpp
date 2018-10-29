#include "Mushroom.h"
#include "MushroomBullet.h"
#include "Global.h"
#include <iostream>

Mushroom::Mushroom(Point position, int row,int col)
{
	this->haveBullet = false;
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("Mushroom.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	this->Scale = this->getImg()->getScale();
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(1200);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}
//�����ӵ��Ķ���
void Mushroom::CreateBullet()
{
	if (!this->haveBullet)
	{
		this->haveBullet = true;
		//���õ�ǰ�ƶ��Ķ���
		Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this->getImg());
		//���Ų����ӵ��Ķ���
		CCScaleBy * scaleup = CCScaleBy::create(0.1f, 0.8f, 0.8f);
		CCScaleBy * scaledown = CCScaleBy::create(0.1f, 1.5625f, 1.5625f);
		CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 0.8f);
		Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
		this->getImg()->runAction(CCRepeatForever::create(sequence));
		//�����ӵ�
		Sprite *sp = this->getImg();
		//ֲ�����ĵ�X���ֲ꣬�����ĵ�+1/4ֲ��߶ȵ�Y����
		Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
		MushroomBullet *pb = new MushroomBullet(a, this->getRow());
		//�ص�����������ӵ����ӵ�����ʱ��Ϊ5��;
		CCDelayTime* delayTime = CCDelayTime::create(1);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Mushroom::clearBullet, this, pb));
		Sequence *sequence1 = Sequence::create(delayTime, actionDone, NULL);
		this->getImg()->runAction(sequence1);
	}
}

void Mushroom::Self_Animation()
{
	Sprite *sp = this->getImg();
	//���õ�ǰ�ƶ��Ķ���
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	//�������µ��ƶ�����
	sp->setScale(this->Scale);
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

void Mushroom::clear(Node * pSender)
{
	pSender->removeFromParent();
}

void Mushroom::clearBullet(Node *pSender, MushroomBullet *bp)
{
	//�����ӵ�
	bp->getImg()->removeFromParent();
	bp->clear(bp->getImg());
	//����ʱ��
	this->setNewBirthTime();
	this->haveBullet = false;
	//���²��Ŷ���
	Self_Animation();
}

void Mushroom::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	clear(this->getImg());

}


