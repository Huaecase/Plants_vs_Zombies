#include "Loading.h"
#include "EntityLayer.h"


Loading::Loading(Point position)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	sprite = Sprite::create("UI\\LoadingBar0.png");
	sprite->retain();
	sprite->setPosition(position);
	//sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setScale(2.0f);
	EntityLayer* layer = EntityLayer::getInstance();
	layer->addChild(sprite);
	setImg(sprite);
	auto fillSprite = Sprite::create("UI\\LoadingBar100.png");
	fillSprite->setScale(2.0f);
	timer = CCProgressTimer::create(fillSprite);//����CCProgressTimer
	timer->setPosition(position);//����CCProgressTimerλ��
	timer->setScale(2.0f);
	timer->setType(kCCProgressTimerTypeBar);//��������
	timer->setPercentage(0);//���õ�ǰ��ʼֵ
	timer->setMidpoint(CCPoint(0, 0));//���ý��ȿ�ʼ��λ��
	timer->setBarChangeRate(CCPoint(1, 0));//���ý�����ռ����
	layer->addChild(timer);
}


Loading::~Loading()
{
}

float Loading::getCurrentValue()
{
	return timer->getPercentage();
}

void Loading::setCurrentValue(float value)
{
	timer->setPercentage(value);
}