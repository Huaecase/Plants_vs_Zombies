#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Clover :public Plants
{
private:
	bool isBlowing = false;
public:
	Clover(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	void Blow(Node * pSender);
	void readyDie(Node * pSender);
	virtual void Die();
	//����֮����¼�
	virtual void Attacked();
	//������
	void clear(Node * pSender);


};

