#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PeaShooter :public Plants
{
public:
	PeaShooter(Point position);
	PeaShooter();
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	//������
	void clear(Node * pSender);
	
};