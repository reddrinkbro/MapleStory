#pragma once
#include "image.h"


//����� �̹����� ���������� �����
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	bool _isInPlayer;
	bool _isLeft;
	bool _isRight;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	bool getIsInplayer() { return _isInPlayer; }
	void setIsInPlayer(bool isInPlayer) { _isInPlayer = isInPlayer; }
	bool getIsLeft() { return _isLeft; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	bool getIsRight() { return _isRight; }
	void setIsRight(bool isRight) { _isRight = isRight; }
	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }
	//�޸� DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ��� (ȭ��DC)
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(){}
	virtual ~gameNode() {}
};

