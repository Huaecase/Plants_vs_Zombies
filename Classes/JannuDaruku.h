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
	virtual void thisDie();
	void Effect(Node * pSender);
	virtual void zombiesDie();
	virtual void creatSprite();
	void clearNode(Node * pSender);
	// ͨ�� Plants �̳�
	virtual void Attacked() override;
};