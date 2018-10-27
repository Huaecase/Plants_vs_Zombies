#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "Plants.h"
USING_NS_CC;
class iceCabbage : public Plants
{
private:
	Point position;
public:
	iceCabbage(Point position, int row);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	void iceWorld(Node *pSender);
	void freezeZombie(Zombie * zombie);
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	void clearIceSprite(Node * pSender, Sprite * iceSprite, Zombie* zombie);
	//������
	void clear(Node * pSender);
};