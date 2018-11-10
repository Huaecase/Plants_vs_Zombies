#pragma once
#include <iostream>
#include <typeinfo>
#include "Entity.h"
#include "CardEntity.h"
#include "EntityLayer.h"
#include "PlantStatus.h"
#include "Plants.h"
#include "PlantsEnum.h"
#include "Global.h"
//using namespace std;
using namespace cocos2d;

template <class T>
class UnSelectCard :public CardEntity
{
public:
	UnSelectCard();
	~UnSelectCard();
	//PlantsEnum plantsEnum = PlantsEnum::IceShooter;
	std::string plantsTypeName;
	Point srcPosition;
	//bool isSelecting = false;
	//int cost;
	//Sprite* plantSprite;

	void addLayer(Node * entity, int order = 0)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->addChild(entity, order);
	}

	void removeLayer(Node * entity)
	{
		EntityLayer* layer = EntityLayer::getInstance();
		layer->removeChild(entity);
	}

	UnSelectCard(Point position, PlantsEnum plantsEnum)
	{
		srcPosition = position;
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("cardbackground\\Card.png"));
		
		sprite->retain();
		//sprite->setScale(0.15f);
		sprite->setContentSize(Size(30, 42));
		sprite->setPosition(position);
		addLayer(sprite, 200);

		string className = typeid(T).name();
		className = className.erase(0, 6);
		string str = string("Card\\") + className + string(".png");
		plantSprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		Size size = sprite->getContentSize();
		auto position1 = Point(size.width / 2, size.height / 2);
		position1.y += 4;
		plantSprite->setPosition(position1);
		//plantSprite->setScale(0.08f);
		plantSprite->setContentSize(Size(18, 24));
		plantSprite->retain();
		//addLayer(plantSprite, 200);
		sprite->addChild(plantSprite);
		this->setImg(sprite);

		plantsTypeName = typeid(T).name();
		this->plantsEnum = plantsEnum;
		addListener();
		
	}

	void addListener()
	{
		listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = [=](Touch* touch, Event *event)
		{
			if (GameStart == true)
				return false;
			Point clickLocation = touch->getLocation();
			Size s = getImg()->getContentSize();
			auto position = getImg()->getPosition();
			Rect rect = Rect(position.x - s.width*getImg()->getScaleX() / 2, position.y - s.height*getImg()->getScaleX() / 2, s.width*getImg()->getScaleX(), s.height*getImg()->getScaleX());
			auto rank = Point2Rank(clickLocation);

			// �����Χ�жϼ��
			if (rect.containsPoint(clickLocation))
			{
				//cout << (int)this->plantsEnum << endl;
				cout << isSelecting << endl;
				if (isSelecting == false && selectingCardsEntity.size() < 7)
				{
					selectingCards.push_back(plantsEnum);
					//auto entity = new SelectCard<T>(position, plantsEnum);
					auto moveTo = MoveTo::create(0.3f, Point(-10 + selectingCards.size() * 32, 290));
					getImg()->stopAllActions();
					getImg()->runAction(moveTo);
					//entity->plantSprite->runAction(moveTo);
					selectingCardsEntity.push_back(this);
					isSelecting = true;
					auto card = new Card<T>(Point(-10 + selectingCards.size() * 32, 290));
					readyCards.push_back(card);
				}
				else
				{
					isSelecting = false;
					auto moveTo = MoveTo::create(0.3f, srcPosition);
					getImg()->stopAllActions();
					getImg()->runAction(moveTo);
					for (int i = 0; i < selectingCards.size(); i++)
					{
						if (selectingCards[i] == this->plantsEnum)
						{
							selectingCards.erase(selectingCards.begin() + i);
							selectingCardsEntity.erase(selectingCardsEntity.begin() + i);
							//readyCards[i]->removeListener();
							removeLayer(readyCards[i]->getImg());
							readyCards.erase(readyCards.begin() + i);
							break;
						}
					}
					for (int i = 0; i < selectingCardsEntity.size(); i++)
					{
						auto moveTo = MoveTo::create(0.2f, Point(-10 + (i + 1) * 32, 290));
						readyCards[i]->getImg()->setPosition(Point(-10 + (i + 1) * 32, 290));
						selectingCardsEntity[i]->getImg()->stopAllActions();
						selectingCardsEntity[i]->getImg()->runAction(moveTo);
						//selectingCardsEntity[i]->getImg()->setPosition((i+1) * 20, 150);
					}
				}
				//for (int i = 0; i < selectingCards.size(); i++)
				//{
				//	cout<<(int)	selectingCards[i]<<endl;
				//}
				return true;
			}

		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, getImg());
	}
};
