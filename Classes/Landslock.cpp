#include "Landslock.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

Landslock::Landslock(Point position, int row)
{
	this->setRow(row);
	Sprite*sp = Sprite::create("Landslock.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(1000);
	this->setInterval(2000);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool Landslock::isWorking()
{
	return true;
}

void Landslock::work()
{

}

void Landslock::driveOut(Zombie* zombie)
{
	Sprite *sp_zb = zombie->getImg();
	//��ͣ��ʬ�Ķ���
	zombie->getImg()->getActionManager()->removeAllActionsByTag(Animation_Tag, zombie->getImg());
	//����Ч��
	Sprite*sp_frigthen = Sprite::create("frigthen.png");
	sp_frigthen->setPosition(Point(sp_zb->getPositionX() + sp_zb->getContentSize().width / 4, sp_zb->getPositionY() + sp_zb->getContentSize().height));
	sp_frigthen->retain();
	sp_frigthen->setScale(1);
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp_frigthen, 100);
	//���λ��
	srand((unsigned)time(NULL));
	//int cnt = rand() % 2;
	int cnt = 0;
	MoveTo *moveTo;
	int moveRow;
	switch (cnt)
	{
		//�����ƶ�
		case 0:
		{
			if ((zombie->getRow() + 1) <= MapRow)
			{
				moveTo = MoveTo::create(1, ccp(sp_zb->getPositionX() - sp_zb->getContentSize().width * sp_zb->getScaleX() / 4, sp_zb->getPositionY() - BlockSize.second));
				moveRow = 1;
			}
			else
			{
				moveTo = MoveTo::create(1, ccp(sp_zb->getPositionX() - sp_zb->getContentSize().width * sp_zb->getScaleX() / 4, sp_zb->getPositionY() + BlockSize.second));
				moveRow = -1;
			}
			break;
		}
		//�����ƶ�
		case 1:
		{
			if ((zombie->getRow() - 1) >= 1)
			{
				moveTo = MoveTo::create(1, ccp(sp_zb->getPositionX() - sp_zb->getContentSize().width * sp_zb->getScaleX() / 4, sp_zb->getPositionY() + BlockSize.second));
				moveRow = -1;
			}
			else
			{
				moveTo = MoveTo::create(1, ccp(sp_zb->getPositionX() - sp_zb->getContentSize().width * sp_zb->getScaleX() / 4, sp_zb->getPositionY() - BlockSize.second));
				moveRow = 1;
			}
			break;
		}
	}
	zombie->setMeeting(false);
	//�����ı佩ʬ������
	zombie->setRow(zombie->getRow() + moveRow);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Landslock::clearNode, this, sp_frigthen));
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Landslock::afterDriveOut, this, zombie, moveRow));
	Sequence *sequence = Sequence::create(CCDelayTime::create(0.5), actionDone, moveTo, actionDone1, NULL);
	sp_zb->runAction(sequence);
}

void Landslock::afterDriveOut(Node* pSender, Zombie* zombie, int changeRow)
{
	//�ָ�����
	zombie->Move();
}

void Landslock::clearNode(Node * sPender, Sprite* sp)
{
	sp->removeFromParent();
}

void Landslock::Die()
{
}
//û�д˷���
void Landslock::Attacked()
{
	//������Ч
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 47, 79, 79);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	this->getImg()->runAction(sequence);
	//��⽩ʬ�Ƿ�����ǰ��
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		if (this->getRow() == zombie->getRow() && this->getImg()->boundingBox().intersectsRect(zombie->getImg()->getBoundingBox()) && this->getImg()->getPositionY() == zombie->getImg()->getPositionY())
		{
			std::cout << "��˹�������ʬ��" << std::endl;
			driveOut(zombie);
			break;
		}
	}
}

void Landslock::Self_Animation()
{
	//�����ǷŴ���С��Q��
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(CCRepeatForever::create(sequence1));
}

void Landslock::CreateBullet()
{
}
