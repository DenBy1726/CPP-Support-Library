#include <cmath>
template <class PointT = double,class NameT = int>
class Polar2D;
template <class PointT = double,class NameT = int>
class Point2D{
	friend class Polar2D<PointT,NameT>;
	PointT _x;
	PointT _y;
	NameT _name;
public:
	Point2D ():x(0.),y(0.){
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
	Polar2D<PointT,NameT> toPolar(){
		Polar2D<PointT,NameT> temp(sqrt(_x*_x +_y*_y),atan(_y/_x));
		return temp;
		}
	};
typedef Point2D<double,int> Point;
template <class PolarT = double,class NameT = int>
class Polar2D{
	PolarT _r;
	PolarT _angle;
	NameT _name;
public:
	Polar2D ():_r(0.),_angle(0.){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		}
	Polar2D (PolarT x1,PolarT y1):_r(x1),_angle(y1){
		static size_t counter = 0;
		_name = (NameT)counter+1;
		counter++;
		if(_angle > 99999){
			//обработка ошибки
			}
		while(_angle>3.1415){
			_angle-=3.1415;
			}
		while(_angle<0){
			_angle+=3.1415;
			}
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
	Point2D<PolarT,NameT> toDecart(){
		Point2D<PolarT,NameT> temp(_r*cos(_angle),_r*sin(_angle));
		return temp;
		}
	void rotate(PolarT angle){
		_angle+=angle;
		if(_angle > 99999){
			//обработка ошибки
			}
		while(_angle>3.1415){
			_angle-=3.1415;
			}
		while(_angle<0){
			_angle+=3.1415;
			}
		}

	};
typedef Polar2D<double,int> Polar;
void main(){
	Point a(0,0);
	Point b(1,1);
	Polar c(5,999999999);
	a = c.toDecart();
	c = a.toPolar();

	}