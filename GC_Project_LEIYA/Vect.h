#pragma once
class Vect
{
	//friend class Ball;
public:
	Vect() = default;
	Vect(const Vect&);
	Vect(double, double, double);
	virtual ~Vect();

	double length() const;
	Vect dirc();
	double dis(const Vect&) const;
	double arg(const Vect&) const;
	double dotProduct(const Vect &) const;
	Vect crossProduct(const Vect &);

	void standardLize();
	void outp() const;

	Vect operator+(const Vect& t)const;
	Vect operator-(const Vect& t)const;
	Vect operator*(double t);
	inline friend Vect operator*(double t, Vect &p);
	inline friend Vect operator-(Vect &p) { return p*(-1); }
	inline double x_() const { return x; }
	inline double y_() const { return y; }
	inline double z_() const { return z; }
protected:
private:
	double x, y, z;
};

