#pragma once
//#include "Entity.h"
#include "cocos2d.h"
#include "Plants.h"
#include "ZombieEquipment.h"
#include "PlantStatus.h"
USING_NS_CC;

#define Animation_Tag 12347
#define Jumping_Tag 123481

class Zombie : public Entity 
{
private:
	long long BirthTime; //����ʱ��
	int _Hp; //Ѫ��
	double _BiteInterval; //�������
	double  _WalkSpeed; //�ƶ��ٶ�
	bool _Head;
	bool _meeting;
	int _row;
	int _col;
	std::vector<int> debuff;
	CCScheduler *sched;
	ZombieEquipment *equip;
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
	long long getBirthTime();
	void setBirthTime(long long seconds);
	void setNewBirthTime();
	std::vector<int>*getDebuff();
	void addLayer(Node* entity);
	void setSche(Node * sprite);
	void setEquip(ZombieEquipment *equip);
	ZombieEquipment *getEquip();
	bool hasEquip();
	CCScheduler* getScheduler();
	virtual void work(); //����
	virtual void Attack(PlantStatus *plantstatus) = 0;
	virtual void Die(Node * pSender) = 0;
	virtual void Attacked() = 0;
	virtual void LostHead() = 0;
	virtual void Move() = 0;
	virtual void DamageZombie(int damage) = 0;
	virtual void DamageEquip(int damage) = 0;
	virtual void DamageBoth(int damage) = 0;
	virtual Sprite *MagnetEquip() = 0;
	virtual void DamagePlant(Node * pSender, PlantStatus *plantstatus);
	void clear(Node * pSender);
	void clear_from_vector(Node * pSender);
	void Stop_Animation();
};