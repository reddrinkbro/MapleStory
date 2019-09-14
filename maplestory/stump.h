#pragma once
#include "monsterBase.h"
class stump : public monsterBase
{
private:
	int random;
	int hitTime;			//맞는 시간
public:
	void monsterMove(void);
	stump();
	~stump();
};

