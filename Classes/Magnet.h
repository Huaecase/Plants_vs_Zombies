#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Magnet :public PeaShooter
{
private:
	bool attracted;
public:
	Magnet(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	void Self_Animation();
	//������
	void attractEquiment();
	void recover(Node* sPender, Sprite* Equiment);
};