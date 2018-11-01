#include "Cushaw.h"
#include "Global.h"

Cushaw::Cushaw(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cushaw.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(3);
	sp->setPosition(position);
	this->setHp(25);
	this->setInterval(0);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

void Cushaw::Attacked()
{
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	this->getImg()->runAction(sequence);
	if (this->getHp() < 5)
	{
		auto sprite = Sprite::create("cushaw_2.png");
		this->getImg()->setTexture(sprite->getTexture());
	}
	else if (this->getHp() < 15)
	{
		auto sprite = Sprite::create("cushaw_1.png");
		this->getImg()->setTexture(sprite->getTexture());
	}
}
