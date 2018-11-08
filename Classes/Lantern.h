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
	virtual void Die();
	//���е���������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//��������
	void clear(Node * pSender);

};