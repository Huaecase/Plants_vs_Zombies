#pragma once
#include "ZombieEquipment.h"

class Roadblock : public ZombieEquipment 
{
public:
	Roadblock();
	virtual void Damage(int damage);
};