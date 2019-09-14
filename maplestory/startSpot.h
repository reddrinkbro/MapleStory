#pragma once
#include "gameNode.h"
struct startSpotPortal
{
	RECT rc;
	int portalFrame;
};
class startSpot : public gameNode
{
private:
	RECT _field;
	int _count;
public:
	startSpotPortal _portal;
	HRESULT init();
	void update(void);
	void release(void);
	void render(HDC hdc);
	void portalFrame(void);		//Æ÷Å» ÇÁ·¹ÀÓ
	void intersectFeild(void);  //¹Ù´Ú¿¡ ÂøÁö
	startSpot(){}
	~startSpot(){}
};

