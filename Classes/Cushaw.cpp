#include "Cushaw.h"
#include "Global.h"
#include "EntityLayer.h"
using namespace map;
Cushaw::Cushaw(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cushaw.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(2.4);
	sp->setPosition(position);
	this->setHp(25);
	this->setInterval(0);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	EntityLayer* bl = EntityLayer::getInstance();
	bl->addChild(sp, this->getRow() * 3 - 2);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}
void Cushaw::work()
{
	if (isProtecting)
	{
		return;
	}
	isProtecting = true;
	std::cout << "�Ϲ��Ѿ���ʼ����ֲ��" << std::endl;
	PlantStatus* plantstatus = find(this->getRow(), this->getCol());
	if (plantstatus != NULL)
	{
		for (int i=0;i< plantstatus->plantVector.size();i++)
		{
			Plants* x = plantstatus->plantVector.at(i);
			if (strcmp(typeid(*x).name(),"class Cushaw") == 0)
			{
				plantstatus->plantVector.erase(plantstatus->plantVector.begin() + i);
				plantstatus->plantVector.insert(plantstatus->plantVector.begin(),this);
				break;
			}
		}
	}
}
void Cushaw::Attacked()
{
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	this->getImg()->runAction(sequence);
	if (this->getHp() < 5)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cushaw_2.png"));
		this->getImg()->setTexture(sprite->getTexture());
	}
	else if (this->getHp() < 15)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cushaw_1.png"));
		this->getImg()->setTexture(sprite->getTexture());
	}
}
