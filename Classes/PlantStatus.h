#pragma once
#include "cocos2d.h"
#include "Plants.h"
USING_NS_CC;
class PlantStatus
{
public:
	int _BlockType = 0;//0Ϊ½��,1Ϊˮ��
	PlantStatus(int row,int col,int BlockType);
	~PlantStatus();
	int _row;
	int _col;
	std::vector<Plants*> plantVector;
};

