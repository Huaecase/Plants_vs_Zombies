#pragma once
#include "Plants.h"
USING_NS_CC;
class Lotus :public Plants
{
public:
	Lotus(Point position, int row, int col);
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
