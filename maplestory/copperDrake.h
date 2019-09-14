#pragma once
#include "monsterBase.h"
class copperDrake : public monsterBase
{
private:
	int hitTime;
	int random;
public:
	void monsterMove(void);
	copperDrake();
	~copperDrake();
};

