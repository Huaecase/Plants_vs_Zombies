#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Tomb :public Plants
{
public:
	Tomb(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateZombie();
	void BirthZombie(Node * pSender, int cnt);
	//������
	void clear(Node * pSender);
};
