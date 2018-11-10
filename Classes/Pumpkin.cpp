#include "Pumpkin.h"
#include "Global.h"
#include <iostream>

Pumpkin::Pumpkin(Point position, int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	this->position = position;
	this->attackRange = 100.0f;
	this->jumpDuration = 1.0f;
	this->isJumping = false;
	this->isChecking = false;

	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Pumpkin\\Pumpkin.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.27);
	sp->setPosition(position);
	this->setHp(100);
	this->setInterval(0.5);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool Pumpkin::isWorking()
{
	return true;
}

void Pumpkin::work()
{
	if (!this->isChecking)
	{
		CheckZombies();
	}
	
}

void Pumpkin::CheckZombies()
{
	for (int i = 0; i < readyZombies.size() && !this->isJumping; i++)
	{
		this->isChecking = true;
		if (readyZombies.at(i)->getRow() == this->getRow()
			&& readyZombies.at(i)->getImg()->getPositionX() - this->position.x <= this->attackRange 
			&& readyZombies.at(i)->getImg()->getPositionX() - this->position.x >= 0
			&& !this->isJumping)
		{
			this->isJumping = true;
			JumpTo(readyZombies.at(i));
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
		this->isChecking = false;
	}
	
}
//��̤
void Pumpkin::JumpTo(Zombie* zombie)
{
	//ͣ��������
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this->getImg());
	//�ƶ�����ʬ�Ϸ�������Ŵ�
	//std::cout << "������" << std::endl;
	float height = 0;
	float preScale = this->getImg()->getScaleX();
	Point p = Point(zombie->getImg()->getPositionX() - this->jumpDuration*zombie->getWalkSpeed(),this->position.y + 50);
	CCActionInterval * jumpto = CCJumpTo::create(this->jumpDuration, p, height, 0.5);
	CCScaleBy * scale1 = CCScaleBy::create(0.5f,  1.25,  0.8);
	CCScaleBy * scale2 = CCScaleBy::create(0.15f,  0.64,  1.5625);
	CCScaleBy * scale3 = CCScaleBy::create(0.35f, 1.25, 0.8);
	CCScaleBy * scale4 = CCScaleBy::create(0.5f, 1.25, 0.8);
	Sequence * sequence0 = Sequence::create(scale2, scale3, NULL);
	//y�����������ϳ�
	Spawn * spawn1 = Spawn::create(sequence0, jumpto, NULL);

	MoveTo *moveTo = MoveTo::create(0.5, ccp(p.x, p.y - 50));

	//ֲ����׹��x������ϳ�
	Spawn * spawn3 = Spawn::create(moveTo, scale4, NULL);

	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Pumpkin::press, this, zombie));
	Sequence * sequence3 = Sequence::create(CCDelayTime::create(0.1), actionDone1, NULL);
	Spawn * spawn4 = Spawn::create(spawn3, sequence3, NULL);

	Sequence *sequence = Sequence::create(scale1, spawn1, spawn4, NULL);
	
	this->getImg()->runAction(sequence);
	
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
}

////��������
//void Pumpkin::FallDown(Node * pSender, Point p)
//{
//	std::cout << "���䣡" << std::endl;
//	MoveTo *moveTo = MoveTo::create(0.5, ccp(p.x, p.y - 50));
//	CCActionInterval * easeSineIn = CCEaseSineIn::create(moveTo);
//	this->getImg()->runAction(easeSineIn);
//}

//ѹ�⽩ʬ
void Pumpkin::press(Node * pSender, Zombie* zombie)
{
	zombie->getImg()->getActionManager()->removeAllActionsFromTarget(zombie->getImg());
	float preScale = zombie->getImg()->getScaleX();
	//ѹ��
	CCScaleBy * scaleupx_ZB = CCScaleBy::create(0.4f, 3, 0.01);
	//��ʬλ����΢��׹
	MoveTo *moveTo = MoveTo::create(0.5, ccp(zombie->getImg()->getPositionX(), zombie->getImg()->getPositionY() - 20));
	//�ϳɶ���
	CCFiniteTimeAction * spawn = CCSpawn::create(scaleupx_ZB, moveTo, NULL);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Pumpkin::clearZombie, this, zombie));
	Sequence *sequence = Sequence::create(spawn, actionDone1, NULL);
	zombie->getImg()->runAction(sequence);
}

void Pumpkin::Die()
{
	//��ʱ֮���������
	CCDelayTime* delayTime = CCDelayTime::create(0.5);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Pumpkin::clear, this));
	Sequence *sequence = Sequence::create(delayTime, actionDone, NULL);
	this->getImg()->runAction(sequence);
}

void Pumpkin::Self_Animation()
{
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	CCActionInterval * moveBy = CCMoveBy::create(1, ccp(8, 0));
	CCActionInterval * actionmoveback = moveBy->reverse();
	CCFiniteTimeAction * spawn1 = CCSpawn::create(sequence1, moveBy, NULL);
	CCFiniteTimeAction * spawn2 = CCSpawn::create(sequence1, actionmoveback, NULL);
	Sequence *sequence2 = Sequence::create(spawn1, spawn2, NULL);
	sp->runAction(CCRepeatForever::create(sequence2));
}

void Pumpkin::Attacked()
{
}

void Pumpkin::clearZombie(Node * pSender, Zombie* zombie)
{
	zombie->getImg()->removeFromParent();
	//����Ҳ����
	//�������
	this->setHp(-1);
}

void Pumpkin::clear(Node * pSender)
{
	pSender->removeFromParent();
}
