#pragma once
class monsterBase
{
private:
	int _monsterHp;			//���� ü��
	int _monsterAtk;		//���� ���ݷ�
	int _startFrameX;		//���� X������ ����
	int _startFrameY;		//���� Y������ ����
	int _distance;			//���Ͱ� �̵��ѰŸ�
	int _relax;				//���� �޽Ľð�
	bool _isHit;			//���Ͱ� ���ظ� �Ծ����� Ȯ��
	bool _isLeft;			//���� ���¹���
	bool _isMove;			//���Ͱ� �����̴���
	bool _isChase;			//�÷��̾ �i����
	bool _isDie;			//���Ͱ� �׾�����
public:
	RECT _monsterRect;		//���� �簢��
	int _monsterCount;		//���� ī��Ʈ
	int getMonsterHp() { return _monsterHp; }
	void setMonsterHp(int monsterHp) { _monsterHp = monsterHp; }
	int getMonsterAttack() { return _monsterAtk; }
	void setMonsterAttack(int monsterAtk) { _monsterAtk = monsterAtk; }
	int getStartFrameX() { return _startFrameX; }
	void setStartFrameX(int startFrameX) { _startFrameX = startFrameX; }
	int getStartFrameY() { return _startFrameY; }
	void setStartFrameY(int startFrameY) { _startFrameY = startFrameY; }
	int getDistance() { return _distance; }
	void setDistance(int distance) { _distance = distance; }
	int getRelax() { return _relax; }
	void setRelax(int relax) { _relax = relax; }
	bool getIsHit() { return _isHit; }
	void setIsHit(bool isHit) { _isHit = isHit; }
	bool getIsLeft() { return _isLeft; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	bool getIsMove() { return _isMove; }
	void setIsMove(bool isMove) { _isMove = isMove; }
	bool getIsChase() { return _isChase; }
	void setIsChase(bool isChase) { _isChase = isChase; }
	bool getIsDie() { return _isDie; }
	void setIsDie(bool isDie) { _isDie = isDie; }

	virtual void monsterMove(void);				//���� �̵��Լ�
	monsterBase();
	~monsterBase();
};

