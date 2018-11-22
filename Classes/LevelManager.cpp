#include "LevelManager.h"
#include "FontConfig.h"
#include "Background.h"
#include "ui/CocosGUI.h"
#include "Global.h"
#include "SelectCardBG.h"
#include "MenuButton.h"
#include "GameStartButton.h"
#include "CardBank.h"
#include "IceShooter.h"
#include "PotatoMine.h"
#include "Pumpkin.h"
#include "BasicZombie.h"
#include "Plants.h"
#include "DoublePeaShooter.h"
#include "RoadblockZombie.h"
#include "Mushroom.h"
#include "Weeds.h"
#include "NutPlus.h"
#include "Melancholy.h"
#include "Sunflower.h"
#include "Doom_shroom.h"
#include "JannuDaruku.h"
#include "StarShooter.h"
#include "TripleShooter.h"
#include "iceCabbage.h"
#include "Card.h"
#include "SelectCard.h"
#include "UnSelectCard.h"
#include "ZombieCard.h"
#include "Torch.h"
#include "Cushaw.h"
#include "Chomper.h"
#include "Lucker.h"
#include "Lancer.h"
#include "Lotus.h"
#include "Magnet.h"
#include "HeroThunder.h"
#include "Landslock.h"
#include "MinerZombie.h"
#include "riceShooter.h"
#include "HeroLucker.h"
#include "Paul.h"
#include "WhiteJannu.h"
#include "Shovel.h"
#include "Lantern.h"
#include "DoorZombie.h"
#include "WaterShooter.h"
#include "Clover.h"
#include "Magnet.h"
#include "Tomb.h"
#include "GraveBuster.h"
#include "NewspaperZombie.h"
#include "ui/CocosGUI.h"
#include "GameStartButton.h"
#include "PoleVaultingZombie.h"
#include "Zomboni.h"
#include "SmallMushRoom.h"
#include "Title.h"
#include "DuckZombie.h"
#include "FootBallZombie.h"
#include "SelectCardBG.h"
#include "CardBank.h"
#include "Thunder.h"
#include "BucketZombie.h"
#include "BombZombie.h"
#include "Gargantuar.h"
#include "ImpZombie.h"
#include "Ladder.h"
#include "LevelManager.h"
#include "MenuButton.h"
using namespace ui;
using namespace map;

LevelManager* LevelManager::instance = nullptr;
int LevelManager::currentLevel = 1;
int LevelManager::bg[11] = { -1,0,0,1,1,2,2,3,3,4,4 };

LevelManager::LevelManager()
{
	auto layer = EntityLayer::getInstance();
	auto s = Director::getInstance()->getWinSize();
	auto bg = Sprite::createWithTexture(TextureCache::getInstance()->addImage("UI\\LevelManager.png"));
	bg->setAnchorPoint(Point(0.5f, 0.5f));
	bg->setPosition(s.width/2, s.height/2);
	bg->setScale(1.6f);
	layer->addChild(bg, 1500);
	setImg(bg);

	auto closeButton = Button::create("UI\\close.png", "UI\\close.png", "UI\\close.png");
	getImg()->addChild(closeButton);
	closeButton->setPosition(Point(180,110));
	closeButton->setScale(1.5f);
	closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			hide();
			break;
		default:
			break;
		}
	});
	int startX = 40;
	int startY = 80;
	int offsetX = 30;
	int offsetY = 30;
	int x, y;
	for (int i = 0; i < totalLevelCount; i++)
	{
		x = startX + i % 5 * offsetX;
		y = startY - i / 5 * offsetY;
		auto button = Button::create("UI\\LevelButton.png", "UI\\LevelButton.png", "UI\\LevelButton.png");
		button->setPosition(Point(x, y));
		button->setScale(0.5f);
		getImg()->addChild(button);
		auto label = Label::createWithTTF(*FontConfig::getInstance(), std::to_string(i + 1));
		label->setPosition(Point(x-0.5f, y+2.5f));
		label->setScale(1.5f);
		label->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
		getImg()->addChild(label);

		button->addTouchEventListener([&,i](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				//std::cout << i << std::endl;
				//currentLevel = i + 1;
				hide();
				LevelManager::loadLevel(i+1);
				break;
			default:
				break;
			}
		});
	}
}

bool LevelManager::isShow()
{
	return showing;
}

void LevelManager::show()
{
	FadeIn* fadein = FadeIn::create(0.3f);
	getImg()->setOpacity(0);
	getImg()->runAction(fadein);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->setOpacity(0);
		childerns.at(i)->runAction(fadein->clone());
	}
	showing = true;
}

void LevelManager::hide()
{
	FadeOut* fadeout = FadeOut::create(0.3f);
	getImg()->runAction(fadeout);
	auto childerns = getImg()->getChildren();
	for (int i = 0; i < childerns.size(); i++)
	{
		childerns.at(i)->runAction(fadeout->clone());
	}
	showing = false;
}

void LevelManager::clear()
{
	getImg()->removeFromParent();
	instance = nullptr;
}

void LevelManager::clearAllUI()
{
	SelectCardBG::getInstance()->clear();
	CardBank::getInstance()->clear();
	getInstance()->clear();
	GameStartButton::clear();
	MenuButton::clear();
}

void LevelManager::showAllUI()
{
	SelectCardBG::getInstance()->show();
	CardBank::getInstance()->show();
	GameStartButton::addListener();
	GameStartButton::enable();
	MenuButton::addListener();
	MenuButton::enable();
}

void LevelManager::createAllCard()
{
	float startX = 5.0f;
	float startY = 230.0f;
	float offsetX = 28.0f;
	float offsetY = 40.0f;
	auto unSelectCard1 = new UnSelectCard<PeaShooter>(Point(startX += offsetX, startY), PlantsEnum::PeaShooter);
	unSelectingCardsEntity.push_back(unSelectCard1);
	auto unSelectCard2 = new UnSelectCard<IceShooter>(Point(startX += offsetX, startY), PlantsEnum::IceShooter);
	unSelectingCardsEntity.push_back(unSelectCard2);
	auto unSelectCard3 = new UnSelectCard<Mushroom>(Point(startX += offsetX, startY), PlantsEnum::Mushroom);
	unSelectingCardsEntity.push_back(unSelectCard3);
	auto unSelectCard4 = new UnSelectCard<Melancholy>(Point(startX += offsetX, startY), PlantsEnum::Melancholy);
	unSelectingCardsEntity.push_back(unSelectCard4);
	auto unSelectCard5 = new UnSelectCard<Sunflower>(Point(startX += offsetX, startY), PlantsEnum::Sunflower);
	unSelectingCardsEntity.push_back(unSelectCard5);
	auto unSelectCard6 = new UnSelectCard<Weeds>(Point(startX += offsetX, startY), PlantsEnum::Weeds);
	unSelectingCardsEntity.push_back(unSelectCard6);
	auto unSelectCard7 = new UnSelectCard<NutPlus>(Point(startX += offsetX, startY), PlantsEnum::NutPlus);
	unSelectingCardsEntity.push_back(unSelectCard7);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard8 = new UnSelectCard<Doom_shroom>(Point(startX += offsetX, startY), PlantsEnum::Doom_shroom);
	unSelectingCardsEntity.push_back(unSelectCard8);
	auto unSelectCard9 = new UnSelectCard<JannuDaruku>(Point(startX += offsetX, startY), PlantsEnum::JannuDaruku);
	unSelectingCardsEntity.push_back(unSelectCard9);
	auto unSelectCard10 = new UnSelectCard<StarShooter>(Point(startX += offsetX, startY), PlantsEnum::StarShooter);
	unSelectingCardsEntity.push_back(unSelectCard10);
	auto unSelectCard11 = new UnSelectCard<TripleShooter>(Point(startX += offsetX, startY), PlantsEnum::TripleShooter);
	unSelectingCardsEntity.push_back(unSelectCard11);
	auto unSelectCard12 = new UnSelectCard<iceCabbage>(Point(startX += offsetX, startY), PlantsEnum::iceCabbage);
	unSelectingCardsEntity.push_back(unSelectCard12);
	auto unSelectCard13 = new UnSelectCard<Torch>(Point(startX += offsetX, startY), PlantsEnum::Torch);
	unSelectingCardsEntity.push_back(unSelectCard13);
	auto unSelectCard14 = new UnSelectCard<Cushaw>(Point(startX += offsetX, startY), PlantsEnum::Cushaw);
	unSelectingCardsEntity.push_back(unSelectCard14);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard15 = new UnSelectCard<Chomper>(Point(startX += offsetX, startY), PlantsEnum::Chomper);
	unSelectingCardsEntity.push_back(unSelectCard15);
	auto unSelectCard16 = new UnSelectCard<PotatoMine>(Point(startX += offsetX, startY), PlantsEnum::PotatoMine);
	unSelectingCardsEntity.push_back(unSelectCard16);
	auto unSelectCard17 = new UnSelectCard<Pumpkin>(Point(startX += offsetX, startY), PlantsEnum::Pumpkin);
	unSelectingCardsEntity.push_back(unSelectCard17);
	auto unSelectCard18 = new UnSelectCard<Lucker>(Point(startX += offsetX, startY), PlantsEnum::Lucker);
	unSelectingCardsEntity.push_back(unSelectCard18);
	auto unSelectCard19 = new UnSelectCard<DoublePeaShooter>(Point(startX += offsetX, startY), PlantsEnum::DoublePeaShooter);
	unSelectingCardsEntity.push_back(unSelectCard19);
	auto unSelectCard20 = new UnSelectCard<Lancer>(Point(startX += offsetX, startY), PlantsEnum::Lancer);
	unSelectingCardsEntity.push_back(unSelectCard20);
	auto unSelectCard21 = new UnSelectCard<Shovel>(Point(startX += offsetX, startY), PlantsEnum::Shovel);
	unSelectingCardsEntity.push_back(unSelectCard21);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard22 = new UnSelectCard<Nut>(Point(startX += offsetX, startY), PlantsEnum::Nut);
	unSelectingCardsEntity.push_back(unSelectCard22);
	auto unSelectCard23 = new UnSelectCard<Landslock>(Point(startX += offsetX, startY), PlantsEnum::Landslock);
	unSelectingCardsEntity.push_back(unSelectCard23);
	auto unSelectCard24 = new UnSelectCard<riceShooter>(Point(startX += offsetX, startY), PlantsEnum::riceShooter);
	unSelectingCardsEntity.push_back(unSelectCard24);
	auto unSelectCard25 = new UnSelectCard<Paul>(Point(startX += offsetX, startY), PlantsEnum::Paul);
	unSelectingCardsEntity.push_back(unSelectCard25);
	auto unSelectCard26 = new UnSelectCard<HeroLucker>(Point(startX += offsetX, startY), PlantsEnum::HeroLucker);
	unSelectingCardsEntity.push_back(unSelectCard26);
	auto unSelectCard27 = new UnSelectCard<Lotus>(Point(startX += offsetX, startY), PlantsEnum::Lotus);
	unSelectingCardsEntity.push_back(unSelectCard27);
	auto unSelectCard28 = new UnSelectCard<Lantern>(Point(startX += offsetX, startY), PlantsEnum::Lantern);
	unSelectingCardsEntity.push_back(unSelectCard28);
	startX = 5;
	startY -= offsetY;
	auto unSelectCard29 = new UnSelectCard<Magnet>(Point(startX += offsetX, startY), PlantsEnum::Magnet);
	unSelectingCardsEntity.push_back(unSelectCard29);
	
}

void LevelManager::loadLevel(int level)
{
	auto scene = Scene::create();
	EntityLayer::create();
	Background::type = bg[level];
	background->clear();
	background = new Background();
	scene->addChild(EntityLayer::getInstance());
	Director::getInstance()->replaceScene(scene);
	currentLevel = level;
	GameStart = false;

	clearAllUI();
	showAllUI();
	sunCnt.first = 0;
	CardBank::updateSunLabel();
	for (int i = 0; i < readyCards.size(); i++)
		readyCards[i]->clear();
	readyCards.clear();
	createAllCard();

	
}