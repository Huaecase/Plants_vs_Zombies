#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class riceShooter :public Plants
{
public:
	riceShooter();
	riceShooter(Point position, int row,int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
};