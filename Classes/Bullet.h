#pragma once
#include "cocos2d.h"
#include "TestZombie.h"
#include "Entity.h"
#include "test.h"
USING_NS_CC;
class Bullet : public Entity
{
private:
	int _Damage;
	double _Speed;
public:
	Bullet();
	Bullet(Point position, int damage, double speed);
	int getDamage();
	void setDamage(int damage);
	double getSpeed();
	void setSpeed(double speed);
	//�����˺����۽�ʬ��Ѫ����
	void cal_damage(TestZombie* zombie);
	//ֱ����ӵ��ӵ���
	void addLayer(Node* entity);
	//�ӵ�·���ƶ�
	virtual void move() = 0;
	//��ʬ�����ӵ�����֮���Ч�������٣�debuff��
	virtual void Hit_Animation(TestZombie* zombie) = 0;
};