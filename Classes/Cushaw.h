#pragma once
#include "Nut.h"
USING_NS_CC;
class Cushaw :public Nut
{
private:
	bool isProtecting = false;;
public:
	Cushaw(Point position, int row, int col);
	void work();
	//����֮����¼�
	virtual void Attacked();

};
