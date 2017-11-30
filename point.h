#ifndef POINT_POLAR_H
#define POINT_POLAR_H
#include <cmath>
template <class PointT = double,class NameT = int>
class Polar2D;
template <class PointT = double, class NameT = int>
class Point2D;
typedef Point2D<double, int> Point;
template <class PointT = double,class NameT = int>
class Point2D{
	friend class Polar2D<PointT,NameT>;
	PointT _x;
	PointT _y;
	NameT _name;
public:
	Point2D ():_x(0.),_y(0.){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		}
	Point2D (PointT x1,PointT y1):_x(x1),_y(y1){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		}
	Point2D (const Point2D & p):_x(p._x),_y(p._y){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		}
	PointT& x(){
		return _x;
		}
	PointT& y(){
		return _y;
		}
	double mod(){
		return sqrt(_x*_x+_y*_y);
		}
	void set(PointT x1, PointT y1){
		_x = x1;
		_y = y1;
	}
	Polar2D<PointT,NameT> toPolar(){
		Polar2D<PointT, NameT> temp(sqrt(_x*_x + _y*_y), atan(_y / _x));
		if (temp.angle() < 0)
			temp.rotate(2 * 3.1415829);
		return temp;
		}
	template<class PolarT, class NameT> inline
	friend bool operator < (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator > (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator <= (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator >= (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator ==(const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator != (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b);
	};
template<class PointT, class NameT> inline
bool operator < (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b)
{
	return a._x == b._x ? a._y < b._y : a._x < b._x;
}

template<class PointT, class NameT> inline
bool operator >(const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b)
{
	return a._x == b._x ? a._y > b._y : a._x > b._x;
}

template<class PointT, class NameT> inline
bool operator <= (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b)
{
	return a._x == b._x ? a._y <= b._y : a._x < b._x;
}

template<class PointT, class NameT> inline
bool operator >= (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b)
{
	return a._x == b._x ? a._y >= b._y : a._x > b._x;
}

template<class PointT, class NameT> inline
bool operator != (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b)
{
	return a._x != b._x || a._y != b._y;
}

template<class PointT, class NameT> inline
bool operator == (const Point2D<PointT, NameT> & a, const Point2D<PointT, NameT> & b)
{
	return a._x == b._x && a._y == b._y;
}
template <class PolarT = double,class NameT = int>
struct Polar2D{
	PolarT _r;
	PolarT _angle;
	NameT _name;
public:
	Polar2D ():_r(0.),_angle(0.){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		}
	Polar2D (const PolarT& x1,const PolarT& y1):_r(x1),_angle(y1){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		/*if(_angle > 99999){
			//обработка ошибки
			}
		while(_angle>3.1415){
			_angle-=3.1415;
			}
		while(_angle<-3.1415){
			_angle+=3.1415;
			}*/
		}
	Polar2D (const Polar2D & p):_r(p._r),_angle(p._angle){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		}
	PolarT& r(){
		return _r;
		}
	PolarT& angle(){
		return _angle;
		}
	double mod(){
		return _r;
		}
	void set(const PolarT& x1, const PolarT& y1){
		_r = x1;
		_angle = y1;
	}
	Point2D<PolarT,NameT> toDecart(){
		Point2D<PolarT, NameT> temp;
		temp.set(_r*cos(_angle),_r*sin(_angle));
		return temp;
		}
	void rotate(PolarT angle){
		_angle+=angle;
		if(_angle > 99999){
			//обработка ошибки
			}
		while(_angle>2*3.1415){
			_angle-=2*3.1415;
			}
		while(_angle<0){
			_angle+=2*3.1415;
			}
		}
	template<class PolarT, class NameT> inline
	friend bool operator < (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator > (const  Polar2D<PolarT, NameT> &  a,const   Polar2D<PolarT, NameT>&  b);
	template<class PolarT, class NameT> inline
	friend bool operator <= (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator >= (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator ==(const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b);
	template<class PolarT, class NameT> inline
	friend bool operator != (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b);
	};
template<class PolarT, class NameT> inline
bool operator < (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b)
{
	return a._r == b._r ? a._angle < b._angle : a._r < b._r;
}

template<class PolarT, class NameT> inline
bool operator >(const  Polar2D<PolarT, NameT> &  a,const   Polar2D<PolarT, NameT> & b)
{
	return a._r == b._r ? a._angle > b._angle : a._r > b._r;
}

template<class PolarT, class NameT> inline
bool operator <= (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b)
{
	return a._r == b._r ? a._angle <= b._angle : a._r < b._r;
}

template<class PolarT, class NameT> inline
bool operator >= (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b)
{
	return a._r == b._r ? a._angle >= b._angle : a._r > b._r;
}

template<class PolarT, class NameT> inline
bool operator != (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b)
{
	return a._r != b._r || a._angle != b._angle;
}

template<class PolarT, class NameT> inline
bool operator == (const Polar2D<PolarT, NameT> & a, const Polar2D<PolarT, NameT> & b)
{
	return a._r == b._r && a._angle == b._angle;
}
typedef Polar2D<double,int> Polar;
#endif