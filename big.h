#ifndef _BIG_INT_
#define _BIG_INT_
#include <vector>
#include <windows.h>
#include "func.h"
//#include "bits.h"
using namespace std;
#define  lnum vector<int>
const int base = 1000000000;
const unsigned short int quantity_one = 9;
#define last size()-1
class bigInt{
	bool sign;
	lnum _elem;
	enum{ POSITIVE, NEGATIVE };
public:
	bigInt(){//пустое число
		sign = POSITIVE;
		_elem.resize(1);
		_elem[0] = 0;
	}
	bigInt(const bigInt& new_elem){//копирование
		sign = new_elem.sign;
		_elem.resize(new_elem._elem.size());
		for (size_t i = 0; i < _elem.size(); ++i){
			_elem[i] = new_elem._elem[i];
		}
	}
	bigInt(long x){//инициализация длинным
		sign = (x < 0 ? NEGATIVE : POSITIVE);
		_elem.resize(1);
		_elem[0] = abs(x);
	}
	bigInt(int x){//инициализация числом
		sign = (x < 0 ? NEGATIVE : POSITIVE);
		_elem.resize(1);
		_elem[0] = abs(x);
	}
	bigInt(long x, long x1...)//последним должен идти ноль
	{
		sign = (x < 0 ? NEGATIVE : POSITIVE);
		long *ptr = &x;
		string num;
		while (*ptr != 0){
			num += ItoS(*ptr);
			ptr++;
		}
		Ini(num);
	}
	bigInt(int x, int x1...)//последним должен идти ноль
	{
		sign = (x < 0 ? NEGATIVE : POSITIVE);
		int *ptr = &x;
		string num;
		while (*ptr != 0){
			num += ItoS(*ptr);
			ptr++;
		}
		Ini(num);
	}
	bigInt(const string& num){//инициализация через строку
		_elem.clear();
		sign = (num[0] == '-' ? NEGATIVE : POSITIVE);
		short first = (num[0] == '-' ? 1 : 0);
		for (int i = (int)num.size(); i > first; i -= quantity_one)
		if (i < quantity_one)
			_elem.push_back(abs(StoI(num.substr(sign, i).c_str())));
		else
			_elem.push_back(abs(StoI(num.substr(i - quantity_one, quantity_one).c_str())));
	}
	void Ini(const string& num){//переинициализация строкой
		_elem.clear();
		sign = (num[0] == '-' ? NEGATIVE : POSITIVE);
		short first = (num[0] == '-' ? 1 : 0);
		for (int i = (int)num.size(); i>first; i -= quantity_one)
		if (i < quantity_one)
			_elem.push_back(abs(StoI(num.substr(sign, i).c_str())));
		else
			_elem.push_back(abs(StoI(num.substr(i - quantity_one, quantity_one).c_str())));
	}
	void print(){//вывод
		cout << (sign ? '-' : ' ');
		cout << (_elem.empty() ? 0 : _elem.back());
		for (int i = _elem.size() - 2; i >= 0; --i)
			cout << _elem[i];
		while (_elem.size() > 1 && _elem.back() == 0)
			_elem.pop_back();
	}
	/*операторы присвания*/
	void operator = (const bigInt& x){
		sign = x.sign;
		_elem.resize(x._elem.size());
		for (size_t i = 0; i< _elem.size(); ++i){
			_elem[i] = x._elem[i];
		}
	}
	void operator = (const string & x){
		_elem.clear();
		sign = (x[0] == '-' ? NEGATIVE : POSITIVE);
		for (int i = (int)x.size(); i>0; i -= quantity_one)
		if (i < quantity_one)
			_elem.push_back(abs(StoI(x.substr(0, i).c_str())));
		else
			_elem.push_back(abs(StoI(x.substr(i - quantity_one, quantity_one).c_str())));
	}
	void operator = (const long& x){
		sign = (x < 0 ? NEGATIVE : POSITIVE);
		_elem.clear();
		_elem.push_back(abs(x));
	}
	void operator = (const int& x){
		sign = (x < 0 ? NEGATIVE : POSITIVE);
		_elem.clear();
		_elem.push_back(abs(x));
	}
	/*Вроде рабочие операторы сравнения
	Перегружены операторы сравнения
	с целом числом,длинным,строкой-числом
	и другим большим числом
	*/
	bool operator == (const bigInt& x){
		if (_elem.size() != x._elem.size()) return false;
		else {
			for (int i = _elem.size() - 1; i >= 0; i--){
				if (_elem[i] != x._elem[i])return false;
			}
			return (sign == x.sign ? true : false);
		}
	}
	bool operator == (const int& x){
		return (_elem.size() == 1 && _elem[0] == abs(x) && sign == Sign(x));
	}
	bool operator == (const long& x){
		return (_elem.size() == 1 && _elem[0] == x && sign == Sign(x));
	}
	bool operator == (const string& x){
		bigInt tmp(x);
		return((*this) == tmp);
	}
	bool operator != (const bigInt& x){
		if ((*this) == x) return false;
		else if (_elem.size() != x._elem.size() || sign != x.sign)return true;
		else {
			for (int i = _elem.size() - 1; i >= 0; i--){
				if (_elem[i] != x._elem[i])return true;
			}
			return false;
		}
	}
	bool operator != (const int& x){
		return (_elem.size() != 1 || _elem[0] != abs(x) || sign != Sign(x));
	}
	bool operator != (const long& x){
		return (_elem.size() != 1 || _elem[0] != abs(x) || sign != Sign(x));
	}
	bool operator != (const string& x){
		bigInt tmp(x);
		return((*this) != tmp);
	}
	bool operator > (const int& x){
		if (sign == Sign(x)){
			//Если знаки равны
			if (sign == POSITIVE){
				//*Если знаки оба положительны,то просто сравниваем на признак большинства
				return CoreLarger(x);
			}
			//*Если оба отрицательны ,то просто сравниваем на признак меньшинства
			else return CoreLess(x);
		}
		else{
			return !sign;
		}
	}
	bool operator > (const bigInt& x){
		if (sign == x.sign){
			//Если знаки равны
			if (sign == POSITIVE){
				//*Если знаки оба положительны,то просто сравниваем на признак большинства
				return CoreLarger(x);
			}
			//*Если оба отрицательны ,то просто сравниваем на признак меньшинства
			else return CoreLess(x);
		}
		else{
			return !sign;
		}
		//*Сравнение в функциях core... идет по модулю
	}
	bool operator > (const string & x){
		bigInt tmp(x);
		return ((*this) > tmp);
	}
	bool operator < (const bigInt & x){
		//Всё с точностью до наоборот (см operator >)
		if (sign == x.sign){
			if (sign == POSITIVE){
				return CoreLess(x);
			}
			else return CoreLarger(x);
		}
		else{
			return sign;
		}
	}
	bool operator < (const int & x){
		//Всё с точностью до наоборот (см operator >)
		if (sign == Sign(x)){
			if (sign == POSITIVE){
				return CoreLess(x);
			}
			else return CoreLarger(x);
		}
		else{
			return sign;
		}
	}
	bool operator < (const string & x){
		bigInt tmp(x);
		return ((*this) < tmp);
	}
	bool operator <= (const bigInt & x){
		return ((*this) < x || (*this) == x);
	}
	bool operator <= (const int& x){
		return (_elem.size() == 1 && _elem[0] <= x);
	}
	bool operator <= (const long& x){
		return (_elem.size() == 1 && _elem[0] <= x);
	}
	bool operator <= (const string & x){
		bigInt tmp(x);
		return ((*this) <= tmp);
	}
	bool operator >= (const bigInt & x){
		return ((*this) > x || (*this) == x);
	}
	bool operator >= (const int& x){
		return (_elem.size() == 1 && _elem[0] >= x);
	}
	bool operator >= (const long& x){
		return (_elem.size() == 1 && _elem[0] >= x);
	}
	bool operator >= (const string & x){
		bigInt tmp(x);
		return ((*this) >= tmp);
	}
	friend size_t QuantityNumber(bigInt x);
	friend ostream& operator<<(ostream& out, bigInt& num);
	friend istream& operator>>(istream& in, bigInt& num);
	string ToString(){
		string res;
		if (sign)res += "-";
		res += (_elem.empty() ? "0" : ItoS(_elem.back()));
		for (int i = _elem.size() - 2; i >= 0; --i){
			if (QuantityNumber(_elem[i]) <= quantity_one)
			for (int j = QuantityNumber(_elem[i]) + 1; j<quantity_one; j++)
				res += ("0");
			res += (ItoS(_elem[i]));
		}
		return res;
	}
	bigInt& operator+=(const bigInt& b){
		*this = *this + b;
		return *this;
	}
	bigInt operator+(const bigInt& b){
		bigInt c;
		bigInt tmp_a(*this);
		bigInt tmp_b(b);
		if (abs(tmp_a) < abs(tmp_b)){
			//большее по модулю должно стоять слева
			std::swap(tmp_a, tmp_b);
		}
		if (tmp_a.sign == tmp_b.sign){
			//Если знаки равны
			if (tmp_a.sign == POSITIVE){
				//и оба положительны то просто сумируем
				CoreSum(tmp_a, tmp_b, c);
			}
			else{
				//если оба отрицательны то сумируем и помечаем что знак стал отрицательным
				CoreSum(tmp_a, tmp_b, c);
				c.sign = NEGATIVE;
			}
		}
		else {
			if (tmp_a.sign == POSITIVE){
				//если только первый положительный то это вычитание
				CoreRes(tmp_a, tmp_b, c);
			}
			else {
				//если только второй положительный то (-a + b = -(a-b) )
				tmp_a.ReverseSign();
				CoreRes(tmp_a, tmp_b, c);
				c.ReverseSign();
			}

		}
		return c;
	}
	bigInt& operator+=(const string& s){
		bigInt b(s);
		*this = *this + b;
		return *this;
	}
	bigInt operator+(const string& s){
		bigInt b(s);
		bigInt tmp_a = *this;
		return tmp_a + b;
	}
	friend bigInt abs(bigInt x);
	bigInt& operator-=(const bigInt& b){
		*this = *this - b;
		return *this;
	}
	bigInt operator-(const bigInt& b){
		bigInt c;
		bigInt tmp_a(*this);
		bigInt tmp_b(b);
		if (abs(tmp_a) < abs(tmp_b) && abs(tmp_a) != abs(tmp_b)){
			swap(tmp_a, tmp_b);
		}
		if (tmp_a.sign == tmp_b.sign){
			if (tmp_a.sign == POSITIVE){
				CoreRes(tmp_a, tmp_b, c);
			}
			else{
				CoreRes(tmp_a, tmp_b, c);
				c.ReverseSign();
			}
		}
		else {
			if (tmp_a.sign == POSITIVE){
				CoreSum(tmp_a, tmp_b, c);
			}
			else {
				tmp_a.ReverseSign();
				CoreSum(tmp_a, tmp_a, c);
				c.ReverseSign();
			}

		}
		return c;
	}

	bigInt& operator-=(const string& s){
		bigInt b(s);
		*this = *this - b;
		return *this;
	}
	bigInt operator-(const string& s){
		bigInt b(s);
		bigInt tmp_a = *this;
		return tmp_a - b;
	}
	bigInt operator*(const bigInt& b){
		bigInt c;
		bigInt b_tmp(b);
		CoreMult(*this, b_tmp, c);
		if (sign != b.sign){
			c.sign = NEGATIVE;
		}
		else c.sign = POSITIVE;
		return c;
	}
	bigInt& operator*=(const bigInt& b){
		*this = *this * b;
		return *this;
	}
	bigInt operator*(const string& s){
		bigInt b(s);
		bigInt c;
		CoreMult(*this, b, c);
		if (sign != b.sign){
			c.sign = NEGATIVE;
		}
		else c.sign = POSITIVE;
		return c;
	}
	bigInt& operator*=(const string& s){
		bigInt b(s);
		*this = *this * b;
		return *this;
	}
	bigInt operator / (const int& b){
		bigInt c;
		c = CoreDivShort(b);
		if (sign != Sign(b)){
			c.sign = NEGATIVE;
		}
		else c.sign = POSITIVE;
		return c;
	}
	bigInt& operator /= (const int& b){
		*this = *this / b;
		return *this;
	}
	bigInt& operator /= (const bigInt& b){
		*this = *this / b;
		return *this;
	}
	bigInt& operator /= (const string& s){
		bigInt b(s);
		*this = *this / b;
		return *this;
	}
	bigInt operator /(const bigInt& b){
		bigInt c;
		bigInt tmp_b(b);
		CoreDivLong(*this, tmp_b, c);
		if (sign != b.sign){
			c.sign = NEGATIVE;
		}
		else c.sign = POSITIVE;
		return c;
	}
	bigInt operator /(const string& s){
		bigInt b(s);
		bigInt c;
		CoreDivLong(*this, b, c);
		if (sign != b.sign){
			c.sign = NEGATIVE;
		}
		else c.sign = POSITIVE;
		return c;
	}
	bigInt operator % (const int& b){
		bigInt c;
		int tmp_b = b;
		c = CoreModShort(tmp_b);
		return c;
	}
	bigInt operator %(const bigInt& b){
		bigInt c;
		bigInt tmp_b(b);
		CoreModLong(*this, tmp_b, c);
		return c;
	}
	bigInt operator %(const string& s){
		bigInt b(s);
		bigInt c;
		CoreModLong(*this, b, c);
		return c;
	}
	bigInt& operator %= (const int& b){
		*this = *this % b;
		return *this;
	}
	bigInt& operator %= (const bigInt& b){
		*this = *this % b;
		return *this;
	}
	bigInt& operator %= (const string& s){
		bigInt b(s);
		*this = *this % b;
		return *this;
	}
	bigInt& operator ++ (){
		bigInt tmp(1);
		if (sign == POSITIVE){
			CoreSum(*this, tmp, *this);
		}
		else {
			CoreRes(*this, tmp, *this);
		}
		return *this;
	}
	bigInt operator++ (int){
		bigInt oldValue(*this);
		this->operator++();
		return oldValue;
	}
	bigInt& operator -- (){
		bigInt tmp(1);
		if (*this == 0){
			*this = -1;
		}
		else if (sign == POSITIVE){
			CoreRes(*this, tmp, *this);
		}
		else {
			CoreSum(*this, tmp, *this);
		}
		return *this;
	}
	bigInt operator-- (int){
		bigInt oldValue(*this);
		this->operator--();
		return oldValue;
	}
	bigInt operator-(){
		bigInt tmp(*this);
		tmp.sign = !tmp.sign;
		return tmp;
	}
public:
	void CoreSum(bigInt& tmp_a, bigInt& tmp_b, bigInt& c){
		c = tmp_a;
		int carry = 0;
		for (size_t i = 0; i < max(c._elem.size(), tmp_b._elem.size()) || carry; ++i) {
			if (i == c._elem.size())_elem.push_back(0);
			c._elem[i] += carry + (i < tmp_b._elem.size() ? tmp_b._elem[i] : 0);
			carry = (c._elem[i] >= base);
			if (carry)  c._elem[i] -= base;
		}
	}
	void CoreRes(bigInt& tmp_a, bigInt& tmp_b, bigInt&c){
		c = tmp_a;
		int carry = 0;
		for (size_t i = 0; i<tmp_b._elem.size() || carry; ++i) {
			c._elem[i] -= carry + (i < tmp_b._elem.size() ? tmp_b._elem[i] : 0);
			carry = c._elem[i] < 0;
			if (carry)  c._elem[i] += base;
		}
		while (c._elem.size() > 1 && c._elem.back() == 0)
			c._elem.pop_back();
	}
	void CoreMult(bigInt& a, bigInt& b, bigInt& c){
		c._elem.resize(a._elem.size() + b._elem.size());
		for (size_t i = 0; i<a._elem.size(); ++i)
		for (int j = 0, carry = 0; j<(int)b._elem.size() || carry; ++j) {
			long long cur = c._elem[i + j] + a._elem[i] * 1ll * (j < (int)b._elem.size() ? b._elem[j] : 0) + carry;
			c._elem[i + j] = int(cur % base);
			carry = int(cur / base);
		}
		while (c._elem.size() > 1 && c._elem.back() == 0)
			c._elem.pop_back();
	}
	bigInt CoreDivShort(const int& b){
		int carry = 0;
		for (int i = (int)_elem.size() - 1; i >= 0; --i) {
			long long cur = _elem[i] + carry * 1ll * base;
			_elem[i] = int(cur / b);
			carry = int(cur % b);
		}
		while (_elem.size() > 1 && _elem.back() == 0)
			_elem.pop_back();
		return *this;
	}
	void CoreDivLong(bigInt& a, bigInt& b, bigInt& c){
		int ceil = 0;
		size_t counter = 0, counter2 = QuantityNumber(b);
		bool f_it = true;
		string res;
		string val = a.ToString();
		string buff;
		bigInt tmp, tmp2 = 1;
		//первая инициализация
		while (tmp < b){
			//срезаем символы пока не получим число большее делителя
			buff.push_back(val[counter++]);
			tmp = buff;
		}
		while (tmp >= b){
			CoreRes(tmp, b, tmp);
			ceil++;
		}
		res.push_back(char(ceil + 48));
		buff = tmp.ToString();
		while (counter < val.size()){
			buff.push_back(val[counter++]);
			tmp = buff;
			ceil = 0;
			//срезаем символы пока не получим число большее делителя
			//как только срезали будем вычитать
			while (tmp >= b){
				CoreRes(tmp, b, tmp);
				ceil++;
			}
			if (ceil != 0)buff = tmp.ToString();
			res.push_back(char(ceil + 48));
		}
		c = res;
	}
	void CoreModLong(bigInt& a, bigInt& b, bigInt& c){
		int ceil = 0;
		size_t counter = 0, counter2 = QuantityNumber(b);
		bool f_it = true;
		string res;
		string val = a.ToString();
		string buff;
		bigInt tmp, tmp2 = 1;
		//первая инициализация
		while (tmp < b){
			//срезаем символы пока не получим число большее делителя
			buff.push_back(val[counter++]);
			tmp = buff;
		}
		while (tmp >= b){
			CoreRes(tmp, b, tmp);
			ceil++;
		}
		res.push_back(char(ceil + 48));
		buff = tmp.ToString();
		while (counter < val.size()){
			buff.push_back(val[counter++]);
			tmp = buff;
			ceil = 0;
			//срезаем символы пока не получим число большее делителя
			//как только срезали будем вычитать
			while (tmp >= b){
				CoreRes(tmp, b, tmp);
				ceil++;
			}
			if (ceil != 0)buff = tmp.ToString();
			res.push_back(char(ceil + 48));
		}
		c = tmp;
	}
	bigInt CoreModShort(int & b){
		int carry = 0;
		for (int i = (int)_elem.size() - 1; i >= 0; --i) {
			long long cur = _elem[i] + carry * 1ll * base;
			_elem[i] = int(cur / b);
			carry = int(cur % b);
		}
		while (_elem.size() > 1 && _elem.back() == 0)
			_elem.pop_back();
		return carry;
	}
	bool CoreLarger(const bigInt& x){
		if (_elem.size() > x._elem.size())return true;
		else if (_elem.size() < x._elem.size())return false;
		else {
			for (int i = _elem.size() - 1; i >= 0; i--){
				if (_elem[i] < x._elem[i])return false;
				else if (_elem[i] != x._elem[i]) return true;
			}
			return false;
		}
	}
	bool CoreLess(const bigInt& x){
		if (_elem.size() > x._elem.size())return false;
		else if (_elem.size() < x._elem.size())return true;
		else {
			for (int i = _elem.size() - 1; i >= 0; i--){
				if (_elem[i] < x._elem[i])return true;
				else if (_elem[i] != x._elem[i]) return false;
			}
			return false;
		}
	}
	void ReverseSign(){
		sign = !sign;
	}
	void LevelUp(){//удаление лидирующих нулей
		for (int i = _elem.size() - 1; i >= 1; i--)
			_elem[i] = _elem[i - 1];
		if (_elem[_elem.size() - 1])
			_elem.resize(_elem.size() + 1);
	}
};
#undef lnum
#undef last
ostream& operator<<(ostream& out, bigInt& num){
	out << (num.sign ? '-' : ' ');
	out << (num._elem.empty() ? 0 : num._elem.back());
	for (int i = num._elem.size() - 2; i >= 0; --i){
		if (QuantityNumber(num._elem[i]) <= quantity_one)
		for (int j = QuantityNumber(num._elem[i]) + 1; j<quantity_one; j++)
			out << 0;
		out << num._elem[i];
	}
	while (num._elem.size() > 1 && num._elem.back() == 0)
		num._elem.pop_back();
	return out;
}
istream& operator>>(istream& in, bigInt& num){
	string buff;
	in >> buff;
	num.Ini(buff);
	return in;
}
bigInt abs(bigInt x){
	x.sign = 0;
	return x;
}
size_t QuantityNumber(bigInt x){
	size_t counter = quantity_one*(x._elem.size() - 1);
	while (x._elem[0] /= 10){
		//берем последний член массива и считаенм количество чисел в нем
		counter++;
	}
	return counter;
}
#endif