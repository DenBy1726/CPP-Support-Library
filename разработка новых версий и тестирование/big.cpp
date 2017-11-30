#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;
typedef vector<int> lnum;
string ItoS(long num);
long StoI(string num);
size_t QuantityNumber(int x);
#define base  1000000000
#define quantity_one  9
#define last size()-1
class bigInt{
	lnum _elem;
public:
	bigInt(){//пустое число
		_elem.resize(1);
		_elem[0] = 0;
	}
	bigInt(const bigInt& new_elem){//копирование
		_elem.resize(new_elem._elem.size());
		for(size_t i = 0;i< _elem.size();++i){
			_elem[i] = new_elem._elem[i];
		}
	}
	bigInt(long x){//инициализация длинным
		_elem.resize(1);
		_elem[0] = x;
	}
	bigInt(int x){//инициализация числом
		_elem.resize(1);
		_elem[0] = x;
	}
	bigInt(long x,long x1...)//последним должен идти ноль
	{
		long *ptr = &x;
		string num;
		while(*ptr != 0){
			num+=ItoS(*ptr);
			ptr++;
		}
		Ini(num);
	}
	bigInt(int x,int x1...)//последним должен идти ноль
	{
		int *ptr = &x;
		string num;
		while(*ptr != 0){
			num+=ItoS(*ptr);
			ptr++;
		}
		Ini(num);
	}
	bigInt(const string& num){//инициализация через строку
		_elem.clear();
		for (int i=(int)num.size(); i>0; i-=quantity_one)
			if (i < quantity_one)
				_elem.push_back (StoI (num.substr (0, i).c_str()));
			else
				_elem.push_back (StoI (num.substr (i-quantity_one, quantity_one).c_str()));
	}
	void Ini(const string& num){//переинициализация строкой
		_elem.clear();
		for (int i=(int)num.size(); i>0; i-=quantity_one)
			if (i < quantity_one)
				_elem.push_back (StoI (num.substr (0, i).c_str()));
			else
				_elem.push_back (StoI (num.substr (i-quantity_one, quantity_one).c_str()));
	}
	void print(){//вывод
		cout<<( _elem.empty() ? 0 : _elem.back());
		for (int i=_elem.size()-2; i>=0; --i)
			cout<< _elem[i];
		while (_elem.size() > 1 && _elem.back() == 0)
		_elem.pop_back();
	}
	/*операторы присвания*/
	void operator = (const bigInt& x){
		_elem.resize(x._elem.size());
		for(size_t i = 0;i< _elem.size();++i){
			_elem[i] = x._elem[i];
		}
	}
	void operator = (const string & x){
		_elem.clear();
		for (int i=(int)x.size(); i>0; i-=quantity_one)
			if (i < quantity_one)
				_elem.push_back (StoI (x.substr (0, i).c_str()));
			else
				_elem.push_back (StoI (x.substr (i-quantity_one, quantity_one).c_str()));
	}
	void operator = (long x){
		_elem.clear();
		_elem.push_back(x);
	}
	void operator = (int x){
		_elem.clear();
		_elem.push_back(x);
	}
	/*Вроде рабочие операторы сравнения
		Перегружены операторы сравнения
		с целом числом,длинным,строкой-числом
		и другим большим числом
	*/
	bool operator == (const bigInt& x){
		if(_elem.size() != x._elem.size()) return false;
		else {
			for(int i = _elem.size()-1;i>=0;i--){
				if(_elem[i] != x._elem[i] )return false;
			}
			return true;
		}
	}
	bool operator == (int x){
		return (_elem.size() == 1 && _elem[0] == x);
	}
	bool operator == (long x){
		return (_elem.size() == 1 && _elem[0] == x);
	}
	bool operator == (const string& x){
		bigInt tmp(x);
		return((*this) == tmp);
	}
	bool operator != (const bigInt& x){
		if((*this) == x) return false;
		else {
			for(int i = _elem.size()-1;i>=0;i--){
				if(_elem[i] != x._elem[i] )return true;
			}
			return false;
		}
	}
	bool operator != (int x){
		return (_elem.size() != 1 || _elem[0] != x);
	}
	bool operator != (long x){
		return (_elem.size() != 1 || _elem[0] != x);
	}
	bool operator != (const string& x){
		bigInt tmp(x);
		return((*this) != tmp);
	}
	bool operator > (const bigInt& x){
		if(_elem.size() > x._elem.size())return true;
		else if(_elem.size() < x._elem.size())return false;
		else {
			for(int i = _elem.size()-1;i>=0;i--){
				if(_elem[i] < x._elem[i] /*|| (_elem[i] == 0 != x._elem[i])*/ )return false;
			}
			return true;
		}
	}
	bool operator > (int x){
		return (_elem.size() == 1 && _elem[0] > x);
	}
	bool operator > (long x){
		return (_elem.size() == 1 && _elem[0] > x);
	}
	bool operator > (const string & x){
		bigInt tmp(x);
		return ((*this) > tmp );
	}
	bool operator < (const bigInt & x){
		if(_elem.size() < x._elem.size())return true;
		else if(_elem.size() > x._elem.size()) return false;
		else {
			for(int i = _elem.size()-1;i>=0;i--){
				if(_elem[i] > x._elem[i] )return false;
			}
			return true;
		}
	}
	bool operator < (int x){
		return (_elem.size() == 1 && _elem[0] < x);
	}
	bool operator < (long x){
		return (_elem.size() == 1 && _elem[0] < x);
	}
	bool operator < (const string & x){
		bigInt tmp(x);
		return ((*this) < tmp);
	}
	bool operator <= (const bigInt & x){
		if(_elem.size() > x._elem.size())return false;
		else if((*this) == x)return true;
		else {
			for(int i = _elem.size()-1;i>=0;i--){
				if(_elem[i] > x._elem[i] )return false;
			}
			return true;
		}
	}
	bool operator <= (int x){
		return (_elem.size() == 1 && _elem[0] <= x);
	}
	bool operator <= (long x){
		return (_elem.size() == 1 && _elem[0] <= x);
	}
	bool operator <= (const string & x){
		bigInt tmp(x);
		return ((*this) <= tmp);
	}
	bool operator >= (const bigInt & x){
		if(_elem.size() < x._elem.size())return false;
		else if((*this) == x)return true;
		else {
			for(int i = _elem.size()-1;i>=0;i--){
				if(_elem[i] < x._elem[i] )return false;
			}
			return true;
		}
	}
	bool operator >= (int x){
		return (_elem.size() == 1 && _elem[0] >= x);
	}
	bool operator >= (long x){
		return (_elem.size() == 1 && _elem[0] >= x);
	}
	bool operator >= (const string & x){
		bigInt tmp(x);
		return ((*this) >= tmp);
	}
	friend size_t QuantityNumber(bigInt x);
	friend ostream& operator<<(ostream& out,bigInt& num);
	friend istream& operator>>(istream& in,bigInt& num);
	string ToString(){
		string res;
		res.push_back( num._elem.empty() ? 0 : num._elem.back());
		for (int i=num._elem.size()-2; i>=0; --i){
			if(QuantityNumber(num._elem[i]) <= quantity_one)
				for(int j = QuantityNumber(num._elem[i])+1;j<quantity_one;j++)
					res.push_back()0;
			res.push_back(num._elem[i]);
		}
		while (num._elem.size() > 1 && num._elem.back() == 0)
		num._elem.pop_back();
	for(int i = num._elem.size()-1;i>=0;i--)

	return res;

	}


};
ostream& operator<<(ostream& out,bigInt& num){
		out<<( num._elem.empty() ? 0 : num._elem.back());
		for (int i=num._elem.size()-2; i>=0; --i){
			if(QuantityNumber(num._elem[i]) <= quantity_one)
				for(int j = QuantityNumber(num._elem[i])+1;j<quantity_one;j++)
					out<<0;
			out<< num._elem[i];
		}
		while (num._elem.size() > 1 && num._elem.back() == 0)
		num._elem.pop_back();
	for(int i = num._elem.size()-1;i>=0;i--)

	return out;

}
istream& operator>>(istream& in,bigInt& num){
	string buff;
	in>>buff;
	num.Ini(buff);
	return in;
}
size_t QuantityNumber(long x){
	size_t counter=0;
	while(x/=10){
		counter++;
	}
	return counter;
}
size_t QuantityNumber(int x){
	size_t counter=0;
	while(x/=10){
		counter++;
	}
	return counter;
}
string ItoS(long num){
	string a;
	stringstream bufer;
	bufer.clear();
	bufer.sync();
	bufer<<num;
	a = bufer.str();
	return a;
}
long StoI(string num){
	long a;
	stringstream bufer(num);
	bufer.clear();
	bufer.sync();
	bufer>>a;
	return a;
}
size_t QuantityNumber(bigInt x){
	size_t counter = quantity_one*x._elem.size();
	while(x._elem[0]/10){
		//берем последний член массива и считаенм количество чисел в нем
		counter++;
	}
	return counter;
}
void main(){



}