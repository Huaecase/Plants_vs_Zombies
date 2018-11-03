#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Bullet.h"
USING_NS_CC;
class Torch :public Plants
{
public:
	Torch(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet(Bullet*bullet);
	//������
	void clear(Node * pSender);
};
