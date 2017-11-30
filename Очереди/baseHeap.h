namespace Heap
{

#ifndef _BASE_HEAP
#define _BASE_HEAP
#define Ptr(a) (unsigned int)a
	//уже освобождена€ пам€ть
#define DELETED 0xfeeefeee
	//пам€ть уже освобождена?
#define IsBadPtr(a) Ptr(a) == DELETED
	//пам€ь ещЄ не освобождена?
#define IsGoodPtr(a) Ptr(a) != DELETED
	//Ёлемент ещЄ не удален?
#define IsNotDeleted(a) Ptr(a->left) != DELETED && Ptr(a->right) != DELETED && Ptr(a->partner) !=DELETED && Ptr(a->parent)!=DELETED && Ptr(a->child)!= DELETED
	//Ёлемент уже удален?
#define IsBadPtrFull(a) Ptr(a->left) != DELETED || Ptr(a->right) != DELETED || Ptr(a->partner) !=DELETED || Ptr(a->parent)!=DELETED || Ptr(a->child)!= DELETED
	//Ёлемент инициализирован?
#define IsNotNull(a) Ptr(a->left) != NULL && Ptr(a->right) != NULL && Ptr(a->partner) !=NULL && Ptr(a->parent)!=NULL && Ptr(a->child)!= NULL

	//‘ункци€ сравнени€ целочисленных ключей
	typedef bool(*compFunc)(int, int);



	//‘ункци€ определени€ минимума
	template <class T>
	T hmin(const T& a, const T& b){
		return a > b ? b : a;
	}

	bool KeyMin(int a,int b)
	{
		return a < b ? true : false;
	}

	enum heapId
	{
		binary, fib, heap23
	};

#endif
}