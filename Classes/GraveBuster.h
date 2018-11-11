#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class GraveBuster :public Plants
{
private:
	bool isEating=false;
	Plants* plant=NULL;
public:
	GraveBuster(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	void readyDie(Node * pSender);
	virtual void Die();
	//����֮����¼�
	virtual void Attacked();
	//������
	void clear(Node * pSender);
};
