#include "Lancer.h"
#include "Global.h"
#include "LancerGun.h"
#include <iostream>

Lancer::Lancer(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Lancer.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	
	//��ӵ�ֲ���
	this->addLayer(sp);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

void Lancer::CreateBullet()
{
	//�Ŵ�׼�����ӵ�
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	//�ӵ��Լ���ʬ������
	Point a = ccp(this->getImg()->getPositionX(), this->getImg()->getContentSize().height * this->getImg()->getScaleY() / 4 + this->getImg()->getPositionY());
	//�����ӵ�
	Bullet *pb = new LancerGun(a, this->getRow());
	setNewBirthTime();
}

