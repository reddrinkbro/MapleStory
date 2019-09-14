#pragma once
#include "monsterBase.h"
class blueMushroom : public monsterBase
{
private:
	int hitTime;
	int random;
	float angle;
	float _time;
	bool _isJump;
	int jumpCount;
public:
	void monsterMove();
	void jump();
	bool getIsJump() { return _isJump; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	float getTime() { return _time; }
	void setTime(float time) { _time = time; }
	blueMushroom();
	~blueMushroom();
};

