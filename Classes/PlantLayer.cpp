#include "PlantLayer.h"
PlantLayer* PlantLayer::create()
{
	PlantLayer *pRet = new PlantLayer();
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
bool PlantLayer::init() {
	//����дʱ�䶨ʱ��
	return true;
}

//ֲ������
void PlantLayer::Produce_Plants(float t) {

}