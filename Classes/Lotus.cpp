#include "Lotus.h"
#include "Global.h"
Lotus::Lotus(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Lotus\\Self_Animation\\1.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position.x,position.y-1.3*sp->getContentSize().height);
	this->setHp(6);
	this->setInterval(0);
	//��ֲͨ��ֱ�Ӳ�����������
	this->Self_Animation();
	//���ӵ�ֲ���
	addLayer(sp);
	//���ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool Lotus::isWorking()
{
	return false;
}

void Lotus::work()
{
}

void Lotus::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Lotus::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void Lotus::Self_Animation()
{
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 3; i++)
	{
		sprintf(str, "Lotus\\Self_Animation\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
	auto animation = RepeatForever::create(Animate::create(an));
	this->getImg()->runAction(animation);
}

void Lotus::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Lotus::clear(Node * pSender)
{
	pSender->removeFromParent();
}