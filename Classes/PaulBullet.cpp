#include "PaulBullet.h"
#include "Global.h"

//����������Ŀ�ĵ�ַ������
PaulBullet::PaulBullet(Point position, double delayTime)
{
	this->delayTime = delayTime;
	this->position = position;
	this->setRow(map::Point2Rank(position).first);
	this->setRow(map::Point2Rank(position).second);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\LancerBullterDown.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.3);
	//��ȡ��Ļ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//����Ļ�Ϸ������ӵ�
	sp->setPosition(Point(position.x, visibleSize.height + sp->getContentSize().height / 2));
	addLayer(sp);
	this->work();
}

void PaulBullet::move()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double time = (visibleSize.height + this->getImg()->getScaleY() / 2) / speed;
	//�ƶ���Ŀ������
	MoveTo *moveTo = MoveTo::create(time, position);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PaulBullet::Effect, this));
	Sequence *sequence = Sequence::create(CCDelayTime::create(this->delayTime), moveTo, actionDone, NULL);
	this->getImg()->runAction(sequence);
}

void PaulBullet::work()
{
	this->move();
}

void PaulBullet::zombiesDie()
{
	//�����Χ�ڽ�ʬ
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		//�жϷ�Χ
		if (pow(zombie->getImg()->getPositionX() - this->position.x, 2) + pow(zombie->getImg()->getPositionY() - this->position.y, 2) <= 90 * 90)
		{
			Sprite* pSender = readyZombies.at(i)->getImg();
			//��¼��ԭ����ʬ�ı�Ҫ��Ϣ
			Point zombiePoint = pSender->getPosition();
			float scale = pSender->getScaleX();
			//ֹͣ��ʬ���ж���
			pSender->removeFromParent();
			pSender->removeAllChildrenWithCleanup(true);
			//��ʬ���鶯��
			char str[100] = { 0 };
			Vector<SpriteFrame*> allframe;
			for (int i = 2; i <= 20; i++)
			{
				sprintf(str, "Boom_Die\\Boom_Die%d.png", i);
				auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
				auto frame = sprite->getSpriteFrame();
				allframe.pushBack(frame);
			}
			Animation* an = Animation::createWithSpriteFrames(allframe, 0.15);
			auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Boom_Die\\Boom_Die1.png"));
			sp->setPosition(zombiePoint);
			sp->retain();
			sp->setScale(scale);
			addLayer(sp);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
			Sequence *sequence = Sequence::create(Animate::create(an), CCDelayTime::create(0.5), actionDone, NULL);
			sp->runAction(sequence);
			//�Ƴ�����
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void PaulBullet::creatSprite()
{
	//��ը����
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "Cannon\\Boom\\BoomSmall%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Boom\\BoomSmall1.png"));
	sp->retain();
	sp->setScale(3);
	sp->setPosition(Point(this->position.x, this->position.y + 20));
	addLayer(sp);
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearSprite, this, sp));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
}
