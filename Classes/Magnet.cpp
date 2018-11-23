#include "Magnet.h"
#include "Global.h"
#include <iostream>

Magnet::Magnet(Point position, int row, int col)
{
	this->attracted = false;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Magnet\\Magnet.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.25);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(5000);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool Magnet::isWorking()
{
	if(!this->attracted)
		return true;
	return false;
}

void Magnet::work()
{
	if (isWorking())
	{
		attractEquiment();
	}
}

void Magnet::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	clearNode(this->getImg());
}

void Magnet::Self_Animation()
{
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(0.7f, preScale, preScale + 0.05);
	CCScaleTo * scaledown = CCScaleTo::create(0.3f, preScale, preScale);
	Sequence *sequence1 = Sequence::create(scaleup, scaledown, NULL);
	sp->runAction(CCRepeatForever::create(sequence1));
}

void Magnet::attractEquiment()
{
	for (auto x : readyZombies)
	{
		Sprite *sp = x->MagnetEquip();
		if (sp != NULL)
		{
			sp->setZOrder(this->getRow() * 3 - 3);
			this->attracted = true;
			//��װ��������
			MoveTo *moveTo = MoveTo::create(1, Point(this->getImg()->getPositionX() + this->getImg()->getContentSize().width / 8 ,this->getImg()->getPositionY() - this->getImg()->getContentSize().height / 20));
			CCRotateBy* rotate = CCRotateBy::create(1, 70);
			CCSpawn* spawn = CCSpawn::create(moveTo, rotate, NULL);
			sp->runAction(spawn);
			//��ʱ�ָ�
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(Magnet::recover, this, sp));
			Sequence *sequence = Sequence::create(CCDelayTime::create(4), actionDone, NULL);
			//ֹͣ����
			Director::getInstance()->getActionManager()->removeAllActionsFromTarget(this->getImg());
			sp->runAction(sequence);
			setNewBirthTime();
			break;
		}
	}
}
void Magnet::recover(Node* sPender, Sprite* Equiment)
{
	this->Self_Animation();
	this->attracted = false;
	//װ������
	Equiment->removeFromParent();
}
