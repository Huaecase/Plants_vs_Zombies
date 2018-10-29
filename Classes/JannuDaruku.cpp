#include "JannuDaruku.h"
#include "Global.h"
#include <iostream>
JannuDaruku::JannuDaruku(Point position,int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("Jannu.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.25);
	this->position = position;
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	//��ӵ�ֲ��㣨��ʾ��
	addLayer(sp);
	//��������die
	Die();
}

bool JannuDaruku::isWorking()
{
	return false;
}

void JannuDaruku::work()
{
	
}

void JannuDaruku::Die()
{
	//�������
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//��±��ͷŻ����ϳɶ���
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::MyFire, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);

	sp->runAction(sequence);
}

void JannuDaruku::MyFire(Node *pSender)
{
	//�Ѿɾ����Ƴ�
	this->getImg()->removeFromParent();
	//����Ч��
	creatFire();
	//���ͬ�Ž�ʬ
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getRow() == this->getRow())
		{
			std::cout << "�����ʬ" << std::endl;
			zombiesDie(readyZombies.at(i)->getImg());
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void JannuDaruku::zombiesDie(Node* pSender)
{
	//��¼��ԭ����ʬ�ı�Ҫ��Ϣ
	Point zombiePoint = pSender->getPosition();
	float scale = pSender->getScale();
	//ֹͣ��ʬ���ж���
	pSender->getActionManager()->removeAllActionsFromTarget(pSender);
	//��ʬ��������
	ActionInterval * fadeout = FadeOut::create(0.5);
	//��ʬ����ɫ����
	CCActionInterval * tintby = CCTintTo::create(0.5, 0, 0, 0);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
	Sequence *sequence = Sequence::create(tintby, fadeout, actionDone,NULL);
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
}
//����������飬ʵ��һ�л���
void JannuDaruku::creatFire()
{
	Sprite*sp = Sprite::create("Fire1.png");
	sp->retain();
	sp->setScale(1.5);

	SpriteFrame *sp1;
	Vector<SpriteFrame*> allframe;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	char str[100] = { 0 };
	for (int i = 1; i <= 7; i++)
	{
		sprintf(str, "Fire%d.png", i);
		sp1 = SpriteFrame::create(str, sp->getDisplayFrame()->getRect());
		allframe.pushBack(sp1);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);

	for (int x = 0; x < visibleSize.width; x += 200)
	{
		Sprite*sp = Sprite::create("Fire8.png");
		sp->retain();
		sp->setScale(1.5);
		//sp->setPosition(this->position);
		sp->setPosition(Point(x, this->position.y - 10));
		addLayer(sp);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
	}
}

void JannuDaruku::Attacked()
{
}

void JannuDaruku::CreateBullet()
{
}

void JannuDaruku::clear(Node * pSender)
{
	pSender->removeFromParent();
}
