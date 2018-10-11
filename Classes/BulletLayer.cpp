#include "BulletLayer.h"
#include "Global.h"
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
	this->schedule(schedule_selector(BulletLayer::Produce_Bullets), 0.1);
	return true;
}

//�ӵ�����
void BulletLayer::Produce_Bullets(float t) {
	for (auto x : preBullet.keys()) {
		Sprite* sp = preBullet.at(x);
		this->addChild(sp);
		readyBullet.insert(x,sp);
		x->move(sp);
		preBullet.erase(x);
	}
}

