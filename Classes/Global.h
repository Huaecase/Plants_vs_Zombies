#pragma once
#include "cocos2d.h"
#include "Bullet.h"
#include "Plants.h"
#include "Zombie.h"
#include "PlantsEnum.h"
#include "PlantStatus.h"
#include "SelectCard.h"
#include "CardEntity.h"
#include "Background.h"
#include "Card.h"

#define Icing 0 //����
#define Freezing 1 //����
#define DrivingOut 2 //����
#define Stick 3 //���
#define Oil 4 //���
#define Invincible 5 //ֲ���޵�


USING_NS_CC;
extern std::vector <Bullet*> readyBullet;
extern std::vector <Plants*>readyPlants;
extern std::vector <Zombie*> readyZombies;
extern Map<Sprite*,Sprite*>readySun;//ֲ�ﾫ�飬̫������
extern std::vector<PlantsEnum> selectingCards;
extern std::vector<CardEntity*> selectingCardsEntity;
extern std::vector<CardEntity*> unSelectingCardsEntity;
extern std::vector<CardEntity*> readyCards;
extern std::vector<Sprite*> dropSun;

namespace map 
{
	extern std::pair<int, std::pair<double, double>>sunCnt;
	extern std::pair<float, float >BlockSize;
	extern std::pair<float, float >Deviation;
	extern int MapRow;
	extern int MapCol;
	extern void init();
	extern std::vector<PlantStatus*>plantstatus;
	extern PlantStatus* find(int row, int col);
	extern void RemoveRegister(const char * plant_name,int row, int col);
	extern void RemoveRegister(Plants * plant);
	extern Point Rank2Point(int row, int col);
	extern std::pair<int, int>Point2Rank(Point point);
	extern bool GameStart;
	extern Background* background;
	extern int totalLevelCount;
}

