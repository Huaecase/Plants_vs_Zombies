#pragma once
//#include "Entity.h"
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;

#define Animation_Tag 1

class Zombie : public Entity 
{
private:
	int _Hp; //Ѫ��
	//long long BirthTime; //����ʱ��
	double _BiteInterval; //�������
	double  _WalkSpeed; //�ƶ��ٶ�
	bool _Head;
	bool _meeting;
	int _row;
	int _col;
	std::vector<int> debuff;
	CCScheduler *sched;
protected:
	void setWalkSpeed(double WalkSpeed);
public:
	Zombie(); //���캯��
	int getHp();
	void setHp(int hp);
	int getRow();
	void setRow(int row);
	int getCol();
	void setCol(int col);
	double getInterval();
	void setInterval(double BiteInterval);
	double getWalkSpeed();//�õ���ǰ�ٶ�
	double getPreWalkSpeed();//�õ�ԭ�����ٶ�
	bool hasHead();
	void setHead(bool Head);
	bool isMeeting();
	void setMeeting(bool meeting);
	std::vector<int>*getDebuff();
	void addLayer(Node* entity);
	void setSche(Node * sprite);
	CCScheduler* getScheduler();
	virtual void attack(Plants *plant) = 0; //����
	virtual bool isAttacking() = 0;
	virtual void Die(Node * pSender) = 0;
	virtual void Attacked() = 0;
	virtual void LostHead() = 0;
	virtual void Move() = 0;
};