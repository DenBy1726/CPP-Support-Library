#pragma once
#ifndef NODE_23
#define NODE_23
#include <iostream>
#define Ptr(a) (unsigned int)a
#define DELETED 0xfeeefeee
#define IsBadPtr(a) Ptr(a) == DELETED
#define IsGoodPtr(a) Ptr(a) != DELETED
#define IsNotDeleted(a) Ptr(a->left) != DELETED && Ptr(a->right) != DELETED && Ptr(a->partner) !=DELETED && Ptr(a->parent)!=DELETED && Ptr(a->child)!= DELETED
#define IsBadPtrFull(a) Ptr(a->left) != DELETED || Ptr(a->right) != DELETED || Ptr(a->partner) !=DELETED || Ptr(a->parent)!=DELETED || Ptr(a->child)!= DELETED
#define IsNotNull(a) Ptr(a->left) != NULL && Ptr(a->right) != NULL && Ptr(a->partner) !=NULL && Ptr(a->parent)!=NULL && Ptr(a->child)!= NULL
//#define CompareFunction(a,b) bool(*compare)(int, int);
typedef bool(*compFunc)(int, int);
template <class T>class HeapNode
{
protected:
	template<class T> friend class Heap;
	template <class T> friend void mergeNode(HeapNode<T>*& a, HeapNode<T>*& b, compFunc);
	HeapNode* parent;
	HeapNode* partner;
	HeapNode* child;
	HeapNode* left;
	HeapNode* right;
	int degree;
	bool sl;
	int _key;
	T _value;
public:
	//конструктор создает узел и инициализирует его
	HeapNode(int k, T v) :left(NULL), child(NULL), right(NULL), _key(k), _value(v), degree(0),sl(false),parent(NULL),partner(NULL){};
	//конструктор создает узел,инициализирует только значение
	HeapNode(T v) :left(NULL), child(NULL), right(NULL), _key(0), _value(v), degree(0), sl(false), parent(NULL), partner(NULL){};
	//Конструктор по умолчанию создает пустой узел
	HeapNode(){};
	~HeapNode(){}
	//возвращает приоритет узла(его ключ)
	int priority()
	{
		return _key;
	}
	//возвращает приоритет узла(его ключ)
	int key()
	{
		return _key;
	}
	//возвращает значение,хранимое в узле
	T value()
	{
		return _value;
	}
	//возвращает степень дерева
	int order()
	{
		return degree;
	}
	//возвращает левого соседа
	HeapNode* getLeft()
	{
		return left;
	}
	//возвращает сына
	HeapNode* getChild()
	{
		return child;
	}
	//возвращает правого соседа
	HeapNode* getRight()
	{
		return right;
	}
	//возвращает партнера
	HeapNode* getPartner()
	{
		return partner;
	}
	//возвращает родителя
	HeapNode* getParent()
	{
		return parent;
	}
	//возвращает насыщенность узла
	bool type()
	{
		return sl;
	}
	//Вставляет сына к текущему узлу
	void addChild(HeapNode<T>* new_child);
	//меняет местами ключи и значения узлов
	void swap(HeapNode<T>* root2);
	//меняет партнеров местами
	void rotatePartner();
	

};
template <class T>
void HeapNode<T>::rotatePartner()
{
	this->partner->sl = (this->partner->sl ? false : true);
	this->sl = (this->sl ? false : true);
}
template <class T>
void HeapNode<T>::swap(HeapNode<T>* root2)
{
	int temp_key = this->_key;
	int temp_val = this->_value;
	this->_key = root2->_key;
	root2->_key = temp_key;
	this->_value = root2->_value;
	root2->_value = temp_val;
}
template <class T>
void HeapNode<T>::addChild(HeapNode<T>* new_child)
{
	/*идея в том чтобы привязать вершину new_child к узлу как сына.
	//сын это один из видов связей(так же есть партнер и сосед).
	//графически связь отображается как связь "вниз"
	//
	[1]
	/\
	||   связь с сыном
	\/
	[2] <->[4]
	подробнее в документации
	*/
	HeapNode<T>* new_left, *new_right;
	new_left = child;
	if (new_left)
	{
		new_right = new_left->right;
		new_child->left = new_left;
		new_child->right = new_right;
		//связываем нового сына со старым соседской связью (см. документацию)
		new_right->left = new_child;
		new_left->right = new_child;
		//cвязываем старого сына с новым
	}
	else
	{
		new_child->left = new_child->right = new_child;
	}
	child = new_child;
	new_child->parent = this;
	//связываем нового сына с родителем
}
template <class T>
void mergeNode(HeapNode<T>*& a, HeapNode<T>*& b, compFunc compare)
{
	//объединяет дерево a с деревом b
	//результат может быть сохранен в любом (по контексту)
	//если в a  то дерево не изменило степени(например ненасыщенное стало насыщенным)
	//если в b то дерево изменило степень и его нужно вставлять снова(так как ячейка ,куда вставляем может быть занята)
//	Heap<T>::compare(1, 3);
	HeapNode<T>* tree_general, *tree_added, *next_general, *next_added;
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
	next_general = tree_general->partner;
	next_added = tree_added->partner;
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
			//next_general != 0 && next_added != 0
			//дописать
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
//template <class T>
template <class T> class Heap
{
private:
	template<class T> friend class HeapNode;
	template<class T> friend void mergeNode(HeapNode<T>*& a, HeapNode<T>*& b, compFunc);
	HeapNode<T>** trees;
	size_t _size;
	int _max;
	compFunc compare;
	static void allocated(int n, HeapNode<T>**&tree);
	static void deAllocated(int n, HeapNode<T>**&tree);
	typedef void(*walkFunc)(HeapNode<T>*);
public:
	static bool isNotDeleted(HeapNode<T>* it);
	//конструктор устанавливает функция сравнения и максимальное количество деревьев в куче
	Heap(compFunc call = keyMin, int max = 16);
	Heap(const Heap& clone);
	~Heap()
	{
		walk(destructHeap);
	}
	//возвращает указатель на фунцию сравнения
	compFunc getFunc() const
	{
		return compare;
	}

	//проверка на пустоту
	bool isEmpty() const
	{
		return (_size == 0);
	}
	//возвращает максимальную степень кучи
	int getMaxDegree() const
	{
		return _max;
	}
	//обход по куче и выполнение функции action для каждой вершины
	void walk(walkFunc action);
protected:
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
	void walkNeighbor(HeapNode<T>*& it, walkFunc action);
	//базовая функция обхода по куче
	void walkBase(HeapNode<T>*& it, HeapNode<T>*& prev, walkFunc action);
public:
	//возвращает количество элементов в куче
	size_t size() const
	{
		return _size;
	}
	//возвращает максимальновозможное количество элементов в куче
	size_t maxSize() const
	{
		return (pow(3, _max + 1) - 1);
	}
	//возвращает дерево степени x
	HeapNode<T>* getTree(int x) const ;
	//вставить узел в кучу
	HeapNode<T>* insert(int k, T v);
	//вставить узел в кучу(узел уже создан)
	void insert(HeapNode<T>* list);
	//возвращает приоритетный элемент
	HeapNode<T>* priority();
	//удаляет из кучи приоритетный элемент и возвращает вырезанный из кучи элемент
	HeapNode<T>* extract();
	//удаляет из кучи приоритетный элемент и возвращает значение ключа вырезанного элемента
	int extractKey();
	//удаляет из кучи приоритетный элемент и возвращает значение,хранимое в вырезанном элемента
	T extractValue();
	//сливает текущую кучу с кучей sum(в результате в sum будет пустая куча)
	void merge(Heap& sum);
	//сливает текущую кучу с кучей sum
	void copy(Heap& sum);
	//изменяет значение ключа
	void editKey(HeapNode<T>* node, int new_key, int new_val);
};
template <class T>
void Heap<T>::editKey(HeapNode<T>* node, int new_key, int new_val)
{
	node->_key = new_key;
	node->_value = new_val;
	while (1)
	{
		//если есть правый сосед и мы увеличили приоритет,то при условии если правый сосед старше по степени(ближе к корню)
		//меняемся с правым соседом
		if (node->right)
		{
			if (compare(node->_key, node->right->_key))
			{
				if (node->right->degree > node->degree)
				{
					node->swap(node->right);
					node = node->right;
					continue;
				}
			}
		}
		//если есть сосед ,то если увеличивае ключ то меняемся только ненасыщенный на насыщенный
		//иначе если уменьшаем ключ то меняемсятолько насыщенный на ненасыщенный
		if (node->partner)
		{
			if (!compare(node->_key, node->partner->_key))
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
		//на родителя идем только при увеличении приоритета
		if (node->parent)
		{
			if (compare(node->_key, node->parent->_key))
			{
				node->swap(node->parent);
				node = node->parent;
				continue;
			}
		}
		if (node->child)
		{
			if (!compare(node->_key, node->child->_key))
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
void Heap<T>::copy(Heap& sum)
{
	HeapNode<T>* buff;
	int max = (_max > sum._max ? _max : sum._max);
	for (size_t i = 0; i <= sum._max; i++)
	{
		if ((buff = sum.getTree(i)) != NULL)
		{
			buff->left = NULL;
			buff->right = NULL;
			this->insert(buff);
			buff->left = buff->right = buff;
		}
	}
	_size += sum.size();
}
template <class T>
void Heap<T>::merge(Heap& sum)
{
	HeapNode<T>* buff;
	int max = (_max > sum._max ? _max : sum._max);
	for (size_t i = 0; i <= sum._max; i++)
	{
		if ((buff = sum.getTree(i)) != NULL)
		{
			buff->left = NULL;
			buff->right = NULL;
			this->insert(buff);
			buff->left = buff->right = buff;
			sum.trees[i] = NULL;
		}
	}
	_size += sum.size();
	sum._size = 0;
}
template <class T>
HeapNode<T>* Heap<T>::extract()
{
	if (_size == 0)
		return NULL;
	HeapNode<T>* pr = priority();
	HeapNode<T>* pt = pr->partner;
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
	HeapNode<T>* ch = pr->child;
	HeapNode<T>* node;
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
T Heap<T>::extractValue()
{
	if (_size == 0)
		return NULL;
	T val;
	HeapNode<T>* v = extract();
	val = v->value();
	delete v;
	return val;
}
template <class T>
int Heap<T>::extractKey()
{
	if (_size == 0)
		return NULL;
	int key;
	HeapNode<T>* k = extract();
	key = k->key();
	delete k;
	return key;
}
template <class T>
HeapNode<T>* Heap<T>::priority()
{
	if (_size == 0)
		return NULL;
	size_t counter;
	for (counter = 0; !trees[counter]; counter++);
	int pr_key = trees[counter]->priority();
	int pr_pos = counter;
	for (; counter < _max; counter++)
	{
		if (trees[counter])
		{
			if (compare(trees[counter]->priority(), pr_key))
			{
				pr_key = trees[counter]->priority();
				pr_pos = counter;
			}
		}
	}
	return trees[pr_pos];
}
template <class T>
void Heap<T>::insert(HeapNode<T>* list)
{
	HeapNode<T> *next, *add_tree, *carry_tree;
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
HeapNode<T>* Heap<T>::insert(int k, T v)
{
	HeapNode<T>* new_node = new HeapNode<T>(k, v);
	insert(new_node);
	_size++;
	return new_node;
}
template <class T>
HeapNode<T>* Heap<T>::getTree(int x)const 
{
	if (trees[x])
	{
		return trees[x];
	}
	else
		return NULL;
}
template <class T>
void Heap<T>::walkBase(HeapNode<T>*& it, HeapNode<T>*& prev, walkFunc action)
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
void Heap<T>::walkNeighbor(HeapNode<T>*& it, walkFunc action)
{
	HeapNode<T>* start = it;
	it = it->left;
	while (start != it)
	{
		walkBase(it, it, action);
		it = it->left;
	}
	it = it->right;
	int deg = it->left->degree;
	for (size_t i = 0; i < deg; i++)
	{
		it = it->right;
		action(it->left);
	}
	it = start;
}
template <class T>
void Heap<T>::walk(walkFunc action)
{
	for (int i = 0; i < getMaxDegree(); i++)
	{
		if (getTree(i))
		{
			HeapNode<T>* prev = NULL;
			walkBase(trees[i], prev, action);
		}
	}
}
template <class T>
Heap<T>::Heap(const Heap& clone)
{
	compare = clone.getFunc();
	_max = clone.getMaxDegree();
	trees = new HeapNode<T>*[_max];
	_size = clone.size();
	for (size_t i = 0; i < _max; i++)
	{
		trees[i] = NULL;
	}
	HeapNode<T>* temp;
	for (size_t i = 0; i < _max; i++)
	{
		temp = clone.getTree(i);
		if (temp != NULL)
		{
			temp->left = NULL;
			temp->right = NULL;
			this->insert(temp);
		}
	}
}
template <class T>
Heap<T>::Heap(compFunc call = keyMin, int max = 16)
{
	trees = new HeapNode<T>*[max];
	for (size_t i = 0; i < max; i++)
	{
		trees[i] = NULL;
	}
	compare = call;
	_max = max;
	_size = 0;

}
bool keyMin(int a, int b)
{
	return a <= b;
}
template <class T>
void destructHeap(HeapNode<T>* it)
{

	if (Heap<T>::isNotDeleted(it))
	{
		delete it;
	}
}
template <class T>
bool Heap<T>::isNotDeleted(HeapNode<T>* it)
{
	return Ptr(it) != DELETED ? true : false;
}
#endif