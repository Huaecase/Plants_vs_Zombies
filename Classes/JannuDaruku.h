#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class JannuDaruku : public Plants
{
private:
	Point position;
public:
	JannuDaruku(Point position);
	virtual bool isWorking();//�Ƿ��ܹ���
	virtual void work();
	virtual void Die();
	void MyFire(Node *pSender);
	void zombiesDie(Node* pSender);
	void creatFire();
	virtual void Attacked();
	//�����ӵ�
	virtual void CreateBullet();
	//������
	void clear(Node * pSender);
	
};