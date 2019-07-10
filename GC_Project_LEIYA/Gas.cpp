#include "Gas.h"



Gas::~Gas()
{
}

bool Gas::is_Overlap(const Ball & temp) const
{
	for (auto it : bVec)
	{
		if (temp.l_().dis(it.l_()) < temp.r_() + it.r_()) return true;
	}
	return false;
}

void Gas::addBall(Ball & temp)
{
	bVec.push_back(temp);
}

void Gas::timePass(Wall &w,double t)
{
    Ball::DT=t;
    //std::cout<<t<<std::endl;
	vector<Ball> test(bVec);
	int n = bVec.size();
	bool flag = false;
	for (int i = 0; i < n; ++i)
	{
		int j = 0;
		flag = false;
		for (; j < n; ++j)
		{
			if (i == j) continue;
			if (bVec[i].isCollision_1(test[j]))
			{
				flag = true;
				break;
			}
		}				
		if (flag)
		{
			bVec[i].colWith_1(test[j]);
			bVec[i].colWith_2(w);
            //std::cout << "Collision between " << i + 1 << " and " << j + 1 << "!\n";
		}
		else
		{
			bVec[i].stepForward(t);
			bVec[i].colWith_2(w);
		}
	}
    //std::cout<<EK()<<std::endl;
}

void Gas::outp()
{
	int i = 0;
	double s(0);
	for (auto it : bVec)
	{
		i++;
        s += it.m_()*it.v_().length()*it.v_().length();
		std::cout << "Particle:" << i << ' ';
		it.l_().outp();
		it.v_().outp();
		std::cout << std::endl;
	}
	std::cout <<"Ek= "<< s<<std::endl;
}

double Gas::EK() const
{
	double s(0);
    for (auto it : bVec)	s += 0.5*(it.v_().length())*(it.v_().length());
	return s;
}

void Gas::reverse()
{
    /*for (auto it : bVec)
    {
        it.v_().outp();
        std::cout<<std::endl;
    }
    std::cout<<std::endl;*/
    for (int i=0;i<bVec.size();++i)
    {
        bVec[i].reverseVelo();
    }
    /*for (auto it : bVec)
    {
        it.v_().outp();
        std::cout<<std::endl;
    }*/
}
