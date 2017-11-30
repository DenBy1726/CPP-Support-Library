#include<stdlib.h>
#ifndef MY_STACK
#define MY_STACK
template <class T>
class Stack{
	#define MAX_SIZE 1024
protected:
	T* _top;
	size_t _size;
public:
	Stack(){
		_size = 0;
		_top = (T*) malloc (1*sizeof(T));
		}
	Stack(size_t n){
		_size = n;
		_top = (T*)malloc (n*sizeof(T));
		}
	Stack(T* _elem,size_t n){
		_size = n;
		_top = (*T)malloc (n*sizeof(T));
		for(size_t i = 0;i<n;i++){
			_top[i] = _elem[i];
			}
		}
	Stack(const Stack& _new){
		_size = _new.size;
		_top = (T*)malloc (_size*sizeof(T));
		for(size_t i = 0;i<n;i++){
			_top[i] = _new._top[i];
			}
		}
	bool empty(){
		return _size == 0;
		}
	size_t size(){
		return _size;
		}
	T& top(){
		return _top[size-1];
		}
	void push(const T& _new){
		try{
			if(_size == MAX_SIZE)throw 1;
			}
		catch(int){
			//Обработка ошибки
			}
		_size++;
		_top =(T*)realloc(_top,_size*sizeof(T));
		_top[_size-1] = _new;
		}
	void pop(){
		try{
			if(size == 0)throw 1;
			}
		catch(int){
			//Обработка ошибки
			}

		_size--;
		_top =(T*)realloc(_top,_size*sizeof(T));
		}
	void operator>>(T & _cont){
		try{
			if(_size == 0)throw 1;
			}
		catch(int ){
			//Обработка ошибки
			}
		_cont = _top[_size-1];
		_size--;
		_top =(T*)realloc(_top,_size*sizeof(T));
		}
	void operator<<(const T& _new){
		try{
			if(_size == MAX_SIZE)throw 1;
			}
		catch(int){
			//Обработка ошибки
			}
		_size++;
		_top =(T*)realloc(_top,_size*sizeof(T));
		_top[_size-1] = _new;
		}
/*#ifdef _VECTOR_
	Stack(vector<T> _elem){
		_size = _elem.size();
		_top = (T*)malloc (_size*sizeof(T));
		for(size_t i = 0;i<_size;i++){
			_top[i] = _elem[i];
			}
		}
#endif*/
	};
#endif