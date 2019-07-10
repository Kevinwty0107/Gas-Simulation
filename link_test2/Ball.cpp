#include "Ball.h"
#include <cmath>


double Ball::DT=dT;

Ball::Ball()
{
}

Ball::Ball(Vect & l, Vect & v)
	:velo(v),loc(l)
{
}

Ball::Ball(double m, double r, Vect l, Vect v)
	: mass(m),radius(r),velo(v), loc(l)
{
}


Ball::~Ball()
{
}

Ball::Ball(const Ball & other)
{
	*this = other;
}

void Ball::stepForward(double t)
{
	loc = loc + velo*t;
}
void Ball::stepBack(double t)
{
	loc = loc + velo*(-t);
}

bool Ball::isCollision_1(Ball a)
{
	stepForward();
	a.stepForward();
	bool flag(false);
	if (loc.dis(a.l_()) < radius+a.r_()) flag = true;
	stepBack();
	return flag;
}
void Ball::colWith_1(Ball & a,double t)
{
	double r = radius + a.r_();
	double d = a.l_().dis(loc);
	Vect vR(velo - a.v_());
	double ceta = abs(vR.arg(a.l_() - loc));
	double B = -2 * d*cos(ceta);
	double C = d*d - r*r;
	double delta = B*B - 4 * C;
	if (delta < 0) { std::cerr << "Delta<0 !\n"; std::cin.get(); exit(0); }
	double x = -(B + std::sqrt(delta)) / 2;
	double t0 = x / vR.length();

	stepForward(t0);
	a.stepForward(t0);
	Vect E12(a.l_() - loc);
	E12.standardLize();
	velo = velo - E12*(2 * a.m_() / (a.m_() + mass)*E12.dotProduct(vR));
    stepForward(t - t0);
	a.stepBack(t0);
}
bool Ball::isCollision_2(Wall &w)
{
	stepForward();
    for (auto it : w.pVec)
	{
		if (isCollision_3(it)) 
		{
			stepBack(); return true;
		}
	}
	stepBack();
	return false;
}
bool Ball::isCollision_2_notStep(Wall &w)
{
	stepForward();
	for (auto it : w.pVec)
	{
		if (isCollision_3(it))
		{
			stepBack(); return true;
		}
	}
	stepBack();
	return false;
}


void Ball::colWith_2(Wall & w)	//只保证不出界，并不向前一步
{
	//stepForward();
	for (auto it : w.pVec)
	{
		if (isCollision_3(it)) colWith_3(it);
	}
}
bool Ball::isCollision_3(Plank & p)
{
	//Vect mLoc(loc + velo*dT);
	bool flag = false;
	switch (p.style)
	{
	
	case 1:
		if (loc.x_() - radius < p.k) flag = true;
		break;
	case 2:
		if (loc.x_() + radius > p.k) flag = true;
		break;
	case 3:
		if (loc.y_() - radius < p.k) flag = true;
		break;
	case 4:
		if (loc.y_() + radius > p.k) flag = true;
		break;
	case 5:
		if (loc.z_() - radius < p.k) flag = true;
		break;
	case 6:
		if (loc.z_() + radius > p.k) flag = true;
		break;
	default:
		break;
	}
	return flag;
}



void Ball::colWith_3(Plank & p)//false标记从正向负运动，true标记从负向正运动
{
	switch (p.style)
	{

	case 1:
		velo = Vect(-velo.x_(), velo.y_(), velo.z_());
		loc = Vect(2 * p.k + 2 * radius - loc.x_(), loc.y_(), loc.z_());
		break;
	case 2:
		velo = Vect(-velo.x_(), velo.y_(), velo.z_());
		loc = Vect(2 * p.k - 2 * radius - loc.x_(), loc.y_(), loc.z_());
		break;
	case 3:
		velo = Vect(velo.x_(), -velo.y_(), velo.z_());
		loc = Vect(loc.x_(), 2 * p.k + 2 * radius - loc.y_(), loc.z_());
		break;
	case 4:
		velo = Vect(velo.x_(), -velo.y_(), velo.z_());
		loc = Vect(loc.x_(), 2 * p.k - 2 * radius - loc.y_(), loc.z_());
		break;
		break;
	case 5:
		velo = Vect(velo.x_(), velo.y_(), -velo.z_());
		loc = Vect(loc.x_(), loc.y_(), 2 * p.k + 2 * radius - loc.z_());
		break;
	case 6:
		velo = Vect(velo.x_(), velo.y_(), -velo.z_());
		loc = Vect(loc.x_(), loc.y_(), 2 * p.k - 2 * radius - loc.z_());
		break;
	default:
		break;
	}
}
