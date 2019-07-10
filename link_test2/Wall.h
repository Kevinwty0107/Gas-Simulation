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
	void addPlank(Plank &p); //添加墙面
protected:
private:
	int n = 0;  //墙面数目，在加隔板时会发生变化
	vector<Plank> pVec;    //直接操作墙板会更好，整个墙体只需包含每一块墙板即可，具体实现细节交给墙板，可以不一定是矩形，甚至可以是其他性状的墙面
};


//第一类：从正到负碰X板
//第二类：从负到正碰x板