#pragma once
#include "cocos2d.h"
#include "Entity.h"
#define Penetrable_tag 159159//��͸tag
#define Pitcher_tag 158158//Ͷ��tag
#define Paul_tag 158157//Ͷ��tag

USING_NS_CC;
class Plants:public Entity
{
private:
	int _Hp; //Ѫ��
	long long BirthTime; //����ʱ��
	long long _WorkInterval; //�������
	int _row;
	int _col;
public:
	Plants(); //���캯��
	int getHp(); 
	void setHp(int hp);
	long long getInterval(); 
	void setInterval(long long Interval);
	long long getBirthTime();
	void setBirthTime(long long seconds);
	void getHurt(int Damage);
	void setRow(int row);
	int getRow();
	void setCol(int col);
	int getCol();
	void setNewBirthTime();
	//�Ѿ���ֱ�ӷŵ�ͼ����
	void addLayer(Node* entity);
	virtual void work() = 0; //����
	virtual bool isWorking() = 0;//�Ƿ��ܹ���(��ʬ����֮����������׳���֮��)
	//������������&�����ڴ�
	virtual void Die() = 0; 
	//������֮��Ķ����Լ�Ч������ը�ȣ�
	virtual void Attacked() = 0;
};