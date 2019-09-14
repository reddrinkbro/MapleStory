#pragma once
#include "monsterBase.h"
class OrangeMushroom : public monsterBase
{
private:
	int hitTime;
	int random;
	float angle;
	float _time;
	bool _isJump;
	int jumpCount;
public:
	void monsterMove(void);
	void jump();
	bool getIsJump() { return _isJump; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	float getTime() { return _time; }
	void setTime(float time) { _time = time; }
	OrangeMushroom();
	~OrangeMushroom();
};

