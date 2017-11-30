#pragma warning (disable : 4067)
#ifndef FUNC_H
#define FUNC_H
#include<iostream>
#include<sstream>
#include<string>
#include<time.h>
#include<windows.h>
#define INF 2147483647//бесконечность
#define pi 3.1415829//число пи
#undef min(a,b)
	template <class T1, class T2>
	T1 power(T1 base, T2 ex){
		// power of 0
		if (ex == 0){
			return 1;
			// negative exponenet
		}
		else if (ex < 0){
			return 1 / pow(base, -ex);
			// even exponenet
		}
		else if ((int)ex % 2 == 0){
			float half_pow = pow(base, ex / 2);
			return half_pow * half_pow;
			//integer exponenet
		}
		else{
			return base * pow(base, ex - 1);
		}
	}
	template <class T>
	T min(const T& a, const T& b){
		return a > b ? b : a;
	}

	template <class T>
	std::string ToString(T num){
		std::string a;
		std::stringstream bufer;
		bufer.clear();
		bufer.sync();
		bufer << num;
		a = bufer.str();
		return a;
	}

	template <class T>
	T StringTo(std::string num){
		T a;
		std::stringstream bufer(num);
		bufer.clear();
		bufer.sync();
		bufer >> a;
		return a;
	}

	template <class T>
	bool Sign(T a){
		return a < 0;
	}
	size_t QuantityNumber(int x){
		size_t counter = 0;
		while (x /= 10){
			counter++;
		}
		return counter;
	}
	size_t QuantityNumber(long x){
		size_t counter = 0;
		while (x /= 10){
			counter++;
		}
		return counter;
	}
	void GoToXY(int x, int y){
		HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { x, y };
		SetConsoleCursorPosition(StdOut, coord);
	}
	template <class _Type>
	bool XOR(_Type val1, _Type val2){
		return ((!val1 || !val2) && (val1 || val2));
		//(!a || !b) && (a || b)
	}
	template <class T>
	T rnd(T min, T max){
		T r = (min + (rand() % (abs(max) + abs(min))));
		return r;
	}
	double randAngle(){
		int a = rand() % 25;
		double b = (1. / (a + 1));
		double x = (rand() % 5 + 0.28 + b);
		return x;
	}
	double fact(double n){
		return pow(6.2831658*n, 0.5)*pow(n / 2.718, n)*((1 / (288 * n*n)) + 1 + (1 / 12 * n));
	}
#ifdef PAIR_AND_TRIO
	template <class T>
	double LengthVector(Pair<T, T> p1, Pair<T, T> p2){
		return pow((p2.first - p1.first)*(p2.first - p1.first) + (p2.second - p1.second)*(p2.second - p1.second), 0.5);
	}
	template <class T>
	double VectorAngleCos(Pair<T, T> p1, Pair <T, T> p2, Pair <T, T> p3){
		Pair<T,T> A = MakePair(p2.first - p1.first, p2.second - p1.second);
		Pair<T,T> B = MakePair(p2.first - p3.first, p2.second - p3.second);
		return((A.first*B.first + A.second*B.second) / (pow((A.first*A.first + A.second*A.second) * (B.first*B.first + B.second*B.second),0.5)));
	}
#endif
#ifdef POINT_POLAR_H
#ifdef _VECTOR_
#define _VECTOR_POINT_POLAR_H 1
#endif
	template <class T>
	bool isInside( Point2D<T> &p1, Point2D<T> &p,  Point2D<T> &p2)
	{
		return (p1.x() <= p.x() && p.x() <= p2.x() &&
			p1.y() <= p.y() && p.y() <= p2.y());
	}
	template <class T1>
	double VectorAngleCos(Point2D<T1> p1, Point2D<T1> p2, Point2D<T1> p3){
		Point2D<T1> A (p2.x() - p1.x(), p2.y() - p1.y());
		Point2D<T1> B (p2.x() - p3.x(), p2.y() - p3.y());
		return ((A.x()*B.x() + A.y()*B.y()) / (pow((A.x()*A.x() + A.y()*A.y()) * (B.x()*B.x() + B.y()*B.y()), 0.5)));
	}
	template <class T>
	T rotateSide(Point2D<T> p1, Point2D<T> p2, Point2D<T> p3) {
		return (p2.x() - p1.x())*(p3.y() - p2.y()) - (p2.y() - p1.y())*(p3.x() - p2.x());
	}
	template <class T>
	int OrientTriangl2( Point2D<T> &p1,  Point2D<T> &p2,  Point2D<T> &p3)
	{
		return p1.x() * (p2.y() - p3.y()) + p2.x() * (p3.y() - p1.y()) + p3.x() * (p1.y() - p2.y());
	}
#endif
#ifdef _VECTOR_POINT_POLAR_H
	template <class T>
	T minIndexX(std::vector<Point2D<T>> cont){
		size_t min_index = 0;
		for (size_t i = 0; i < cont.size(); i++){
			if (cont[min_index].x() > cont[i].x()){
				min_index = i;
			}
		}
		return min_index;
	}
	template <class T>
	T minIndexY(std::vector<Point2D<T>> cont){
		size_t min_index = 0;
		for (size_t i = 0; i < cont.size(); i++){
			if (cont[min_index].y() < cont[i].y()){
				min_index = i;
			}
		}
		return min_index;
	}
	template <class T>
	T minIndexMod(std::vector<Point2D<T>> cont){
		size_t min_index = 0;
		for (size_t i = 0; i < cont.size(); i++){
			if (cont[min_index].mod() < cont[i].mod()){
				min_index = i;
			}
		}
		return min_index;
	}
	template <class T>
	T maxIndexX(std::vector<Point2D<T>> cont){
		size_t max_index = 0;
		for (size_t i = 0; i < cont.size(); i++){
			if (cont[max_index].x() > cont[i].x()){
				max_index = i;
			}
		}
		return max_index;
	}
	template <class T>
	T maxIndexY(std::vector<Point2D<T>> cont){
		size_t max_index = 0;
		for (size_t i = 0; i < cont.size(); i++){
			if (cont[max_index].y() > cont[i].y()){
				max_index = i;
			}
		}
		return max_index;
	}
	template <class T>
	T maxIndexMod(std::vector<Point2D<T>> cont){
		size_t max_index = 0;
		for (size_t i = 0; i < cont.size(); i++){
			if (cont[max_index].mod() > cont[i].mod()){
				max_index = i;
			}
		}
		return max_index;
	}
#endif
#if defined(_VECTOR_) && defined(BITS_H)
	std::vector<int> make_tree(std::vector<int> tree)
	{
		std::vector<int> res;
		if (!std::is_sorted(tree.begin(), tree.end()))
			std::sort(tree.begin(), tree.end());
		/*	for (int i = 0; i < tree.size() - 1; i++)
			{
			if (tree[i] == tree[i + 1])
			tree.erase(tree.begin() + i);
			}*/
		Bits flags(tree.size());
		flags.CheckAll();
		std::vector<int> num;
		for (size_t i = 0; i < tree.size(); i++)
		{
			num.push_back(i);
		}

		std::vector<int> queue;
		int mid = num.size() / 2;
		queue.push_back(mid);
		flags.UnCheck(mid);
		while (queue.size())
		{
			if (queue[0] / 2 && flags[queue[0] / 2])
			{
				queue.push_back(queue[0] / 2);
				flags.UnCheck(queue[0] / 2);
			}
			if ((queue[0] + num.size()) / 2 < num.size() && flags[(queue[0] + num.size()) / 2])
			{
				queue.push_back((queue[0] + num.size()) / 2);
				flags.UnCheck((queue[0] + num.size()) / 2);
			}
			res.push_back(queue[0]);
			queue.erase(queue.begin());
		}
		res.push_back(num[0]);
		for (size_t i = 0; i < res.size(); i++)
		{
			num[i] = tree[res[i]];
		}

		//	make_tree(tree, res);
		return num;
	}

#endif
#endif
