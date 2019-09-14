#pragma once
#include "gameNode.h"

class startMap : public gameNode
{
private:
	//루프용 변수
	//x
	int _offsetX;
	//y
	int _offsetY;
	//루프될 배경의 이동속도(x)
	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	startMap(){}
	~startMap(){}
};

