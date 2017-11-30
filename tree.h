#include <utility>
#ifndef TREE_BINARY_H
#define TREE_BINARY_H
#pragma warning(disable : 4348)
template <class KeyT = int, class ValueT = int> class BinaryTree;
template <class KeyT = int, class ValueT = int> class HaffmanTree;
//*********************BINARY NODE********************************************
template <class Key,class Value>
class BinaryNodeTree
{
	template <class KeyT, class ValueT> friend class BinaryTree;
	Key _key;
	Value _value;
	BinaryNodeTree<Key, Value> *_right, *_left, *_parent;

public:
	BinaryNodeTree(){};
	BinaryNodeTree(const Key& k, const Value& v) : _key(k), _value(v), _left(NULL), _right(NULL), _parent(NULL){};
	BinaryNodeTree(const BinaryNodeTree<Key, Value>& x);
	Key key()
	{
		return _key;
	}

	Value value()
	{
		return _value;
	}

	BinaryNodeTree <Key, Value>* right()
	{
		return _right;
	}
	BinaryNodeTree <Key, Value>* left()
	{
		return _left;
	}
	BinaryNodeTree <Key, Value>* parent()
	{
		return _parent;
	}
};


template <class Key,class Value>
BinaryNodeTree<Key,Value>::BinaryNodeTree(const BinaryNodeTree<Key, Value>& x)
{
	key = x->_key;
	value = x->_value;
	if (x->_left)
		left = new BinaryNodeTree<KeyT, ValueT>(x->left->_key, x->left->_value);
	if (x->_right)
		right = new BinaryNodeTree<KeyT, ValueT>(x->right->_key, x->right->_value);
	if (x->_parent)
		parent = new BinaryNodeTree<KeyT, ValueT>(x->parent->_key, x->parent->_value);
}

//*********************AVL NODE********************************************
template <class Key, class Value > class AvlNode
{
protected:
	unsigned char height;
	AvlNode <Key, Value> *_right, *_left;
	Key _key;
	Value _value;
public:
	template <class KeyT, class ValueT> friend class AvlTree;
	AvlNode():height(1){}
	AvlNode(const Key& k, const Value& v) : key(k),
		value(v), _left(0), _right(0),height(1){}
	AvlNode(const AvlNode<Key, Value>& x)
	{
		key = x.key;
		value = x.value;
		height = x.height;
		if (x._left)
			_left = new AvlNode<Key, Value>(x.left->_key, x.left->_value);
		if (x._right)
			_right = new AvlNode<Key, Value>(x.right->_key, x.right->_value);
	}
	Key key()
	{
		return _key;
	}
	Value value()
	{
		return value;
	}
	AvlNode <Key, Value>* right()
	{
		return left;
	}
	AvlNode <Key, Value>* left()
	{
		return right;
	}
	char balanceFactor();
protected:
	void _over_height();
};

template <class Key, class Value>
void AvlNode<Key, Value>::_over_height()
{
	char hleft = left->get_height();
	char hright = right->get_height();
	height = (hleft>hright ? hleft : hright) + 1;
}

template <class Key,class Value>
char AvlNode<Key, Value>::balanceFactor()
{
	return right->get_height() - left->get_height();
}

//**********************Basic Node******************************************
template <class KeyT,class ValueT>
struct BasicNode
{
	KeyT key;
	ValueT value;
	BasicNode<KeyT, ValueT>* left, *right, *parent;
	BasicNode(KeyT _k,ValueT _v) : key(_k), value(_v), left(NULL), right(NULL), parent(NULL){};
	BasicNode() : key(KeyT()), value(ValueT()), left(NULL), right(NULL), parent(NULL){};


};


//************************BINARY TREE*************************************

template <class KeyT, class ValueT>
class BinaryTree
{
protected:
	template <class KeyT, class ValueT> friend class BinaryNodeTree;
	
	BinaryNodeTree<KeyT, ValueT> *root;
	int _size;

	BinaryNodeTree<KeyT, ValueT>* copy(BinaryNodeTree<KeyT, ValueT>* x, BinaryNodeTree<KeyT, ValueT>* pred) const;

	BinaryNodeTree<KeyT, ValueT>* find_node(BinaryNodeTree<KeyT, ValueT>* n, const KeyT & val);

	BinaryNodeTree<KeyT, ValueT>* find_node(BinaryNodeTree<KeyT, ValueT>* n, const KeyT & key, const ValueT& val);

	void preorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<KeyT>& res, bool flag);

	void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<BinaryNodeTree<KeyT, ValueT>*>& res);

	void min_height(BinaryNodeTree<KeyT, ValueT>* it, int & min, int temp);

	void max_height(BinaryNodeTree<KeyT, ValueT>* it, int & max, int temp);

	void is_balanced(BinaryNodeTree<KeyT, ValueT>* it, int & min, int & max, int temp);

	void mark();

#ifdef _VECTOR_
	void getEdges(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<std::pair<KeyT, ValueT>, std::pair<KeyT, ValueT> > >& res);

	void getEdgesKeys(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, KeyT> >& res);

#endif
public:

	enum TRAVERSAL{INORDER,PREORDER,POSTORDER};

	size_t size() const
	{
		return _size;
	}

	BinaryTree() :root(0),_size(0){}

	BinaryTree(const BinaryTree<KeyT, ValueT>& x)
	{
		_size = 0;
		root = NULL;
		this->root = x.clone();
		root->_parent = NULL;
		this->_size = x._size;
	
	}

	void operator = (const BinaryTree<KeyT, ValueT>& x)
	{
		_size = 0;
		root = NULL;
		//BinaryTree<KeyT, ValueT> rez = copy(x.root, x);
		//rez._size = x.size();
		this->root = x.clone();
		root->_parent = NULL;
		this->_size = x._size;
	}

	BinaryTree(BinaryNodeTree<KeyT, ValueT>* x)
	{
		root = x;
		int count = 0;
		getSizeOfTree(this->root, count);
		_size = count;
		//_size = 1;
	}

	BinaryTree(const KeyT& k, const ValueT& v)
	{
		root = new BinaryNodeTree<KeyT, ValueT>(k, v);
		_size = 1;
	}

	//Сливает два дерева. В root2 Будет null
	void merge(BinaryNodeTree<KeyT, ValueT>* root2)
	{
		if (root2->_left != NULL)
			merge(root2->_left);
		if (root2->_right != NULL)
			merge(root2->_right);
		insert(root2->_key, root2->_value);
		delete root2;
		root2 = NULL;
	}

	//Сливает два дерева. В root2 Будет null
	void merge(BinaryTree<KeyT, ValueT>& root2)
	{
		this->merge(root2.root);
		root2._size = 0;
	}

	virtual ~BinaryTree()
	{
		if (_size != 0)
		{
			Delete(root);
			_size = 0;
		}
	}

	void insert(const KeyT &k, const ValueT &v = 0);

	BinaryNodeTree<KeyT, ValueT>* copy(BinaryTree<KeyT, ValueT>* x) const;

	BinaryNodeTree<KeyT, ValueT>* clone() const;

	void clear()
	{
		Delete(root);
	}

	void isEmpty()
	{
		return _size == 0;
	}

	std::pair<KeyT, ValueT> remove(BinaryNodeTree<KeyT, ValueT> *z);

	static BinaryNodeTree<KeyT, ValueT>* findMax(BinaryNodeTree<KeyT, ValueT> *x);

	static BinaryNodeTree<KeyT, ValueT>* findMin(BinaryNodeTree<KeyT, ValueT> *x);


	BinaryNodeTree<KeyT, ValueT>* findMax();

	BinaryNodeTree<KeyT, ValueT>* findMin();

	BinaryNodeTree<KeyT, ValueT>* find(const KeyT& val);

	BinaryNodeTree<KeyT, ValueT>* find(const KeyT& key, const ValueT& val);

	BinaryNodeTree<KeyT, ValueT>* prev(BinaryNodeTree<KeyT, ValueT>* x);

	BinaryNodeTree<KeyT, ValueT>* next(BinaryNodeTree<KeyT, ValueT>* x);

#ifdef _IOSTREAM_

	void print(BinaryNodeTree<KeyT, ValueT>* n);

	void print();
#endif



#ifdef _VECTOR_

	void BinaryTree<KeyT, ValueT>::getAllHeight(BinaryNodeTree<KeyT, ValueT>* n, std::vector<std::pair<std::pair<KeyT, ValueT>, int > >& data, int height);

	std::vector<std::pair<std::pair<KeyT, ValueT>, int > > getAllHeight();

	void inorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, ValueT>>& res);

	void preorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, ValueT>>& res);

	void postorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, ValueT>>& res);

	std::vector<std::pair<KeyT, ValueT> > getAllNodes(TRAVERSAL tr = TRAVERSAL::INORDER);

	std::vector<std::pair<KeyT, ValueT> > getPath(KeyT key);

	std::vector<std::pair<KeyT, ValueT> > getPath(KeyT key, ValueT val);

	std::vector<std::pair<std::pair<KeyT, ValueT>, std::pair<KeyT, ValueT> > > getEdges();

	std::vector<std::pair<KeyT, KeyT> > getEdgesKeys();

#ifdef _IOSTREAM_

	void printTree();

#endif
#endif

	int minHeight();

	int maxHeight();

	bool isBalanced();



	bool isIsomorph(BinaryTree<KeyT, ValueT> x);

	bool isEqual(BinaryNodeTree<KeyT, ValueT>* a, BinaryNodeTree<KeyT, ValueT>* b);

	bool isEqual (BinaryTree<KeyT, ValueT> b);

	static double countTrees(int n);

#if defined( _STRING_) && defined(FUNC_H) && defined(_SSTREAM_)

	std::string getBracketForm();

	void getBracketForm(BinaryNodeTree<KeyT, ValueT> *it, std::string& rez);

	static BinaryTree<KeyT, ValueT> recognizeBracketForm(std::string str);


#endif

	};

//Удаляет узел z из дерева
template <class KeyT = int, class ValueT = int>
std::pair<KeyT, ValueT> BinaryTree<KeyT, ValueT>::remove(BinaryNodeTree<KeyT, ValueT> *z)
{
	if (z == NULL)
		return std::make_pair(KeyT(),ValueT());
	BinaryNodeTree<KeyT, ValueT>* p = z->_parent;
	if (z->_left == 0 && z->_right == 0)
	{
		if (p == NULL)
		{
			root = NULL;
			return std::make_pair(z->_key,z->_value);
		}
		if (p->_left == z)
			p->_left = NULL;
		if (p->_right == z)
			p->_right = NULL;
		//если удаляем лист то просто обнуляем указатели родителя
	}
	else if (z->_left == 0 || z->_right == 0)
	{
		//если есть ровно один сын
		if (z->_left == NULL)
		{
			//если сын не левый а правый
			//соединяем родителя с сыном удаляемой вершины
			if (p == NULL)
			{
				root = z->_right;
				root->_parent = NULL;
				return std::make_pair(z->_key, z->_value);
			}
			if (p->_left == z)
			{
				p->_left = z->_right;
			}
			else
			{
				p->_right = z->_right;
			}
			z->_right->_parent = p;
			//обновляем указатель на родителя
		}
		else
		{
			//если сын левый
			if (p == NULL)
			{
				root = z->_left;
				root->_parent = NULL;
				return std::make_pair(z->_key, z->_value);
			}
			if (p->_left == z)
				p->_left = z->_left;
			else
				p->_right = z->_left;
			z->_left->_parent = p;
		}
	}
	else
	{
		BinaryNodeTree<KeyT, ValueT>* s = next(z);
		//s- узел,который является наиболее приближенным по ключу к удалямому элементу
		//справа (например если удаляем 7,то это  самое близкое значение его сыновей,но большее
		//например 8)
		z->_key = s->_key;
		z->_value = s->_value;
		if (s->_parent->_left == s)
		{
			s->_parent->_left = s->_right;
			if (s->_right != NULL)
			{
				s->_right->_parent = s->_parent;
			}
		}
		else
		{
			s->_parent->_right = s->_right;
			if (s->_right != NULL)
			{
				s->_right->_parent = s->_parent;
			}
		}

	}
	return std::make_pair(z->_key, z->_value);
}

//Функция вставляет ключ и значение в дерево
	template <class KeyT = int, class ValueT = int>
	void BinaryTree<KeyT, ValueT>::insert(const KeyT &k, const ValueT &v = 0)
	{
		BinaryNodeTree<KeyT, ValueT> * _new = new BinaryNodeTree<KeyT, ValueT>(k, v);
		BinaryNodeTree<KeyT, ValueT> * ptr = root;
		BinaryNodeTree<KeyT, ValueT> * ptr1 = ptr;
		_new->_parent = _new->_left = _new->_right = 0;		
		//1) Ищем куда вставить новый узел
		while (ptr != 0)
		{
			ptr1 = ptr;
			if (k < ptr->key())
				ptr = ptr->_left;
			else
				ptr = ptr->_right;
		}

		//2) Вставка в корень
		_new->_parent = ptr1;
		if (ptr1 == NULL)
		{
			root = _new;
		}
		//3) Определяем влево или в вправо
		else 
		{
			if (k < ptr1->key())
				ptr1->_left = _new;
			else
				ptr1->_right = _new;
		}
		_size++;
	}
	
	//Функция копирует дерево x в текущее
	template <class KeyT, class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::copy(BinaryTree<KeyT, ValueT>* x) const
	{
		return copy(x->root, x->root);
	}

	//функция копирует текущее дерево и возвращает указатель на корень
	template <class KeyT, class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::clone() const
	{
		return copy(root, root);
	}
	template <class KeyT, class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::copy(BinaryNodeTree<KeyT, ValueT>* x, BinaryNodeTree<KeyT, ValueT>* pred) const
	{
		if (x == NULL)
			return NULL;
		BinaryNodeTree<KeyT, ValueT>* new_node = new BinaryNodeTree<KeyT, ValueT>(x->key(), x->value());
		new_node->_parent = pred;
		new_node->_left = copy(x->_left, new_node);
		new_node->_parent = pred;
		new_node->_right = copy(x->_right, new_node);
		//	new_node->parent = pred;
		return new_node;
	}

	//Функция возвращает максимальный узел
	template <class KeyT, class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::findMax(BinaryNodeTree<KeyT, ValueT> *x)
	{
		while (x->_right)
			x = x->_right;
		return x;
	}

	//Функция возвращает максимальный узел
	template <class KeyT, class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::findMax()
	{
		BinaryNodeTree<KeyT, ValueT>* x = new BinaryNodeTree<KeyT, ValueT>;
		x = root;
		while (x->_right)
			x = x->_right;
		return x;
	}

	//Функция возвращает минимальный узел
	template <class KeyT = int, class ValueT = int>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::findMin(BinaryNodeTree<KeyT, ValueT> *x)
	{
		while (x->_left)
			x = x->_left;
		return x;
	}

	//Функция возвращает минимальный узел
	template <class KeyT = int, class ValueT = int>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::findMin()
	{
		BinaryNodeTree<KeyT, ValueT>* x = new BinaryNodeTree<KeyT, ValueT>;
		x = root;
		while (x->_left)
			x = x->_left;
		return x;
	}

	//Функция ищет узел с заданным ключом
	template <class KeyT = int, class ValueT = int>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find(const KeyT& val)
	{
		BinaryNodeTree<KeyT, ValueT>* x = find_node(root, val);
		return x;
	}

	//Функция ищет узел с заданным ключом и значением
	template <class KeyT = int, class ValueT = int>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find(const KeyT& key, const ValueT& val)
	{
		BinaryNodeTree<KeyT, ValueT>* x = find_node(root,key, val);
		return x;
	}

	template <class KeyT = int, class ValueT = int>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find_node(BinaryNodeTree<KeyT, ValueT>* n, const KeyT & val)
	{
		if (n == 0 || val == n->key())
			return n;
		if (val > n->key())
			return find_node(n->_right, val);
		else
			return find_node(n->_left, val);
	}

	template <class KeyT = int, class ValueT = int>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find_node(BinaryNodeTree<KeyT, ValueT>* n, const KeyT & key, const ValueT& val)
	{
		if (n == 0 || (key == n->key() && val == n->value()))
			return n;
		if (key > n->key())
			return find_node(n->_right,key, val);
		else
			return find_node(n->_left,key, val);
	}


	template <class KeyT,class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT,ValueT>::next(BinaryNodeTree<KeyT, ValueT>* node)
	{
		//логика такова что у элемента x(положем 12) если он имеет правого сына
		//то минимальный элемент правого сына будет следуйщим за корнем по возрастанию
		//              12
		//            /    \
		//           6     14
		//         /  \   /  \
		//        4    9 13  16
		//
		if (node == NULL)
			return NULL;
		if (node->_right != NULL) 
		{
			return next(node->_right);
		}
		return node;
	}

	template <class KeyT, class ValueT>
	BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::prev(BinaryNodeTree<KeyT, ValueT>* node)
	{
		//логика такова что у элемента x(положем 12) если он имеет левого сына
		//то максимвльный элемент левого сына будет предыдущий за корнем по возрастанию
		//              12
		//            /    \
				//           6     14
		//         /  \   /  \
				//        4    9 13  16
		//
		if (node == NULL)
			return NULL;
		if (node->_left != NULL) {
			return prev(node->_left);
		}
		return node;
	}

#ifdef _IOSTREAM_
	template <class KeyT = int, class ValueT = int>
	void BinaryTree<KeyT, ValueT>::print(BinaryNodeTree<KeyT, ValueT>* n)
	{
		if (n != 0)
		{
			print(n->_left);
			std::cout << "(" << n->key() << "," << n->value() << ")";
			print(n->_right);
		}
	}

	template <class KeyT = int, class ValueT = int>
	void BinaryTree<KeyT, ValueT>::print()
	{
		print(root);
	}

#endif
#ifdef _VECTOR_
	//Возвращает высоты всех вершин дерева
	//Аргумент 1: указатель на корень
	//Аргумент 2: возвращаемое значение
	//вектор: ((ключ,значение), высота)
	//Аргумент 3: ссылка на int инициализированная нулем
	template <class KeyT = int, class ValueT = int>
	void BinaryTree<KeyT, ValueT>::getAllHeight(BinaryNodeTree<KeyT, ValueT>* n, std::vector<std::pair<std::pair<KeyT, ValueT>, int > >& data,int height)
	{
		if (n)
		{
			/*inorder_traversal(root->left, res);
			res.push_back(root);
			inorder_traversal(root->right, res);*/
			getAllHeight(n->_left, data,height);
			data.push_back(std::make_pair(std::make_pair(n->_key, n->_value), ++height));
			getAllHeight(n->_right, data,height);
		}
	}

	//Возвращает высоты всех вершин дерева
	//в виде вектор: ((ключ,значение), высота)
	template <class KeyT = int, class ValueT = int>
	std::vector<std::pair<std::pair<KeyT, ValueT>, int > > BinaryTree<KeyT, ValueT>::getAllHeight()
	{
		int height = 0;
		std::vector<std::pair<std::pair<KeyT, ValueT>, int > > data;
		getAllHeight(root, data, height);
		return data;
	}

	template <class KeyT = int, class ValueT = int>
	std::vector<std::pair<KeyT, ValueT> > BinaryTree<KeyT, ValueT>::getAllNodes(TRAVERSAL tr)
	{
		std::vector<std::pair<KeyT, ValueT> > data;
		switch (tr)
		{
		case INORDER:
			inorder_traversal(root, data);
			break;
		case PREORDER:
			preorder_traversal(root, data);
			break;
		case POSTORDER:
			postorder_traversal(root, data);
			break;
		default:
			inorder_traversal(root, data);
		}
		return data;

	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, ValueT>>& res)//симметричный обход
	{
		if (root)
		{
			inorder_traversal(root->_left, res);
			res.push_back(std::make_pair(root->_key, root->_value));
			inorder_traversal(root->_right, res);
		}
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::preorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, ValueT>>& res)//симметричный обход
	{
		if (root)
		{
			
			res.push_back(std::make_pair(root->_key,root->_value));
			inorder_traversal(root->_left, res);
			inorder_traversal(root->_right, res);
		}
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::postorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, ValueT>>& res)//симметричный обход
	{
		if (root)
		{
			inorder_traversal(root->_left, res);
			inorder_traversal(root->_right, res);
			res.push_back(std::make_pair(root->_key, root->_value));
		}
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::preorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<KeyT>& res, bool flag)//в ширину
	{
		std::vector<BinaryNodeTree<KeyT, ValueT>*> queue;
		BinaryNodeTree<KeyT, ValueT>* it;
		queue.push_back(root);
		while (!queue.empty())
		{
			if (queue[0]->_left)
				queue.push_back(queue[0]->_left);
			if (queue[0]->_right)
				queue.push_back(queue[0]->_right);

			it = queue.front();
			int maxl = 0;
			int maxr = 0;
			if (it->_left)
				max_height(it->_left, maxl, 0);
			else
				maxl = -1;
			if (it->_right)
				max_height(it->_right, maxr, 0);
			else
				maxr = -1;
			res.push_back(maxl);
			res.push_back(maxr);

			queue.erase(queue.begin());
		}
	}

	//возвращает путь к ключу
	template<class KeyT, class ValueT>
	std::vector<std::pair<KeyT, ValueT> > BinaryTree<KeyT, ValueT>::getPath(KeyT key)
	{
		std::vector<std::pair<KeyT, ValueT> > path;
		BinaryNodeTree<KeyT, ValueT>* it = root;
		while ((it->_left && it->_right) != 0 || key != it->_key)
		{
			path.push_back(std::make_pair(it->_key, it->_value));
			if (key >= it->_key)
			{
				
				it = it->_right;
			}
			else
			{
				it = it->_left;
			}
		}
		return path;
	}

	//возвращает путь к вершине (ключ , значение)
	template<class KeyT, class ValueT>
	std::vector<std::pair<KeyT, ValueT> > BinaryTree<KeyT, ValueT>::getPath(KeyT key, ValueT val)
	{
		std::vector<std::pair<KeyT, ValueT> > path;
		BinaryNodeTree<KeyT, ValueT>* it = root;
		while ((it->_left && it->_right) != 0 || ((key != it->_key) || (val != it->_value)))
		{
			path.push_back(std::make_pair(it->_key, it->_value));
			if (key >= it->_key)
			{
				it = it->_right;
				if (key < it->_key)
					return std::vector<std::pair<KeyT, ValueT> >();
			}
			else
			{
				it = it->_left;
			}
		}
		return path;
	}

#ifdef _IOSTREAM_
	template <class KeyT = int, class ValueT = int> 
	void BinaryTree<KeyT, ValueT>::printTree()
	{
		std::vector<std::pair<std::pair<KeyT, ValueT>, int > > data;
		int height = 0;
		getAllHeight(root,data,height);
		
		for (size_t i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data[i].second; j++)
			{
				std::cout << "  ";
			}
			std::cout << "(" << data[i].first.first << "," << data[i].first.second << ")"<<std::endl;
		}
	}
#endif

	//возвращает список ребер дерева
	//вектор: пара ( вершина начало, вершина конец )
	//вершина начало, вершина конец : (ключ, значение)
	//Получает все ребра дерева в формате пара исхода(ключ значение) пара захода( ключ значение)
	template<class KeyT, class ValueT>
	std::vector<std::pair<std::pair<KeyT, ValueT>, std::pair<KeyT, ValueT> > > BinaryTree<KeyT, ValueT>::getEdges()
	{
		std::vector<std::pair<std::pair<KeyT, ValueT>, std::pair<KeyT, ValueT> > > res;
		getEdges(root, res);
		return res;
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::getEdges(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<std::pair<KeyT, ValueT>, std::pair<KeyT, ValueT> > >& res)
	{
		if (root)
		{
			res.push_back
				(std::make_pair
				(std::make_pair(root->_key, root->_value),
				std::make_pair(root->_parent->_key, root->_parent->_value)));
			getEdges(root->_left, res);
			getEdges(root->_right, res);
		}
	}


	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::getEdgesKeys(BinaryNodeTree<KeyT, ValueT>* root, std::vector<std::pair<KeyT, KeyT> >& res)
	{
		if (root)
		{
			res.push_back(std::make_pair(root->_key, root->_parent->_key));
			getEdgesKeys(root->_left, res);
			getEdgesKeys(root->_right, res);
		}
	}

	template<class KeyT, class ValueT>
	std::vector<std::pair<KeyT, KeyT> > BinaryTree<KeyT, ValueT>::getEdgesKeys()
	{
		std::vector<std::pair<KeyT, KeyT> > res;
		getEdgesKeys(root, res);
		return res;
	}

#endif

	//Определяет расстояние до самого близкого листа дерева
	template<class KeyT, class ValueT>
	int BinaryTree<KeyT, ValueT>::minHeight()
	{	
		int min = 99999999;
		min_height(root, min, 0);
		return min;
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::min_height(BinaryNodeTree<KeyT, ValueT>* it, int & min, int temp)
	{
		if (it)
		{
			if (min>temp && it->_left == NULL && it->_right == NULL)
			{
				min = temp;
			}
			min_height(it->_left, min, ++temp);
			temp--;
			min_height(it->_right, min, ++temp);
		}
	}

	//Определяет расстояние до саиого дальнего листа дерева
	template<class KeyT, class ValueT>
	int BinaryTree<KeyT, ValueT>::maxHeight()
	{
		int max = 0;
		max_height(root, max, 0);
		return max;
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::max_height(BinaryNodeTree<KeyT, ValueT>* it, int & max, int temp)
	{
		if (it)
		{
			if (max<temp)
			{
				max = temp;
			}
			max_height(it->left, max, ++temp);
			temp--;
			max_height(it->right, max, ++temp);
		}
	}

	//лпределяет является ли дерево сбалансированным
	template<class KeyT, class ValueT>
	bool BinaryTree<KeyT, ValueT>::isBalanced()
	{
		int min = 9999999;
		int max = 0;
		is_balanced(root, min, max, 0);
		if (max == min + 1)
		{
			return true;
		}
		else return false;
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::is_balanced(BinaryNodeTree<KeyT, ValueT>* it, int & min, int & max, int temp)
	{
		if (it)
		{
			if (min > temp && it->_left == NULL && it->_right == NULL)
			{
				min = temp;
			}
			if (max < temp)
			{
				max = temp;
			}
			is_balanced(it->_left, min, max, ++temp);
			--temp;
			is_balanced(it->_right, min, max, ++temp);
		}
		temp--;
	}

	
	

#if defined( _VECTOR_ ) && defined (_ALGORITHM_)
	//Проверка деревьев на изоморфизм
	template <class KeyT, class ValueT>
	bool BinaryTree<KeyT, ValueT>::isIsomorph(BinaryTree<KeyT, ValueT> x)
	{

		//1) Получить все ребра каждого дерева, при этом вместо ключей используется нумерация
		std::vector<std::pair<KeyT,KeyT>> prop1, prop2;
		BinaryTree<KeyT, ValueT> t_copy(clone()), x_copy(x.clone());
		t_copy.mark();
		x_copy.mark();
		prop1 = t_copy.getEdgesKeys();
		prop2 = x_copy.getEdgesKeys();

		//2) Если количество ребер не равно или они отстутствуют 
		//то деревья не изоморфны
		if (prop1.size() != prop2.size() || prop1.size() == 0)
			return false;

		//3) сортировка ребер
		std::sort(prop1.begin(), prop1.end());
		std::sort(prop2.begin(), prop2.end());

		//4) проверяем найдется ли для ребра(а б) из дерева 1 ребро (а б) или ( б а) из дерева 2
		//если нет то не изоморфны
		//иначе изоморфны
		for (int i = prop1.size() - 1; i >= 0; i--)
		{
			for (int j = prop2.size() - 1; j >= 0; j--)
			{
				if ((prop1[i].first == prop2[j].first && prop1[i].second == prop2[j].second) ||
					prop1[i].first == prop2[j].second && prop1[i].second == prop2[j].first)
				{
					prop1.pop_back();
					prop2.erase(prop2.begin() + i);
					break;
				}
			}
			if (prop1.size() != i)
				return false;
		}
		return true;
	}
#endif

	//помечает все вершины дерева
	template <class KeyT, class ValueT>
#ifdef _VECTOR_
	void BinaryTree<KeyT, ValueT>::mark()
	{
		std::vector<BinaryNodeTree<KeyT, ValueT>*> vertex;
		inorder_traversal(root, vertex);
		for (size_t i = 0; i < vertex.size(); i++)
		{
			vertex[i]->_key = i;
		}
	}
#endif
	//получает указатели на все узлы
	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNodeTree<KeyT, ValueT>* root, std::vector<BinaryNodeTree<KeyT, ValueT>*>& res)
	{
		if (root)
		{
			inorder_traversal(root->_left, res);
			res.push_back(root);
			inorder_traversal(root->_right, res);
		}
	}

	//проверяет равны ли два дерева
	template<class KeyT, class ValueT>
	bool BinaryTree<KeyT, ValueT>::isEqual(BinaryTree<KeyT, ValueT> b)
	{
		return isEqual(root, b.root);
	}

	//проверяет равны ли два дерева
	template<class KeyT, class ValueT>
	bool BinaryTree<KeyT, ValueT>::isEqual(BinaryNodeTree<KeyT, ValueT>* a, BinaryNodeTree<KeyT, ValueT>* b)
	{
		if ((a == NULL && b != NULL) || (a != NULL && b == NULL))
		{
			return false;
		}
		if (a == NULL && b == NULL) 
		{
			return true;
		}


		if (isEqual(a->_left, b->_left) == true && isEqual(a->_right, b->_right) == true)
		{
			if (a->_key == b->_key)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		return false;
	}

	//считаем максимальное количество деревьев из n вершин
	template<class KeyT, class ValueT>
	double BinaryTree<KeyT, ValueT>::countTrees(int n)
	{
		double temp = 1;
		for (int i = 0; i < n; i++)
		{
			temp = (2 * (2 * double(i) + 1)) / (double(i) + 2) * temp;
		}
		return temp;
	}

#if defined( _STRING_) && defined(FUNC_H) && defined(_SSTREAM_)

	//Функция кодирует дерево в скобочную последовательность
	template<class KeyT, class ValueT>
	std::string BinaryTree<KeyT, ValueT>::getBracketForm()
	{
		BinaryNodeTree<KeyT, ValueT> *it = root;
		std::string rez;
		getBracketForm(root, rez);
		return rez;
	}

	template<class KeyT, class ValueT>
	void BinaryTree<KeyT, ValueT>::getBracketForm(BinaryNodeTree<KeyT, ValueT> *it, std::string& rez)
	{
		rez += ItoS(it->_key);
		rez += ":";
		rez += ItoS(it->_value);
		rez += "(";
		if (it->_left)
			getBracketForm(it->_left, rez);
		else
			rez += " ";
		if (it->_right)
			getBracketForm(it->_right, rez);
		else
			rez += " ";
		rez += ")";
	}

	//Функция восстанавливает дерево из скобочной последовательности
	//раскодирует дерево.
	//если раскодироапть не удалось возвращает код
	//ошибки как value корневой вершины
	// 1 : лишние скобки
	// 2 : скобок недостаточно
	template <class KeyT,class ValueT>
	BinaryTree<KeyT, ValueT> BinaryTree<KeyT, ValueT>::recognizeBracketForm(std::string str)
	{

		std::vector<std::string> token;
		std::vector<std::string> elem;
		BinaryTree<KeyT, ValueT> tree;
		for (size_t i = 0, j = 0; i < str.size(); i++)
		{
			token.resize(j + 1);
			while (str[i] != '(' && i < str.size())
			{
				if (str[i] != ')' && str[i] != ' ')
					token[j].push_back(str[i]);
				i++;
			}
			j++;
		}
		for (size_t i = 0; i < token.size(); i++)
		{
			if (token[i].size() > 0)
			{
				elem = split(token[i], ':');
				tree.insert(StoI<KeyT>(elem[0]), StoI<ValueT>(elem[1]));
			}

		}
		return tree;
	}
	
	



	//*********************************HAFFMAN TREE****************************************
	template<class KeyT = int, class ValueT = int>
	class BasicTree
	{
	public:
		BasicNode<KeyT,ValueT>* root;
		
		BasicTree() :root(0), _size(0){}

		BasicTree(KeyT key, ValueT val) 
		{
			root = new BasicNode<KeyT, ValueT>(key, val);
			_size = 1;
		}

		BasicTree(const BasicTree<KeyT, ValueT>& x)
		{
			_size = 0;
			root = NULL;
			this->root = x.clone();
			root->parent = NULL;
			this->_size = x._size;


		}

		virtual ~BasicTree()
		{
			if (_size != 0)
			{
				Delete(root);
				_size = 0;
			}
		}

		BasicNode<KeyT, ValueT>* copy(BasicNode<KeyT, ValueT>* x, BasicNode<KeyT, ValueT>* pred) const;

		BasicNode<KeyT, ValueT>* copy(BasicTree<KeyT, ValueT> x) const;

		BasicNode<KeyT, ValueT>* clone() const;

		int insertLeft(const KeyT& key1, const ValueT& val1, const KeyT& key2, const ValueT& val2);

		int insertRight(const KeyT& key1, const ValueT& val1, const KeyT& key2, const ValueT& val2);

		int insert(const KeyT& key1, const ValueT& val1, const KeyT& key2, const ValueT& val2);

		BasicNode<KeyT, ValueT>* find(KeyT k, ValueT v);

		void find_traversal(BasicNode<KeyT, ValueT> *it, KeyT k, ValueT v, BasicNode<KeyT, ValueT>*& retval);

	
#ifdef _VECTOR_
		void recursive_walk(const KeyT& k, const ValueT& v, std::vector<bool> res, BinaryNodeTree<KeyT, ValueT>* it, std::vector<bool>& retval);

		std::vector<bool> path(const KeyT& k, const ValueT& v);//создает битовую строку

		BasicTree<KeyT, ValueT>* mark();

#endif

#if defined (_STRING_) && defined (FUNC_H) && defined (_SSTREAM_)

		//Функция кодирует дерево в скобочную последовательность
		std::string getBracketForm();

		void getBracketForm(BasicNode<KeyT, ValueT> *it, std::string& rez);

		static BasicTree<KeyT, ValueT> recognizeBracketForm(std::string code);
#endif

	private:
		size_t _size;
	};

#if defined (_STRING_) && defined (FUNC_H) && defined (_SSTREAM_)

	//Функция кодирует дерево в скобочную последовательность
	template<class KeyT, class ValueT>
	std::string BasicTree<KeyT, ValueT>::getBracketForm()
	{
		BasicNode<KeyT, ValueT> *it = root;
		std::string rez;
		getBracketForm(root, rez);
		return rez;
	}

	template<class KeyT, class ValueT>
	void BasicTree<KeyT, ValueT>::getBracketForm(BasicNode<KeyT, ValueT> *it, std::string& rez)
	{
		rez += ItoS(it->key);
		rez += ":";
		rez += ItoS(it->value);
		rez += "(";
		if (it->left)
			getBracketForm(it->left, rez);
		else
			rez += " ";
		if (it->right)
			getBracketForm(it->right, rez);
		else
			rez += " ";
		rez += ")";
	}

	//Функция восстанавливает дерево из скобочной последовательности
	//раскодирует дерево.
	//если раскодироапть не удалось возвращает код
	//ошибки как value корневой вершины
	// 1 : лишние скобки
	// 2 : скобок недостаточно
	template <class KeyT, class ValueT>
	BasicTree<KeyT, ValueT> BasicTree<KeyT, ValueT>::recognizeBracketForm(std::string code)
	{
		BasicTree<KeyT, ValueT> rez;
		int check = check_stack_correct(code);
		int size = 0;
		if (check != 0)
			rez.root = new BasicNode<KeyT, ValueT>(KeyT(), check);
		else
		{
			BasicNode<KeyT, ValueT>* prev = NULL;
			recursiveEncoder(rez.root, code, prev, 0, size);
			rez._size = size;
		}
		return rez;
	}

#endif

#ifdef _STRING_

	//проверяет корректность скобочной последовательности
	int check_stack_correct(const std::string& code)
	{
		int h = 0;
		for (size_t i = 0; i < code.size(); i++)
		{
			if (code[i] == '(')
				h++;
			else if (code[i] == ')')
				h--;
		}
		if (h > 0)
			return 1;
		else if (h < 0)
			return 2;
		else return 0;
	}

	//вырезает из последовательности вида (()())(()())
	// кусок вида (()())
	std::string stack_cutter(std::string& code)
	{
		if (code.empty())
			return std::string();
		if (code[0] == ' ')
		{
			return std::string(" ");
		}
		int stack = 0;
		bool flag = true;
		int i = 0;
		std::string rez;
		char c;
		while (stack || flag)
		{
			c = code[i++];
			switch (c)
			{
			case '(':
				stack++;
				flag = false;
				break;
			case ')':
				stack--;
				break;
			}
			rez.push_back(c);
			if (i == code.size())
				return rez;
		}
		return rez;
	}

	template <class KeyT,class ValueT>
	void recursiveEncoder(BasicNode<KeyT, ValueT> *&it, std::string code, BasicNode<KeyT, ValueT> *prev,char dir,int &size)
	{
		if (!isNullToken(code))
		{
			int pos = code.find_first_of(':');
			std::string key = code.substr(0, pos);
			code.erase(0, pos + 1);
			pos = code.find_first_of('(');
			std::string val = code.substr(0, pos);
			code.erase(0, pos + 1);
			code.pop_back();
			KeyT _key = StoI<KeyT>(key);
			ValueT _val = StoI<ValueT>(val);
			it = new BasicNode<KeyT, ValueT>(_key, _val);
			size++;
			it->parent = prev;
			if (dir == 1)
				prev->left = it;
			if (dir == 2)
				prev->right = it;
			std::string new_code = stack_cutter(code);
			code.erase(0, new_code.size());
			recursiveEncoder(it->left, new_code, it,1,size);
			recursiveEncoder(it->right, code, it,2,size);
		}
	}

	bool isNullToken(const std::string& code)
	{
		if (code != "  " && code != "" && code != " ")
			return false;
		else
			return true;
	}

#endif

	//Функция копирует дерево x в текущее
	template <class KeyT, class ValueT>
	BasicNode<KeyT, ValueT>* BasicTree<KeyT, ValueT>::copy(BasicTree<KeyT, ValueT> x) const
	{
		return copy(x.root, x.root);
	}

	//функция копирует текущее дерево и возвращает указатель на корень
	template <class KeyT, class ValueT>
	BasicNode<KeyT, ValueT>* BasicTree<KeyT, ValueT>::clone() const
	{
		return copy(root, root);
	}
	template <class KeyT, class ValueT>
	BasicNode<KeyT, ValueT>* BasicTree<KeyT, ValueT>::copy(BasicNode<KeyT, ValueT>* x, BasicNode<KeyT, ValueT>* pred) const
	{
		if (x == NULL)
			return NULL;
		BasicNode<KeyT, ValueT>* new_node = new BasicNode<KeyT, ValueT>(x->key, x->value);
		new_node->parent = pred;
		new_node->left = copy(x->left, new_node);
		new_node->parent = pred;
		new_node->right = copy(x->right, new_node);
		return new_node;
	}

	//ищет узел ( key1,value1 ). Если найдет то вставляет слева узел (key2,val2)
	//если слева уже есть узел просто меняет ключи
	template <class KeyT, class ValueT>
	int BasicTree<KeyT, ValueT>::insertLeft(const KeyT& key1, const ValueT& val1, const KeyT& key2, const ValueT& val2)
	{
		BasicNode<int, int>* x = find_traversal(key1, val1);
		if (x)
		{
			if (x->left)
			{
				x->left->key = key2;
				x->left->value = val2;
				x->left->parent = x;
			}
			else
			{
				x->left = new BasicNode<int, int>(key2, val2);
				x->left->parent = x;
			}
		}
		else return 0;
		return 1;
	}

	//ищет узел ( key1,value1 ). Если найдет то вставляет справа узел (key2,val2)
	//если слева уже есть узел просто меняет ключи
	template <class KeyT, class ValueT>
	int insertRight(const KeyT& key1, const ValueT& val1,const KeyT& key2,const ValueT& val2)
	{
		BasicNode<int, int>* x = find_traversal(key1, val1);
		if (x)
		{
			if (x->right)
			{
				x->right->key = key2;
				x->right->value = val2;
				x->right->parent = x;
			}
			else
			{
				x->right = new BasicNode<int, int>(key2, val2);
				x->right->parent = x;
			}
		}
		else return 0;
		return 1;
	}

	//ищет узел ( key1,value1 ). Если найдет то вставляет слева или справа ( где свободно) узел (key2,val2)
	template <class KeyT, class ValueT>
	int insert(const KeyT& key1, const ValueT& val1, const KeyT& key2, const ValueT& val2)
	{
		BasicNode<int, int>* x = find_traversal(key1, val1);
		if (x)
		{
			if (!x->left)
			{
				x->left = new BasicNode<int, int>(key2, val2);
				x->left->parent = x;
			}
			else if (!x->right)
			{
				x->right = new BasicNode<int, int>(key2, val2);
				x->right->parent = x;
			}
			else
				return 0;
		}
		else 
			return 0;
		return 1;
	}

#ifdef _VECTOR_
	//возвращает путь к вершине в формате  битовой строки ( 0 влево , 1 вправо)
	template<class KeyT,class ValueT>
	std::vector<bool> path(const KeyT& k, const ValueT& v)//создает битовую строку
	{
		std::vector<bool> rez;
		std::vector<bool> path;
		BasicNode<KeyT,ValueT>* it = root;
		recursive_walk(k, v, buff, it, res);
		return res;
	}

	template<class KeyT, class ValueT>
	void recursive_walk(const KeyT& k, const ValueT& v, std::vector<bool> res, BinaryNodeTree<KeyT, ValueT>* it, std::vector<bool>& retval)
	{
		if (it)//Если дерево сушествует
		{
			if (it->key == k && it->value == v)
			{
				retval = res;
				return;
			}
			res.push_back(false);
			recursive_walk(k, v, res, it->left, retval);
			res.pop_back();
			res.push_back(true);
			recursive_walk(k, v, res, it->right, retval);
		}
	}

	//помечает вершины дерева
	template<class KeyT, class ValueT>
	BasicTree<KeyT, ValueT>* mark()
	{
		BasicTree<KeyT, ValueT>* a = this;
		std::vector< BasicNode<KeyT, ValueT>*> queue;
		queue.push_back(root);
		for (size_t i = 0; i < queue.size(); i++)
		{
			if (queue[i]->left)
				queue.push_back(queue[i]->left());
			if (queue[i]->right())
				queue.push_back(queue[i]->right());
		}
		size_t count = 1;
		for (int i = queue.size() - 1; i >= 0; i--)
		{
			queue[i]->key = count++;
		}
		return a;
	}
#endif

	template <class KeyT, class ValueT>
	BasicNode<KeyT, ValueT>*  BasicTree<KeyT, ValueT>::find(KeyT k, ValueT v)
	{
		BasicNode<KeyT, ValueT>* retval = NULL;
		find_traversal(root, k, v, retval);
		return retval;
	}
	template <class KeyT, class ValueT>
	void  BasicTree<KeyT, ValueT>::find_traversal(BasicNode<KeyT, ValueT> *it, KeyT k, ValueT v, BasicNode<KeyT, ValueT>*& retval)
	{
		if (it)
		{
			if (it->key == k && it->value == v)
			{
				retval = it;
				return;
			}
			find_traversal(it->left, k, v, retval);
			find_traversal(it->right, k, v, retval);
		}
	}

#endif
	/*



//*********************************HAFFMAN TREE****************************************
template<class KeyT = int,class ValueT = int>
class HaffmanTree : public BinaryTree<KeyT, ValueT>{
public:
	template <class KeyT, class ValueT> friend class BianryNode;
	template <class KeyT, class ValueT>
	friend void set_key(BinaryNodeTree<KeyT, ValueT>* tree, KeyT new_key);
	template <class KeyT, class ValueT>
	friend void set_val(BinaryNodeTree<KeyT, ValueT>* tree, ValueT val);
	HaffmanTree() :BinaryTree(){}
	HaffmanTree(const BinaryTree<KeyT, ValueT>& x) :BinaryTree(x){}
	HaffmanTree(const BinaryNodeTree<KeyT, ValueT>*& x) :BinaryTree(x){}
	HaffmanTree(const KeyT& k, const ValueT& v) :BinaryTree(k, v){}
	BinaryNodeTree<KeyT, ValueT>* find_min();
	BinaryNodeTree<KeyT, ValueT>* find_traversal(KeyT k, ValueT v);
	void find_traversal(BinaryNodeTree<KeyT, ValueT> *it, KeyT k, ValueT v, BinaryNodeTree<KeyT, ValueT>*& retval);
	~HaffmanTree(){};


	



#ifdef BITS_H
	Bits create_bitpath_if_val_string(const KeyT& k, const ValueT& v)//создает битовую строку из дерева(применимо к деревьям с 
		//соблюдением принципов кучи и с ключем - строкой
	{
		Bits res(0);
		auto it = root;
		walk(k, v, it, res);
		return res;
	}
#ifdef _VECTOR_
	
#endif
protected:

	
	void walk(const KeyT& k, const ValueT& v, BinaryNodeTree<KeyT, ValueT>* it, Bits& retval)
	{
		char a = v[0];
		size_t check = -1;
		while (it)
		{
			if (it->get_left()->get_val().find(a) != check )
			{
				it = it->get_left();
				retval.Add(false);
			}
			else if (it->get_right()->get_val().find(a) != check)
			{
				it = it->get_right();
				retval.Add(true);
			}
			if(it->get_key() == k && it->get_val() == v)
				return;

		}
	}
	
#endif
};
template <class KeyT,class ValueT>
BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::copy(BinaryNodeTree<KeyT, ValueT>* x)
{
	return copy(x,x);
}
template <class KeyT, class ValueT>
BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::clone()
{
	return copy(root,root);

}
template <class KeyT, class ValueT>
BinaryNodeTree<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::copy(BinaryNodeTree<KeyT, ValueT>* x, BinaryNodeTree<KeyT, ValueT>* pred)
{
	if (x == NULL)
		return NULL;
	BinaryNodeTree<KeyT, ValueT>* new_node = new BinaryNodeTree<KeyT, ValueT>(x->get_key(), x->get_val());
	new_node->parent = pred;
	new_node->left = copy(x->left,new_node);
	new_node->parent = pred;
	new_node->right = copy(x->right,new_node);
//	new_node->parent = pred;
	return new_node;
}


template <class KeyT,class ValueT>
BinaryNodeTree<KeyT, ValueT>* HaffmanTree<KeyT,ValueT>::find_min()
{
	std::vector< BinaryNodeTree<KeyT, ValueT>*> queue;
	BinaryNodeTree<KeyT, ValueT>* min_val = new BinaryNodeTree<KeyT, ValueT>(root->get_key(), root->get_val());
	queue.push_back(root);
	for (size_t i = 0; i < queue.size(); i++)
	{
		if (queue[i]->get_left())
			queue.push_back(queue[i]->get_left());
		if (queue[i]->get_right())
			queue.push_back(queue[i]->get_right());
	}
	for (size_t i = 0; i < queue.size(); i++)
	{
		if (queue[i]->get_key() < min_val->get_key())
			min_val = queue[i];
	}
	return min_val;
}

template <class KeyT,class ValueT>
void set_key(BinaryNodeTree<KeyT, ValueT>* tree, KeyT new_key)
{
	tree->key = new_key;

}
template <class KeyT, class ValueT>
void set_val(BinaryNodeTree<KeyT, ValueT>* tree, ValueT val)
{
	tree->value = val;

}
//***********************************AVL TREE******************************************
template<class KeyT, class ValueT> class AvlTreeBase
{
	AvlNode<KeyT, ValueT>* root;
	template <class KeyT, class ValueT> friend class AvlNode;
public:
	virtual ~AvlTreeBase()
	{
		Delete(root);
	}
	AvlTreeBase() :root(0){}
	AvlTreeBase(const AvlTreeBase<KeyT, ValueT>& x)
	{
		root = new AvlNode<KeyT, ValueT>(x.root->key, x.root->value);
	}
	AvlTreeBase(const KeyT& k, const ValueT& v)
	{
		root = new AvlNode<KeyT, ValueT>(k, v);
	}
	AvlNode<KeyT, ValueT>* get_root()
	{
		return root;
	}
	void insert( KeyT k, ValueT v)
	{
		root = _insert(root, k, v);
	}

	AvlNode<KeyT, ValueT>* remove(KeyT k)
	{
		AvlNode<KeyT, ValueT>* ret = remove(root, k);
		return ret;
	}

	AvlNode<KeyT, ValueT>* findmin(AvlNode<KeyT, ValueT>* p) // поиск узла с минимальным ключом в дереве p 
	{
		return p->left ? findmin(p->left) : p;
	}

	AvlNode<KeyT, ValueT>* removemin(AvlNode<KeyT, ValueT>* p) // удаление узла с минимальным ключом из дерева p
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	AvlNode<KeyT, ValueT>* remove(AvlNode<KeyT, ValueT>* p, KeyT k)
	{
		if (!p) return NULL;
		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else 
		{
			AvlNode<KeyT, ValueT>* q = p->left;
			AvlNode<KeyT, ValueT>* r = p->right;
			delete p;
			if (!r) return q;
			AvlNode<KeyT, ValueT>* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

#if defined(_IOSTREAM_) && defined(_WINDOWS_)
	void print()
	{
		_print(root, 37, 5, 2, 'k');
	}
#endif
	ValueT find(KeyT k)
	{
		AvlNode <KeyT, ValueT>* it = root;
		while (it)
		{
			if (it->key > k)
				it = it->left;
			else if (it->key < k)
				it = it->right;
			else return it->value;
		}
		return ValueT();
	}

#undef min
	ValueT min()
	{
		AvlNode<KeyT, ValueT>* it = root;
		return _min(it)->get_val();
	}
#undef max
	ValueT max()
	{
		AvlNode<KeyT, ValueT>* it = root;
		return _max(it)->get_val();
	}
protected:
	AvlNode<KeyT,ValueT> *right_rotation(AvlNode<KeyT,ValueT>* x)
	{
		/*
					x                    Y
				   / \                  / \
				 Y     C			   A    x
				/ \			---->	 /	   / \ 
			   A   B               v       B   C
			 /
			V
		*/
/*		AvlNode<KeyT, ValueT> *y = x->left;
		x->left = y->right;
		y->right = x;
		x->_over_height();
		y->_over_height();
		return y;
	}
	AvlNode<KeyT, ValueT>* left_rotation(AvlNode<KeyT, ValueT>* y)
	{
		AvlNode<KeyT, ValueT> *x = y->right;
		y->right = x->left;
		x->left = y;
		x->_over_height();
		y->_over_height();
		return x;
	}
	AvlNode<KeyT, ValueT>* balance(AvlNode<KeyT, ValueT> *x)
	{
		x->_over_height();
		if (x->balance_factor() == 2)
		{
			if (x->right->balance_factor()<0) x->right = right_rotation(x->right);
			return left_rotation(x);
		}
		if (x->balance_factor() == -2)
		{
			if (x->left->balance_factor()>0) x->left = left_rotation(x->left);
			return right_rotation(x);
		}
		return x;
	}
	AvlNode<KeyT, ValueT> *_insert(AvlNode<KeyT, ValueT> *x, KeyT k, ValueT v)
	{
		if (!x) return new AvlNode<KeyT, ValueT>(k, v);
		if (k<x->key) x->left = _insert(x->left, k, v);
		else x->right = _insert(x->right, k, v);
		return balance(x);
	}
#if defined(_IOSTREAM_) && defined(_WINDOWS_)
	void _print(AvlNode<KeyT, ValueT> * a, int x, int y, int b, char c)
	{
		if (a)//Если дерево сушествует
		{
			if (b>0 && c != 'k')
			{
				if (c == 'l')x -= 10;//Если запись идёт влево то уменьшаем координату x на 10
				else x += 10;//иначе увеличиваем
			}
			else if (c != 'k')
			if (c == 'l')x -= 4;//если интервал для следуйшего уровня равен нулю то отсупаем по два
			else x += 4;
			GoToXY(x, y += 2);
			b--;//уменьшаем интервал для размещения элементов следуйшего уровня
			std::cout << a->get_key();
			_print(a->get_left(), x, y, b, 'l');//заходим в правое поддерево
			_print(a->get_right(), x, y, b, 'r');//заходим в левое поддерево
		}
	}
	void GoToXY(int x, int y)
	{
		HANDLE StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord = { x, y };
		SetConsoleCursorPosition(StdOut, coord);
	}
#endif
	AvlNode<KeyT,ValueT>* _min(AvlNode<KeyT, ValueT> *it)
	{
		return it->left ? _min(it->left) : it;
	}
	AvlNode<KeyT, ValueT>* _max(AvlNode<KeyT, ValueT> *it)
	{
		return it->right ? _max(it->right) : it;
	}
	void Delete(AvlNode<KeyT,ValueT> *p)
	{
		if (p != NULL)
		{
			Delete(p->left);
			Delete(p->right);
			delete p;
		}
	}
};*/

template <class KeyT,class ValueT>
void Delete(BinaryNodeTree<KeyT, ValueT> *p)
{
	if (p != NULL)
	{
		Delete(p->left());
		Delete(p->right());
		delete p;
	}
}

template <class KeyT, class ValueT>
void Delete(BasicNode<KeyT, ValueT> *p)
{
	if (p != NULL)
	{
		Delete(p->left);
		Delete(p->right);
		delete p;
	}
}

//Возвращает размер дерева
template <class KeyT,class ValueT>
void getSizeOfTree(BinaryNodeTree<KeyT, ValueT> *root, int & count)
{
	if (root)
	{
		getSizeOfTree(root->left(), count);
		++count;
		getSizeOfTree(root->right(), count);
	}
}

#endif