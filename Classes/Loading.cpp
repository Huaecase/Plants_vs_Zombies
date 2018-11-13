#include "Loading.h"
#include "EntityLayer.h"
#include <iostream>

Loading::Loading(Point position, Scene* scene, Title*title)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	sprite = Sprite::create("UI\\LoadingBar0.png");
	sprite->retain();
	sprite->setPosition(position);
	//sprite->setAnchorPoint(Vec2(0, 0));
	sprite->setScale(3.0f);
	EntityLayer* layer = EntityLayer::getInstance();
	setImg(sprite);
	auto fillSprite = Sprite::create("UI\\LoadingBar100.png");
	fillSprite->setScale(3.0f);
	timer = CCProgressTimer::create(fillSprite);//����CCProgressTimer
	timer->setPosition(position);//����CCProgressTimerλ��
	timer->setScale(3.0f);
	timer->setType(kCCProgressTimerTypeBar);//��������
	timer->setPercentage(0);//���õ�ǰ��ʼֵ
	timer->setMidpoint(CCPoint(0, 0));//���ý��ȿ�ʼ��λ��
	timer->setBarChangeRate(CCPoint(1, 0));//���ý�����ռ����
	//Sequence *sequence = Sequence::create(ProgressTo::create(2, 100), actionDone, NULL);
	scene->addChild(timer,1000);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Loading::clear, this));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Loading::afterload, this,title));
	Sequence *sequence = Sequence::create(ProgressTo::create(2, 100), actionDone, actionDone1, NULL);
	timer->runAction(sequence);
	
	
	scene->addChild(sprite,0);
}
void Loading::afterload(Node*pSender,Title*title)
{
	title->enableStartButton();
}
void Loading::clear(Node*pSender)
{
	timer->removeFromParent();
	this->getImg()->removeFromParent();
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
	if (value == 100)
	{
		std::cout << "100lee" << std::endl;
	}
}