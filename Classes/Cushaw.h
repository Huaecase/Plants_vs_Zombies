#pragma once
#include "Nut.h"
USING_NS_CC;
class Cushaw :public Nut
{
public:
	Cushaw(Point position, int row, int col);
	//����֮����¼�
	virtual void Attacked();

};
