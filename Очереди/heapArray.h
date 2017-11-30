#pragma once
#ifndef NODE_23AR
#include <list>
#include "baseHeap.h"
#define NODE_23AR
//******************************************************************
//*****************************МАКРО-ОПРЕДЕЛЕНИЯ********************
//******************************************************************

typedef bool(*compFuncAr)(std::list<int>, std::list<int>);
//возвращает число равное номеру ячейки, в которой храниться данное


//***********************************************************************
//************************Узел Кучи(HeapNode) : Прототип*****************
//***********************************************************************

//Позволяет хранить одно значение в куче.
//Содержит служебные указатели и данные
//Дружелюбен по отношению к Heap и PriorityQueue
template <class T>class HeapNodeAr
{
protected:
	template<class T> friend class HeapArray;
	template<class T> friend class PriorityQueueArray;
	template <class T> friend void mergeNode(HeapNodeAr<T>*& a, HeapNodeAr<T>*& b, compFuncAr);
	//Служебные указатели
	HeapNodeAr* parent;
	HeapNodeAr* partner;
	HeapNodeAr* child;
	HeapNodeAr* left;
	HeapNodeAr* right;
	//Служебные данные
	int degree;
	bool sl;
	//Хранимые данные
	std::list<int> _key;
	T _value;
public:
	//конструктор создает узел и инициализирует его
	HeapNodeAr(std::list<int> k, T v) :left(NULL), child(NULL), right(NULL), _key(k), _value(v), degree(0),sl(false),parent(NULL),partner(NULL){};
	//конструктор создает узел,инициализирует только значение( ключ равен нулю)
	HeapNodeAr(T v) :left(NULL), child(NULL), right(NULL), _key(std::list<int>()), _value(v), degree(0), sl(false), parent(NULL), partner(NULL){};
	//Конструктор по умолчанию создает пустой узел
	HeapNodeAr(){};
	~HeapNodeAr(){}
	//возвращает приоритет узла(его ключ). Является синонимом метода key()
	std::list<int> priority()
	{
		return _key;
	}
	//возвращает приоритет узла(его ключ)
	std::list<int> key()
	{
		return _key;
	}
	int key(int i)
	{
		return _key[i];
	}
	//возвращает значение,хранимое в узле
	T value()
	{
		return _value;
	}
	//возвращает степень дерева(фактически его высота)
	int order()
	{
		return degree;
	}
	//возвращает указатель на левого соседа
	HeapNodeAr* getLeft()
	{
		return left;
	}
	//возвращает указатель на сына
	HeapNodeAr* getChild()
	{
		return child;
	}
	//возвращает указатель на правого соседа
	HeapNodeAr* getRight()
	{
		return right;
	}
	//возвращает указатель на партнера
	HeapNodeAr* getPartner()
	{
		return partner;
	}
	//возвращает указатель на родителя
	HeapNodeAr* getParent()
	{
		return parent;
	}
	//возвращает насыщенность узла
	bool type()
	{
		return sl;
	}
	//Вставляет сына к текущему узлу
	void addChild(HeapNodeAr<T>* new_child);
	//меняет местами ключи и значения узлов
	void swap(HeapNodeAr<T>* root2);
	//оператор сравнения
	bool operator<(HeapNodeAr<T>* right)
	{
		return this->key() < right->key();
	}
	
};

//***********************************************************************
//************************Узел Кучи(HeapNode) : Реализация***************
//***********************************************************************

template <class T>
void HeapNodeAr<T>::swap(HeapNodeAr<T>* root2)
{
	//достаточно поменять местами ключи и значения
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
	/*идея в том чтобы привязать вершину new_child к узлу как сына.
	//сын это один из видов связей(так же есть партнер и сосед).
	//графически связь отображается как связь "вниз"
	//
	[1]
	/\
	||   связь с сыном
	\/
	[2] <->[4]
	*/

	HeapNodeAr<T>* new_left, *new_right;
	new_left = child;
	if (new_left)
	{
		//связываем нового сына со старым соседской связью
		new_right = new_left->right;
		new_child->left = new_left;
		new_child->right = new_right;
		//cвязываем старого сына с новым
		new_right->left = new_child;
		new_left->right = new_child;	
	}
	else
	{
		new_child->left = new_child->right = new_child;
	}
	//связываем нового сына с родителем
	child = new_child;
	new_child->parent = this;
	
}
template <class T>
void mergeNode(HeapNodeAr<T>*& a, HeapNodeAr<T>*& b, compFuncAr compare)
{
	/*
	объединяет дерево a с деревом b
	результат может быть сохранен в любом (по контексту)
	если в a  то дерево не изменило степени(например ненасыщенное стало насыщенным)
	если в b то дерево изменило степень и его нужно вставлять снова(так как ячейка ,куда вставляем может быть занята)
	*/

	HeapNodeAr<T>* tree_general, *tree_added, *next_general, *next_added;
	//определяем главный узел(наиболее приоритетный)
	//и добавляемый (наименее приоритетный)
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
	//также запоминаем партнеров
	next_general = tree_general->partner;
	next_added = tree_added->partner;
	//рассматриваем всевозможные варианты ( наличия или отсутствия)
	//партнеров( по сути определяет тип дерева
	//всего существует три вида взаимодействия:
	// 1) без партнера + без партнера
	// 2) без партнера + с партнером
	// 3) с партнером + с партнером
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
//****************************Куча ( Heap ) : Прототип*********
//*************************************************************

/*

	Класс для работы с кучей. 
	Содержит массив узлов ( по сути деревьев), и служебную информацию
	Дружелюбен с HeapNode

*/
template <class T> class HeapArray
{
protected:
	template<class T> friend class HeapNodeAr;
	template<class T> friend void mergeNode(HeapNodeAr<T>*& a, HeapNodeAr<T>*& b, compFuncAr);
	//массив узлов

	HeapNodeAr<T>** trees;

	//служебная информация

	size_t _size;
	int _max;
	compFuncAr compare;
	typedef void(*walkFuncAr)(HeapNodeAr<T>*);
public:
	//Фунция проверяет был ли удален узел
	static bool isNotDeleted(HeapNodeAr<T>* it);
	//конструктор устанавливает функцию сравнения и максимальное количество деревьев в куче
	HeapArray(compFuncAr call = basicAComp, int max = 16);

	~HeapArray()
	{
		walk(destructHeap);
	}

	//возвращает указатель на фунцию сравнения
	compFuncAr getFunc() const
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
	void walk(walkFuncAr action);

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
	HeapNodeAr<T>* getTree(int x) const ;

	//создать узел и вставить его в кучу
	HeapNodeAr<T>* insert(std::list<int> k, T v);

	//вставить узел в кучу
	void insert(HeapNodeAr<T>* list);

	//возвращает приоритетный элемент
	HeapNodeAr<T>* priority();

	//удаляет из кучи приоритетный элемент и возвращает вырезанный из кучи элемент
	//Внимание: в данном случае узел не удалиться автоматически,
	//нужно позаботиттся об этом свмостоятельно
	HeapNodeAr<T>* extract();

	//удаляет из кучи приоритетный элемент и возвращает значение ключа вырезанного элемента
	std::list<int> extractKey();

	//удаляет из кучи приоритетный элемент и возвращает значение,хранимое в вырезанном элемента
	T extractValue();

	//сливает текущую кучу с кучей sum(в результате в sum будет пустая куча)
	void merge(HeapArray& sum);

	//изменяет значение ключа
	void editKey(HeapNodeAr<T>* node, std::list<int> newkey(), T new_val);

protected:
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
	void walkNeighbor(HeapNodeAr<T>*& it, walkFuncAr action);

	//базовая функция обхода по куче
	void walkBase(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, walkFuncAr action);
};

//*************************************************************
//****************************Куча ( Heap ) : Реализация*******
//*************************************************************


template <class T>
void HeapArray<T>::editKey(HeapNodeAr<T>* node, std::list<int> newkey(), T new_val)
{
	node->key() = newkey();
	node->value() = new_val;
	while (1)
	{
		//если есть правый сосед и мы увеличили приоритет,то при условии если правый сосед старше по степени(ближе к корню)
		//меняемся с правым соседом
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
		//если есть сосед ,то если увеличивае ключ то меняемся только ненасыщенный на насыщенный
		//иначе если уменьшаем ключ то меняемся только насыщенный на ненасыщенный
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
		//на родителя идем только при увеличении приоритета
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
	// если размеры куч разные, end равно минимальному из размеров.
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
//***Очередь с приоритетом ( PriorityQueue ) : Прототип********
//*************************************************************

/*
	Класс добавляет дополнительные методы к класу Heap для упращения работы
	Большинство методов требуют подключения класса list
	Дружит с классом HeapNode
*/
template <class T> class PriorityQueueArray : public HeapArray<T>
{
public:
	//унарный предикат
	typedef bool(*unarPredAr)(HeapNodeAr<T>*);

	template<class T> friend class HeapNodeArray;

	//Конструктор по умолчанию
	PriorityQueueArray<T>(compFuncAr call = basicAComp, int max = 16);
	//предикат для копирования данных из узлов
	typedef void(*copyFuncAr)(HeapNodeAr<T>*, std::list<std::pair< std::list<int> , T > >&);

	//Предикат для копирования узлов
	typedef void(*copyNodesAr)(HeapNodeAr<T>*, std::list < HeapNodeAr< T>* >&);

	PriorityQueueArray<T>(const PriorityQueueArray<T>&);
	void operator=(const PriorityQueueArray<T>&);

	//очищает кучу
	void clear();

	//копирует из кучи x все ключи
	void copy(const PriorityQueueArray<T>& x);

	//возвращает все ключи кучи в формате списка <ключ, значение>
	std::list<std::pair<std::list<int>,T> > getAllData() const;

	//возвращает все ключи кучи в формате списка узлов.
	std::list<HeapNodeAr<T>* > getAllNode();

	//создает новую очередь с приоритетом на основании старой , помещая в новую все ключи,
	//которые подходят по условию
	//прототип предиката : bool f(HeapNode<T>)
	PriorityQueueArray<T> createHeapIf(unarPredAr);
protected:
	void _walkCopy(copyFuncAr action,std::list<std::pair<std::list<int>,T> >&) const;
	void _walkCopy(copyNodesAr action, std::list<HeapNodeAr<T>* >&) const;
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
	void _walkNeighborCopy(HeapNodeAr<T>*& it, copyFuncAr action, std::list<std::pair<std::list<int>, T> >&) const;
	void _walkNeighborCopy(HeapNodeAr<T>*& it, copyNodesAr action, std::list<HeapNodeAr<T>* >&) const;
	//базовая функция обхода по куче
	void _walkBaseCopy(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, copyFuncAr action, std::list<std::pair<std::list<int> , T> >&) const;
	void _walkBaseCopy(HeapNodeAr<T>*& it, HeapNodeAr<T>*& prev, copyNodesAr action, std::list<HeapNodeAr<T>* >&) const;

};
	template <class T>
	void PriorityQueueArray<T>::operator=(const PriorityQueueArray<T>& rez)
	{
		//если кучи не равны то очишаем "левую" кучу
		//создаем новую пустую кучу, и копируем туда все 
		//узлы из "правой" кучи
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
	//очищает кучу
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
	//копирует из кучи x все ключи
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
	//возвращает все ключи кучи в формате списка <ключ, значение>
	template <class T>
	std::list<std::pair<std::list<int> , T> > PriorityQueueArray<T>::getAllData() const
	{
		std::list<std::pair<std::list<int>,T> > temp_list;
		_walkCopy(basicCopyFunc, temp_list);
		return temp_list;
	}
	//возвращает все ключи кучи в формате списка узлов.
	template <class T>
	std::list<HeapNodeAr<T>* > PriorityQueueArray<T>::getAllNode()
	{
		std::list<HeapNodeAr<T>* > temp_list;
		_walkCopy(basicNodesFunc, temp_list);
		return temp_list;
	}
	//создает новую очередь с приоритетом на основании старой , помещая в новую все ключи,
	//которые подходят по условию
	//прототип предиката : bool f(HeapNode<T>)
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
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
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
	//базовая функция обхода по куче
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
