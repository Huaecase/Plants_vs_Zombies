#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "test.h"
#include "TestZombie.h"
#define Icing 0
USING_NS_CC;
extern std::vector <Bullet*> readyBullet;
extern std::vector <Plants*> readyPlants;
extern Map<Sprite*,Sprite*>readySun;//ֲ�ﾫ�飬̫������
extern std::vector<TestZombie*> testMap;
extern std::pair<int ,std::pair<double,double>>sunCnt;