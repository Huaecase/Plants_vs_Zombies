#pragma once
#include "cocos2d.h"
#include "PeaShooter.h"
USING_NS_CC;
class Paul :public PeaShooter
{
private:
	bool canShoot;
	bool shootReady;
	bool canSelect;
	bool jumpListener;
	Point touchPos;
	Sprite* AimSprite;
private:
	static bool plantSelect;
public:
	Paul(Point position, int row, int col);
	virtual bool isWorking();
	//�Ƿ��ܹ���
	virtual void Die();
	virtual void work();
	//�����ӵ�
	virtual void CreateBullet();
	void Self_Animation();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onMouseMove(Event * event);
};