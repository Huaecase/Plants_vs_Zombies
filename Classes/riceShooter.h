#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class riceShooter :public Plants
{
public:
	riceShooter(Point position, int row);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//���е���������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	//��������
	void clear(Node * pSender);

};