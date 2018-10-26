#include "TripleShooter.h"
#include "TripleBullet.h"
#include "Global.h"
TripleShooter::TripleShooter(Point position, int row)
{
	this->setRow(row);
	Sprite*sp = Sprite::create("TripleShooter.png");
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	//��ֲͨ��ֱ�Ӳ���������
	this->Self_Animation();
	//��ӵ�ֲ���
	addLayer(sp);
	//��ӵ��Ѵ���ֲ��������������Ϊ�������ڴ˴�
	readyPlants.push_back(this);
}

bool TripleShooter::isWorking()
{
	return true;
}

void TripleShooter::work()
{
	if(isWorking())
	CreateBullet();
}

void TripleShooter::Die()
{
}

void TripleShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite *sp = this->getImg();
	//ֲ�����ĵ�X���ֲ꣬�����ĵ�+1/4ֲ��߶ȵ�Y����
	Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	Bullet *pb = new TripleBullet(a, this->getRow(),1);
	Bullet *pb1 = new TripleBullet(a, this->getRow(), 2);
	Bullet *pb2 = new TripleBullet(a, this->getRow(), 3);
	setNewBirthTime();
}
