#pragma once
#include "Plants.h"
USING_NS_CC;
class Lantern :public Plants
{
private:
	Sprite* maskImg=NULL;
	bool isLightUp = false;
public:
	Lantern(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();

	void Die();
	//������
	void clear(Node * pSender);
};
