#pragma once

#include "stdafx.h"
class Plank
{
	friend class Ball;
public:
	Plank();
	Plank(int f, int s);
	virtual ~Plank();
protected:
private:
	//������ķ��̣�Ϊ���㴦��ֻ��Ϊ���࣬�ֱ�ƽ����xy,xz,yzƽ�棬����ÿ����ֻ��һ����������
	int style;  //����������
	int k;      //������
};
