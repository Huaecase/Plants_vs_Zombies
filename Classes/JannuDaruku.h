#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class JannuDaruku : public Plants
{
protected:
	Point position;
public:
	JannuDaruku();
	JannuDaruku(Point position,int row,int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	void Effect(Node * pSender);
	void zombiesDie();
	void creatSprite();
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	//������
	void clear(Node * pSender);
	
};