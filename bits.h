#ifndef _BITS_H_
#define _BITS_H_
#define _Debug_Bits debugBits
#define _Bits_Throw
#define _NULLpt (DWORD*)0xcccccccc
#define ALL_ONE 4294967295
#define byte(n) (((n)/(32)) +1)
#define needAllocated need/*(len,i) ((((len) / 32) != (i / 32))? 1 : 0)*/
#define min(a,b) a<b ? a : b;
#include <cstdlib>
#include <new>
#include <Windows.h>
class pBool;
class Bits{
	size_t len;
	DWORD *elem;
private:
	bool get_system(size_t i)const;
	void set_system(size_t i, bool state);
public:
	friend Bits* allocated(Bits* arg, size_t i);
	friend void deallocated(Bits* arg);
	friend inline void debugBits(const size_t& a, const int& i);
	friend inline bool need(const size_t& a, const int& i);
	Bits();
	Bits(size_t n,bool state,DWORD ini = 0);
	Bits(const Bits& a);
	template<class T>
	Bits(const T a);
	template<class T>
	Bits(const T* a, int size);
	~Bits();
#ifdef _VECTOR_
	template <class T>
	Bits(std::vector<T> n);
#endif
	
#ifdef FUNC_H
	long sub(int start, int end);
	long* subLong(int start,int end);
#endif
	void pushBit(bool rez);
	void pushBits(Bits& val);
#ifdef _IOSTREAM_
	void print();
	void print_invert();
#endif
	//получает значение i-ого бита
	bool get(size_t i)const;
	//устанавливает значение i-ого бита в state
	void set(size_t i, bool state);
	//меняет последовательность битов на противоположную
	// 123456 -> 654321
	Bits& rotate();
	//удаляет i бит с конца
	void pop(size_t i = 1);
	//устанавливает биты с позиции start до позиции end в состояние state
	//отсчет с нуля,последний не включается
	void reset(int start, int end,bool state = false);
	//возвращает ссылку на число(32 бита),взятое на срезе битов с 32*i по 32*(i+1) не включая
	DWORD& longVal(size_t i);
	//возвращает срез из 8 битов [8*i, 8*i+1)
	unsigned char getByte(size_t i);
	//возвращает длинну в битах
	size_t size() const;
	//возвращает длинну в байтах
	size_t sizeBytes() const;
	//возвращает фактическое количество хранимых 4-ех байтных чисел
	size_t sizeData() const;
	//возвращает указатель на первое число [0,32)
	DWORD* data();
	//возвращает ссылку на первое число [0,32)
	DWORD*& ref();
	//очищает битовый массив
	void clear();
	//проверяет битовый массив на пустоту
	bool empty();
	//возвращает значение i-ого бита
	bool check(size_t i);
	//реверсирует i-ый бит
	void reverse(size_t i);
	//реверсирует биты из полуинтервала [start,end)
	void reverseOfRange(size_t start, size_t end);
	
	void on(size_t i);
	void off(size_t i);
	bool state(size_t i);
	void all(bool state);
	bool checkAll(bool state);
	void reverseAll();
	void operator=(const Bits& a);
	bool operator[](size_t i);
	bool operator==(const Bits& a);
	bool operator!=(const Bits& a);
	bool operator<(const Bits& b);
	bool operator <=(const Bits& b);
	bool operator >(const Bits& b);
	bool operator >=(const Bits& b);
	void operator~();
	void operator>>(size_t i);
	void operator<<(size_t i);
	void and(const Bits& a);
	void or(const Bits& a);
	void xor(const Bits& a);
	void not();
	void and(const int& i,const bool& state);
	void or(const int& i,const bool& state);
	void xor(const int& i,const bool& state);
	void not(const int& i);
	void swap(const int&i, const int& j);

#ifdef FUNC_H
#undef mi
	pBool TopBool();
#endif
#ifdef _VECTOR_
	template <class T>
	std::vector<T> ToVector();
#endif
	//возвращает значение числа(32 бита),взятое на срезе битов  [0,32)
	DWORD toInt()
	{	
		return *elem;
	}
	//возвращает значение числа(32 бита),взятое на срезе битов  [32*i,32*(i+1))
	DWORD toInt(int i)
	{
		return elem[i];
	}
	//инициализирует биты на срезе [32*i,32*(i+1)) числом x
	void setPack(int x, int i = 0)
	{
		elem[i] = x;
	}
};
//создает пустой массив битов
Bits::Bits()

{
	allocated(this, 0);
	*elem = 0;

}
/*Если true,то инициализируется значением ini,иначе инициализации не будет
ALL_ONE = 0xffffffff
*/
Bits::Bits(size_t n, bool state, DWORD ini)

{
	allocated(this,n);
	if (state)
	{
		for (size_t i = 0; i < byte(n); i++)
			elem[i] = ini;
	}
}
//конструктор копирования
Bits::Bits(const Bits& a)

{
	allocated(this, a.len);
	for (size_t i = 0; i < byte(len); i++)
	{
		elem[i] = a.elem[i];
	}
}
template <class T>
//создает битовый массив на основе произвольного скалярного типа
Bits::Bits(const T a)

{
	allocated(this, sizeof(a)* 8);
	elem[0] = 0;
	T mask;
	T temp;
	for (size_t i = 0; i < len; i++)
	{
		temp = a;
		mask = 1 << i;
		temp &= mask;
		this->set(i, temp ? 1 : 0);
	}
}
template<class T>
//создает битовый массив на основе произвольного типа(в тч и массива),Т имеет размер size
Bits::Bits(const T* a,int size)
{
	allocated(this,size*sizeof(T)* 8);
	size_t index = 0;
	for (size_t i = 0; i < byte(len); i++)
	{
		elem[i] = 0;
	}
	T temp;
	T mask;
	T  one = 1;
	/*
	As though it may seem strange , but for us in this situation, it is important how many bytes should take "one"
			   */
	int counter = 0;
	for (size_t i = 0; counter < len; i++,counter++)
	{
		if (i%(sizeof(T)* 8) == 0 && i != 0)
		{
			index++;
			i = 0;
		}
		temp = a[index];
		mask = one << i;
		temp &= mask;
		this->set(counter, temp ? 1 : 0);
	}
}
Bits::~Bits()
{
	free(elem);
}
//получает значение i-ого бита
bool Bits::get(size_t i)const
{
#ifdef _Bits_Throw
	_Debug_Bits(len, i);
#endif
	size_t index = i / 32;
	index ? i -= (32 * index) : i;
	DWORD mask = 1 << i;
	DWORD temp = elem[index];
	temp &= mask;
	return temp ? 1 : 0;	
}
bool Bits::get_system(size_t i)const
{
	size_t index = i / 32;
	index ? i -= (32 * index) : i;
	DWORD mask = 1 << i;
	DWORD temp = elem[index];
	temp &= mask;
	return temp ? 1 : 0;
}
void Bits::set_system(size_t i, bool state)
{

	size_t index = i/32;
	index ? i-=(32*index) : i;
	state ?elem[index] |= 1<<i : elem[index] &= ~ (1<<i);
}
//устанавливает значение i-ого бита в state
void Bits::set(size_t i, bool state)
{
#ifdef _Bits_Throw
	_Debug_Bits(len, i);
#endif
	size_t index = i / 32;
	index ? i -= (32 * index) : i;
	state ? elem[index] |= 1 << i : elem[index] &= ~(1 << i);
}
//добавляет бит в конец 
void Bits::pushBit(bool rez)
{
	if (needAllocated(len, this->len +1 ) || len == 0)
	{
		allocated(this, len + 1);
		elem[byte(len) - 1] = 0;
	}
	else
	{
		++len;
	}
	set(len-1, rez);
}
//добавляет массив бит в конец
void Bits::pushBits(Bits& val)
{
	size_t temp = len;
	if (needAllocated(len, this->len + val.len))
	{
		//если после добавления битов понадобитьс новые ячейки,то выделяем их
		allocated(this, len + val.len);
		elem[byte(len) - 1] = 0;
	}
	else
	{
		len += val.len;
		//иначе просто увеличиваем доступную длинну
	}
	for (size_t i = temp; i < len;i++)
	{
		set(i, val.get(i - temp));
	}
}
//меняет последовательность битов на противоположную
// 123456 -> 654321
Bits& Bits::rotate()
{
	for (size_t i = 0; i < len / 2; i++)
		swap(i, len - i - 1);
	return *this;
}
//удаляет i бит с конца
void Bits::pop(size_t i)
{
	int q = 0;
	int temp = len - i;//длинна после удаления
	if (needAllocated(len, (len - i)))
	{
		allocated(this, len - i );
		//len = 32 * (byte(len));
	}
	else
	{
		len -= i;
	}
	q = 32 - i % 32;
	reset(temp, 32 * (byte(len)));
}
//устанавливает биты с позиции start до позиции end в состояние state
//отсчет с нуля,последний не включается
void Bits::reset(int start, int end,bool state)
{
	for (; start % 32 != 0 && start<end; start++)
	{
		set_system(start, state);
	}
	for (; (start - 32) < end && start % 32 != 0;start++)
	{
		elem[byte(start)] = 0;
	}
	for (; start < end; start++)
	{
		set_system(start, state);
	}
}
//возвращает ссылку на число(32 бита),взятое на срезе битов с 32*i по 32*(i+1) не включая
DWORD& Bits::longVal(size_t i)
{
	return elem[i];
}
//возвращает срез из 8 битов [8*i, 8*i+1)
unsigned char Bits::getByte(size_t i)
{
	size_t pos_start = 8 * i;
	size_t pos_end = pos_start + 8;
	unsigned char res = 0;
	for (; pos_start < pos_end; pos_start++)
	{
		if (get(pos_start))
		{
			res |= 1 << 8 - (pos_end - pos_start);
		}
	}
	return res;
}
//возвращает длинну в битах
size_t Bits::size() const
{
	return len;
}
//возвращает длинну в байтах
size_t Bits::sizeBytes() const
{
	return len%8 ?(len / 8)+1 : len/8;
}
//возвращает фактическое количество хранимых 4-ех байтных чисел
size_t Bits::sizeData() const
{
	return len % 32 ? (len / 32) + 1 : len / 32;
}
//возвращает указатель на первое число [0,32)
DWORD* Bits::data()
{
	return elem;
}
//возвращает ссылку на первое число [0,32)
DWORD*& Bits::ref()
{
	return elem;
}
//очищает битовый массив
void Bits::clear()
{
	if (needAllocated(len, 0))
		allocated(this, 0);
}
//проверяет битовый массив на пустоту
bool Bits::empty()
{
	return len == 0;
}
//возвращает значение i-ого бита
bool Bits::check(size_t i)
{
	return get(i);
}
//реверсирует i-ый бит
void Bits::reverse(size_t i)
{
	bool flag = get(i);
	set(i, !flag);
}
//реверсирует биты из полуинтервала [start,end)
void Bits::reverseOfRange(size_t start, size_t end)
{
	bool flag;
	while (start++ < end)
	{
		flag = get(start-1);
		set(start - 1, !flag);
	}
}
//отмечает i ячейку в состояние true
void Bits::on(size_t i)
{
	set(i, true);
}
//отмечает i ячейку в состояние false
void Bits::off(size_t i)
{
	set(i, false);
}
//возвращает значение i-ого бита
bool Bits::state(size_t i)
{
	return get(i);
}
//устанавливает все биты в состояние state
void Bits::all(bool state)
{
	size_t i = 0;
	if (state)
	{
		for (; i < byte(len) - 1; i++)
		{
			elem[i] = ALL_ONE;
		}
		for (i*=32; i < len; i++)
		{
			set(i, true);
		}
	}
	else
	{ 
		for (; i < byte(len); i++)
		{
			elem[i] = 0;
		}
	}

}
//устанавливает все биты в состояние state
bool Bits::checkAll(bool state)
{
	if (state)
	{
		for (size_t i = 0; i < byte(len); i++)
		{
			if (elem[i] != ALL_ONE)
				return false;
		}
		return true;
	}
	else
	{
		for (size_t i = 0; i < byte(len); i++)
		{
			if (elem[i] != 0)
				return false;
		}
		return true;
	}
}
//реверсирует все биты
void Bits::reverseAll()
{
	for (size_t i = 0; i < byte(len); i++)
	{
		~elem[i];
	}
}
void Bits::operator=(const Bits& a)
{
	if(needAllocated(len,a.len))
		allocated(this, a.len);
	for (size_t i = 0; i < byte(len); i++)
	{
		elem[i] = a.elem[i];
	}
}
bool Bits::operator[](size_t i)
{
	return get(i);
}
bool Bits::operator==(const Bits& a)
{
	if (len != a.len)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < byte(len); i++)
		{
			if (elem[i] == a.elem[i])
				continue;
			else
				return false;
		}
		return true;
	}
}
bool Bits::operator!=(const Bits& a)
{

	for (size_t i = 0; i < byte(len); i++)
	{
		if (elem[i] == a.elem[i])
			continue;
		else
			return true;
	}
	return false;
}
bool Bits::operator<(const Bits& b)
{
	if (len < b.len)
	{
		return true;
	}
	else
	{
		for (size_t i = 0; i < byte(len); i++)
		{
			if (elem[i] == b.elem[i])
				continue;
			else if (elem[i] < b.elem[i])
				return true;
			else return false;
		}
	}
	return false;
}
bool Bits::operator <=(const Bits& b)
{
	if (len < b.len)
	{
		return true;
	}
	for (size_t i = 0; i<byte(len); i++)
	{
		if (elem[i] == b.elem[i])
			continue;
		else if (elem[i] < b.elem[i])
			return true;
		else return false;
	}
	return true;
}
bool Bits::operator >(const Bits& b)
{
	if (len > b.len)
	{
		return true;
	}
	for (size_t i = 0; i < byte(len); i++)
	{
		if (elem[i] == b.elem[i])
			continue;
		else if (elem[i] > b.elem[i])
			return true;
		else return false;
	}
	return false;
}
bool Bits::operator >=(const Bits& b)
{
	if (len > b.len)
	{
		return true;
	}
	for (size_t i = 0; i < byte(len); i++)
	{
		if (elem[i] == b.elem[i])
			continue;
		else if (elem[i] > b.elem[i])
			return true;
		else return false;
	}
	return true;
}
void Bits::operator~()
{
	reverseAll();
}
void Bits::operator>>(size_t i)
{
	if (((len - 1) / 32) == 0){
		long tmp = *elem;
		for (size_t j = 0; j<i; j++){
			__asm{
				ror tmp, 1;
			}
			elem[0] = tmp;
		}
	}
	else{
		size_t right_index = 0;
		size_t left_index = right_index + 1;
		bool buff, buff2;
		for (size_t j = 0; j<i; j++){
			while (left_index < (((len - 1) / 32) + 1)){
				buff = this->get(left_index);
				buff2 = this->get(0);
				elem[right_index] = elem[right_index] >> 1;
				this->set(32 * left_index - 1, buff);//перенос значения левого бита
				elem[left_index] = elem[left_index] >> 1;
				this->set(len - 1, buff2);//устанавливаем последний в значения первого
				right_index++;
				left_index++;
			}
		}
	}
}
void Bits::operator<<(size_t i)
{
	if (((len - 1) / 32) == 0){
		//elem[0] = elem[0]<<i;
		long tmp = *elem;
		for (size_t j = 0; j<i; j++){
			__asm{
				rol tmp, 1;
			}
		}
		elem[0] = tmp;
	}
	else{
		size_t right_index = 0;
		size_t left_index = right_index + 1;
		bool buff, buff2;
		for (size_t j = 0; j<i; j++){
			while (left_index < (((len - 1) / 32) + 1)){
				buff = this->get(left_index);
				buff2 = this->get(len - 1);
				elem[right_index] = elem[right_index] << 1;
				this->set(32 * left_index - 1, buff);//перенос значения левого бита
				elem[left_index] = elem[left_index] << 1;
				this->set(0, buff2);//устанавливаем первый в значения последнего
				right_index++;
				left_index++;
			}
		}
	}
}
//перемножает два битовых массива
//1*1 = 1
//0*1 = 1*0 = 0*0 = 0
//если длинна a меньше длинны массива,то лишние биты массива не трогаются
void Bits::and(const Bits& a)
{
	size_t _min = min(len, a.len);
	for (size_t i = 0; i < byte(_min); i++)
	{
		elem[i] &= a.elem[i];
	}
}
//складывает два битовых массива
//1+1 = 1+0 = 0+1 = 1
//0*0 = 0
//если длинна a меньше длинны массива,то лишние биты массива не трогаются
void Bits::or(const Bits& a)
{
	size_t _min = min(len, a.len);
	for (size_t i = 0; i < byte(_min); i++)
	{
		elem[i] |= a.elem[i];
	}
}
//складывает два битовых массива по модулю два
//1+1 = 1+0 = 0+1 = 1
//0*0 = 0
//если длинна a меньше длинны массива,то лишние биты массива не трогаются
void Bits::xor(const Bits& a)
{
	size_t _min = min(len, a.len);
	for (size_t i = 0; i < byte(_min); i++)
	{
		elem[i] ^= a.elem[i];
	}
}
//реверсирует все элементы
void Bits::not()
{
	for (size_t i = 0; i < byte(len); i++)
	{
		~elem[i];
	}
}
//логическое & между i элементом и значением state
void Bits::and(const int& i, const bool& state)
{
	set(i, state&get(i));
}
//логическое | между i элементом и значением state
void Bits::or(const int& i, const bool& state)
{
	set(i, state|get(i));
}
//логическое ^ между i элементом и значением state
void Bits::xor(const int& i, const bool& state)
{
	set(i, state^get(i));
}
//реверсирует i элемент
void Bits::not(const int& i)
{
	bool flag = get(i);
	set(i, !flag);
}
//меняет бит i с битом j местами
void Bits::swap(const int&i, const int& j)
{
	bool temp = get(i);
	set(i, get(j));
	set(j, temp);
}
//выводит массив в stdout
void Bits::print()
{
	for (size_t i = 0; i < len; i++)
	{
		std::cout << get(i);
	}
}
inline void debugBits(const size_t& len, const int& i)
{
	try{
		if (i<0 || i >len - 1)throw 1;
	}
	catch (int){
		MessageBox(NULL, "index out of range!", "Error!", MB_OK | MB_ICONERROR);
		exit(0);
		//обработка ошибки
	}
}

Bits* allocated(Bits* arg, size_t i)
{
	if (arg->elem == _NULLpt)
	{
		arg->len = i;
		arg->elem = (DWORD*)malloc((byte(arg->len))*sizeof(DWORD));
		if (arg->elem == 0)
		{
				_THROW_NCEE(_XSTD bad_alloc, );
		}
	}
	else
	{
		arg->len = i;
		arg->elem = (DWORD*)realloc(arg->elem, (byte(arg->len))*sizeof(DWORD));
	}
	return arg;
}
inline bool need(const size_t& a, const int& i)
{
	return (a / 32 != i / 32);
}
#undef min
#endif