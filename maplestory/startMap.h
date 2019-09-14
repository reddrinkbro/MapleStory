#pragma once
#include "gameNode.h"

class startMap : public gameNode
{
private:
	//������ ����
	//x
	int _offsetX;
	//y
	int _offsetY;
	//������ ����� �̵��ӵ�(x)
	int _bgSpeed;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	startMap(){}
	~startMap(){}
};

