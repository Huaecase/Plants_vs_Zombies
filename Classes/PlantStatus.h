#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PlantStatus
{
public:
	bool Enabled;
	bool isIcing = false;
	int _BlockType = 0;//0Ϊ½��,1Ϊˮ��
	PlantStatus(int row,int col,int BlockType,bool enable);
	~PlantStatus();
	int _row;
	int _col;
	std::vector<Plants*> plantVector;
};

