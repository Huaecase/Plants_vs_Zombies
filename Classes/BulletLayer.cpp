#include "BulletLayer.h"

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
	return true;
}

//ֲ������
void BulletLayer::Produce_Bullets(float t) {

}