#include "MenuButton.h"
#include "LevelManager.h"

Button* MenuButton::instance;

MenuButton::MenuButton()
{

}

MenuButton::~MenuButton()
{

}

Button* MenuButton::create(Point position)
{
	auto button = Button::create("UI\\SelectCardButton.png", "UI\\SelectCardButton_Light.png", "UI\\SelectCardButton.png");
	button->setPosition(position);
	button->setScale(2.0f);
	auto label = Label::createWithTTF("Menu", "Font\\TianShiYanTi.ttf", 4);
	label->setTextColor(Color4B::BLACK);
	button->setTitleLabel(label);

	EntityLayer::getInstance()->addChild(button, 1000);
	return button;
}

void MenuButton::enable()
{
	getInstance()->setEnabled(true);
	getInstance()->setVisible(true);
}

void MenuButton::disable()
{
	getInstance()->setEnabled(false);
	getInstance()->setVisible(false);
}

void MenuButton::clear()
{
	getInstance()->removeFromParent();
}

void MenuButton::addListener()
{
	getInstance()->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (LevelManager::getInstance()->isShow() == false)
				LevelManager::getInstance()->show();
			break;
		default:
			break;
		}
	});
}