#include "Roadblock.h"

Roadblock::Roadblock()
{
	setHp(12);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("none.png"));
	sp->retain();
	this->setImg(sp);
}

void Roadblock::Damage(int damage)
{
	setHp(getHp() - damage);
}