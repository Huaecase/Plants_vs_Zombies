#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Magnet :public PeaShooter
{
public:
	Magnet(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//�����ӵ�
	virtual void CreateBullet();
	//������
	void attractEquiment();
};