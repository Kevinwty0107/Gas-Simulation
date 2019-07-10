#pragma once
#include "Vect.h"
#include "stdafx.h"
#include "Wall.h"


class Ball
{
public:
    static double DT;
	Ball();
	Ball(Vect &l, Vect &v);
    Ball(double m,double r,Vect l, Vect v);
	virtual ~Ball();
	Ball(const Ball& other);

	inline void setVelo(Vect &v) { velo = v; }
	inline void setLoc(Vect &l) { loc = l; }
    void reverseVelo() { /*std::cout<<"Yes!"<<std::endl;velo.outp();*/velo = velo*(-1);/*velo.outp(); */}
	inline const Vect v_()const { return velo; }
	inline const Vect l_()const { return loc; }
	inline const double r_()const { return radius; }
	inline const double m_()const { return mass; }

    void stepForward(double t=DT);
    void stepBack(double t = DT);
	bool isCollision_1(Ball a);     //ÓëÐ¡ÇòÅö×²µÄ¼ì²â
	bool isCollision_2(Wall &w);
	bool isCollision_2_notStep(Wall &w);
	bool isCollision_3(Plank &p);

    void colWith_1(Ball &a,double t=DT);        //ÓëÐ¡ÇòÅö×²
	void colWith_2(Wall &w);
	void colWith_3(Plank &p);

protected:
private:
	Vect velo, loc;
	double mass=1, radius=1;

};
