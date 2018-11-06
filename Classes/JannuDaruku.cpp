#include "JannuDaruku.h"
#include "Global.h"
#include <iostream>
JannuDaruku::JannuDaruku()
{
}
JannuDaruku::JannuDaruku(Point position,int row,int col)
{
	this->thisIsEnd = false;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Jannu\\Jannu.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.25);
	this->position = position;
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(0);
	//��ӵ�ֲ��㣨��ʾ��
	addLayer(sp);
	readyPlants.push_back(this);

}

bool JannuDaruku::isWorking()
{
	return true;
}

void JannuDaruku::work()
{
	if (!thisIsEnd)
	{
		thisIsEnd = true;
		thisDie();
	}
}

void JannuDaruku::Die()
{
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
}

void JannuDaruku::thisDie()
{
	//�������
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//��±��ͷŻ����ϳɶ���
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::Effect, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);

	sp->runAction(sequence);
}

void JannuDaruku::Effect(Node *pSender)
{
	//�Ѿɾ����Ƴ�
	this->getImg()->removeFromParent();
	//��HP��Ϊ-1
	this->setHp(-1);
	//����Ч��
	this->creatSprite();
	//���ͬ�Ž�ʬ
	this->zombiesDie();
}

void JannuDaruku::zombiesDie()
{
	//������ʬ
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getRow() == this->getRow())
		{
			Sprite* pSender = readyZombies.at(i)->getImg();
			//��¼��ԭ����ʬ�ı�Ҫ��Ϣ
			Point zombiePoint = pSender->getPosition();
			float scale = pSender->getScale();
			//ֹͣ��ʬ���ж���
			pSender->removeFromParent();
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
//����������飬ʵ��һ�л���
void JannuDaruku::creatSprite()
{
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Jannu\\Fire1.png"));
	sp->retain();
	sp->setScale(1.5);

	SpriteFrame *sp1;
	Vector<SpriteFrame*> allframe;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	char str[100] = { 0 };
	for (int i = 1; i <= 7; i++)
	{
		sprintf(str, "Jannu\\Fire%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);

	for (int x = 0; x < visibleSize.width; x += 100)
	{
		auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Jannu\\Fire8.png"));
		sp->retain();
		sp->setScale(1);
		//sp->setPosition(this->position);
		sp->setPosition(Point(x, this->position.y - this->getImg()->getContentSize().height *this->getImg()->getScaleY() / 4));
		addLayer(sp);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
	}
}

void JannuDaruku::CreateBullet()
{
}

void JannuDaruku::clear(Node * pSender)
{
	pSender->removeFromParent();
}
