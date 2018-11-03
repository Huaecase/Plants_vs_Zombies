#include "LancerGun.h"
#include "Global.h"
#include "Paul.h"

LancerGun::LancerGun(Point a, int Plant_row)
{
	this->setDamage(2);
	this->getRange()->push_back(Plant_row);
	auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Cannon\\Gun.png"));
	sprite->setScale(0.2);
	this->setImg(sprite);
	sprite->retain();
	sprite->setPosition(a.x + sprite->getContentSize().width*sprite->getScaleX() / 2, a.y);
	this->addLayer(sprite);
	readyBullet.push_back(this);
	this->findTarget();
	//�ƶ�����
	this->move();
}

void LancerGun::move()
{
	if (this->targetZb != NULL)
	{
		//����������
		Sprite*sp = this->getImg();
		Point TargetPoint = this->targetZb->getImg()->getPosition();
		Point targetPoint = Point(TargetPoint.x - this->targetZb->getWalkSpeed() * 2, TargetPoint.y);

		// �ѽǶ�ת��Ϊ����
		float radian = 70 * 3.14159 / 180.0;
		// ��һ�����Ƶ�Ϊ��������뻡���е�
		float q1x = sp->getPosition().x + (targetPoint.x - sp->getPosition().x) / 4.0;
		CCPoint q1 = ccp(q1x, 0 + targetPoint.y + cos(radian)*q1x);
		// �ڶ������Ƶ�Ϊ���������ߵ��е�
		float q2x = sp->getPosition().x + (targetPoint.x - sp->getPosition().x) / 2.0;
		CCPoint q2 = ccp(q2x, 0 + sp->getPosition().y + cos(radian)*q2x);

		ccBezierConfig cfg;
		cfg.controlPoint_1 = q1;
		cfg.controlPoint_2 = q2;
		cfg.endPosition = targetPoint;
		//ʹ��CCEaseInOut�������˶���һ����������ı仯���Եø���Ȼ
		CCEaseInOut* test = CCEaseInOut::create(CCBezierTo::create(2, cfg), 0.5);
		CCRotateBy* rotate = CCRotateBy::create(2, 50);
		CCSpawn* spawn = CCSpawn::create(test, rotate, NULL);
		CallFuncN* actionDone = actionDone = CallFuncN::create(CC_CALLBACK_1(riceBullet::clear, this));
		CCSequence* sequence = CCSequence::create(spawn, actionDone, NULL);
		sp->runAction(sequence);
	}
}
