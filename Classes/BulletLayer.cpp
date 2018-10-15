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
	this->schedule(schedule_selector(BulletLayer::test), 0.1);
	return true;
}


//�ӵ�����
void BulletLayer::Produce_Bullets(float t) {
	if (preBullet.size() != 0) 
	{
		Bullet* bullet = preBullet.front();
		Sprite *sp = bullet->getImg();
		this->addChild(sp);
		Sprite *hole = bullet->attack_Animation();
		if (hole != NULL)
		{
			this->addChild(hole);
		}
		readyBullet.push_back(bullet);
		bullet->work();
		bullet->move();
		preBullet.erase(preBullet.begin());
	}
}

void BulletLayer::test(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < readyBullet.size(); i++) 
	{
		Bullet*bullet = readyBullet.at(i);
		Sprite*sp = bullet->getImg();
		for (int j = 0; j < testMap.size(); j++)
		{
			if (sp->boundingBox().intersectsRect(testMap.at(j)->getImg()->getBoundingBox()))
			{
				std::cout << "��ײ��" << std::endl;
				bullet->Hit_Animation(testMap.at(j));
			}
		}
	}
}
void BulletLayer::clear1(Node *pSender)
{
	//std::cout << "�����Ľ����������" << std::endl;
	pSender->removeFromParent();
}

