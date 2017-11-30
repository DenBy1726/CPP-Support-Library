#ifndef BITS_H
#define BITS_H
#include<stdlib.h>
#include<windows.h>
//#include "func.h"
#pragma warning(disable : 4244)
class pBool;
#define MAX_LONG LONG_MAX
#define FIRST_NULL MAX_LONG - 1
class pBool{
        bool* elem;
        size_t size;
public:
        pBool(){
                /*Конструктор по умолчмнию,указывает что размер объекта равен нулю*/
                size = 0;
                elem = (bool*)malloc(0);
        }
        pBool(int n){
                /*Конструктор с параметром,создает объект размерностью n*/
                elem = (bool*)malloc(n);
                size = n;
				UnCheckAll();
        }
        pBool(const pBool& a){
                /*Конструктор копирования*/
                size = a.size;
                elem = (bool*)malloc(size);
                for(size_t i = 0;i<size;i++){
                        elem[i] = a.elem[i];
                }
        }
		~pBool(){
			delete[]elem;
		}
        bool* val(){
                return elem;
        }
        void Clear(){
                Resize(0);
        }
        bool Empty(){
                return size==0;
        }
		size_t Size() const
		{
                return size;
        }
#ifdef _IOSTREAM_
		void ToScreen(){
			for (size_t i = 0; i < size; i++){
				std::cout << (elem[i] == true ? 1 : 0);
			}
		}
		void ToScreenRev(){
			for (int i = size-1; i >=0; i--){
				std::cout << (elem[i] == true ? 1 : 0);
			}
		}
#endif

        void Check(size_t i){
        /*устанавливает элемент в состояние true*/
                try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }
                elem[i] = true;
        }
        void UnCheck(size_t i){
                /*устанавливает элемент в состояние false*/
                try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }
                elem[i] = false;
        }
        void Set(size_t i,bool res){
                /*устанавливает элемент в некоторое состояние*/
                try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }
                elem[i] = res;
        }
        bool State(size_t i){
                /*Возвращает состояние элемента*/
                try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }
                return elem[i];
        }
        void CheckAll(){
                for(size_t i = 0;i<size;i++){
                        elem[i] = true;
                }
        }
        void UnCheckAll(){
                for(size_t i = 0;i<size;i++){
                        elem[i] = false;
                }
        }
        void SetAll(bool res){
                for(size_t i = 0;i<size;i++){
                        elem[i] = res;
                }
        }
        void Add(bool rez){
                /*добавляет один элемент в конец*/
                size++;
                elem = (bool*)realloc(elem,size);
                elem[size-1] = rez;
        }
        void Resize(size_t n){
                size = n;
                elem = (bool*)realloc(elem,size);
        }
        void Resize(size_t n,bool rez){
                size_t i = size;
                size = n;
                elem = (bool*)realloc(elem,size);
                for(;i<size;i++){
                        elem[i] = rez;
                }
        }
        template <typename T>
		T ToType(T id){
			/*преобразует объект в любой тип для которого определен оператор +=*/


			T res = 0;
			for (size_t i = 0; i < size && i < sizeof(T)* 8; i++){
				if (elem[i])
					res += pow(2., (double)i);
			}
			return res;
		}
        void operator=(const pBool& a){
                elem = (bool*)realloc(elem,a.size);
                size = a.size;
                for(size_t i = 0;i<size;i++){
                        elem[i] = a.elem[i];
                }
        }
        bool& operator[](size_t i){
                try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }
                return elem[i];
        }
        bool operator==(const pBool& a){
                if(size!=a.size)return false;
                for(size_t i=0;i<size;i++){
                        if(elem[i] != a.elem[i])return false;
                }
                return true;
        }
        bool operator!=(const pBool& a){
                if(size!=a.size)return true;
                for(size_t i=0;i<size,a.size;i++){
                        if(elem[i] == a.elem[i])return false;
                }
                return true;
        }
		void operator >> (size_t i){
			try{
				if (i < 0)throw 1;
				else if (i >= size - 1)throw 2;
			}
			catch (int x){
				if (x == 1){
					MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
					exit(0);
					//обработка ошибки
				}
				else if (x == 2){
					UnCheckAll();
					return;
				}
			}
			size_t j = 0;
			for (; j < i && i + j < size; j++)
				elem[j] = elem[i + j];
			for (; j <  size; j++)
				elem[j] = 0;
		}
		void operator << (size_t i){
			try{
				if (i < 0)throw 1;
				else if (i >= size - 1)throw 2;
			}
			catch (int x){
				if (x == 1){
					MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
					exit(0);
					//обработка ошибки
				}
				else if (x == 2){
					UnCheckAll();
					return;
				}
			}
			size_t j = 0;
			int k = size - 1;
			for (; j < i && k > 0; j++, k--)
				elem[k] = elem[k - i];
			for (; k >= 0; k--)
				elem[k] = 0;
		}
		void CyclicalRight(size_t i){
			try{
				if (i < 0)throw 1;
				else if (i%size == 0)throw 2;
			}
			catch (int x){
				if (x == 1){
					MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
					exit(0);
					//обработка ошибки
				}
				else if (x == 2){
					return;
				}
			}
			if (i > size){
				while (i > size)
					i -= size;
			}
			pBool tmp = *this;
			for (size_t j = 0; j < i; j++){
				for (size_t k = 1; k < size; k++)
					tmp[k-1] = elem[k];
				tmp[size - 1] = elem[0];
				*this = tmp;
			}
		}
		void CyclicalLeft(size_t i){
			try{
				if (i < 0)throw 1;
				else if (i%size == 0)throw 2;
			}
			catch (int x){
				if (x == 1){
					MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
					exit(0);
					//обработка ошибки
				}
				else if (x == 2){
					return;
				}
			}
			pBool tmp = *this;
			for (size_t j = 0; j < i; j++){
				for (size_t k = 1; k < size; k++)
					tmp[k] = elem[k-1];
				tmp[0] = elem[size-1];
				*this = tmp;
			}
		}

};
class Bits{
       size_t size;
       unsigned  long *elem;
public:
	friend bool operator <(const Bits& a, const Bits& b);
	friend bool operator==(const Bits& a, const Bits& b);
        Bits(){//пустой
                size = 0;
				elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
                *elem = 0;
        }
        Bits(size_t n){//размерностью n
                size = n;
				elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
				for (size_t i = 0; i < 1; i++){
					elem[i] = 0;
				}
        }
		~Bits()
		{
			free(elem);
		}
       template <class T>
#ifdef _VECTOR_
        Bits(std::vector<T> n){
                size = sizeof(T)*8;
				elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
                for (size_t i = 0; i < (size / 32) + 1; i++){
                        elem[i] = n[i];
                }
        }
#endif
		Bits(const Bits& a){//копирования
			size = a.size;
			elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
			for (size_t i = 0; i < (size / 32) + 1; i++){
				elem[i] = a.elem[i];
			}
		}
		/*Bits(Bits& a){//копирования
			size = a.size;
			elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
			for (size_t i = 0; i < (size / 32) + 1; i++){
				elem[i] = a.elem[i];
			}
		}*/
#ifdef _STRING_
		Bits(const std::string & a)
		{
			size = 0;
			elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
			*elem = 0;
			for (size_t i = 0; i < a.size(); i++)
				Add(Bits((char)a[i]));
		}
#endif
		Bits(char& a)
		{
			size = 8;
			elem = (unsigned long*)malloc(((size / 32) + 1) * sizeof(long));
			*elem = a;
			if (a < 0)
				UnCheck(8);
		}
#ifdef FUNC_H
		int Sub(int start, int end)
		{
			int res = 0;
			if (end - start > 32)
			{
				MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
				exit(0);
			}
			else
			{
				
				for (int i = start; i < end; i++)
				{
					if (State(i))
						res += power(2.0, i - start);
				}
			}
			return res;
		}
#endif
		void Add(bool rez){
			if (size % 32 == 0 && size != 0)elem = (unsigned long*)realloc(elem, sizeof(unsigned long)*((size / 32) + 1));
			size++;
			this->Set(size - 1, rez);
		}
		void Add(Bits& val)
		{
			for (size_t i = 0; i < val.size; i++)
			{
				Add(val.State(i));
			}
		}
#ifdef _IOSTREAM_
		void print(){
			for (size_t i = 0; i < size; i++)
			{
				std::cout << State(i);
			}
		}
		void print_invert(){
			for (int i = size - 1; i >= 0; i--)
			{
				std::cout << State(i);
			}
		}
#endif
		Bits rotate(){
			bool temp;
			bool temp2;
			for (size_t i = 0; i < size/2; i++){
				temp = State(i);
				temp2 = State(size - i - 1);
				Set(i, temp2);
				Set(size - i - 1, temp);
			}
			return *this;
		}
		void pop_back(){
			if (size % 32 == 0 && size != 0)elem = (unsigned long*)realloc(elem, sizeof(unsigned long)*((size / 32) + 1));
			if (size == 0)
			{
				MessageBox(NULL, L"No such file of directiry", NULL, MB_OK | MB_ICONERROR | MB_TOPMOST);
				exit(0);
			}
			this->Set(size - 1, false);
			size--;

		}
		unsigned long& val(size_t i){//возвращает значение как число
                //при выборе например числа 53
                //выбираются значения битов от 32 до 63
                return elem[i];
        }
        size_t Size() const
		{//размер
                return size;
        }
		unsigned long* Elem(){//возвращает значение как массив
                return elem;
        }
        void Clear(){//очистка
                size = 0;
				elem = (unsigned long*)realloc(elem, sizeof(unsigned long)*((size / 32) + 1));
				*elem = 0;
        }
        bool Empty(){//проверка на пустоту
                return size==0;
        }
        void Check(size_t i){
        /*устанавливает элемент в состояние true*/
          /*      try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }*/
                size_t index = 0;
                while(i >= 32){
                        i-=32;
                        index++;
                }
               // if(i == 31)elem[index] |= -1;
               // else{
                       unsigned long temp = 1<<i;
                        elem[index] |=temp;
              //  }
        //	if(!(temp & elem))elem += temp;
        }
        void Reverse(size_t i){
        /*устанавливает элемент в состояние true*/
           /*     try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }*/
                size_t index = 0;
                while(i >= 32){
                        i-=32;
                        index++;
                }
                //long temp = pow(2l,i);
                long temp = elem[index];
                temp ^= (1<<i);
                elem[index] =temp;
        //	if(!(temp & elem))elem += temp;
        }
        void UnCheck(size_t i){
                /*устанавливает элемент в состояние false*/
       /*         try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }*/
                size_t index = 0;
                while(i >= 32){
                        i-=32;
                        index++;
                }
                //long temp = pow(2,i);
                //if((temp & elem))elem -= temp;
             //   if(i == 31){
              //          elem[index] = abs(elem[index]);
              //  }
             //   else{
                        unsigned long temp = elem[index];
                //11111101111111011111.110111001101
                //11111101111111011111.110111001001

                        temp = temp& (~(1<<i));
                //long temp = FIRST_NULL<<i;
                        elem[index] =temp;
             //   }
        }
        void Set(int i,bool res){
                if(res){
                        (*this).Check(i);
                }
                else (*this).UnCheck(i);
        }
        bool State(size_t i){
                /*Возвращает состояние элемента*/
                try{
                        if(i<0 || i >size-1)throw 1;
                }
                catch(int){
                        MessageBox( NULL,L"index out of range!",L"Error!", MB_OK | MB_ICONERROR);
                        exit(0);
                        //обработка ошибки
                }
                size_t index = 0;
                while(i >= 32){
                        i-=32;
                        index++;
                }
                //long temp = pow(2l,i);
                unsigned long temp = 1<<i;
                //long a = elem[index];
                unsigned long temp2 = elem[index];
                temp2 &= temp;
                bool res = temp2<=0 ? false : true;
                return res;

                //return (pow(2,i) & elem);
        }
        void CheckAll(){
        //	for(size_t i = 0;i<size/32 + 1;i++){
        //		elem[i] = MAX_LONG;
        //	}
                for(size_t i = 0;i<size;i++){
                        this->Check(i);
                }
        }
        void UnCheckAll(){
        //	for(size_t i = 0;i<size/32 + 1;i++){
        //		elem[i] = 0;
        //	}
                for(size_t i = 0;i<size;i++){
                        this->UnCheck(i);
                }
        }
        void ReverseAll(){
                for(size_t i = 0;i<size/32 + 1;i++){
                        this->Reverse(i);
                }
        }
        void SetAll(bool res){
                if(res)CheckAll();
                else UnCheckAll();
        }
		void operator=(const Bits& a){
			size = a.size;
			for (size_t i = 0; i < size / 32 + 1; i++){
				elem[i] = a.elem[i];
			}
		}
        bool operator[](size_t i){
                return State(i);
        }
		bool operator==( Bits& a){
			if (size != a.Size()) return false;
			for (size_t i = 0; i < (size / 32) + 1; i++)
			{
				if (elem[i] != a.elem[i])return false;
			}
			return true;
        }
        bool operator!=( Bits& a){
			if (size == a.Size()) return false;
			for (size_t i = 0; i < (size / 32) + 1; i++)
			{
				if (elem[i] == a.elem[i])return false;
			}
			return true;
        }
        bool operator<(const Bits& b){
                if (*this == b)return false;
                for (size_t i = 0; i < size/32; i++){
                        if (elem[i] < b.elem[i])return true;
                        else if (elem[i] > b.elem[i])return false;
                }
        }
        bool operator <=(Bits b){
                if (*this == b)return true;
                for (size_t i = 0; i < size; i++){
                        if (this->State(i) < b.State(i))return true;
                        else if (this->State(i) < b.State(i))return false;
                }
        }
        bool operator >(Bits b){
                if (*this == b)return false;
                for (size_t i = 0; i > size; i++){
                        if (this->State(i) > b.State(i))return true;
                        else if (this->State(i) > b.State(i))return false;
                }
        }
        bool operator >=(Bits b){
                if (*this == b)return true;
                for (size_t i = 0; i > size; i++){
                        if (this->State(i) > b.State(i))return true;
                        else if (this->State(i) > b.State(i))return false;
                }
        }
        void operator~(){
                for(size_t i = 0;i<size/32 + 1;i++){
                        this->Reverse(i);
                }
        }
        void operator>>(size_t i){
                if(((size-1) / 32) == 0){
                        elem[0] = elem[0]>>i;
                }
                else if(((size-1) / 32) == 0){
                        size_t right_index = 0;
                        size_t left_index = right_index + 1;
                        bool buff;
                        for(size_t j = 0;j<i ; j++){
                                while(left_index < (((size-1)/32)+ 1)){
                                        buff = this->State(left_index);
                                        elem[right_index] = elem[right_index]>>1;
                                        this->Set(32*left_index - 1,buff);//перенос значения левого бита
                                        elem[left_index] = elem[left_index]>>1;
                                        right_index++;
                                        left_index++;
                                }
                        }
                }
        }
        void operator<<(size_t i){
                if(((size-1) / 32) == 0){
                        elem[0] = elem[0]<<i;
                }
                else if(((size-1) / 32) == 0){
                        size_t right_index = 0;
                        size_t left_index = right_index + 1;
                        bool buff;
                        for(size_t j = 0;j<i ; j++){
                                while(left_index < (((size-1)/32)+ 1)){
                                        buff = this->State(left_index);
                                        elem[right_index] = elem[right_index]<<1;
                                        this->Set(32*left_index - 1,buff);//перенос значения левого бита
                                        elem[left_index] = elem[left_index]<<1;
                                        right_index++;
                                        left_index++;
                                }
                        }
                }
        }
        void CyclicalRigth(size_t i){
                if(((size-1) / 32) == 0){
                        long tmp = *elem;
                        for(size_t j=0;j<i;j++){
                                __asm{
                                        ror tmp, 1;
                        }
                        elem[0] = tmp;
                        }
                }
                else if(((size-1) / 32) == 0){
                        size_t right_index = 0;
                        size_t left_index = right_index + 1;
                        bool buff,buff2;
                        for(size_t j = 0;j<i ; j++){
                                while(left_index < (((size-1)/32)+ 1)){
                                        buff = this->State(left_index);
                                        buff2 = this->State(0);
                                        elem[right_index] = elem[right_index]>>1;
                                        this->Set(32*left_index - 1,buff);//перенос значения левого бита
                                        elem[left_index] = elem[left_index]>>1;
                                        this->Set(size-1,buff2);//устанавливаем последний в значения первого
                                        right_index++;
                                        left_index++;
                                }
                        }
                }
        }
        void CyclicalLeft(size_t i){
                if(((size-1) / 32) == 0){
                        //elem[0] = elem[0]<<i;
                        long tmp = *elem;
                        for(size_t j=0;j<i;j++){
                                __asm{
                                        rol tmp, 1;
                                }
                        }
                        elem[0] = tmp;
                }
                else if(((size-1) / 32) == 0){
                        size_t right_index = 0;
                        size_t left_index = right_index + 1;
                        bool buff,buff2;
                        for(size_t j = 0;j<i ; j++){
                                while(left_index < (((size-1)/32)+ 1)){
                                        buff = this->State(left_index);
                                        buff2 = this->State(size-1);
                                        elem[right_index] = elem[right_index]<<1;
                                        this->Set(32*left_index - 1,buff);//перенос значения левого бита
                                        elem[left_index] = elem[left_index]<<1;
                                        this->Set(0,buff2);//устанавливаем первый в значения последнего
                                        right_index++;
                                        left_index++;
                                }
                        }
                }
        }
#ifdef FUNC_H
#undef min
        pBool TopBool(){//преобразование в pBool
                pBool res(size);
                int tmp_size = size;
                size_t i = 0;
                while(tmp_size >0){
                        size_t val = ::min(tmp_size,32);
                        for(size_t j = 0; j<val;j++){
                                res.Set(i,this->State(i));
                                i++;
                        }
                        tmp_size -=32;
                }
                return res;
        }
#endif
#ifdef _VECTOR_
        template <class T>
        std::vector<T> ToVector(){
                std::vector<T> temp;
                for (size_t i = 0; i < size/32 + 1; i++){
                        temp.push_back(_elem[i]);
                }
                return temp;
        }
#endif
        long ToInt(){
                return *elem;
        }
        long ToInt(int i){
                return elem[i];
        }
        void Ini(int x,int i=0){
                elem[i] = x;
        }
#ifdef _STRING_
		std::string to_string()
		{
			std::string res;
			for (size_t i = 0; i < size;)
			{
				char buff = 0;
				for (size_t j = 0; j < 8 && i < size; i++,j++)
				{
					if (State(i))buff += pow(2, j);
				}
				res.push_back(buff);
			}
			return res;
		}
#endif
};
bool operator <(const Bits& a, const Bits& b)
{
	if (a == b)return false;
	for (size_t i = 0; i < (a.size / 32)+1; i++){
		if (a.elem[i] < b.elem[i])return true;
		else if (a.elem[i] > b.elem[i])return false;
	}
}
bool operator==(const Bits& a,const Bits& b){
//	if (a.size != b.size)return false;
	return *(a.elem) == *(b.elem);
}
template <typename T>
pBool TopBool(T a){
        /*Возвращает объект , созданный на основе любого типа,для которого
        перегружен оператор/=

		иными словами переводит число в двоичную систему
		*/
        size_t n=0;
        T temp = a;
        for(;temp != 0;n++){
                temp/=2;
        }
        pBool c(n);
        temp = a;
		T temp2 = temp;
		bool res;
        for(size_t i = 0;i<n;i++){
                temp2 %= 2;
				res = (temp2 == 0 ? false : true);
                c.Set(i,res);
                temp2 = temp/=2;
        }
        return c;
}


class Bits8{
	size_t size;
	char *elem;
public:
	Bits8(){//пустой
		size = 0;
		elem = (char*)malloc((size / 8) + 1);
		elem = 0;
	}
	Bits8(size_t n){//размерностью n
		size = n;
		elem = (char*)malloc((size / 8) + 1);
		for (size_t i = 0; i < (size /8 ) + 1; i++){
			elem[i] = 0;
		}
	}
#ifdef _VECTOR_
	template <class T>
	Bits8(std::vector<T> n){
		size = sizeof(T)* 8;
		elem = (long*)malloc((size / 8) + 1);
		for (size_t i = 0; i < (size / 8) + 1; i++){
			elem[i] = n[i];
		}
	}
#endif
	Bits8(const Bits8& a){//копирования
		size = a.size;
		elem = (char*)malloc((size / 32) + 1);
		for (size_t i = 0; i < (size / 32) + 1; i++){
			elem[i] = 0;
		}

	}
	void Add(bool rez){
		if (size % 8 == 0)elem = (char*)realloc(elem, (size / 8) + 1);
		size++;
		this->Set(size - 1, rez);
	}
	char& val(size_t i){//возвращает значение как число
		//при выборе например числа 53
		//выбираются значения битов от 32 до 63
		return elem[i];
	}
	size_t Size(){//размер
		return size;
	}
	char* Elem(){//возвращает значение как массив
		return elem;
	}
	void Clear(){//очистка
		size = 0;
	}
	bool Empty(){//проверка на пустоту
		return size == 0;
	}
	void Check(size_t i){
		/*устанавливает элемент в состояние true*/
		try{
			if (i<0 || i >size - 1)throw 1;
		}
		catch (int){
			MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
			exit(0);
			//обработка ошибки
		}
		size_t index = 0;
		while (i >= 8){
			i -= 8;
			index++;
		}
		if (i == 7)elem[index] |= -1;
		else{
			long temp = 1 << i;
			elem[index] |= temp;
		}
		//	if(!(temp & elem))elem += temp;
	}
	void Reverse(size_t i){
		/*устанавливает элемент в состояние true*/
		try{
			if (i<0 || i >size - 1)throw 1;
		}
		catch (int){
			MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
			exit(0);
			//обработка ошибки
		}
		size_t index = 0;
		while (i >= 8){
			i -= 8;
			index++;
		}
		//long temp = pow(2l,i);
		long temp = elem[index];
		temp ^= (1 << i);
		elem[index] = temp;
		//	if(!(temp & elem))elem += temp;
	}
	void UnCheck(size_t i){
		/*устанавливает элемент в состояние false*/
		try{
			if (i<0 || i >size - 1)throw 1;
		}
		catch (int){
			MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
			exit(0);
			//обработка ошибки
		}
		size_t index = 0;
		while (i >= 8){
			i -= 8;
			index++;
		}
		//long temp = pow(2,i);
		//if((temp & elem))elem -= temp;
		if (i == 7){
			elem[index] = abs(elem[index]);
		}
		else{
			unsigned long temp = elem[index];
			//11111101111111011111.110111001101
			//11111101111111011111.110111001001

			temp = temp& (~(1 << i));
			//long temp = FIRST_NULL<<i;
			elem[index] = temp;
		}
	}
	void Set(int i, bool res){
		if (res){
			(*this).Check(i);
		}
		else (*this).UnCheck(i);
	}
	bool State(size_t i){
		/*Возвращает состояние элемента*/
		try{
			if (i<0 || i >size - 1)throw 1;
		}
		catch (int){
			MessageBox(NULL, L"index out of range!", L"Error!", MB_OK | MB_ICONERROR);
			exit(0);
			//обработка ошибки
		}
		size_t index = 0;
		while (i >= 8){
			i -= 8;
			index++;
		}
		//long temp = pow(2l,i);
		unsigned long temp = 1 << i;
		//long a = elem[index];
		unsigned long temp2 = elem[index];
		temp2 &= temp;
		bool res = temp2 <= 0 ? false : true;
		return res;

		//return (pow(2,i) & elem);
	}
	void CheckAll(){
		//	for(size_t i = 0;i<size/32 + 1;i++){
		//		elem[i] = MAX_LONG;
		//	}
		for (size_t i = 0; i<size; i++){
			this->Check(i);
		}
	}
	void UnCheckAll(){
		//	for(size_t i = 0;i<size/32 + 1;i++){
		//		elem[i] = 0;
		//	}
		for (size_t i = 0; i<size; i++){
			this->UnCheck(i);
		}
	}
	void ReverseAll(){
		for (size_t i = 0; i<size / 8 + 1; i++){
			this->Reverse(i);
		}
	}
	void SetAll(bool res){
		if (res)CheckAll();
		else UnCheckAll();
	}
	void operator=(const Bits8& a){
		size = a.size;
		for (size_t i = 0; i<size / 8 + 1; i++){
			elem[i] = a.elem[i];
		}
	}
	bool operator[](size_t i){
		return State(i);
	}
	bool operator==(const Bits8& a){
		return elem == a.elem;
	}
	bool operator!=(const Bits8& a){
		return  elem != a.elem;
	}
	bool operator <(Bits8 b){
		if (*this == b)return false;
		for (size_t i = 0; i < size; i++){
			if (this->State(i) < b.State(i))return true;
			else if (this->State(i) < b.State(i))return false;
		}
	}
	bool operator <=(Bits8 b){
		if (*this == b)return true;
		for (size_t i = 0; i < size; i++){
			if (this->State(i) < b.State(i))return true;
			else if (this->State(i) < b.State(i))return false;
		}
	}
	bool operator >(Bits8 b){
		if (*this == b)return false;
		for (size_t i = 0; i > size; i++){
			if (this->State(i) > b.State(i))return true;
			else if (this->State(i) > b.State(i))return false;
		}
	}
	bool operator >=(Bits8 b){
		if (*this == b)return true;
		for (size_t i = 0; i > size; i++){
			if (this->State(i) > b.State(i))return true;
			else if (this->State(i) > b.State(i))return false;
		}
	}
	void operator~(){
		for (size_t i = 0; i<size / 8 + 1; i++){
			this->Reverse(i);
		}
	}
	void operator>>(size_t i){
		if (((size - 1) / 8) == 0){
			elem[0] = elem[0] >> i;
		}
		else if (((size - 1) / 8) == 0){
			size_t right_index = 0;
			size_t left_index = right_index + 1;
			bool buff;
			for (size_t j = 0; j<i; j++){
				while (left_index < (((size - 1) / 8) + 1)){
					buff = this->State(left_index);
					elem[right_index] = elem[right_index] >> 1;
					this->Set(8 * left_index - 1, buff);//перенос значения левого бита
					elem[left_index] = elem[left_index] >> 1;
					right_index++;
					left_index++;
				}
			}
		}
	}
	void operator<<(size_t i){
		if (((size - 1) / 8) == 0){
			elem[0] = elem[0] << i;
		}
		else if (((size - 1) / 8) == 0){
			size_t right_index = 0;
			size_t left_index = right_index + 1;
			bool buff;
			for (size_t j = 0; j<i; j++){
				while (left_index < (((size - 1) / 8) + 1)){
					buff = this->State(left_index);
					elem[right_index] = elem[right_index] << 1;
					this->Set(8 * left_index - 1, buff);//перенос значения левого бита
					elem[left_index] = elem[left_index] << 1;
					right_index++;
					left_index++;
				}
			}
		}
	}
	void CyclicalRigth(size_t i){
		if (((size - 1) / 8) == 0){
			long tmp = *elem;
			for (size_t j = 0; j<i; j++){
				__asm{
					ror tmp, 1;
				}
				elem[0] = tmp;
			}
		}
		else if (((size - 1) / 8) == 0){
			size_t right_index = 0;
			size_t left_index = right_index + 1;
			bool buff, buff2;
			for (size_t j = 0; j<i; j++){
				while (left_index < (((size - 1) / 8) + 1)){
					buff = this->State(left_index);
					buff2 = this->State(0);
					elem[right_index] = elem[right_index] >> 1;
					this->Set(8 * left_index - 1, buff);//перенос значения левого бита
					elem[left_index] = elem[left_index] >> 1;
					this->Set(size - 1, buff2);//устанавливаем последний в значения первого
					right_index++;
					left_index++;
				}
			}
		}
	}
	void CyclicalLeft(size_t i){
		if (((size - 1) / 8) == 0){
			//elem[0] = elem[0]<<i;
			long tmp = *elem;
			for (size_t j = 0; j<i; j++){
				__asm{
					rol tmp, 1;
				}
			}
			elem[0] = tmp;
		}
		else if (((size - 1) / 8) == 0){
			size_t right_index = 0;
			size_t left_index = right_index + 1;
			bool buff, buff2;
			for (size_t j = 0; j<i; j++){
				while (left_index < (((size - 1) / 8) + 1)){
					buff = this->State(left_index);
					buff2 = this->State(size - 1);
					elem[right_index] = elem[right_index] << 1;
					this->Set(8 * left_index - 1, buff);//перенос значения левого бита
					elem[left_index] = elem[left_index] << 1;
					this->Set(0, buff2);//устанавливаем первый в значения последнего
					right_index++;
					left_index++;
				}
			}
		}
	}
#ifdef FUNC_H
	pBool TopBool(){//преобразование в pBool
		pBool res(size);
		int tmp_size = size;
		size_t i = 0;
		while (tmp_size >0){
			size_t val = ::min(tmp_size, 8);
			for (size_t j = 0; j<val; j++){
				res.Set(i, this->State(i));
				i++;
			}
			tmp_size -= 8;
		}
		return res;
	}
#endif
#ifdef _VECTOR_
	template <class T>
	std::vector<T> ToVector(){
		std::vector<T> temp;
		for (size_t i = 0; i < size / 8 + 1; i++){
			temp.push_back(_elem[i]);
		}
		return temp;
	}
#endif
	long ToInt(){
		return *elem;
	}
	long ToInt(int i){
		return elem[i];
	}
	void Ini(int x, int i = 0){
		elem[i] = x;
	}
};
#endif