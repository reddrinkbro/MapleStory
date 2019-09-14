#include "stdafx.h"
#include "startSpot.h"

HRESULT startSpot::init()
{
	setIsInPlayer(true);
	setIsLeft(false);
	setIsRight(false);
	IMAGEMANAGER->addImage("���۸�", "Map/����.bmp", WINSIZEX, WINSIZEY);								//���
	IMAGEMANAGER->addFrameImage("portal", "Map/portal.bmp", 1286, 133, 14, 1, true, RGB(255, 0, 255));	//��Ż
	_portal.rc = RectMake(0, 450, 40, 133);																//��Ż �簢��(��׽ý� ����� ���±�)
	_portal.portalFrame = 0;																			//��Ż X�� ������
	_field = RectMake(0, 585, WINSIZEX, 50);
	return S_OK;
}

void startSpot::update(void)
{
	RECT rcTemp;
	
	PLAYER->_isPlayerMoveMap = true;
	
	_count++;
	PLAYER->_playerRect.rc.top += GRAVITY;			//������ �߷� �ۿ�
	PLAYER->_playerRect.rc.bottom += GRAVITY;
	portalFrame();
	intersectFeild();
	if (PLAYER->_playerRect.rc.right > WINSIZEX)
	{
		PLAYER->_playerRect.rc.left -= 3;
		PLAYER->_playerRect.rc.right -= 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_portal.rc))
		{
			setIsLeft(true);
		}
	}
	if (PLAYER->_moveCount == -1)//��׽ý� ����Ϳ��� ������ ��ž������ ��Ÿ��
	{
		PLAYER->_playerRect.rc.left = _portal.rc.left;
		PLAYER->_playerRect.rc.right = PLAYER->_playerRect.rc.left + 79;
		PLAYER->_playerRect.rc.bottom = _portal.rc.top;
		PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
		PLAYER->_moveCount = 0;
	}
}

void startSpot::release(void)
{
}


void startSpot::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	IMAGEMANAGER->loopRender("���۸�", getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, 0);
	IMAGEMANAGER->frameRender("portal", getMemDC(), _portal.rc.left, _portal.rc.top);
	char str[128];
	
	this->getBackBuffer()->render(getHDC());
}

void startSpot::portalFrame(void)
{
	IMAGEMANAGER->findImage("portal")->setFrameY(0);
	if (_count % 7 == 0)
	{
		_portal.portalFrame++;
		if (_portal.portalFrame > 13)
		{
			_portal.portalFrame = 0;
		}
		IMAGEMANAGER->findImage("portal")->setFrameX(_portal.portalFrame);
	}
}

void startSpot::intersectFeild(void)
{
	RECT rcTemp;
	if (IntersectRect(&rcTemp, &PLAYER->_playerRect.rc, &_field))
	{
		if (PLAYER->_playerRect.rc.bottom < _field.bottom)
		{
			PLAYER->_playerRect.rc.bottom = _field.top ;
			PLAYER->_playerRect.rc.top = PLAYER->_playerRect.rc.bottom - 85;
			PLAYER->_playerRect.time = 0;
			PLAYER->_isJump = false;
			PLAYER->_jumpCount = 0;
		}
	}
}

