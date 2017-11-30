#pragma once
#ifndef NODE_23AR
#include <list>
#include "baseHeap.h"
#define NODE_23AR
//******************************************************************
//*****************************�����-�����������********************
//******************************************************************

typedef bool(*compFuncAr)(std::list<int>, std::list<int>);
//���������� ����� ������ ������ ������, � ������� ��������� ������


//***********************************************************************
//************************���� ����(HeapNode) : ��������*****************
//***********************************************************************

//��������� ������� ���� �������� � ����.
//�������� ��������� ��������� � ������
//���������� �� ��������� � Heap � PriorityQueue
template <class T>class HeapNodeAr
{
protected:
	template<class T> friend class HeapArray;
	template<class T> friend class PriorityQueueArray;
	template <class T> friend void mergeNode(HeapNodeAr<T>*& a, HeapNodeAr<T>*& b, compFuncAr);
	//��������� ���������
	HeapNodeAr* parent;
	HeapNodeAr* partner;
	HeapNodeAr* child;
	HeapNodeAr* left;
	HeapNodeAr* right;
	//��������� ������
	int degree;
	bool sl;
	//�������� ������
	std::list<int> _key;
	T _value;
public:
	//����������� ������� ���� � �������������� ���
	HeapNodeAr(std::list<int> k, T v) :left(NULL), child(NULL), right(NULL), _key(k), _value(v), degree(0),sl(false),parent(NULL),partner(NULL){};
	//����������� ������� ����,�������������� ������ ��������( ���� ����� ����)
	HeapNodeAr(T v) :left(NULL), child(NULL), right(NULL), _key(std::list<int>()), _value(v), degree(0), sl(false), parent(NULL), partner(NULL){};
	//����������� �� ��������� ������� ������ ����
	HeapNodeAr(){};
	~HeapNodeAr(){}
	//���������� ��������� ����(��� ����). �������� ��������� ������ key()
	std::list<int> priority()
	{
		return _key;
	}
	//���������� ��������� ����(��� ����)
	std::list<int> key()
	{
		return _key;
	}
	int key(int i)
	{
		return _key[i];
	}
	//���������� ��������,�������� � ����
	T value()
	{
		return _value;
	}
	//���������� ������� ������(���������� ��� ������)
	int order()
	{
		return degree;
	}
	//���������� ��������� �� ������ ������
	HeapNodeAr* getLeft()
	{
		return left;
	}
	//���������� ��������� �� ����
	HeapNodeAr* getChild()
	{
		return child;
	}
	//���������� ��������� �� ������� ������
	HeapNodeAr* getRight()
	{
		return right;
	}
	//���������� ��������� �� ��������
	HeapNodeAr* getPartner()
	{
		return partner;
	}
	//���������� ��������� �� ��������
	HeapNodeAr* getParent()
	{
		return parent;
	}
	//���������� ������������ ����
	bool type()
	{
		return sl;
	}
	//��������� ���� � �������� ����
	void addChild(HeapNodeAr<T>* new_child);
	//������ ������� ����� � �������� �����
	void swap(HeapNodeAr<T>* root2);
	//�������� ���������
	bool operator<(HeapNodeAr<T>* right)
	{
		return this->key() < right->key();
	}
	
};

//***********************************************************************
//************************���� ����(HeapNode) : ����������***************
//***********************************************************************

template <class T>
void HeapNodeAr<T>::swap(HeapNodeAr<T>* root2)
{
	//���������� �������� ������� ����� � ��������
	std::list<int> tempkey() = this->key();
	T temp_val = this->value();
	this->key() = root2->key();
	root2->key() = tempkey();
	this->value() = root2->value();
	root2->value() = temp_val;
}
template <class T>
void HeapNodeAr<T>::addChild(HeapNodeAr<T>* new_child)
{
	/*���� � ��� ����� ��������� ������� new_child � ���� ��� ����.
	//��� ��� ���� �� ����� ������(��� �� ���� ������� � �����).
	//���������� ����� ������������ ��� ����� "����"
	//
	[1]
	/\
	||   ����� � �����
	\/
	[2] <->[4]
	*/

	HeapNodeAr<T>* new_left, *new_right;
	new_left = child;
	if (new_left)
	{
		//��������� ������ ���� �� ������ ��������� ������
		new_right = new_left->right;
		new_child->left = new_left;
		new_child->right = new_right;
		//c�������� ������� ���� � �����
		new_right->left = new_child;
		new_left->right = new_child;	
	}
	else
	{
		new_child->left = new_child->right = new_child;
	}
	//��������� ������ ���� � ���������
	child = new_child;
	new_child->parent = this;
	
}
template <class T>
void mergeNode(HeapNodeAr<T>*& a, HeapNodeAr<T>*& b, compFuncAr compare)
{
	/*
	���������� ������ a � ������� b
	��������� ����� ���� �������� � ����� (�� ���������)
	���� � a  �� ������ �� �������� �������(�������� ������������ ����� ����������)
	���� � b �� ������ �������� ������� � ��� ����� ��������� �����(��� ��� ������ ,���� ��������� ����� ���� ������)
	*/

	HeapNodeAr<T>* tree_general, *tree_added, *next_general, *next_added;
	//���������� ������� ����(�������� ������������)
	//� ����������� (�������� ������������)
	if (compare(a->priority(), b->priority()))
	{
		tree_general = a;
		tree_added = b;
	}
	else
	{
		tree_general = b;
		tree_added = a;
	}
	//����� ���������� ���������
	next_general = tree_general->partner;
	next_added = tree_added->partner;
	//������������� ������������ �������� ( ������� ��� ����������)
	//���������( �� ���� ���������� ��� ������
	//����� ���������� ��� ���� ��������������:
	// 1) ��� �������� + ��� ��������
	// 2) ��� �������� + � ���������
	// 3) � ��������� + � ���������
	if (next_general == 0)
	{
		if (next_added == 0)
		{
			tree_general->partner = tree_added;
			tree_added->partner = tree_general;
			tree_added->sl = true;
			a = tree_general;
			b = NULL;
		}
		else
		{
			tree_general->addChild(tree_added);
			tree_general->degree++;
			b = tree_general;
			a = NULL;
		}
	}
	else
	{
		if (next_added == 0)
		{
			tree_general->partner = NULL;
			tree_added->partner = next_general;
			next_general->partner = tree_added;
			if (compare(next_general->priority(),tree_added->priority()))
			{
				next_general->sl = false;
				tree_added->sl = true;
				tree_general->addChild(next_general);
			}
			else
			{
				tree_general->addChild(tree_added);
			}
			tree_general->degree++;
			b = tree_general;
			a = NULL;
		}
		else
		{
			tree_general->partner = NULL;
			next_general->partner = NULL;
			next_general->sl = false;
			next_general->left = next_general->right = next_general;
			next_general->parent = NULL;

			tree_general->addChild(tree_added);
			++(tree_general->degree);

			a = next_general;
			b = tree_general;
		}
	}
}


//*************************************************************
//****************************���� ( Heap ) : ��������*********
//*************************************************************

/*

	����� ��� ������ � �����. 
	�������� ������ ����� ( �� ���� ��������), � ��������� ����������
	���������� � HeapNode

*/
template <class T> class HeapArray
{
protected:
	template<class T> friend class HeapNodeAr;
	template<class T> friend void mergeNode(HeapNodeAr<T>*& a, HeapNodeAr<T>*& b, compFuncAr);
	//������ �����

	HeapNodeAr<T>** trees;

	//��������� ����������

	size_t _size;
	int _max;
	compFuncAr compare;
	typedef void(*walkFuncAr)(HeapNodeAr<T>*);
public:
	//������ ��������� ��� �� ������ ����
	static bool isNotDeleted(HeapNodeAr<T>* it);
	//����������� ������������� ������� ��������� � ������������ ���������� �������� � ����
	HeapArray(compFuncAr call = basicAComp, int max = 16);

	~HeapArray()
	{
		walk(destructHeap);
	}

	//���������� ��������� �� ������ ���������
	compFuncAr getFunc() const
	{
		return compare;
	}

	//�������� �� �������
	bool isEmpty() const
	{
		return (_size == 0);
	}

	//���������� ������������ ������� ����
	int getMaxDegree() const
	{
		return _max;
	}

	//����� �� ���� � ���������� ������� action ��� ������ �������
	void walk(walkFuncAr action);

	//���������� ���������� ��������� � ����
	size_t size() const
	{
		return _size;
	}

	//���������� �������������������� ���������� ��������� � ����
	size_t maxSize() const
	{
		return (pow(3, _max + 1) - 1);
	}
	//���������� ������ ������� x
	HeapNodeAr<T>* getTree(int x) const ;

	//������� ���� � �������� ��� � ����
	HeapNodeAr<T>* insert(std::list<int> k, T v);

	//�������� ���� � ����
	void insert(HeapNodeAr<T>* list);

	//���������� ������������ �������
	HeapNodeAr<T>* priority();

	//������� �� ���� ������������ ������� � ���������� ���������� �� ���� �������
	//��������: � ������ ������ ���� �� ��������� �������������,
	//����� ������������ �� ���� ��������������
	HeapNodeAr<T>* extract();

	//������� �� ���� ������������ ������� � ���������� �������� ����� ����������� ��������
	std::list<int> extractKey();

	//������� �� ���� ������������ ������� � ���������� ��������,�������� � ���������� ��������
	T extractValue();

	//������� ������� ���� � ����� sum(� ���������� � sum ����� ������ ����)
	void merge(HeapArray& sum);

	//�������� �������� �����
	void editKey(HeapNodeAr<T>* node, std::list<int> newkey(), T new_val);

protected:
	//��������������� ������� ��� ������ �� ����
	//��������� ����� �� �������
	void walkNeighbor(HeapNodeAr<T>*& it, walkFuncAr action);

	//������� ������� ������ �� ����
	void walkBase(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, walkFuncAr action);
};

//*************************************************************
//****************************���� ( Heap ) : ����������*******
//*************************************************************


template <class T>
void HeapArray<T>::editKey(HeapNodeAr<T>* node, std::list<int> newkey(), T new_val)
{
	node->key() = newkey();
	node->value() = new_val;
	while (1)
	{
		//���� ���� ������ ����� � �� ��������� ���������,�� ��� ������� ���� ������ ����� ������ �� �������(����� � �����)
		//�������� � ������ �������
		if (node->right)
		{
			if (compare(node->key(), node->right->key()))
			{
				if (node->right->degree > node->degree)
				{
					node->swap(node->right);
					node = node->right;
					continue;
				}
			}
		}
		//���� ���� ����� ,�� ���� ���������� ���� �� �������� ������ ������������ �� ����������
		//����� ���� ��������� ���� �� �������� ������ ���������� �� ������������
		if (node->partner)
		{
			if (!compare(node->key(), node->partner->key()))
			{
				if (node->partner->sl)
				{
					node->swap(node->partner);
					node = node->partner;
					continue;
				}
			}
			else
			{
				if (!(node->partner->sl))
				{
					node->swap(node->partner);
					node = node->partner;
					continue;
				}
			}
		}
		//�� �������� ���� ������ ��� ���������� ����������
		if (node->parent)
		{
			if (compare(node->key(), node->parent->key()))
			{
				node->swap(node->parent);
				node = node->parent;
				continue;
			}
		}
		if (node->child)
		{
			if (!compare(node->key(), node->child->key()))
			{
				node->swap(node->child);
				node = node->child;
				continue;
			}
		}
		break;
	}
}
template <class T>
void HeapArray<T>::merge(HeapArray& sum)
{
	// ���� ������� ��� ������, end ����� ������������ �� ��������.
	HeapNodeAr<T>* buff;
	int end = hmin(_max, sum._max);
	for (int i = 0; i <= end; i++)
	{
		if ((buff = sum.getTree(i)) != NULL)
		{
			buff->left = NULL;
			buff->right = NULL;
			this->insert(buff);
			sum.trees[i] = NULL;
		}
	}
	_size += sum.size();
	sum._size = 0;
}
template <class T>
HeapNodeAr<T>* HeapArray<T>::extract()
{
	if (_size == 0)
		return NULL;
	HeapNodeAr<T>* pr = priority();
	HeapNodeAr<T>* pt = pr->partner;
	int type = pr->degree;
	if (pt)
	{
		trees[type] = pt;
		pr->partner = NULL;
		pt->partner = NULL;
		pt->sl = false;
		pt->left = pt->right = pt;
	}
	else
	{
		trees[type] = NULL;
	}
	HeapNodeAr<T>* ch = pr->child;
	HeapNodeAr<T>* node;
	if (ch)
	{
		node = ch->right;
		node->left = ch->right = NULL;
		insert(node);
	}
	_size--;
	return pr;
}
template <class T>
T HeapArray<T>::extractValue()
{
	if (_size == 0)
		return NULL;
	T val;
	HeapNodeAr<T>* v = extract();
	val = v->value();
	delete v;
	return val;
}
template <class T>
std::list<int> HeapArray<T>::extractKey()
{
	if (_size == 0)
		return NULL;
	std::list<int> key;
	HeapNodeAr<T>* k = extract();
	key = k->key();
	delete k;
	return key;
}
template <class T>
HeapNodeAr<T>* HeapArray<T>::priority()
{
	if (_size == 0)
		return NULL;
	int counter;
	for (counter = 0; !trees[counter]; counter++);
	std::list<int> prkey() = trees[counter]->priority();
	int pr_pos = counter;
	for (; counter < _max; counter++)
	{
		if (trees[counter])
		{
			if (compare(trees[counter]->priority(), prkey()))
			{
				prkey() = trees[counter]->priority();
				pr_pos = counter;
			}
		}
	}
	return trees[pr_pos];
}
template <class T>
void HeapArray<T>::insert(HeapNodeAr<T>* list)
{
	HeapNodeAr<T> *next, *add_tree, *carry_tree;
	add_tree = list;
	carry_tree = NULL;
	next = NULL;
	do{
		if (add_tree)
		{
			next = add_tree->right;
			add_tree->parent = NULL;
			add_tree->left = add_tree->right = add_tree;
		}
		else
		{
			add_tree = carry_tree;
			carry_tree = NULL;
		}
		if (carry_tree)
		{
			mergeNode(add_tree, carry_tree, compare);
		}
		if (add_tree)
		{
			int d = add_tree->degree;
			if (trees[d])
			{
				mergeNode(trees[d], add_tree, compare);
				carry_tree = add_tree;
			}
			else
			{
				trees[d] = add_tree;
			}
		}
		add_tree = next;
	}
	while (add_tree || carry_tree);
}
template <class T>
HeapNodeAr<T>* HeapArray<T>::insert(std::list<int> k, T v)
{
	HeapNodeAr<T>* new_node = new HeapNodeAr<T>(k, v);
	insert(new_node);
	_size++;
	return new_node;
}
template <class T>
HeapNodeAr<T>* HeapArray<T>::getTree(int x)const 
{
	if (trees[x])
	{
		return trees[x];
	}
	else
		return NULL;
}
template <class T>
void HeapArray<T>::walkBase(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, walkFuncAr action)
{
	if (it->child)
	{
		auto ptr = it->child;

		walkBase(ptr, prev, action);
	}
	if (it->partner && it->sl == false)
	{
		auto ptr = it->partner;
		walkBase(ptr, prev, action);
	}
	if (it->left && it->left != it && it != prev)
	{
		walkNeighbor(it, action);
	}
	if (it != prev)
		action(it);
}
template <class T>
void HeapArray<T>::walkNeighbor(HeapNodeAr<T>*& it, walkFuncAr action)
{
	HeapNodeAr<T>* start = it;
	it = it->left;
	while (start != it)
	{
		walkBase(it, it, action);
		it = it->left;
	}
	it = it->right;
	int deg = it->left->degree;
	for (int i = 0; i < deg; i++)
	{
		it = it->right;
		action(it->left);
	}
	it = start;
}
template <class T>
void HeapArray<T>::walk(walkFuncAr action)
{
	for (int i = 0; i < getMaxDegree(); i++)
	{
		if (getTree(i))
		{
			HeapNodeAr<T>* prev = NULL;
			walkBase(trees[i], prev, action);
		}
	}
}
template <class T>
HeapArray<T>::HeapArray(compFuncAr call = basicAComp, int max = 16)
{
	trees = new HeapNodeAr<T>*[max];
	for (int i = 0; i < max; i++)
	{
		trees[i] = NULL;
	}
	compare = call;
	_max = max;
	_size = 0;

}
bool basicAComp(std::list<int> a, std::list<int> b)
{
	double a_val = 0, b_val = 0;
	for (std::list<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		a_val += *it;
	}
	for (std::list<int>::iterator it = b.begin(); it != b.end(); it++)
	{
		b_val += *it;
	}
	a_val /= a.size();
	b_val /= b.size();
	return a > b;
}
template <class T>
void destructHeap(HeapNodeAr<T>* it)
{

	if (HeapArray<T>::isNotDeleted(it))
	{
		delete it;
	}
}
template <class T>
bool HeapArray<T>::isNotDeleted(HeapNodeAr<T>* it)
{
	return Ptr(it) != DELETED ? true : false;
}


//*************************************************************
//***������� � ����������� ( PriorityQueue ) : ��������********
//*************************************************************

/*
	����� ��������� �������������� ������ � ����� Heap ��� ��������� ������
	����������� ������� ������� ����������� ������ list
	������ � ������� HeapNode
*/
template <class T> class PriorityQueueArray : public HeapArray<T>
{
public:
	//������� ��������
	typedef bool(*unarPredAr)(HeapNodeAr<T>*);

	template<class T> friend class HeapNodeArray;

	//����������� �� ���������
	PriorityQueueArray<T>(compFuncAr call = basicAComp, int max = 16);
	//�������� ��� ����������� ������ �� �����
	typedef void(*copyFuncAr)(HeapNodeAr<T>*, std::list<std::pair< std::list<int> , T > >&);

	//�������� ��� ����������� �����
	typedef void(*copyNodesAr)(HeapNodeAr<T>*, std::list < HeapNodeAr< T>* >&);

	PriorityQueueArray<T>(const PriorityQueueArray<T>&);
	void operator=(const PriorityQueueArray<T>&);

	//������� ����
	void clear();

	//�������� �� ���� x ��� �����
	void copy(const PriorityQueueArray<T>& x);

	//���������� ��� ����� ���� � ������� ������ <����, ��������>
	std::list<std::pair<std::list<int>,T> > getAllData() const;

	//���������� ��� ����� ���� � ������� ������ �����.
	std::list<HeapNodeAr<T>* > getAllNode();

	//������� ����� ������� � ����������� �� ��������� ������ , ������� � ����� ��� �����,
	//������� �������� �� �������
	//�������� ��������� : bool f(HeapNode<T>)
	PriorityQueueArray<T> createHeapIf(unarPredAr);
protected:
	void _walkCopy(copyFuncAr action,std::list<std::pair<std::list<int>,T> >&) const;
	void _walkCopy(copyNodesAr action, std::list<HeapNodeAr<T>* >&) const;
	//��������������� ������� ��� ������ �� ����
	//��������� ����� �� �������
	void _walkNeighborCopy(HeapNodeAr<T>*& it, copyFuncAr action, std::list<std::pair<std::list<int>, T> >&) const;
	void _walkNeighborCopy(HeapNodeAr<T>*& it, copyNodesAr action, std::list<HeapNodeAr<T>* >&) const;
	//������� ������� ������ �� ����
	void _walkBaseCopy(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, copyFuncAr action, std::list<std::pair<std::list<int> , T> >&) const;
	void _walkBaseCopy(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, copyNodesAr action, std::list<HeapNodeAr<T>* >&) const;

};
	template <class T>
	void PriorityQueueArray<T>::operator=(const PriorityQueueArray<T>& rez)
	{
		//���� ���� �� ����� �� ������� "�����" ����
		//������� ����� ������ ����, � �������� ���� ��� 
		//���� �� "������" ����
		if (this->trees != rez.trees)
		{
			this->clear();
			this->copy(rez);
		}
	}

	template <class T>
	PriorityQueueArray<T>::PriorityQueueArray(compFuncAr call = basicAComp, int max = 16) : HeapArray(call, max)
	{}

	template <class T>
	PriorityQueueArray<T>::PriorityQueueArray(const PriorityQueueArray& rez)
	{
		if (this->trees != rez.trees)
		{
			this->clear();
			this->copy(rez);
		}
	}
	//������� ����
	template < class T>
	void PriorityQueueArray<T>::clear()
	{
		this->~PriorityQueueArray();
		this->trees = new HeapNodeAr<T>*[_max];
		for (int i = 0; i < _max; i++)
		{
			this->trees[i] = NULL;
		}
		this->_size = 0;
	}
	//�������� �� ���� x ��� �����
	template <class T>
	void PriorityQueueArray<T>::copy(const PriorityQueueArray& x)
	{
		std::list<std::pair<std::list<int>, T> > temp_list = x.getAllData();
		std::list<std::pair<std::list<int>, T> >::iterator it;
		for (it = temp_list.begin();it != temp_list.end(); it++)
		{
			this->insert(it->first, it->second);
		}
	}
	//���������� ��� ����� ���� � ������� ������ <����, ��������>
	template <class T>
	std::list<std::pair<std::list<int> , T> > PriorityQueueArray<T>::getAllData() const
	{
		std::list<std::pair<std::list<int>,T> > temp_list;
		_walkCopy(basicCopyFunc, temp_list);
		return temp_list;
	}
	//���������� ��� ����� ���� � ������� ������ �����.
	template <class T>
	std::list<HeapNodeAr<T>* > PriorityQueueArray<T>::getAllNode()
	{
		std::list<HeapNodeAr<T>* > temp_list;
		_walkCopy(basicNodesFunc, temp_list);
		return temp_list;
	}
	//������� ����� ������� � ����������� �� ��������� ������ , ������� � ����� ��� �����,
	//������� �������� �� �������
	//�������� ��������� : bool f(HeapNode<T>)
	template <class T>
	PriorityQueueArray<T> PriorityQueueArray<T>::createHeapIf(unarPredAr f)
	{
		std::list<HeapNodeAr<T>* > all_vertex = getAllNode();
		std::list<HeapNodeAr<T>* >::iterator it;
		PriorityQueueArray<T> new_heap;
		for (it = all_vertex.begin(); it != all_vertex.end(); it++)
		{
			if (f(*it) == true)
			{
				new_heap.insert((*it)->key(),(*it)->value());
			}
		}
		return new_heap;
	}
	template <class T>
	void PriorityQueueArray<T>::_walkCopy(copyFuncAr action, std::list<std::pair<std::list<int> , T> >& sp) const
	{
		for (int i = 0; i < getMaxDegree(); i++)
		{
			if (getTree(i))
			{
				HeapNodeAr<T>* prev = NULL;
				_walkBaseCopy(trees[i], prev, action,sp);
			}
		}
	}
	template <class T>
	void PriorityQueueArray<T>::_walkCopy(copyNodesAr action, std::list<HeapNodeAr<T>* >& sp) const
	{
		for (int i = 0; i < getMaxDegree(); i++)
		{
			if (getTree(i))
			{
				HeapNodeAr<T>* prev = NULL;
				_walkBaseCopy(trees[i], prev, action, sp);
			}
		}
	}
	//��������������� ������� ��� ������ �� ����
	//��������� ����� �� �������
	template <class T>
	void PriorityQueueArray<T>::_walkNeighborCopy(HeapNodeAr<T>*& it, copyFuncAr action, std::list<std::pair<std::list<int> , T> >& sp) const
	{
		HeapNodeAr<T>* start = it;
		it = it->left;
		while (start != it)
		{
			_walkBaseCopy(it, it, action,sp);
			it = it->left;
		}
		it = it->right;
		int deg = it->left->degree;
		for (int i = 0; i < deg; i++)
		{
			it = it->right;
			action(it->left,sp);
		}
		it = start;
	}
	template < class T>
	void PriorityQueueArray<T>::_walkNeighborCopy(HeapNodeAr<T>*& it, copyNodesAr action, std::list<HeapNodeAr<T>* >& sp) const
	{
		HeapNodeAr<T>* start = it;
		it = it->left;
		while (start != it)
		{
			_walkBaseCopy(it, it, action, sp);
			it = it->left;
		}
		it = it->right;
		int deg = it->left->degree;
		for (int i = 0; i < deg; i++)
		{
			it = it->right;
			action(it->left, sp);
		}
		it = start;
	}
	//������� ������� ������ �� ����
	template <class T>
	void PriorityQueueArray<T>::_walkBaseCopy(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, copyFuncAr action, std::list<std::pair<std::list<int> , T> >& sp) const
	{
		if (it->child)
		{
			auto ptr = it->child;

			_walkBaseCopy(ptr, prev, action,sp);
		}
		if (it->partner && it->sl == false)
		{
			auto ptr = it->partner;
			_walkBaseCopy(ptr, prev, action,sp);
		}
		if (it->left && it->left != it && it != prev)
		{
			_walkNeighborCopy(it, action,sp);
		}
		if (it != prev)
			action(it,sp);
	}
	template <class T>
	void PriorityQueueArray<T>::_walkBaseCopy(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, copyNodesAr action, std::list<HeapNodeAr<T>* >& sp) const
	{
		if (it->child)
		{
			auto ptr = it->child;
			_walkBaseCopy(ptr, prev, action, sp);
		}
		if (it->partner && it->sl == false)
		{
			auto ptr = it->partner;
			_walkBaseCopy(ptr, prev, action, sp);
		}
		if (it->left && it->left != it && it != prev)
		{
			_walkNeighborCopy(it, action, sp);
		}
		if (it != prev)
			action(it, sp);
	}
	template <class T>
	void basicCopyFunc(HeapNodeAr<T>* it, std::list<std::pair< std::list<int> , T > >& sp)
	{
		sp.push_back(std::make_pair(it->key(),it->value()));
	}
	template <class T>
	void basicNodesFunc(HeapNodeAr<T>* it, std::list<HeapNodeAr<T>* >& sp)
	{
		sp.push_back(it);
	}

#endif
