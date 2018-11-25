#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Zombie.h"
USING_NS_CC;
class PotatoMine :public Plants
{
private: 
	bool bornFinish = false;
	Point position;
	int maxHp;
	int birthDelay;
public:
	PotatoMine(Point position, int row,int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	void removeSprite(Node * pSender);
	//����֮���������
	void Self_Animation();
	//�����Ķ���������������
	void Born_Animation(Node *pSender);
	//����֮����¼�
	virtual void Attacked();
	void CreateBullet(Zombie* zombie);
	void afterBornHandle(Node *pSender);
	void clear(Node *pSender);
};