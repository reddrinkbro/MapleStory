#pragma once
#include "singletonBase.h"

struct playerRect
{
	RECT rc;
	RECT hp;
	RECT mp;
	RECT exp;
	float angle;
	int moveFrame;					//�����ϋ� ����ϴ� ������
	int attackFrame;				//�����Ҷ� ����ϴ� ������
	int climbFrame;					//�������� ����ϴ� ������
	int luckySevenFrame;			//��Ű�������Ҷ� ����ϴ� ������
	int surikenFrame;				//�����˹���Ʈ ����Ҷ� ����ϴ� ������
	int windFrame;					//����Ż������ ����Ҷ� ����ϴ� ������
	float time;						// �����ϴ� �ð�
};
struct javelin
{
	RECT _rc;
	float _angle;					// ǥâ ����
	int _frame;						// ǥâ ������
	float _time;					// ǥâ �����Ǵ� �ð�
	bool _usingJavelin;				// ǥâ ����ϴ��� Ȯ��
};
class player : public singletonBase<player>
{
private:
	int _currnetHp;		//���� ü��
	int _maxHp;			//�ִ� ü��
	int _currentMp;		//���� ����
	int _maxMp;			//�ִ� ����
	int _damage;		//������
	int _level;			//�÷��̾� ����
public:
	HRESULT init();
	playerRect _playerRect;			// �÷��̾� ����ü
	javelin _javelin1;				// ǥâ����ü
	javelin _javelin2;				// ǥâ����ü
	int _attack;					// �÷��̾� ���� ������ ����
	int _count; 					// ������ ī��Ʈ
	int _moveCount;					// ���̵��� Ȯ���� ���� (���� �� Ű������ ���� Ű������ �̵��Ҷ� -1, ����Ű������ ���� Ű������ �̵��Ҷ� 1, ���̵��� 0���� �ʱ�ȭ)
	int _jumpCount;					// �÷��� ���� ����ϱ� ���� ����
	int _safeTime;					// ���ݴ��ϰ� �����ð�
	bool _isLeft; 					// �÷��̾� �¿� ���� Ȯ��
	bool _isLie; 					// �÷��̾ ����ȴ��� Ȯ��
	bool _isJump; 					// �÷��̾� �������� Ȯ��
	bool _isAttack;					// �÷��̾� ���ݻ��� Ȯ��
	bool _isHit; 					// �÷��̾� �ǰݻ��� Ȯ��
	bool _isMove; 					// �÷��̾� ������ ���� Ȯ��
	bool _isRopeUsing;				// �÷��̾� ������ ��������� Ȯ��
	bool _isLadderUsing;			// �÷��̾� ��ٸ� ��������� Ȯ��
	bool _isUsingSkill;				// �÷��̾� ��ų������
	bool _isPlayerMoveMap;			// �÷��̾� �� �̵� Ȯ��
	bool _isHurt;					// �÷��̾ ���� ���ߴ���
	bool _isClimbing;				// �÷��̾ ��ٸ��� ������ �ִ��� Ȯ��
	bool _isDownClimbing;			// �÷��̾ ��ٸ��� ������ �ִ��� Ȯ��
	bool _isDownJump;				// �÷��̾ ������ ��ٸ��� ������ ����ϴ��� Ȯ��
	int getCurrentHp() { return _currnetHp; }
	void setCurrentHp(int currnetHp) { _currnetHp = currnetHp; }	// ���� ü�� Get Set
	int getMaxHp() { return _maxHp; }
	void setMaxHp(int maxHp) { _maxHp = maxHp; }					// �ִ� ü�� Get Set
	int getCurrentMp() { return _currentMp; }
	void setCurrentMp(int currnetMp) { _currentMp = currnetMp;}		// ���� ���� Get Set
	int getMaxMp() { return _maxMp; }
	void setMaxMp(int maxMp) { _maxMp = maxMp; }					// �ִ� ���� Get Set
	int getDamage() { return _damage; }
	void setDamage(int damage) { _damage = damage; }				// ������ Get Set
	int getLevel() { return _level; }
	void setLevel(int level) { _level = level; }					// ���� ���� Get Set
	
	void playerLevelUp(void);										// �÷��̾� ������
	void playerJump(void);											//�÷��̾� ����
	float getAngle(float x1, float y1, float x2, float y2);			//���� ���
	float getDistance(float x1, float y1, float x2, float y2);		//�Ÿ����
	void flashJump(void);											//�÷��̾� �÷�������

	player(){}
	~player(){}
	
};

