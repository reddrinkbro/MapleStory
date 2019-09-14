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
		if (getDistance() < 0)									//�̵��Ÿ��� 0���� �ǰų� ���� �������� �������
		{
			setIsMove(false);									//������ ����
			setDistance(RND->getInt(800));						//�̵��Ÿ� �缳��

		}
	}
	else
	{
		setRelax(getRelax() - 1);								//�޽Ľð� ����
		if (getRelax() < 0)										//�޽��� ������
		{
			if (random % 2 == 0)								//�������� ¦���϶�
			{
				setIsLeft(true);								//�������� �̵�
				random = RND->getInt(2);
			}
			else if (random % 2 == 1)							//Ȧ���̰ų� ���� �����϶�
			{
				setIsLeft(false);								//���������� �̵�
				random = RND->getInt(2);
			}
			setIsMove(true);									//�����δ�
			setRelax(300);										//�޽Ľð� �缳��
		}
	}
	if (getIsHit())													//�¾�����
	{
		setIsMove(false);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//�÷��̾ �����ʿ� �ִٸ�
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(false);										//�������� ����
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//�÷��̾ ���ʿ� �ִٸ�
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(true);										//�������� ����
		}
		setIsChase(false);
		setRelax(getRelax() - hitTime);
		if (getRelax() < 0)
		{
			setIsHit(false);
			setIsChase(true);										//�÷��̾ �i�´�
		}
	}
	if (getIsChase())
	{
		setRelax(300);
		if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//�÷��̾ �����ʿ� �ִٸ�
		{
			_monsterRect.left++;
			_monsterRect.right++;
			setIsLeft(false);
		}
		else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//�÷��̾ ���ʿ� �ִٸ�
		{
			_monsterRect.left--;
			_monsterRect.right--;
			setIsLeft(true);
		}
		if (getIsHit())
		{
			if (PLAYER->_playerRect.rc.left > _monsterRect.left)		//�÷��̾ �����ʿ� �ִٸ�
			{
				_monsterRect.left -= 2;
				_monsterRect.right -= 2;
			}
			else if (PLAYER->_playerRect.rc.right < _monsterRect.right)	//�÷��̾ ���ʿ� �ִٸ�
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
	setIsChase(false);				//��ų���߿��� �i�ư��� �ʴ´�
	setIsMove(false);				//��ų���߿��� �̵����� �ʴ´�
	setIsHit(false);				//��ų���߿��� �ǰݸ���� ������ �ʴ´�.
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
