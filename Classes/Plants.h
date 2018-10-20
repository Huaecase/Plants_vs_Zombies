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
	long long _WorkInterval; //�������
public:
	Plants(); //���캯��
	int getHp(); 
	void setHp(int hp);
	long long getInterval(); 
	void setInterval(long long Interval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	void getHurt(int Damage);
	//�Ѿ���ֱ�ӷŵ�ͼ����
	void addLayer(Node* entity);
	virtual void work() = 0; //����
	virtual bool isWorking() = 0;//�Ƿ��ܹ���(��ʬ����֮����������׳���֮��)
	//������������&�����ڴ�
	virtual void Die() = 0; 
	//������֮��Ķ����Լ�Ч������ը�ȣ�
	virtual void Attacked() = 0;
	
};