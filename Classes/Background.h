#pragma once
#include "Entity.h"
class Background :
	public Entity
{
private:
	int type = 1;//0����ȫ½�ص�ͼ��1����ˮ·��ͼ
public:
	Background();
	void initPlantStatus();
};

