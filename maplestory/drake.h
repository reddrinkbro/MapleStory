#pragma once
#include "monsterBase.h"
class drake : public monsterBase
{
private:
	int hitTime;
	int random;
public:
	void monsterMove(void);
	drake();
	~drake();
};

