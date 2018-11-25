#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "Zombie.h"
#define self_tag 99999
USING_NS_CC;
class Chomper:public Plants
{
private:
	bool isEating = false;
public:
	Chomper(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	void Eat(Zombie * zombie);
	void resume(Node * pSender);
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//������
	void clear(Node * pSender);
	void clear1(Node * pSender, Sprite * sp);
};
