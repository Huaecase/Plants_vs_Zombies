#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Shovel :public Plants
{
public:
	Shovel(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//������
	void clear(Node * pSender);


};
