#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Zombie.h"
USING_NS_CC;
class Landslock :public Plants
{
public:
	Landslock(Point position, int row ,int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	void Self_Animation();
	void driveOut(Zombie* zombie);
	void afterDriveOut(Node* sPender, Zombie* zombie, int changeRow);
	void clearNode(Node* sPender, Sprite* sp);
};