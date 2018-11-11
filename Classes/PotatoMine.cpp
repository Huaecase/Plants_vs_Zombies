#include "PotatoMine.h"
#include "PotatoBullet.h"
#include "Global.h"
#include <iostream>



PotatoMine::PotatoMine(Point position, int row,int col)
{
	this->maxHp = 10;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("PotatoMine\\1.1.png"));
	this->setImg(sp);
	this->birthDelay = 5;

	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(Point(position.x, position.y - this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 5));
	this->setHp(this->maxHp);
	this->setInterval(1000);
	this->position = Point(position.x, position.y - this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 5);
	//�ӳٳ���
	CCDelayTime* delayTime = CCDelayTime::create(this->birthDelay);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::Born_Animation, this));
	Sequence *sequence = Sequence::create(delayTime, actionDone, NULL);
	sp->runAction(sequence);
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}


bool PotatoMine::isWorking()
{
	return true;
}

void PotatoMine::work()
{
	//�����ײ��ǰ
	if (bornFinish)
	{
		for (int i = 0; i < readyZombies.size(); i++)
		{
			Zombie* zombie = readyZombies.at(i);
			if (this->getRow() == zombie->getRow() && this->getImg()->boundingBox().intersectsRect(zombie->getImg()->getBoundingBox()))
			{
				if (strcmp(typeid(*zombie).name(), "class PoleVaultingZombie") == 0)
				{
					Vec2 pointA = this->getImg()->getPosition();
					Vec2 pointB = zombie->getImg()->getPosition();
					float distance = sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2));
					if (distance > map::BlockSize.first*0.8)
					{
						continue;
					}
				}
				std::cout << "�е��ˣ���ը��" << std::endl;
				CreateBullet();
				Die();
				break;
			}
		}
	}
}

void PotatoMine::Die()
{
	clear(this->getImg());
}

void PotatoMine::removeSprite(Node *pSender)
{
	std::cout << "�����Ƴ�" << std::endl;
	pSender->removeFromParent();
}

void PotatoMine::Self_Animation()
{
	if (this->bornFinish)
	{
		std::cout << "��ɣ��������" << std::endl;
		SpriteFrame *sp;
		Vector<SpriteFrame*> allframe;
		char str[100] = { 0 };
		for (int i = 8; i <= 13; i++)
		{
			sprintf(str, "PotatoMine\\%d.1.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		for (int j = 13; j >= 8; j--)
		{
			sprintf(str, "PotatoMine\\%d.1.png", j);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
		this->getImg()->runAction(CCRepeatForever::create(Animate::create(an)));
	}
}
//��������
void PotatoMine::Born_Animation(Node *pSender)
{
	std::cout << "��ɣ׼������" << std::endl;
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	SpriteFrame *sp;
	for (int i = 2; i <= 8; i++)
	{
		sprintf(str, "PotatoMine\\%d.1.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::afterBornHandle, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	this->getImg()->runAction(sequence);
}
void PotatoMine::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}
//����֮���Ӧ�еĲ���
void PotatoMine::afterBornHandle(Node *pSender)
{
	//���ó���boolֵ
	this->bornFinish = true;
	//���¶��徫��ͼƬ
	this->getImg()->removeFromParent();
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("PotatoMine\\9.1.png"));
	this->setImg(sp);
	sp->retain();
	sp->setScale(0.5);
	sp->setPosition(this->position);
	//��ӵ�ֲ���
	addLayer(sp);
	Self_Animation();
}

//�������ε��ӵ�
void PotatoMine::CreateBullet()
{
	if (this->bornFinish)
	{
		std::cout << "��ɣ��ը" << std::endl;
		//�����Ƴ���������������
		clear(this->getImg());
		//���屬ըЧ��
		auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("PotatoMine\\Explode1.png"));
		sp->retain();
		sp->setScale(0.6);
		sp->setPosition(Point(position.x + 10, position.y + 20));
		addLayer(sp);
		//��ը����
		char str[100] = { 0 };
		Vector<SpriteFrame*> allframe;
		for (int i = 2; i <= 4; i++)
		{
			sprintf(str, "PotatoMine\\Explode%d.png", i);
			auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
			auto frame = sprite->getSpriteFrame();
			allframe.pushBack(frame);
		}
		Animation* an = Animation::createWithSpriteFrames(allframe, 0.2);
		//�����궯��֮����������
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(PotatoMine::removeSprite, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
	}
	//������ը��
	std::cout << "�����ӵ�" << std::endl;
	Sprite *sp = this->getImg();
	//��������
	Point a = ccp(sp->getPositionX()+sp->getContentSize().width/2*sp->getScaleX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	//ֻ��Ҫnewһ���Լ����ӵ�����
	Bullet *pb = new PotatoBullet(a,this->getRow());
}

void PotatoMine::clear(Node *pSender)
{
	std::cout << "�����Ƴ�" << std::endl;
	pSender->removeFromParent();
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	this->setHp(-1);
}