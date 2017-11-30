#include "baseHeap.h"
#ifndef _FIBONACCI_HEAP
#define _FIBONACCI_HEAP
#ifndef NULL
#define NULL 0
#endif
//#include <iostream>
//#include <vector>
//#include <list>
//#include <algorithm>
//#include <string>

using namespace std;

//const int INF = 1e9;
//#undef ERROR;
//const int ERROR = -1;
//const int SIZE = 31;

//const int MAX_VERTEXES = 1e4 + 2;
//int dist[MAX_VERTEXES];

template <class T>
class FibNode 
{
	template <class T> friend class FibHeap;
	
	FibNode* parent;
	FibNode* child;
	FibNode* left;
	FibNode* right;
	int degree;
	bool mark;
	int _key;
	T _val;
public:
	FibNode(int Key,T val) : parent(NULL), child(NULL), left(this), right(this), degree(0), mark(false), _key(Key),_val(val) {}
	FibNode<T>* getParent()
	{
		return parent;
	}
	FibNode<T>* getChild()
	{
		return child;
	}
	FibNode<T> getLeft()
	{
		return left;
	}
	FibNode<T> getRight()
	{
		return right;
	}
	int getDegree()
	{
		return degree;
	}
	bool getMark()
	{
		return mark;
	}
	int key()
	{
		return _key;
	}
	int value()
	{
		return _val;
	}

private:
	void remove(bool delete_row) 
	{
		//������� ���������� �������� ����, � ���� ��������� � ��� �����

		//1) ���������� ���������� �� �������� � ������� ��
		if (child) 
		{
			child->remove(true);
			delete child;
		}

		//2) �������� ��������� �������� �������
		if (delete_row) 
		{
			FibNode<T>* cur = right;
			while (cur != this) {
				FibNode<T> * next = cur->right;
				cur->remove(false);
				delete cur;
				cur = next;
			}
		}
	}
};

template <class T>
class FibHeap
{
	template <class T> friend class FibNode;
	
	FibNode<T>* min;
	int roots_amount;
	compFunc less;
public:
	typedef void(*walkfunc)(FibNode<T>*);
	FibHeap(compFunc cmp = baseComp) :min(NULL), roots_amount(0), less(cmp){}
#ifdef _LIST_
	FibHeap(std::list<std::pair<int, T> > list, compFunc cmp = baseComp) : min(NULL), roots_amount(0), less(cmp)
	{
		for each(auto it in list)
			insert(it.first, it.second);
	}
	FibHeap(std::list<int> list, compFunc cmp = baseComp) : min(NULL), roots_amount(0), less(cmp)
	{
		for each(auto it in list)
			insert(it, 0);
	}
#endif
	~FibHeap() 
	{
		//��������� �� ����� ����������� ��������
		if (!min) return;
		min->remove(true);
		delete min;
	}

	void walk(walkfunc action)
	{
		if (!min) return;
		walkPart(min, true, action);
		action(min);
	}
	

	size_t getSize()
	{
		return roots_amount;
	}
	compFunc getFunc()
	{
		return less;
	}
	bool isEmpty()
	{
		return roots_amount == 0;
	}
	FibNode<T>* insert(int key,T _val)
	{
		//������� ����� ���� � �������� ��� � ����
		FibNode<T>* Node = new FibNode<T>(key,_val);
		add(Node, min);
		return Node;
	}
	int priority() 
	{
		return min->key;
	}
	//������ ������� ��� ���� � ����. � fb ����� NULL
	void merge(FibHeap &fb) 
	{
		//1) ������� ������������ �������� ���������
		union_root(fb.min, fb.roots_amount);
		//2) ���������� ����� ������
		if (!min || (fb.min && less(fb.min->key(), min->key())))
			min = fb.min;
		fb.clear();
	}
	//������ ��������� ���������� ������� �� ����
	//�������� ����������� �� ������������! (����������� ��������� delete)
	FibNode<T>* extract() 
	{
		//1) �������� ������������ ������

		FibNode<T>* res = min;

		//2) �������� ��������� ������������ �������, ��� �����:

		//2.1) ������������� ���� ������� ������������ � ������, ����� �������� ������
		//2.2) ���� ���� �� ����� �����������
		if (res) 
		{
			childs_in_root(res);
			remove_root(res);
			if (res->right == res)
				min = 0;
			else 
			{
				min = min->right;
				consolidate();
			}
		}
		else return NULL;
		return res;
	}
	int extractKey()
	{
		FibNode<T>* res = min;
		if (res)
		{
			childs_in_root(res);
			remove_root(res);
			if (res->right == res)
				min = 0;
			else {
				min = min->right;
				consolidate();
			}
		}
		else return 0;
		int ans = res->key;
		delete res;
		return ans;
	}
	T extractValue()
	{
		FibNode<T>* res = min;
		if (res)
		{
			childs_in_root(res);
			remove_root(res);
			if (res->right == res)
				min = 0;
			else {
				min = min->right;
				consolidate();
			}
		}
		else return T();
		T ans = res->value();
		delete res;
		return ans;
	}
	void editKey(FibNode<T>* Node,int new_k,T new_t) 
	{
		//1) ������������� ����� �������� ����� � ����
		Node->_key = new_k;
		Node->_val = new_t;

		//2)���� ����������� ��������� ��������, � �� ����� ������������ ����
		//���������� ��� �������� � ����� ��������
		//����� ���� ���� ��� ��������� �� ���� �� �� ����� ������������ ���������
		FibNode<T>* par = Node->parent;
		if (par && less(Node->key(), par->key())) 
		{
			remove_child(Node);
			cascading_cut(par);
		}
		else if (less(Node->key(), min->key()))
			min = Node;
	}
private:
	void walkPart(FibNode<T>* node,bool flag,walkfunc action)
	{
		{
			

			//1) ���������� ���������� �� ��������
			if (node->child)
			{
				walkPart(node->child, true,action);
				action(node->child);
			}

			//2) �������� ��������� �������� �������
			if (flag)
			{
				FibNode<T>* cur = node->right;
				while (cur != node) {
					FibNode<T> * next = cur->right;
					walkPart(cur, false, action);
					action(cur);
					cur = next;
				}
			}
		}
	}
	void clear()
	{
		min = NULL;
		roots_amount = 0;
	}
	//������� ������� �� ���� ����(���������������� ����) � ��������� ������
	void remove_child(FibNode<T> *Node) 
	{
		

		//1) ��������� ���������� �������� �����
		//���� ��������� �������� �� ��������� �����, ���� � NULL
		Node->parent->degree--;
		Node->parent->child = (Node->right == Node ? NULL : Node->right);
		kill_LR_links(Node);
		add(Node, min);
		Node->mark = false;
	}

	//������� ������� ������� cur �� ���������� ������ ������� 
	//� ���� ���� P(cur) �������� �� ���� ������� cur, �� ������������� 
	//������ child �������� P �� ������� ����� cur. ��������� ������� 
	//���������� ������� � P � ������ ����� mark ������ true. 
	//��� �������, ��� � �������� P ��� ������ ���. 
	//������ ����� ��������� �� ��, ��� ���� ��������� ����� ��������, 
	//��� � ������ ���� ����� ������� ����� ������ ����, �� ��� ����� 
	//��������� � ��������� ������ ������. 
	void cascading_cut(FibNode<T> *cur) 
	{
		FibNode<T> *par = cur->parent;
		if (par && par->degree)
		{
			if (!par->mark)
				par->mark = true;
			else 
			{
				remove_child(cur);
				cascading_cut(par);
			}
		}
	}

	void union_root(FibNode<T>* Node, int nodes_amount) 
	{
		if (Node == NULL) return;
		if (min == NULL) 
		{
			min = Node;
			roots_amount = nodes_amount;
		}
		else 
		{
			FibNode<T> *L = Node->left;
			FibNode<T> *R = min->right;
			min->right = Node;
			Node->left = min;
			L->right = R;
			R->left = L;
			roots_amount += nodes_amount;
		}
	}
	//������� ��������� �������� �������� �� Node ��� �������
	// 3 - 4 - 5 -> 3 - 5
	void kill_LR_links(FibNode<T>* Node) 
	{
		if (Node->left != Node) 
		{
			Node->right->left = Node->left;
			Node->left->right = Node->right;
		}
	}
	void add(FibNode<T>* Node, FibNode<T>*& bro, FibNode<T>* par = NULL)
	{
		if (bro == NULL) 
		{
			bro = Node;
			Node->left = Node;
			Node->right = Node;
		}
		else 
		{
			Node->right = bro->right;
			Node->right->left = Node;
			Node->left = bro;
			bro->right = Node;
		}
		if (less(Node->key(), bro->key()))
			bro = Node;

		if (bro == min) 
		{
			roots_amount++;
			Node->parent = NULL;
		}
		if (par)
		{
			par->degree++;
			Node->parent = par;
		}
	}
	//������� ��������� �������� �������� �� Node ��� ������� ������������ �����
	void remove_root(FibNode<T>* Node) 
	{
		kill_LR_links(Node);
		roots_amount--;
	}
	//������ �������� ���� �� ��������� ������ � ��������� ��� ������
	//������ �� �������� �������� ��� ���� �����������
	void fib_heap_link(FibNode<T>* ch, FibNode<T>* par) 
	{
		remove_root(ch);
		add(ch, par->child, par);
		ch->mark = false;
	}
	//������� ����������� ����
	void consolidate()
	{

		//�� ������ ���� ����� ������������� ����� ������������ �������
		//�������� ������ ������� ������.���� �� ����� - �� ����� 
		//���������� ��� ������ ����������� ������� ��� ������������
		//� ���� � ��� ����������� �� ��� ��� ���� � ������ ��������
		//������� ����������� �������.

		FibNode<T>* A[31];
		memset(A, 0, sizeof(A));
		FibNode<T>* x = min;
		int init_roots = roots_amount;
		int max_degree = 0;
		for (int i = 0; i<init_roots; ++i) 
		{
			int d = x->degree;
			FibNode<T>* next = x->right;
			while (A[d]) 
			{
				FibNode<T>* y = A[d];
				if (less(y->key(), x->key()))
					swap(x, y);
				fib_heap_link(y, x);
				A[d++] = NULL;
			}
			A[d] = x;
			max_degree = max(max_degree, d);
			x = next;
		}
		min = NULL;
		roots_amount = 0;
		for (int i = 0; i <= max_degree; ++i)
		{
			if (A[i]) 
			{
				add(A[i], min);
			}
		}
	}
	//������� ������������� ���� ������� ������� ���� � ������
	void childs_in_root(FibNode<T> *Node) 
	{
		while (Node->child)
			remove_child(Node->child);
	}
};
#endif