#pragma once
#include "Entity.h"
#include "ui/CocosGUI.h"
using namespace ui;

class MainMenu: public Entity
{
public:
	MainMenu();
	~MainMenu();

	void show();
	void hide();
	void clear();
	bool isShow();

	static MainMenu* getInstance()
	{
		if (instance == nullptr)
			instance = new MainMenu();
		return instance;
	}

private:
	bool showing = false;
	Button* retryButton;
	Button* levelButton;
	Button* exitButton;
	Button* closeButton;
	Layer* pauseLayer = nullptr;
	Scene* pauseScene = nullptr;
	static MainMenu* instance;
};

