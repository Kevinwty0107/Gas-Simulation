#include "Wall.h"


Wall::Wall(int size)
	:Wall(-size, size, -size, size ,- size, size)
{
}

Wall::Wall(int x1, int x2, int y1, int y2, int z1, int z2)
	:n(6)
{
	pVec.push_back(Plank(x1, 1));
	pVec.push_back(Plank(x2, 2));
	pVec.push_back(Plank(y1, 3));
	pVec.push_back(Plank(y2, 4));
	pVec.push_back(Plank(z1, 5));
	pVec.push_back(Plank(z2, 6));
}

Wall::~Wall()
{
}

void Wall::addPlank(Plank & p)
{
	++n;
	pVec.push_back(p);
}
