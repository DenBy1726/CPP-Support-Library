namespace Heap
{

#ifndef _BASE_HEAP
#define _BASE_HEAP
#define Ptr(a) (unsigned int)a
	//��� ������������ ������
#define DELETED 0xfeeefeee
	//������ ��� �����������?
#define IsBadPtr(a) Ptr(a) == DELETED
	//����� ��� �� �����������?
#define IsGoodPtr(a) Ptr(a) != DELETED
	//������� ��� �� ������?
#define IsNotDeleted(a) Ptr(a->left) != DELETED && Ptr(a->right) != DELETED && Ptr(a->partner) !=DELETED && Ptr(a->parent)!=DELETED && Ptr(a->child)!= DELETED
	//������� ��� ������?
#define IsBadPtrFull(a) Ptr(a->left) != DELETED || Ptr(a->right) != DELETED || Ptr(a->partner) !=DELETED || Ptr(a->parent)!=DELETED || Ptr(a->child)!= DELETED
	//������� ���������������?
#define IsNotNull(a) Ptr(a->left) != NULL && Ptr(a->right) != NULL && Ptr(a->partner) !=NULL && Ptr(a->parent)!=NULL && Ptr(a->child)!= NULL

	//������� ��������� ������������� ������
	typedef bool(*compFunc)(int, int);



	//������� ����������� ��������
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