#include "BulletLayer.h"
#include "Global.h"
#include <iostream>
BulletLayer* BulletLayer::create()
{
	BulletLayer *pRet = new BulletLayer();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}
bool BulletLayer::init() {
	//����дʱ�䶨ʱ��
	this->schedule(schedule_selector(BulletLayer::Produce_Bullets), 0.01);
	//this->schedule(schedule_selector(BulletLayer::test), 0.1);
	return true;
}


//�ӵ�����
void BulletLayer::Produce_Bullets(float t) {
	for (auto x : preBullet.keys()) {
		Sprite* sp = preBullet.at(x);
		this->addChild(sp);

		Sprite *hole = x->attack_Animation(sp);
		if (hole != NULL)
		{
			this->addChild(hole);
		}

		readyBullet.insert(x,sp);
		x->work(sp);
		x->move(sp);
		preBullet.erase(x);
	}
}

void BulletLayer::test(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (auto x : readyBullet.keys())
	{
		Sprite*sp = readyBullet.at(x);
		if (sp->getPositionX() > visibleSize.width - 200)
		{
			//std::cout << "�������н�ʬ" << std::endl;
			x->Hit_Animation(sp);
			
		}
	}
}
void BulletLayer::test1(float t) 
{
	for (auto x : readyPlants.keys())
	{
		Sprite *sp = readyPlants.at(x);
		x->Die(sp);
	}
}
void BulletLayer::clear1(Node *pSender)
{
	//std::cout << "�����Ľ����������" << std::endl;
	pSender->removeFromParent();
}

