#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
#include "Zombie.h"
USING_NS_CC;
class Lucker :public PeaShooter
{
private:
	int damage;
public:
	Lucker(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	//���е�������
	void Self_Animation();
	void stab();
};