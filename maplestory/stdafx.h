// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKver.h>

// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define WIN32_LEAN_AND_MEAN

// Windows ��� ����:
#include <Windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//======================================
//	## ���� ���� ��������� �̰��� �߰� ##
//======================================
#include "commonMacroFiunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "player.h"
#include "FlashJump.h"
#include "luckSeven.h"
#include "shurikenBurst.h"
#include "shadeSplit.h"
#include "windTalisman.h"

//================================
//	## �̱����� �̰��� �߰��Ѵ� ##
//================================
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define PLAYER player::getSingleton()
#define FLASHJUMP FlashJump::getSingleton()
#define LUCKSEVEN luckSeven::getSingleton()
#define SHURIKENBURST shurikenBurst::getSingleton()
#define SHADESPLIT shadeSplit::getSingleton()
#define WINDTALISMAN windTalisman::getSingleton()

//================================
//	## ��ũ�� ## (������â �ʱ�ȭ)
//================================
#define WINNAME			(LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX		0
#define WINSTARTY		0
#define WINSIZEX		950
#define WINSIZEY		700
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## ��ũ�� �Լ� ## (Ŭ�������� �����Ҵ�� �κ� ����)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## �������� ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

//================
//	## ��ó�� ##
//================
#define PI 3.141592f
#define GRAVITY 9
