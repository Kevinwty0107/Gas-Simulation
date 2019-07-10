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
	//表征面的方程，为方便处理，只分为六类，分别平行于xy,xz,yz平面，这样每个面只需一个参数即可
	int style;  //表征面类型
	int k;      //面特征
};
