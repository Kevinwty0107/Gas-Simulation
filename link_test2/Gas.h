#pragma once
#include "stdafx.h"
#include "Ball.h"
using std::vector;

class Gas
{
public:
	Gas() = default;
	virtual ~Gas();


	bool is_Overlap(const Ball &temp) const;
	void addBall(Ball &temp);
	void timePass(Wall &w, double t=dT);
	void outp();
	const vector<Ball>& output() { return bVec; }
	double EK() const;
    void reverse();
protected:

private:
	vector<Ball> bVec;
	
};


