#include "stdafx.h"
#include "FlashJump.h"

HRESULT FlashJump::init()
{
	_skillRange = RectMake(0, 0, 130, 85);
	_skillCount = 0;
	setStartLeft(0);
	setStartRight(4);
	setDamage(0);
	setIsPossible(true);
	return S_OK;
}

