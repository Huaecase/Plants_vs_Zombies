#pragma once
#include "Entity.h"
#include "cocos2d.h"
USING_NS_CC;

class Zombie : public Entity {
private:
	int _Hp; //Ѫ��
	long long BirthTime; //����ʱ��
	long long _BiteInterval; //�������
	int _WalkSpeed; //�ƶ��ٶ�
	int _WalkDirection; //�ƶ�����
	bool _Head;
	bool _Hand;

public:
	Zombie(); //���캯��
	int getHp();
	void setHp(int hp);
	long long getInterval();
	void setInterval(long long BiteInterval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	int getWalkSpeed();
	void setWalkSpeed(int WalkSpeed);
	int getWalkDirection();
	void setWalkDirection(int WalkDirection);
	bool hasHead();
	void setHead(bool Head);
	bool hasHand();
	void setHand(bool Hand);
	virtual void init() = 0; //��ʼ��
	virtual void work() = 0; //����
	virtual void Die() = 0; //
	void Self_Animation();
};