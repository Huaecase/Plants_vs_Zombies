#include "TripleShooter.h"
#include "TripleBullet.h"
#include "Global.h"
TripleShooter::TripleShooter(Point position, int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("TripleShooter.png"));
	this->setImg(sp);
	//һ��Ҫretain��������Զ��ͷ�
	sp->retain();
	sp->setScale(0.25);
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
	for (int i = 0; i < readyPlants.size(); i++)
	{
		if (readyPlants.at(i) == this)
		{
			readyPlants.erase(readyPlants.begin() + i);
			break;
		}
	}
	Sprite * sp = this->getImg();
	ActionInterval * fadeout = FadeOut::create(0.5);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TripleShooter::clear, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
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
void TripleShooter::clear(Node * pSender)
{
	pSender->removeFromParent();
}
