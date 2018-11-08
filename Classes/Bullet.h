#pragma once
#include "cocos2d.h"
#include "Zombie.h"
#include "Entity.h"
#define En_Burn 11111
#define Penetrable_tag 159159//��͸tag
#define Pitcher_tag 158158//Ͷ��tag
#define Paul_tag 158157//��ũ��tag

USING_NS_CC;
class Bullet : public Entity
{
private:
	int _Damage;
	double _Speed;
	std::vector<int>range;
public:
	Bullet();
	Bullet(Point position, int damage, double speed);
	int getDamage();
	void setDamage(int damage);
	double getSpeed();
	void setSpeed(double speed);
	std::vector<int> *getRange();
	//�����˺����۽�ʬ��Ѫ����
	void cal_damage(Zombie * zombie);
	//ֱ����ӵ��ӵ���
	virtual void addLayer(Node* entity);
	//�ӵ�·���ƶ�
	virtual void move() = 0;
	//��ʬ�����ӵ�����֮���Ч�������٣�debuff��
	virtual void Hit_Animation(Zombie * zombie) = 0;
};