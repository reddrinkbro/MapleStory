#include "stdafx.h"
#include "startMap.h"


HRESULT startMap::init(void)
{

	IMAGEMANAGER->addImage("배경화면", "image/BackGround.bmp", 3554, 700);

	//루프 변수들 초기화
	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	return S_OK;
}

void startMap::release(void)
{
}

void startMap::update(void)
{
	_offsetX++;
	_bgSpeed += 3;
}

void startMap::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	IMAGEMANAGER->loopRender("배경화면", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _bgSpeed, 0);
	
	//투명하게 하는 것으로 글자 뒤로 배경이 보이게 한다
	SetBkMode(getMemDC(), TRANSPARENT);
	//기존 텍스트
	char str[128];
	wsprintf(str, "기존의 폰트");
	TextOut(getMemDC(), 230, 250, str, strlen(str));

	//새로운 방법
	HFONT font;
	HFONT oldFont;

	//font = CreateFont
	//(
	//문자크기, 문자폭, 문자전체기울기, 문자방향, 문자굵기,
	//기울기(true, false), 밑줄(할꺼냐, 말꺼냐), 취소선(),
	//문자세팅, 출력정확도, 클리핑정확도, 출력의질, 자간, 폰트
	//)
	//문자폭은 문자크기에따라 비례하니 0으로 두고 손대지 말것
	font = CreateFont(70, 0, 0, 0, 600,
		0, 0, 1,
		HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(str, "새로운 폰트");
	TextOut(getMemDC(), 100, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	this->getBackBuffer()->render(getHDC());
}
