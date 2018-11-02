#pragma once
#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;
class TripleBullet :public Bullet
{
private:
	int _type;//1�����ϣ�2�����У�3������
public:
	TripleBullet(Point position, int Plant_row,int type);
	void Self_Animation();
	void move();
	void afterMove(Node * pSender);
	void clear(Node * pSender);
	void clearNode(Node * pSender);
	virtual void attack_Animation();
	virtual void Hit_Animation(Zombie* zombie);
};
