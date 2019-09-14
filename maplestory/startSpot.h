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
	void portalFrame(void);		//��Ż ������
	void intersectFeild(void);  //�ٴڿ� ����
	startSpot(){}
	~startSpot(){}
};

