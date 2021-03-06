#include "MushroomBullet.h"
#include "Global.h"
#include <iostream>

MushroomBullet::MushroomBullet()
{
}

MushroomBullet::MushroomBullet(Point position, int Plant_row) :Bullet(position, 0.1, 0)
{
	this->existTime = 1;
	this->getRange()->push_back(Plant_row);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Mushroom\\Attack\\1.png"));
	sp->setAnchorPoint(Point::ZERO);
	//方便以后获取子弹精灵
	this->setImg(sp);
	this->setDamage(1);
	this->getImg()->setTag(Penetrable_tag);
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(position.x + sp->getContentSize().width * sp->getScaleX() / 0.8, position.y);
	this->addLayer(sp);
	readyBullet.push_back(this);
	this->attack_Animation();
}

MushroomBullet::MushroomBullet(Point position, int Plant_row, float Scale, float existTime)
{
	this->existTime = existTime;
	this->getRange()->push_back(Plant_row);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Mushroom\\Attack\\1.png"));
	sp->setAnchorPoint(Point::ZERO);
	//方便以后获取子弹精灵
	this->setImg(sp);
	this->setDamage(1);
	// this->getImg()->setTag(Penetrable_tag);
	sp->retain();
	sp->setScale(Scale);
	sp->setPosition(position.x + sp->getContentSize().width * sp->getScaleX() / 0.8, position.y);
	this->addLayer(sp);
	readyBullet.push_back(this);
	this->attack_Animation();
}

void MushroomBullet::move()
{
}

void MushroomBullet::clear(Node * pSender)
{
	pSender->removeFromParent();
	pSender->removeAllChildrenWithCleanup(true);
	Sprite* sp = this->getImg();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ActionInterval * fadeout = FadeOut::create(0.3);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(MushroomBullet::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}

void MushroomBullet::clearNode(Node * pSender)
{
	pSender->removeAllChildrenWithCleanup(true);
	pSender->removeFromParent();
}
//播放攻击动画
void MushroomBullet::attack_Animation()
{
	SpriteFrame *sp;
	Sprite* bulletSprite = this->getImg();
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "Mushroom\\Attack\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
	//回调函数，清除子弹，子弹持续时间为1秒;
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(MushroomBullet::clear, this));
	Sequence *sequence1 = Sequence::create(CCDelayTime::create(existTime), actionDone, NULL);
	this->getImg()->runAction(sequence1);
}

void MushroomBullet::Hit_Animation(Zombie * zombie)
{
}

