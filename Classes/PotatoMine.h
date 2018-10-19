#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PotatoMine :public Plants
{
private: 
	bool bornFinish = false;
public:
	PotatoMine(Point position);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	//����֮���������
	void Self_Animation();
	//�����Ķ���������������
	void Born_Animation(Node *pSender, Point position);
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	void afterBornHandle(Node *pSender, Point position);
	void clear(Node *pSender);
};