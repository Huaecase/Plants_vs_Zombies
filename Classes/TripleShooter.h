#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class TripleShooter :public PeaShooter
{
public:
	TripleShooter(Point position, int row);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//�����ӵ�
	virtual void CreateBullet();

};
