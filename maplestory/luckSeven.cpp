#include "stdafx.h"
#include "luckSeven.h"

HRESULT luckSeven::init()
{
	_skillRange = RectMake(0, 0, 60, 44);
	_skillCount = 0;
	setStartLeft(0);
	setStartRight(4);
	setDamage(RND->getFromIntTo(PLAYER->getDamage(), PLAYER->getDamage() * 2));
	setMana(0);
	setIsPossible(true);
	setIsUsing(false);
	return S_OK;
}
void luckSeven::usingSkill(void)
{
	if (getIsPossible())
	{
		PLAYER->setCurrentMp(PLAYER->getCurrentMp() - getMana());
		setIsUsing(true);
	}
	if (PLAYER->_isLeft)
	{
		_skillRange.left = PLAYER->_playerRect.rc.left - 43;
		_skillRange.right = _skillRange.left + 43;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 44;
		_skillRange.bottom =_skillRange.top + 44;
	}
	else
	{
		_skillRange.left = PLAYER->_playerRect.rc.right;
		_skillRange.right = _skillRange.left + 43;
		_skillRange.top = PLAYER->_playerRect.rc.bottom - 44;
		_skillRange.bottom = _skillRange.top + 44;
	}
}
void luckSeven::possibleSkill(void)
{
	if (PLAYER->_playerRect.mp.left < WINSIZEX / 2 - 252)
	{
		setIsPossible(false);
	}
	else
	{
		setIsPossible(true);
	}
}