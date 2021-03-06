#include "Zombie.h"
#include "EntityLayer.h"
#include "Global.h"
#include "LevelManager.h"
#include <sys/timeb.h>
Zombie::Zombie()
{
	this->BirthTime = 0;
}

Zombie::~Zombie()
{
	LevelManager::kill++;
	std::cout << "僵尸死了，当前共杀死了" << LevelManager::kill << "只僵尸" << std::endl;
}

int Zombie::getHp()
{
	return _Hp;
}

void Zombie::setHp(int hp)
{
	_Hp = hp;
}

int Zombie::getRow()
{
	return _row;
}

void Zombie::setRow(int row)
{
	_row = row;
	if(this->getImg() != NULL)
		this->getImg()->setZOrder(_row * 3 - 1);
}
void Zombie::setCol(int col)
{
	_col = col;
}
int Zombie::getCol()
{
	return _col;
}
double Zombie::getInterval()
{
	return _BiteInterval;
}

void Zombie::setInterval(double BiteInterval)
{
	_BiteInterval = BiteInterval;
}

void Zombie::setWalkSpeed(double WalkSpeed)
{
	_WalkSpeed=WalkSpeed;
}

double Zombie::getWalkSpeed()
{
	if (isMeeting())
	{
		return 0;
	}
	else
	{
		return _WalkSpeed * sched->getTimeScale();
	}
}

double Zombie::getPreWalkSpeed()
{
	return _WalkSpeed;
}

bool Zombie::hasHead()
{
	return _Head;
}

void Zombie::setHead(bool Head)
{
	_Head = Head;
}

bool Zombie::isMeeting()
{
	return _meeting;
}

void Zombie::setMeeting(bool meeting)
{
	_meeting = meeting;
}

long long Zombie::getBirthTime()
{
	return BirthTime;
}

void Zombie::setBirthTime(long long seconds)
{
	BirthTime = seconds;
}
void Zombie::setNewBirthTime()
{
	struct timeb t1;
	ftime(&t1);
	long long seconds = t1.time * 1000 + t1.millitm;
	this->setBirthTime(seconds);
}

std::vector<int>* Zombie::getDebuff() 
{
	return &debuff;
}

void Zombie::addLayer(Node * entity)
{
	EntityLayer* zl = EntityLayer::getInstance();
	zl->addChild(entity, _row * 3 - 1);
}

void Zombie::setSche(Node* sprite)
{
	CCActionManager *actionManager;
	CCScheduler *defaultScheduler = CCDirector::sharedDirector()->getScheduler();
	// Create a new scheduler, and link it to the main scheduler
	sched = new CCScheduler();
	defaultScheduler->scheduleUpdateForTarget(sched, 0, false);
	// Create a new ActionManager, and link it to the new scheudler
	actionManager = new CCActionManager();
	sched->scheduleUpdateForTarget(actionManager, 0, false);
	sprite->setActionManager(actionManager);
	if (hasEquip()) {
		getEquip()->getImg()->setActionManager(actionManager);
	}
}

void Zombie::setEquip(ZombieEquipment * equip)
{
	this->equip = equip;
}

ZombieEquipment * Zombie::getEquip()
{
	return equip;
}

bool Zombie::hasEquip()
{
	return equip != nullptr;
}

CCScheduler * Zombie::getScheduler()
{
	return sched;
}

void Zombie::work()
{
}

void Zombie::DamagePlant(Node * pSender, PlantStatus *plantstatus)
{

	if (plantstatus->plantVector.size() == 0 || strcmp(typeid(*(plantstatus->plantVector.at(0))).name(), "class Lucker") == 0|| strcmp(typeid(*(plantstatus->plantVector.at(0))).name(), "class Tomb") == 0) {
		this->Move();
		this->setMeeting(false);
		return;
	}
	//for (int i=0;i<this->getDebuff()->size();i++)
	//{
	//	if (this->getDebuff()->at(i) == AttackToZero)
	//		return;
	//}

	for (int i=0;i<plantstatus->plantVector.at(0)->getbuff()->size();i++)
	{
		if (plantstatus->plantVector.at(0)->getbuff()->at(i) == Invincible)
			return;
	}
	plantstatus->plantVector.at(0)->getHurt(1);
	plantstatus->plantVector.at(0)->Attacked();
}

void Zombie::clear(Node * pSender)
{
	pSender->removeFromParent();
	pSender->removeAllChildrenWithCleanup(true);
	delete this;
}

void Zombie::clear_from_vector(Node * pSender)
{
	for (unsigned i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i) == this)
		{
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
	}
}

void Zombie::Stop_Animation()
{
	getImg()->getActionManager()->removeAllActionsByTag(Animation_Tag, getImg());
	if (hasEquip()) {
		getEquip()->getImg()->getActionManager()->removeAllActionsByTag(Animation_Tag, getEquip()->getImg());
	}
}

void Zombie::Climb_Animation(Sprite* sp)
{
	this->getDebuff()->push_back(Climb_Tag);
	this->setWalkSpeed(this->getPreWalkSpeed()*3);
	double time = map::BlockSize.first*1.8 / getPreWalkSpeed();
	MoveBy* mb = MoveBy::create(time/2, Point(0,sp->getContentSize().height/2*sp->getScaleY()+ this->getImg()->getContentSize().height/2* this->getImg()->getScaleY()));
	auto fun = [this](Node*psender)
	{
		for (int i = 0; i < getDebuff()->size(); i++)
		{
			if (getDebuff()->at(i) == Climb_Tag)
			{
				getDebuff()->erase(getDebuff()->begin() + i);
				break;
			}
		}
		this->setWalkSpeed(this->getPreWalkSpeed()/3);
		this->Move();
		this->setMeeting(false);
	};
	auto call = CallFuncN::create(fun);
	Sequence *sequence = Sequence::create(mb, mb->reverse(), call, NULL);
	this->getImg()->runAction(sequence);
	this->Move();
	this->setMeeting(false);
}

void Zombie::Lost_Equip()
{
	if (hasEquip()) {
		getEquip()->Die();
		setEquip(nullptr);
		if (hasHead()) {
			setMeeting(false);
			Move();
		}
	}
}
