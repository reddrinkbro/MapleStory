#pragma once
#include "monsterBase.h"
class AxeStump : public monsterBase
{
private:
	int hitTime;
	int random;
public:
	void monsterMove(void);
	AxeStump();
	~AxeStump();
};

