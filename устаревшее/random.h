#ifndef _RAND_H_
#define _RAND_H_
#include <time.h>
#include <cmath>
#include <stdlib.h>
typedef unsigned long MaxGen;
class CRand
{
	MaxGen mod;
	MaxGen a;
	MaxGen b;
	MaxGen c;
	MaxGen x_cur;
	const static MaxGen max_p = 4294967291;
	const static MaxGen best_c = 12345L;
	const static MaxGen best_a = 1073741823;//34;
	const static MaxGen best_b = 1103515245L;
	const static MaxGen best_x = 4;

public:
	enum mode{ NO_OPTIMISED_MOD = 0, OPTIMISED_MOD = 1,REDUCE_BIG_MOD = 2};
	CRand(MaxGen set_mod = max_p , MaxGen set_a = best_a, MaxGen set_x = best_x,MaxGen set_b = best_b, MaxGen set_c = best_c)
		:a(set_a), x_cur(set_x), c(set_c), mod(set_mod),b(set_b){};
	MaxGen get(int min = 0,int max = 0);
	float getFloat(int min = 0, int max = 0, int order_mod = 3);
	void set(long new_x);
	void setCurrentTime();
#ifdef _BITS_H_
	Bits getBits(int n);
#endif
	static long GCD(long m, long n);
	static bool isPrime(long p);
	static long sqrtInt(long p);
	static CRand optimalGenerator(int mod = 1009, int mode = 0);
	static CRand optimalGeneratorToScreen(int mod = 1009, int mode = 0);
	static bool isGoodMod(int mod);
	static void testGenerator(CRand gen);
private:
	MaxGen getPeriod();
};
long CRand::GCD(long m,long n)
{
	//Алгоритм Евклида для нахождения НОД
	if (n == 0)
		return m;
	return(n, m%n);
}
bool CRand::isPrime(long p)
{
	//Алгоритм определяет является ли число простым
	if (p == 2)
		return true;
	long max = sqrtInt(p);
	for (long i = 1; i <= max; i+=2)
	if (p%i == 0)
		return false;
	return true;
}
static bool isGoodMod(int mod)
{
	//определяет является ли число хорошим модулем
	return CRand::isPrime(mod);
}
long CRand::sqrtInt(long p)
{
	//корень из целого
	unsigned rslt = (unsigned)p;
	long div = p;
	if (p <= 0)
		return 0;
	while (1)
	{
		div = (p / div + div) / 2;
		if (rslt > div)
			rslt = (unsigned)div;
		else
			return rslt;
	}
}
MaxGen CRand::get(int min, int max)
{
	//получить случаайное целое число
	max = (max == 0 ? mod - 1 : max);
	MaxGen new_x_cur = (a*x_cur*x_cur + b*x_cur + c) % mod;
	MaxGen rez = min + (new_x_cur%(max - min));
	x_cur = new_x_cur;
	return rez;
}
float CRand::getFloat(int min , int max ,int number_of_sign)
{
	//получить случайное вещественное число
	max = (max == 0 ? mod - 1 : max);
	double dot = 0;
	for (size_t i = 0; i < number_of_sign; i++)
	{
		x_cur = get();
		dot += double(x_cur%10) / pow(10, i + 1);
	}
	x_cur = get();
	MaxGen mantiss = min + (x_cur/10) % (max - min);
	double res = (double)mantiss + (double)dot;
	return res;
}
void CRand::set(long new_x)
{
	//устанавливает x
	x_cur = new_x;
}
void CRand::setCurrentTime()
{
	//устанавливает x = текущее время
	x_cur = time(NULL);
}
#ifdef _BITS_H_
MaxGen CRand::getPeriod()
{
	//получить период
	Bits table(mod,false);
	int counter = 0;
	while (1)
	{
		long x = get();
		if (table[x] == true)
			break;
		else
			table.check(x);
		counter++;
	}
	return counter;
}
#else
MaxGen CRand::getPeriod()
{
	//получить период
	bool *table = new bool[mod];
	int counter = 0;
	for (int i = 0; i<mod; i++)
	{
		table[i] = false;
	}
	while (1)
	{
		long x = get();
		if (table[x] == true)
			break;
		else
			table[x] = true;
		counter++;
	}
	delete [mod]table;
	return counter;
}
#endif
#ifdef _BITS_H_
CRand CRand::optimalGenerator(int mod,int mode)
{
	//функция возвращает оптимальный генератор при заданном модуле
	Bits flags(mode);
	if (flags.state(0))//OPTIMISED_MOD
	{
		while (!isPrime(mod))
		{
			--mod;
		}
	}
	if (flags.state(1))//REDUCE_BIG_MOD
	{
		mod = (mod > 1009 ? 1009 : mod);
	}
	long opt_a, opt_c, opt_b;
	long max_period = 0;
	for (size_t i = 0; i < sqrtInt(mod); i++)//c
	{
		if (GCD(mod, i) != 1)
			continue;
		for (size_t j = 0; j < sqrtInt(mod); j++)//a
		{
			for (size_t k = 0; k < sqrtInt(mod); k++)//b
			{
				CRand test(mod, j, best_x, k, i);
				long per = test.getPeriod();
				if (per >= max_period)
				{
					max_period = per;
					opt_a = j;
					opt_c = i;
					opt_b = k;
				}
			}
		}
	}
	CRand res(mod, opt_a, best_x, opt_b, opt_c);
	return res;
}
Bits CRand::getBits(int n)
{
	bool state;
	Bits res(n);
	for (size_t i = 0; i < n; i++)
	{
		x_cur = get();
		state = x_cur % 10 > 5 ? 1 : 0;
		res.set(i,state);
	}
	return res;
}
#ifdef _IOSTREAM_
CRand CRand::optimalGeneratorToScreen(int mod,int mode)
{
	//функция выводит все относительно приемлимые варианты параметров,и возвращает 
	// один из самых оптимальных генератор
	Bits flags(mode);
	if (flags.state(0))//OPTIMISED_MOD
	{
		while (!isPrime(mod))
		{
			--mod;
		}
	}
	if (flags.state(1))//REDUCE_BIG_MOD
	{
		mod = (mod > 1009 ? 1009 : mod);
	}
	long opt_a, opt_c, opt_b;
	long max_period = 0;
	for (size_t i = 0; i < mod; i++)//c
	{
		if (GCD(mod, i) != 1)
			continue;
		for (size_t j = 0; j < mod; j++)//a
		{
			for (size_t k = 0; k < mod; k++)//b
			{
				CRand test(mod, j,best_x, k, i);
				long per = test.getPeriod();
				if (per >= max_period)
				{
					max_period = per;
					std::cout <<"a = "<< j << " " <<"x0 = "<< k << " " <<"c = "<< i << " "<<"mod = "<<mod<<" | ";
					long first = test.get(),end = first + 1;
					std::cout << first << " ";
					for (size_t i = 0;i < per; i++)
					{
						end = test.get();
						std::cout << end<<" ";
					}
					std::cout << std::endl;
					opt_a = j;
					opt_c = i;
					opt_b = k;
				}
			}
		}
	}
	CRand res(mod, opt_a, best_x, opt_b, opt_c);
	return res;
}
#endif
void CRand::testGenerator(CRand gen)
{
	//функция тестирует генератор(выводит все значения до зацикливания)
	int first = gen.get();
	std::cout << first<<" ";
	MaxGen buff = -1;
	int counter = 0;
	while (buff != first && counter<= gen.mod)
	{
		buff = gen.get();
		std::cout << buff << " ";
		counter++;
	}
}
#endif
#define rand10() rand()%10
#define randBit() rand()%2
#define randByte() rand()%256
class Rand
{
public:
	Rand()
	{
	}
	long get();
	long get(long min, long max);
	float getFloat(long sign_num = 3);
	float getFloat(long min, long max, long sign_num = 3);
	void set(long x);
	void setTime();
	bool getBit();
	unsigned char getByte();
#ifdef _BITS_H_
	Bits getBits(int size);
#endif
#ifdef _BIG_INT_
	bigInt getBig();
#endif

};
long Rand::get()
{
	return rand();
}
long Rand::get(long min, long max)
{
	return min + rand() % (min + max);
}
float Rand::getFloat(long sign_num)
{
	float mantiss = get();
	for (size_t i = 0; i < sign_num; i++)
		mantiss += (rand10() / pow(10, i + 1));
	return mantiss;

}
float Rand::getFloat(long min, long max, long sign_num)
{
	float mantiss = min + get()%(max+min);
	for (size_t i = 0; i < sign_num; i++)
	{
		mantiss += (rand10() / pow(10, i+1));
	}
	return mantiss;
}
void Rand::set(long x)
{
	srand(x);
}
void Rand::setTime()
{
	srand(time(NULL));
}
bool Rand::getBit()
{
	return randBit();
}
unsigned char Rand::getByte()
{
	return randByte();
}
#ifdef _BITS_H_
Bits Rand::getBits(int size)
{
	Bits res;
	while(size >= 32)
	{
		res.pushBits(Bits(get()));
	}
	for(size_t i=0;i<size;i++)
	{
		res.pushBit(randBit());
	}
}
#endif
#ifdef _BIG_INT_
bigInt Rand::getBig()
{
	bigInt res =  bigInt(rand())*bigInt(rand());
	return res;
}
#endif
#endif