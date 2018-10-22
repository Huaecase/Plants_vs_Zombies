#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "ZombieLayer.h"
USING_NS_CC;

class Zombie : public Entity 
{
private:
	int _Hp; //Ѫ��
	long long BirthTime; //����ʱ��
	long long _BiteInterval; //�������
	int _WalkSpeed; //�ƶ��ٶ�
	bool _Head;
	std::vector<int> debuff;
	CCScheduler *sched;

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
	bool hasHead();
	void setHead(bool Head);
	std::vector<int> getDebuff();
	void addLayer(Node* entity);
	void setActionManger(Node * sprite);
	virtual void attack() = 0; //����
	virtual bool isAttacking() = 0;
	virtual void Die() = 0;
	virtual void Attacked() = 0;
	virtual void LostHead() = 0;
	virtual void Move() = 0;
};