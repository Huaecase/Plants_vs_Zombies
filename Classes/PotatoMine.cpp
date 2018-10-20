#include "PotatoMine.h"
#include "PotatoBullet.h"
#include "Global.h"
#include <iostream>



PotatoMine::PotatoMine(Point position)
{
	Sprite*sp = Sprite::create("1.1.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	this->position = position;
	//�ӳٳ���
	CCDelayTime* delayTime = CCDelayTime::create(1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::Born_Animation, this, position));
	Sequence *sequence = Sequence::create(delayTime, actionDone, NULL);
	sp->runAction(sequence);
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool PotatoMine::isWorking()
{
	return false;
}

void PotatoMine::work()
{
}

void PotatoMine::Die()
{
	std::cout << "��ɣ��ը" << std::endl;
	//�����Ƴ���������������
	clear(this->getImg());
	//���屬ըЧ��
	Sprite* sp = Sprite::create("Explode1.png");
	sp->retain();
	sp->setScale(0.6);
	sp->setPosition(this->position);
	addLayer(sp);
	//��ը����
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 2; i <= 4; i++)
	{
		sprintf(str, "Explode%d.png", i);
		sp1 = SpriteFrame::create(str, Rect(0, 0, 150, 100));
		allframe.pushBack(sp1);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
	//�����궯��֮����������
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::removeSprite, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
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
			sp = SpriteFrame::create(str, Rect(0, 0, 90, 70));
			allframe.pushBack(sp);
		}
		for (int j = 13; j >= 8; j--)
		{
			sprintf(str, "%d.1.png", j);
			sp = SpriteFrame::create(str, Rect(0, 0, 90, 70));
			allframe.pushBack(sp);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
	}
}

void PotatoMine::Born_Animation(Node *pSender, Point position)
{
	std::cout << "��ɣ׼������" << std::endl;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	SpriteFrame *sp;
	for (int i = 2; i <= 7; i++)
	{
		sprintf(str, "%d.1.png", i);
		sp = SpriteFrame::create(str, Rect(0, 0, 90, 70));
		allframe.pushBack(sp);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::afterBornHandle, this, position));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
}
//����֮���Ӧ�еĲ���
void PotatoMine::afterBornHandle(Node *pSender,Point position)
{
	//���ó���boolֵ
	//std::cout << "�������"<<std::endl;
	this->bornFinish = true;
	//���¶��徫��ͼƬ
	this->getImg()->removeFromParent();
	Sprite* sp = Sprite::create("8.1.png");
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(position);
	//��ӵ�ֲ���
	addLayer(sp);
	//����գ�۶���
	Self_Animation();
}

//������ʱ�Ĳ���
void PotatoMine::Attacked()
{
	if (bornFinish)
	{
		CreateBullet();
		Die();
	}
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
	Bullet *pb = new PotatoBullet(a);
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