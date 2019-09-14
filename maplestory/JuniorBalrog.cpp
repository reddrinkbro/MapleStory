#include "stdafx.h"
#include "JuniorBalrog.h"


JuniorBalrog::JuniorBalrog()
{
	random = RND->getInt(2);
	setStartFrameX(0);
	setMonsterHp(100000000);
	setMonsterAttack(50);
	setDistance(RND->getInt(800));
	setRelax(300);
	hitTime = getRelax() / 15;
	skillSelect = 1;
	isreal = false;
	setIsHit(false);
	setIsMove(true);
	setIsLeft(false);
	setIsDie(false);
	setIsChase(false);
	setIsUsingSkill(false);
	_monsterRect = RectMake(RND->getFromIntTo(0, WINSIZEX), 809, 533, 231);
	for (int i = 0;i < 2;i++)
	{
		_skill[i].count = 0;
		_skill[i].frame = 0;
		_skill[i].skillUse = false;			//스킬 사용
		_skill[i].skillEnd = true;			//스킬 쿨타임 시작
	}
	coolDownTime = 400;
	_skill[0].rc = RectMake(1920, 1080, 163, 133);
	_skill[1].rc = RectMake(1920, 1080, 87, 99);
}


JuniorBalrog::~JuniorBalrog()
{

}



void JuniorBalrog::monsterMove(void)
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
	}
}

void JuniorBalrog::usingSkill(void)
{
	setIsMove(false);
	setIsChase(false);
	setIsHit(false);
	
	if (PLAYER->_playerRect.rc.left > _monsterRect.left && PLAYER->_playerRect.rc.right < _monsterRect.right )
	{
		if (coolDownTime <= 0 && skillSelect == 0)
		{
			setIsUsingSkill(true);
			if (getStartFrameX() > 5)
			{
				_skill[skillSelect].rc.left = PLAYER->_playerRect.rc.left;
				_skill[skillSelect].rc.right = _skill[skillSelect].rc.left + 163;
				_skill[skillSelect].rc.top = PLAYER->_playerRect.rc.top - 50;
				_skill[skillSelect].rc.bottom = _skill[skillSelect].rc.bottom + 133;
			}
		}
		if (coolDownTime <= 0 && skillSelect == 1)
		{
			setIsUsingSkill(true);
			if (getStartFrameX() > 0)
			{
				_skill[skillSelect].rc.left = PLAYER->_playerRect.rc.left;
				_skill[skillSelect].rc.right = _skill[skillSelect].rc.left + 74;
				_skill[skillSelect].rc.top = PLAYER->_playerRect.rc.top;
				_skill[skillSelect].rc.bottom = _skill[skillSelect].rc.bottom + 122;
			}
		}
	}

	
}

