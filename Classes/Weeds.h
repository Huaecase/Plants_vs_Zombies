#pragma once
#include "cocos2d.h"
#include "Plants.h"
#include "PeaShooter.h"
USING_NS_CC;

class Weeds :public PeaShooter
{
public:
	Weeds(Point position,int row,int col);
	virtual bool isWorking();
	void CreateBullet();
};
