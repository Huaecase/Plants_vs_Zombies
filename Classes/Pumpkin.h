#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Zombie.h"
USING_NS_CC;
class Pumpkin :public Plants
{
private:
	Point position;
	float attackRange;
	float jumpDuration;
	bool isJumping;
public:
	Pumpkin(Point position);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	void CheckZombies();
	void Trample(Zombie* zombie);
	virtual void Die();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	void clear(Node * pSender);
};