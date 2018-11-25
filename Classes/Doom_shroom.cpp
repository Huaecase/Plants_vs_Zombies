#include "Doom_shroom.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

Doom_shroom::Doom_shroom()
{
}

Doom_shroom::Doom_shroom(Point position, int row, int col)
{
	this->thisIsEnd = false;
	this->position = position;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Doom_shroom.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(0);
	//��ӵ�ֲ���
	addLayer(sp);
	readyPlants.push_back(this);
}

void Doom_shroom::thisDie()
{
	//��������(����)
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//����ͱ�ը�����ϳɶ���
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::Effect, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);
	sp->runAction(sequence);
}

void Doom_shroom::Effect(Node * pSender)
{
	//�Ѿɾ����Ƴ�
	this->getImg()->removeFromParent();
	//��hp��Ϊ-1
	this->setHp(-1);
	//����Ч��
	this->creatSprite();
	//�����Χ��ʬ
	this->zombiesDie();
}

void Doom_shroom::creatSprite()
{
	//��ը����
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "Doom\\Boom%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Doom\\Boom1.png"));
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(Point(this->position.x, this->position.y + 20));
	addLayer(sp);
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearSprite, this, sp));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);

}

void Doom_shroom::zombiesDie()
{
	//�����Χ�ڽ�ʬ
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		//�жϷ�Χ
		//if(pow(zombie->getImg()->getPositionX() - this->position.x, 2) + pow(zombie->getImg()->getPositionY() - this->position.y, 2) <= 90 * 90)
		if (fabs(map::Point2Rank(zombie->getImg()->getPosition()).first - this->getRow()) <= 2 && fabs(map::Point2Rank(zombie->getImg()->getPosition()).second - this->getCol()) <= 2)
		{
			std::cout << "�����ʬ" << std::endl;
			///
			//��¼��ԭ����ʬ�ı�Ҫ��Ϣ
			Node* pSender = zombie->getImg();
			Point zombiePoint = pSender->getPosition();
			float scale = pSender->getScaleX();
			//ֹͣ��ʬ���ж���
			pSender->getActionManager()->removeAllActionsFromTarget(pSender);
			//��ʬ��������
			ActionInterval * fadeout = FadeOut::create(0.5);
			//��ʬ����ɫ����
			CCActionInterval * tintby = CCTintTo::create(0.2, 0, 0, 0);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearNode, this));
			Sequence *sequence = Sequence::create(tintby, fadeout, actionDone, NULL);
			pSender->runAction(sequence);
			//��ʬ��������Ч��
			CCParticleSystem* particleSystem = CCParticleExplosion::create();
			particleSystem->setStartColor(Color4F(0, 0, 0, 255));
			particleSystem->setPosition(zombiePoint);
			particleSystem->setLife(1);
			particleSystem->setGravity(Point(zombiePoint.x - this->position.x, zombiePoint.y - this->position.y + 50));
			particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("grain1.png"));
			particleSystem->setScale(0.3);
			particleSystem->setStartSize(90.0f);
			particleSystem->setEndSize(5.0f);
			addLayer(particleSystem);
			//�Ƴ�������
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void Doom_shroom::clearSprite(Node* pSender, Sprite* sp)
{
	std::cout << "�����Ч" << std::endl;
	sp->removeFromParent();
}