#include "stdafx.h"
#include "mushMom.h"

mushMom::mushMom()
{
	random = RND->getInt(2);
	setStartFrameX(0);
	setMonsterHp(3050);
	setDistance(RND->getInt(500));
	setRelax(300);
	setMonsterAttack(100);
	hitTime = getRelax() / 15;
	setIsHit(false);
	setIsMove(true);
	setIsLeft(true);
	setIsDie(false);
	setIsChase(false);
	setIsUsingSkill(false);
	_monsterRect = RectMake(RND->getFromIntTo(0, 750), 880, 183, 150);
	_skill.rc = RectMake(1920, 1080, 256, 125);
	_skill.count = 0;
	_skill.frame = 0;
	_skill.skillend = true;
	_skill.coolDownTime = 100;
	isreal = false;
	test = 0;
}


mushMom::~mushMom()
{
}


void mushMom::monsterMove(void)
{
	if (getIsMove())
	{
		if (getIsLeft())
		{
			_monsterRect.left--;
			_monsterRect.right--;
		}
		else
		{
			_monsterRect.left++;
			_monsterRect.right++;
		}
		setDistance(getDistance() - 1);
		if (getDistance() < 0)									//이동거리가 0으로 되거나 제일 왼쪽으로 갔을경우
		{
			setIsMove(false);									//움직임 멈춤
			setDistance(RND->getInt(800));						//이동거리 재설정

		}
	}
	else
	{
		setRelax(getRelax() - 1);								//휴식시간 감소
		if (getRelax() < 0)										//휴식이 끝나면
		{
			if (random % 2 == 0)								//랜덤값이 짝수일때
			{
				setIsLeft(true);								//왼쪽으로 이동
				random = RND->getInt(2);
			}
			else if (random % 2 == 1)							//홀수이거나 제일 왼쪽일때
			{
				setIsLeft(false);								//오른쪽으로 이동
				random = RND->getInt(2);
			}
			setIsMove(true);									//움직인다
			setRelax(300);										//휴식시간 재설정
		}
	}
	if (getIsHit())													//맞았을때
	{
		setIsMove(false);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//플레이어가 오른쪽에 있다면
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(false);										//오른쪽을 본다
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//플레이어가 왼쪽에 있다면
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(true);										//오른쪽을 본다
		}
		setIsChase(false);
		setRelax(getRelax() - hitTime);
		if (getRelax() < 0)
		{
			setIsHit(false);
			setIsChase(true);										//플레이어를 쫒는다
		}
	}
	if (getIsChase())
	{
		setRelax(300);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//플레이어가 오른쪽에 있다면
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(false);
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//플레이어가 왼쪽에 있다면
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(true);
		}
		if (getIsHit())
		{
			if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//플레이어가 오른쪽에 있다면
			{
				_monsterRect.left -= 2;
				_monsterRect.right -= 2;
			}
			else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//플레이어가 왼쪽에 있다면
			{
				_monsterRect.left += 2;
				_monsterRect.right += 2;
			}
		}
	}
	if (getIsDie())
	{
		setIsMove(false);
		setIsChase(false);
		setIsHit(false);
		setIsUsingSkill(false);
	}
}

void mushMom::usingSkill(void)
{
	test = 1;
	_skill.skillend = false;
	setIsUsingSkill(true);
	setIsChase(false);				//스킬도중에는 쫒아가지 않는다
	setIsMove(false);				//스킬도중에는 이동하지 않는다
	setIsHit(false);				//스킬도중에는 피격모션을 취하지 않는다.
	if (getStartFrameX() == 6)
	{
		test = 2;
		_monsterRect.top -= 12;
		_monsterRect.bottom -= 12;
	}
	else if (getStartFrameX() > 7)
	{
		test = 3;
		_monsterRect.top +=12;
		_monsterRect.bottom +=12;
	}
	if (getStartFrameX() > 8)
	{
		test = 4;
		_skill.rc = RectMake(_monsterRect.left-30, _monsterRect.top + 50, 256, 125);
	}
}
