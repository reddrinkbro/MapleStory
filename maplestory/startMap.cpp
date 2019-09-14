#include "stdafx.h"
#include "startMap.h"


HRESULT startMap::init(void)
{

	IMAGEMANAGER->addImage("���ȭ��", "image/BackGround.bmp", 3554, 700);

	//���� ������ �ʱ�ȭ
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

	IMAGEMANAGER->loopRender("���ȭ��", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _bgSpeed, 0);
	
	//�����ϰ� �ϴ� ������ ���� �ڷ� ����� ���̰� �Ѵ�
	SetBkMode(getMemDC(), TRANSPARENT);
	//���� �ؽ�Ʈ
	char str[128];
	wsprintf(str, "������ ��Ʈ");
	TextOut(getMemDC(), 230, 250, str, strlen(str));

	//���ο� ���
	HFONT font;
	HFONT oldFont;

	//font = CreateFont
	//(
	//����ũ��, ������, ������ü����, ���ڹ���, ���ڱ���,
	//����(true, false), ����(�Ҳ���, ������), ��Ҽ�(),
	//���ڼ���, �����Ȯ��, Ŭ������Ȯ��, �������, �ڰ�, ��Ʈ
	//)
	//�������� ����ũ�⿡���� ����ϴ� 0���� �ΰ� �մ��� ����
	font = CreateFont(70, 0, 0, 0, 600,
		0, 0, 1,
		HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	wsprintf(str, "���ο� ��Ʈ");
	TextOut(getMemDC(), 100, 300, str, strlen(str));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	this->getBackBuffer()->render(getHDC());
}
