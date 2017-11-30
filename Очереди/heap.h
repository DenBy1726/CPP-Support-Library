#pragma once
#ifndef NODE_23
#define NODE_23
#include "baseHeap.h"
//******************************************************************
//*****************************МАКРО-ОПРЕДЕЛЕНИЯ********************
//******************************************************************


//***********************************************************************
//************************Узел Кучи(HeapNode) : Прототип*****************
//***********************************************************************

//Позволяет хранить одно значение в куче.
//Содержит служебные указатели и данные
//Дружелюбен по отношению к Heap и PriorityQueue
template <class T>
class HeapNode
{
protected:
	template<class T> friend class Heap;
	template<class T> friend class PriorityQueue;
	template <class T> friend void mergeNode(HeapNode<T>*& a, HeapNode<T>*& b, compFunc);
	//Служебные указатели
	HeapNode* parent;
	HeapNode* partner;
	HeapNode* child;
	HeapNode* left;
	HeapNode* right;
	//Служебные данные
	int degree;
	bool sl;
	//Хранимые данные
	int _key;
	T _value;
public:
	//конструктор создает узел и инициализирует его
	HeapNode(int k, T v) :left(NULL), child(NULL), right(NULL), _key(k), _value(v), degree(0),sl(false),parent(NULL),partner(NULL){};
	//конструктор создает узел,инициализирует только значение( ключ равен нулю)
	HeapNode(T v) :left(NULL), child(NULL), right(NULL), _key(0), _value(v), degree(0), sl(false), parent(NULL), partner(NULL){};
	//Конструктор по умолчанию создает пустой узел
	HeapNode(){};
	~HeapNode(){}
	//возвращает приоритет узла(его ключ). Является синонимом метода key()
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
	//возвращает степень дерева(фактически его высота)
	int order()
	{
		return degree;
	}
	//возвращает указатель на левого соседа
	HeapNode<T>* getLeft()
	{
		return left;
	}
	//возвращает указатель на сына
	HeapNode<T>* getChild()
	{
		return child;
	}
	//возвращает указатель на правого соседа
	HeapNode<T>* getRight()
	{
		return right;
	}
	//возвращает указатель на партнера
	HeapNode<T>* getPartner()
	{
		return partner;
	}
	//возвращает указатель на родителя
	HeapNode<T>* getParent()
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
	//оператор сравнения
	bool operator<(HeapNode<T>* right)
	{
		return this->_key < right->_key;
	}

};

//***********************************************************************
//************************Узел Кучи(HeapNode) : Реализация***************
//***********************************************************************

template <class T>
void HeapNode<T>::swap(HeapNode<T>* root2)
{
	//достаточно поменять местами ключи и значения
	int temp_key = this->_key;
	T temp_val = this->_value;
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
	*/

	HeapNode<T>* new_left, *new_right;
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
void mergeNode(HeapNode<T>*& a, HeapNode<T>*& b, compFunc compare)
{
	/*
	объединяет дерево a с деревом b
	результат может быть сохранен в любом (по контексту)
	если в a  то дерево не изменило степени(например ненасыщенное стало насыщенным)
	если в b то дерево изменило степень и его нужно вставлять снова(так как ячейка ,куда вставляем может быть занята)
	*/

	HeapNode<T>* tree_general, *tree_added, *next_general, *next_added;
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
template <class T>
class Heap
{
protected:
	template<class T> friend class HeapNode;
	template<class T> friend void mergeNode(HeapNode<T>*& a, HeapNode<T>*& b, compFunc);
	//массив узлов

	HeapNode<T>** trees;

	//служебная информация

	size_t _size;
	int _max;
	compFunc compare;
	typedef void(*walkFunc)(HeapNode<T>*);
public:
	//Фунция проверяет был ли удален узел
	static bool isNotDeleted(HeapNode<T>* it);
	//конструктор устанавливает функцию сравнения и максимальное количество деревьев в куче
	Heap(compFunc call = keyMin, int max = 16);

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

	//создать узел и вставить его в кучу
	HeapNode<T>* insert(int k, T v);

	//вставить узел в кучу
	void insert(HeapNode<T>* list);

	//возвращает приоритетный элемент
	HeapNode<T>* priority();

	//удаляет из кучи приоритетный элемент и возвращает вырезанный из кучи элемент
	//Внимание: в данном случае узел не удалиться автоматически,
	//нужно позаботиттся об этом свмостоятельно
	HeapNode<T>* extract();

	//удаляет из кучи приоритетный элемент и возвращает значение ключа вырезанного элемента
	int extractKey();

	//удаляет из кучи приоритетный элемент и возвращает значение,хранимое в вырезанном элемента
	T extractValue();

	//сливает текущую кучу с кучей sum(в результате в sum будет пустая куча)
	void merge(Heap& sum);

	///изменяет значение ключа
	///метод небезопасен, и лучше воздержаться от его использования, так как с 
	///увеличением количества вершин и при частом изменении ключей
	///возникает вероятность "ложного просеивания"
	///в результате куча отклоняется от корректного состояния, и при извлечении 
	///минимума может в еденичных случаях выдавать не приритетное значение, а 
	///следующее за ним.
	//лошади с хуями
	void editKey(HeapNode<T>* node, int new_key, T new_val);

protected:
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
	void walkNeighbor(HeapNode<T>*& it, walkFunc action);

	//базовая функция обхода по куче
	void walkBase(HeapNode<T>*& it, HeapNode<T>*& prev, walkFunc action);


};

//*************************************************************
//****************************Куча ( Heap ) : Реализация*******
//*************************************************************


template <class T>
///изменяет значение ключа
///метод небезопасен, и лучше воздержаться от его использования, так как с 
///увеличением количества вершин и при частом изменении ключей
///возникает вероятность "ложного просеивания"
///в результате куча отклоняется от корректного состояния, и при извлечении 
///минимума может в еденичных случаях выдавать не приритетное значение, а 
///следующее за ним.
void Heap<T>::editKey(HeapNode<T>* node, int new_key, T new_val)
{
	int i = 0;
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
		//если есть партнер ,то если увеличивае ключ то меняемся только ненасыщенный на насыщенный
		//иначе если уменьшаем ключ то меняемся только насыщенный на ненасыщенный
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
void Heap<T>::merge(Heap& sum)
{
	// если размеры куч разные, end равно минимальному из размеров.
	HeapNode<T>* buff;
	int end = hmin(_max, sum._max);
	for (int i = 0; i < end; i++)
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
	int counter;
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
	for (int i = 0; i < deg; i++)
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
Heap<T>::Heap(compFunc call = keyMin, int max = 16)
{
	trees = new HeapNode<T>*[max];
	for (int i = 0; i < max; i++)
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


//*************************************************************
//***Очередь с приоритетом ( PriorityQueue ) : Прототип********
//*************************************************************

/*
	Класс добавляет дополнительные методы к класу Heap для упращения работы
	Большинство методов требуют подключения класса list
	Дружит с классом HeapNode
*/
template <class T> class PriorityQueue : public Heap<T>
{
public:
	//унарный предикат
	typedef bool(*unarPred)(HeapNode<T>*);

	template<class T> friend class HeapNode;

	//Конструктор по умолчанию
	PriorityQueue<T>(compFunc call = keyMin, int max = 16);
#ifdef _LIST_
	//предикат для копирования данных из узлов
	typedef void(*copyFunc)(HeapNode<T>*, std::list<std::pair< int , T > >&);

	//Предикат для копирования узлов
	typedef void(*copyNodes)(HeapNode<T>*, std::list < HeapNode< T>* >&);

	//Конструктор с параметром listData - список пар<ключ, значение>
	PriorityQueue(std::list<std::pair<int, T> > listData, compFunc call = keyMin, int max = 16);

	//Конструктор с параметром listData - список ключей
	PriorityQueue(std::list<int> listData, compFunc call = keyMin, int max = 16);

	PriorityQueue(const PriorityQueue<T>&);
	void operator=(const PriorityQueue<T>&);

	//очищает кучу
	void clear();

	//копирует из кучи x все ключи
	void copy(const PriorityQueue<T>& x);

	//возвращает все ключи кучи в формате списка <ключ, значение>
	std::list<std::pair<int,T> > getAllData() const;

	//возвращает все ключи кучи в формате списка узлов.
	std::list<HeapNode<T>* > getAllNode();

	//создает новую очередь с приоритетом на основании старой , помещая в новую все ключи,
	//которые подходят по условию
	//прототип предиката : bool f(HeapNode<T>)
	PriorityQueue<T> createHeapIf(unarPred);
protected:
	void _walkCopy(copyFunc action,std::list<std::pair<int,T> >&) const;
	void _walkCopy(copyNodes action, std::list<HeapNode<T>* >&) const;
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
	void _walkNeighborCopy(HeapNode<T>*& it, copyFunc action, std::list<std::pair<int, T> >&) const;
	void _walkNeighborCopy(HeapNode<T>*& it, copyNodes action, std::list<HeapNode<T>* >&) const;
	//базовая функция обхода по куче
	void _walkBaseCopy(HeapNode<T>*& it, HeapNode<T>*& prev, copyFunc action, std::list<std::pair<int , T> >&) const;
	void _walkBaseCopy(HeapNode<T>*& it, HeapNode<T>*& prev, copyNodes action, std::list<HeapNode<T>* >&) const;

#endif
};
	template <class T>
	PriorityQueue<T>::PriorityQueue(std::list<std::pair<int, T> > listData, compFunc call = keyMin, int max = 16)
		:Heap<T>(call,max)
	{
		for each(auto it in listData)
			insert(it.first, it.second);
	}

	template <class T>
	PriorityQueue<T> :: PriorityQueue(std::list<int> listData, compFunc call = keyMin, int max = 16)
		: Heap<T>(call, max)
	{
			for each(auto it in listData)
				insert(it, T());
		}


	template <class T>
	void PriorityQueue<T>::operator=(const PriorityQueue<T>& rez)
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
	PriorityQueue<T>::PriorityQueue(compFunc call = keyMin, int max = 16) : Heap(call, max)
	{}
#ifdef _LIST_

	template <class T>
	PriorityQueue<T>::PriorityQueue(const PriorityQueue& rez)
	{
		if (this->trees != rez.trees)
		{
			this->clear();
			this->copy(rez);
		}
	}
	//очищает кучу
	template < class T>
	void PriorityQueue<T>::clear()
	{
		this->~PriorityQueue();
		this->trees = new HeapNode<T>*[_max];
		for (int i = 0; i < _max; i++)
		{
			this->trees[i] = NULL;
		}
		this->_size = 0;
	}
	//копирует из кучи x все ключи
	template <class T>
	void PriorityQueue<T>::copy(const PriorityQueue& x)
	{
		std::list<std::pair<int, T> > temp_list = x.getAllData();
		std::list<std::pair<int, T> >::iterator it;
		for (it = temp_list.begin();it != temp_list.end(); it++)
		{
			this->insert(it->first, it->second);
		}
	}
	//возвращает все ключи кучи в формате списка <ключ, значение>
	template <class T>
	std::list<std::pair<int , T> > PriorityQueue<T>::getAllData() const
	{
		std::list<std::pair<int,T> > temp_list;
		_walkCopy(basicCopyFunc, temp_list);
		return temp_list;
	}
	//возвращает все ключи кучи в формате списка узлов.
	template <class T>
	std::list<HeapNode<T>* > PriorityQueue<T>::getAllNode()
	{
		std::list<HeapNode<T>* > temp_list;
		_walkCopy(basicNodesFunc, temp_list);
		return temp_list;
	}
	//создает новую очередь с приоритетом на основании старой , помещая в новую все ключи,
	//которые подходят по условию
	//прототип предиката : bool f(HeapNode<T>)
	template <class T>
	PriorityQueue<T> PriorityQueue<T>::createHeapIf(unarPred f)
	{
		std::list<HeapNode<T>* > all_vertex = getAllNode();
		std::list<HeapNode<T>* >::iterator it;
		PriorityQueue<T> new_heap;
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
	void PriorityQueue<T>::_walkCopy(copyFunc action, std::list<std::pair<int , T> >& sp) const
	{
		for (int i = 0; i < getMaxDegree(); i++)
		{
			if (getTree(i))
			{
				HeapNode<T>* prev = NULL;
				_walkBaseCopy(trees[i], prev, action,sp);
			}
		}
	}
	template <class T>
	void PriorityQueue<T>::_walkCopy(copyNodes action, std::list<HeapNode<T>* >& sp) const
	{
		for (int i = 0; i < getMaxDegree(); i++)
		{
			if (getTree(i))
			{
				HeapNode<T>* prev = NULL;
				_walkBaseCopy(trees[i], prev, action, sp);
			}
		}
	}
	//вспомогательная функция для обхода по куче
	//совершает обход по соседям
	template <class T>
	void PriorityQueue<T>::_walkNeighborCopy(HeapNode<T>*& it, copyFunc action, std::list<std::pair<int , T> >& sp) const
	{
		HeapNode<T>* start = it;
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
	void PriorityQueue<T>::_walkNeighborCopy(HeapNode<T>*& it, copyNodes action, std::list<HeapNode<T>* >& sp) const
	{
		HeapNode<T>* start = it;
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
	void PriorityQueue<T>::_walkBaseCopy(HeapNode<T>*& it, HeapNode<T>*& prev, copyFunc action, std::list<std::pair<int , T> >& sp) const
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
	void PriorityQueue<T>::_walkBaseCopy(HeapNode<T>*& it, HeapNode<T>*& prev, copyNodes action, std::list<HeapNode<T>* >& sp) const
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
	void basicCopyFunc(HeapNode<T>* it, std::list<std::pair< int , T > >& sp)
	{
		sp.push_back(std::make_pair(it->key(),it->value()));
	}
	template <class T>
	void basicNodesFunc(HeapNode<T>* it, std::list<HeapNode<T>* >& sp)
	{
		sp.push_back(it);
	}

#endif



#endif