#include "TrackBullet.h"
#include "Global.h"
#include <math.h>
#include <iostream>


TrackBullet::TrackBullet(Point position, int Plant_row):Bullet(position, 2, 6)
{
	for (int i = 0; i < 10; i++)
	{
		this->getRange()->push_back(i);
	}
	Sprite *sp = Sprite::create("TrackBullet.png");
	sp->setScale(0.5);
	this->setImg(sp);
	sp->retain();
	sp->setPosition(position.x + sp->getContentSize().width*sp->getScaleX() / 2, position.y);
	this->addLayer(sp);
	readyBullet.push_back(this);
	this->move();
}

void TrackBullet::move()
{
	Rotate(this->getImg());
	/*Sprite*sp = this->getImg();
	double time = 100 / this->getSpeed()/10;
	MoveTo *moveTo = MoveTo::create(time, ccp(sp->getPositionX() +100, sp->getPosition().y));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TrackBullet::Rotate, this));
	Sequence *sequence = Sequence::create(moveTo, actionDone, NULL);
	sp->runAction(sequence);*/
}

void TrackBullet::Rotate(Node* pSender)
{
	if (readyZombies.size() == 0)
	{
		Sprite* sp = this->getImg();
		for (int i = 0; i < readyBullet.size(); i++)
		{
			if (readyBullet.at(i) == this)
			{
				readyBullet.erase(readyBullet.begin() + i);
				break;
			}
		}
		sp->removeFromParent();
		return;
	}
	double minDistance = 100000000;
	Zombie* zombie=NULL;
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Sprite *sp = readyZombies.at(i)->getImg();
		double x1 = pSender->getPositionX();
		double x2 = sp->getPositionX();
		double y1 = pSender->getPositionY();
		double y2 = sp->getPositionY();
		double dis = sqrt(pow((x1 - x2), 2)+pow(( y1- y2),2));
		if (dis < minDistance)
		{
			
			minDistance = dis;
			zombie = readyZombies.at(i);
		}
	}
	double rotation = pSender->getRotation()/180*3.14;
	Point startPoint = pSender->getPosition();
	Point endPoint = zombie->getImg()->getPosition();
	Point vec1=Point(cos(rotation), -sin(rotation));
	Point vec2 = endPoint - startPoint;
	//Vec2 dis = endPoint - startPoint;
	//�õ��ǶȵĻ���ֵ
	
	double angle = ccpAngle(vec1, vec2) / 3.14 * 180;
	
	//double sign = vec1.x * vec2.y - vec1.y * vec2.x;
    angle = -angle;
	double time = minDistance / this->getSpeed() / 20;
	ccBezierConfig tr0;
	tr0.endPosition = Point((endPoint.x-zombie->getWalkSpeed()*time),endPoint.y);//�յ�  
	tr0.controlPoint_1 = Vec2(startPoint.x+(endPoint.x-startPoint.x)/4, startPoint.y+ (endPoint.y - startPoint.y) / 4);//���Ƶ�1  
	tr0.controlPoint_2 = Vec2(startPoint.x + (endPoint.x - startPoint.x) / 2, startPoint.y + (endPoint.y - startPoint.y) / 2);//���Ƶ�2
	ActionInterval* bezierForward = BezierTo::create(time, tr0);
	ActionInterval *forwardBy = RotateBy::create(time, angle);
	Spawn* spawn = Spawn::create(bezierForward, forwardBy, NULL);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TrackBullet::Rotate, this));
	Sequence* sequence = Sequence::create(spawn, actionDone, NULL);
	pSender->runAction(sequence);
}

float TrackBullet::getAng(Point a, Point b)
{
	float angle = 0.0f; // �н�

	// ����Vector a��(x, y)����
	float va_x = a.x;
	float va_y = a.y;

	// ����b��(x, y)����
	float vb_x = b.x;
	float vb_y = b.y;

	float productValue = (va_x * vb_x) + (va_y * vb_y);  // �����ĳ˻�
	float va_val = (float)sqrt(va_x * va_x + va_y * va_y);  // ����a��ģ
	float vb_val = (float)sqrt(vb_x * vb_x + vb_y * vb_y);  // ����b��ģ
	float cosValue = productValue / (va_val * vb_val);      // ���ҹ�ʽ
	// acos�����������Χ������[-1, 1]֮�䣬�����"domain error"
	// �����������У��ʹ���
	if (cosValue < -1 && cosValue > -2)
		cosValue = -1;
	else if (cosValue > 1 && cosValue < 2)
		cosValue = 1;

	// acos���ص��ǻ���ֵ��ת��Ϊ�Ƕ�ֵ
	angle = (float)(acos(cosValue) * 180 / 3.14);
	return angle;
	
}
void TrackBullet::clearNode(Node * pSender)
{
	pSender->removeFromParent();
}

void TrackBullet::Hit_Animation(Zombie* zombie)
{
	Sprite* sp = this->getImg();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ActionInterval * fadeout = FadeOut::create(0.3);
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(TrackBullet::clearNode, this));
	Sequence *sequence = Sequence::create(fadeout, actionDone, NULL);
	sp->runAction(sequence);
}
