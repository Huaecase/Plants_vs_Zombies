#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class JannuDaruku : public Plants
{
protected:
	Point position;
	bool thisIsEnd;
public:
	JannuDaruku();
	JannuDaruku(Point position,int row,int col);
	virtual bool isWorking();//�Ƿ��ܹ���
    void work();
	void Die();
	virtual void thisDie();
	void Effect(Node * pSender);
	void zombiesDie();
	void creatSprite();
	//�����ӵ�
	virtual void CreateBullet();
	//������
	void clear(Node * pSender);
};