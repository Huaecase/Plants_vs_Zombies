#pragma once
#include "cocos2d.h"
#include "Entity.h"
#include "Bullet.h"
USING_NS_CC;
class Plants:public Entity
{
private:
	int _Hp; //Ѫ��
	long long BirthTime; //����ʱ��
	long long _BulletInterval; //�������
public:
	Plants(); //���캯��
	int getHp(); 
	void setHp(int hp);
	long long getInterval(); 
	void setInterval(long long BulletInterval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	virtual void init(Sprite * sp) = 0; //��ʼ��
	virtual void work(Sprite * sp) = 0; //����
	virtual void Die(Sprite *sp) = 0; //
	virtual void Attacked(Sprite* sp) = 0;
	virtual bool isAttacking() = 0;
};