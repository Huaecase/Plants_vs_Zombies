#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "test.h"
#define Icing 0
USING_NS_CC;

extern Map <Bullet*,Sprite*> preBullet;
extern Map <Plants*,Sprite*> prePlants;
extern Map <Bullet*, Sprite*> readyBullet;
extern Map <Plants*,Sprite*> readyPlants;
extern Map<Sprite*,Sprite*>preSun;//ֲ�ﾫ�飬̫������
extern Map<Sprite*,Sprite*>readySun;
extern Vector<Sprite*> testMap;
extern std::pair<int ,std::pair<double,double>>sunCnt;
extern std::vector<int> debuff;

extern int speed_;