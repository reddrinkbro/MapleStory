#pragma once
#include "image.h"


//백버퍼 이미지를 정적변수로 만들기
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
	//백버퍼 이미지 얻기
	image* getBackBuffer(void) { return _backBuffer; }
	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기 (화면DC)
	HDC getHDC() { return _hdc; }

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(){}
	virtual ~gameNode() {}
};

