#pragma once
#include "Plants.h"
USING_NS_CC;
class Nut :public Plants
{
public:
	Nut(Point position, int row,int col);
	Nut();
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//������
	void clear(Node * pSender);

};