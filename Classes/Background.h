#pragma once
#include "Entity.h"
class Background :
	public Entity
{
public:
	static int type;//0����ȫ½�ص�ͼ��1����ˮ·��ͼ,2�����ҹȫ½��
	static Node* holesStencil;
public:
	Background();
	void initPlantStatus();
};

