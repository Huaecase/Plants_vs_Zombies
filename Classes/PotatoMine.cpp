#include "PotatoMine.h"
#include "PotatoBullet.h"
#include "Global.h"
#include <iostream>



PotatoMine::PotatoMine(Point position, int row,int col)
{
	this->maxHp = 10;
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("1.1.png");
	this->setImg(sp);
	this->birthDelay = 5;

	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(Point(position.x, position.y - 15));
	this->setHp(this->maxHp);
	this->setInterval(2000);
	this->position = Point(position.x, position.y - 15);
	//�ӳٳ���
	CCDelayTime* delayTime = CCDelayTime::create(this->birthDelay);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::Born_Animation, this));
	Sequence *sequence = Sequence::create(delayTime, actionDone, NULL);
	sp->runAction(sequence);
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}


bool PotatoMine::isWorking()
{
	return true;
}

void PotatoMine::work()
{
	//�����ײ��ǰ
	if (bornFinish)
	{
		for (int i = 0; i < readyZombies.size(); i++)
		{

			Zombie* zombie = readyZombies.at(i);
			if (this->getRow() == zombie->getRow() && this->getImg()->boundingBox().intersectsRect(zombie->getImg()->getBoundingBox()))
			{
				std::cout << "�е��ˣ���ը��" << std::endl;
				CreateBullet();
				Die();
				break;
			}
		}
	}
}

void PotatoMine::Die()
{
	if (this->bornFinish)
	{
		std::cout << "��ɣ��ը" << std::endl;
		//�����Ƴ���������������
		clear(this->getImg());
		//���屬ըЧ��
		Sprite* sp = Sprite::create("Explode1.png");
		sp->retain();
		sp->setScale(0.6);
		sp->setPosition(Point(position.x + 10, position.y + 20));
		addLayer(sp);
		//��ը����
		SpriteFrame *sp1;
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 2; i <= 4; i++)
		{
			sprintf(str, "Explode%d.png", i);
			sp1 = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
			allframe.pushBack(sp1);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
		//�����궯��֮����������
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::removeSprite, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
	}
	else
	{
		clear(this->getImg());
	}
	
}

void PotatoMine::removeSprite(Node *pSender)
{
	std::cout << "�����Ƴ�" << std::endl;
	pSender->removeFromParent();
}

void PotatoMine::Self_Animation()
{
	if (this->bornFinish)
	{
		std::cout << "��ɣ��������" << std::endl;
		SpriteFrame *sp;
		Vector<SpriteFrame*> allframe;
		char str[100] = { 0 };
		for (int i = 8; i <= 13; i++)
		{
			sprintf(str, "%d.1.png", i);
			sp = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
			allframe.pushBack(sp);
		}
		for (int j = 13; j >= 8; j--)
		{
			sprintf(str, "%d.1.png", j);
			sp = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
			allframe.pushBack(sp);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
	}
}
//��������
void PotatoMine::Born_Animation(Node *pSender)
{
	std::cout << "��ɣ׼������" << std::endl;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	SpriteFrame *sp;
	for (int i = 2; i <= 8; i++)
	{
		sprintf(str, "%d.1.png", i);
		sp = SpriteFrame::create(str, this->getImg()->getDisplayFrame()->getRect());
		allframe.pushBack(sp);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::afterBornHandle, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
}
void PotatoMine::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}
//����֮���Ӧ�еĲ���
void PotatoMine::afterBornHandle(Node *pSender)
{
	//���ó���boolֵ
	this->bornFinish = true;
	//���¶��徫��ͼƬ
	this->getImg()->removeFromParent();
	Sprite* sp = Sprite::create("9.1.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(this->position);
	//��ӵ�ֲ���
	addLayer(sp);
	//�ж���û������
	//if (this->getHp() < this->maxHp)
	//{
	//	work();
	//}
	//����գ�۶���
	Self_Animation();
}

//�������ε��ӵ�
void PotatoMine::CreateBullet()
{
	//������ը��
	std::cout << "�����ӵ�" << std::endl;
	Sprite *sp = this->getImg();
	//��������
	Point a = ccp(sp->getPositionX()+sp->getContentSize().width/2*sp->getScaleX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	//ֻ��Ҫnewһ���Լ����ӵ�����
	Bullet *pb = new PotatoBullet(a,this->getRow());
}

void PotatoMine::clear(Node *pSender)
{
	std::cout << "�����Ƴ�" << std::endl;
	pSender->removeFromParent();
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
}