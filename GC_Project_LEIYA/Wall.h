#pragma once
#include "stdafx.h"
#include "Plank.h"

using std::vector;

class Wall
{
	friend class Ball;
public:
	Wall()=default;
	Wall(int size);
	Wall(int x1, int x2, int y1, int y2, int z1, int z2);
	virtual ~Wall();

	//void initialize();
	void addPlank(Plank &p); //���ǽ��
protected:
private:
	int n = 0;  //ǽ����Ŀ���ڼӸ���ʱ�ᷢ���仯
	vector<Plank> pVec;    //ֱ�Ӳ���ǽ�����ã�����ǽ��ֻ�����ÿһ��ǽ�弴�ɣ�����ʵ��ϸ�ڽ���ǽ�壬���Բ�һ���Ǿ��Σ�����������������״��ǽ��
};


//��һ�ࣺ����������X��
//�ڶ��ࣺ�Ӹ�������x��