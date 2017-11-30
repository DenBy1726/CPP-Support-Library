#include<stdlib.h>
#include<windows.h>
template <typename T>
#undef min(a,b)
T min(T a, T b);
class pBool;
#define MAX_LONG LONG_MAX
#define FIRST_NULL MAX_LONG - 1
long pow(long a,int b);
int pow(int a,int b);
template <typename T>
void ToBits(T a,pBool& b);

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
        }
        pBool(const pBool& a){
                /*Конструктор копирования*/
                size = a.size;
                elem = (bool*)malloc(size);
                for(size_t i = 0;i<size;i++){
                        elem[i] = a.elem[i];
                }
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
        size_t Size(){
                return size;
        }
        void Check(int i){
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
        void UnCheck(int i){
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
        void Set(int i,bool res){
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
        bool State(int i){
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
                int i = size;
                size = n;
                elem = (bool*)realloc(elem,size);
                for(;i<size;i++){
                        elem[i] = rez;
                }
        }
        template <typename T>
        T ToType(){
                /*преобразует объект в любой тип для которого определен оператор +=*/
                T res=0;
                for(size_t i=0;i<size && i<sizeof(T)*8 ;i++){
                        if(elem[i])
                                res+=pow(2l,i);
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
        bool operator[](size_t i){
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
};
class Bits{
        size_t size;
        long *elem;
public:
        Bits(){//пустой
                size = 0;
                elem = (long*)malloc((size/32) +1);
                elem = 0;
        }
        Bits(size_t n){//размерностью n
                size = n;
                elem = (long*)malloc((size/32) +1);
                for(size_t i = 0;i < (size/32) +1 ;i++){
                        elem[i] = 0;
                }
        }
        template <class T>
        Bits(std::vector<T> n){
                size = sizeof(T)*8;
                elem = (long*)malloc((size / 32) + 1);
                for (size_t i = 0; i < (size / 32) + 1; i++){
                        elem[i] = n[i];
                }
        }
        Bits(const Bits& a){//копирования
                size = a.size;
                elem = (long*)malloc((size/32) +1);
                for(size_t i = 0;i < (size/32) +1 ;i++){
                        elem[i] = 0;
                }

        }
        long& val(size_t i){//возвращает значение как число
                //при выборе например числа 53
                //выбираются значения битов от 32 до 63
                return elem[i];
        }
        size_t Size(){//размер
                return size;
        }
        long* Elem(){//возвращает значение как массив
                return elem;
        }
        void Clear(){//очистка
                size = 0;
        }
        bool Empty(){//проверка на пустоту
                return size==0;
        }
        void Check(int i){
        /*устанавливает элемент в состояние true*/
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
                if(i == 31)elem[index] |= -1;
                else{
                        long temp = 1<<i;
                        elem[index] |=temp;
                }
        //	if(!(temp & elem))elem += temp;
        }
        void Reverse(int i){
        /*устанавливает элемент в состояние true*/
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
                long temp = elem[index];
                temp ^= (1<<i);
                elem[index] =temp;
        //	if(!(temp & elem))elem += temp;
        }
        void UnCheck(int i){
                /*устанавливает элемент в состояние false*/
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
                //long temp = pow(2,i);
                //if((temp & elem))elem -= temp;
                if(i == 31){
                        elem[index] = abs(elem[index]);
                }
                else{
                        unsigned long temp = elem[index];
                //11111101111111011111.110111001101
                //11111101111111011111.110111001001

                        temp = temp& (~(1<<i));
                //long temp = FIRST_NULL<<i;
                        elem[index] =temp;
                }
        }
        void Set(int i,bool res){
                if(res){
                        (*this).Check(i);
                }
                else (*this).UnCheck(i);
        }
        bool& State(int i){
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
                for(size_t i = 0;i<size/32 + 1;i++){
                        elem[i] = a.elem[i];
                }
        }
        bool operator[](size_t i){
                return State(i);
        }
        bool operator==(const Bits& a){
                return elem == a.elem;
        }
        bool operator!=(const Bits& a){
                return  elem != a.elem;
        }
        bool operator <(Bits b){
                if (*this == b)return false;
                for (size_t i = 0; i < size; i++){
                        if (this->State(i) < b.State(i))return true;
                        else if (this->State(i) < b.State(i))return false;
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
        void operator>>(int i){
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
        void operator<<(int i){
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
        void CyclicalRigth(int i){
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
        void CyclicalLeft(int i){
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
        pBool TopBool(){//преобразование в pBool
                pBool res(size);
                int tmp_size = size;
                size_t i = 0;
                while(tmp_size >0){
                        size_t val = min(tmp_size,32);
                        for(size_t j = 0; j<val;j++){
                                res.Set(i,this->State(i));
                                i++;
                        }
                        tmp_size -=32;
                }
                return res;
        }
        template <class T>
        std::vector<T> ToVector(){
                std::vector<T> temp;
                for (size_t i = 0; i < size/32 + 1; i++){
                        temp.push_back(_elem[i]);
                }
                return temp;
        }
        long ToInt(){
                return *elem;
        }
        long ToInt(int i){
                return elem[i];
        }
        void Ini(int x,int i=0){
                elem[i] = x;
        }
};
template <typename T>
T min(T a, T b){
        return a > b ? b : a;
}
template <typename T>
pBool ToBits(T a){
        /*Возвращает объект , созданный на основе любого типа,для которого
        перегружен оператор/=*/
        size_t n=0;
        T temp = a;
        for(;temp;n++){
                temp/=2;
        }
        pBool c(n);
        temp = a;
        for(size_t i = 0,temp2=temp;i<n;i++){
                temp2 %= 2;
                c.Set(i,temp2);
                temp2 = temp/=2;
        }
        return c;
}
long pow(long a,int b){
        if(b == 0)return 1;
        long tmp=a;
        for(size_t i=1;i<b;i++){
                a*=tmp;
        }
        return a;
}
int pow(int a,int b){
        if(b == 0)return 1;
        int tmp=a;
        for(size_t i=1;i<b;i++){
                a*=tmp;
        }
        return a;
}
