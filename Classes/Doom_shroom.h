#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class Doom_shroom :public Plants
{
private:
	Point position;
public:
	Doom_shroom(Point position, int row, int col);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	void Boom(Node * pSender);
	void clearSprite(Node * pSender, Sprite * sp);
	void zombiesDie(Node * pSender);
	//���е�������
	void Self_Animation();
	//����֮����¼�
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	//������
	void clear(Node * pSender);
};