// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN

// Windows 헤더 파일:
#include <Windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//======================================
//	## 내가 만든 헤더파일을 이곳에 추가 ##
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
//	## 싱글톤을 이곳에 추가한다 ##
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
//	## 매크로 ## (윈도우창 초기화)
//================================
#define WINNAME			(LPTSTR)(TEXT("WindowAPI"))
#define WINSTARTX		0
#define WINSTARTY		0
#define WINSIZEX		950
#define WINSIZEY		700
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=================================================
//	## 매크로 함수 ## (클래스에서 동적할당된 부분 해제)
//=================================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//================
//	## 전역변수 ##
//================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

//================
//	## 전처리 ##
//================
#define PI 3.141592f
#define GRAVITY 9
