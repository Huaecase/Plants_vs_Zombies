#include "BulletLayer.h"
#include "Global.h"
#include <iostream>
BulletLayer* BulletLayer::pRet=NULL;
BulletLayer* BulletLayer::create()
{
	BulletLayer::pRet = new BulletLayer();
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
	this->schedule(schedule_selector(BulletLayer::test), 0.1);
	return true;
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


