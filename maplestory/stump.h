#pragma once
#include "monsterBase.h"
class stump : public monsterBase
{
private:
	int random;
	int hitTime;			//�´� �ð�
public:
	void monsterMove(void);
	stump();
	~stump();
};

