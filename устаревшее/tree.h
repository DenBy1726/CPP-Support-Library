#ifndef TREE_BINARY_H
#define TREE_BINARY_H
#pragma warning(disable : 4348)
template <class KeyT = int, class ValueT = int> class BinaryTree;
template <class KeyT = int, class ValueT = int> class HaffmanTree;
//*********************BINARY NODE********************************************
template <class KeyT = int, class ValueT = int> class BinaryNode{
protected:
	template <class KeyT, class ValueT> friend class HaffmanTree;
	BinaryNode <KeyT, ValueT> *right, *left, *parent;
	KeyT key;
	ValueT value;
public:
	template <class KeyT, class ValueT>
	friend void set_val(BinaryNode<KeyT, ValueT>* tree, ValueT val);
	template <class KeyT, class ValueT>
	friend void set_key(BinaryNode<KeyT, ValueT>* tree, KeyT new_key);
	template <class KeyT2 = int, class ValueT2 = int> friend class BinaryTree;
	BinaryNode(){}
	BinaryNode(const KeyT& k, const ValueT& v) : key(k),
		value(v), left(0), right(0), parent(0){}
	BinaryNode(const BinaryNode<KeyT, ValueT>& x);
	virtual ~BinaryNode()
	{
		//delete right;
		//delete left;
		//delete parent;
	}
	KeyT get_key();//получить ключ
	ValueT get_val();//получить значение,хранимое по ключу
	BinaryNode <KeyT, ValueT>* get_right();
	BinaryNode <KeyT, ValueT>* get_left();
	BinaryNode <KeyT, ValueT>* get_parent();
};
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT,ValueT>::BinaryNode(const BinaryNode<KeyT, ValueT>& x)
{
	key = x->key;
	value = x->value;
	if (x->left)
		left = new BinaryNode<KeyT, ValueT>(x->left->key, x->left->value);
	if (x->right)
		right = new BinaryNode<KeyT, ValueT>(x->right->key, x->right->value);
	if (x->parent)
		parent = new BinaryNode<KeyT, ValueT>(x->parent->key, x->parent->value);
}
template <class KeyT = int, class ValueT = int>
KeyT BinaryNode<KeyT,ValueT>::get_key()
{
	return key;
}
template <class KeyT = int, class ValueT = int>
BinaryNode <KeyT, ValueT>* BinaryNode<KeyT, ValueT>::get_left()
{
	return left;
}
template <class KeyT = int, class ValueT = int>
BinaryNode <KeyT, ValueT>* BinaryNode<KeyT, ValueT>::get_right()
{
	return right;
}
template <class KeyT = int, class ValueT = int>
BinaryNode <KeyT, ValueT>* BinaryNode<KeyT, ValueT>::get_parent()
{
	return parent;
}
template <class KeyT = int, class ValueT = int>
ValueT BinaryNode<KeyT, ValueT>::get_val()
{
	return value;
}
//*********************AVL NODE********************************************
template <class KeyT = int, class ValueT = int> class AvlNode
{
protected:
	unsigned char height;
	AvlNode <KeyT, ValueT> *right, *left;
	KeyT key;
	ValueT value;
public:
	template <class KeyT, class ValueT> friend class AvlTreeBase;
	AvlNode():height(1){}
	AvlNode(const KeyT& k, const ValueT& v) : key(k),
		value(v), left(0), right(0),height(1){}
	AvlNode(const AvlNode<KeyT, ValueT>& x)
	{
		key = x.key;
		value = x.value;
		height = x.height;
		if (x.left)
			left = new AvlNode<KeyT, ValueT>(x.left->key, x.left->value);
		if (x.right)
			right = new AvlNode<KeyT, ValueT>(x.right->key, x.right->value);
	}
	virtual ~AvlNode()
	{
		//delete right;
		//delete left;
		//delete parent;
	}
	KeyT get_key();//получить ключ
	ValueT get_val();//получить значение,хранимое по ключу
	AvlNode <KeyT, ValueT>* get_right();
	AvlNode <KeyT, ValueT>* get_left();
	unsigned char get_height();
	char balance_factor();
protected:
	void _over_height();
};
template <class KeyT = int, class ValueT = int>
void AvlNode<KeyT, ValueT>::_over_height()
{
	char hleft = left->get_height();
	char hright = right->get_height();
		height = (hleft>hright ? hleft : hright) + 1;
}
template <class KeyT = int, class ValueT = int>
char AvlNode<KeyT, ValueT>::balance_factor()
{
	return right->get_height() - left->get_height();
}
template <class KeyT = int, class ValueT = int>
unsigned char AvlNode<KeyT,ValueT>::get_height()
{
	return this ? height : 0;
}
template <class KeyT = int, class ValueT = int>
KeyT AvlNode<KeyT, ValueT>::get_key()
{
	return key;
}
template <class KeyT = int, class ValueT = int>
AvlNode <KeyT, ValueT>* AvlNode<KeyT, ValueT>::get_left()
{
	return left;
}
template <class KeyT = int, class ValueT = int>
AvlNode <KeyT, ValueT>* AvlNode<KeyT, ValueT>::get_right()
{
	return right;
}
template <class KeyT = int, class ValueT = int>
ValueT AvlNode<KeyT, ValueT>::get_val()
{
	return value;
}
template <class KeyT = int, class ValueT = int>
//************************BINARY TREE*************************************
class BinaryTree{
protected:
	BinaryNode<KeyT, ValueT> *root;
public:
	BinaryTree() :root(0){}
	BinaryTree(const BinaryTree<KeyT, ValueT>& x)
	{
		//root = new BinaryNode<KeyT, ValueT>(x.root->key, x.root->value);
		root = x->clone();
	}
	BinaryTree(BinaryNode<KeyT, ValueT>* x)
	{
		//root = new BinaryNode<KeyT, ValueT>(x.root->key, x.root->value);
		root = x;
	}
	BinaryTree(const KeyT& k, const ValueT& v)
	{
		root = new BinaryNode<KeyT, ValueT>(k, v);
	}
	BinaryNode<KeyT, ValueT>* merge(BinaryNode<KeyT, ValueT>* n1, BinaryNode<KeyT, ValueT>* n2)
	{
		BinaryNode<KeyT, ValueT>  *head1, *head2;
		//prev = head1 = 0;// spine(n1, prev, head1);
		//prev = head2 = 0;// spine(n2, prev, head2
		head1 = n1;
		head2 = n2;
		root->left = head1;
		root->left->parent = root;
		root->right = head2;
		root->right->parent = root;
		return root;
		//return mergeSpines(head1, head2);
	}
	BinaryNode<KeyT, ValueT>* merge_left(BinaryNode<KeyT, ValueT>* n1)
	{
		BinaryNode<KeyT, ValueT>  *head1;
		head1 = n1;
		root->left = head1;
		root->left->parent = root;
		return root;
	}
	BinaryNode<KeyT, ValueT>* merge_right(BinaryNode<KeyT, ValueT>* n1)
	{
		BinaryNode<KeyT, ValueT>  *head1;
		head1 = n1;
		root->right = head1;
		root->right->parent = root;
		return root;
	}
	BinaryNode<KeyT, ValueT>* swap()
	{
		BinaryNode<KeyT, ValueT>  *temp;
		temp = root->right;
		root->right = root->left;
		root->left = temp;
		return root;
	}
		
protected:
	BinaryNode<KeyT, ValueT>* copy(BinaryNode<KeyT, ValueT>* x,BinaryNode<KeyT,ValueT>* pred);
public:
	virtual ~BinaryTree()
	{
		Delete(root);
	}
public:
	BinaryNode<KeyT, ValueT>* get_root();
	void insert(const KeyT &k, const ValueT &v = 0);
	void insert(const  BinaryNode<KeyT, ValueT>& lc, const  BinaryNode<KeyT, ValueT>& rc, const KeyT &k, const ValueT &v = 0);
	BinaryNode<KeyT, ValueT>* cut(BinaryNode<KeyT, ValueT> *z);
	BinaryNode<KeyT, ValueT>* find_max(BinaryNode<KeyT, ValueT> *x);
	BinaryNode<KeyT, ValueT>* find_max();
	BinaryNode<KeyT, ValueT>* copy(BinaryNode<KeyT, ValueT>* x);
	BinaryNode<KeyT, ValueT>* clone();
	BinaryNode<KeyT, ValueT>* find_min(BinaryNode<KeyT, ValueT> *x);
	//template <class KeyT = int, class ValueT = int>
	BinaryNode<KeyT, ValueT>* find_min();
	BinaryNode<KeyT, ValueT>* find(const KeyT& val);
	BinaryNode<KeyT, ValueT>* find_node(BinaryNode<KeyT, ValueT>* n, const KeyT & val);
	void print(BinaryNode<KeyT, ValueT>* n);
	int min_height();
	void min_height(BinaryNode<KeyT, ValueT>* it, int & min, int temp);
	int max_height();
	void max_height(BinaryNode<KeyT, ValueT>* it, int & min, int temp);
	bool is_balanced();
	void is_balanced(BinaryNode<KeyT, ValueT>* it, int & min,int & max,int temp);
#ifdef _VECTOR_
	//ОБХОДЫ(возврат вектора с номерами ключей)
	std::vector<KeyT> preorder_traversal();//в ширину
	std::vector<KeyT> inorder_traversal();//симметричный обход
	std::vector<KeyT> postorder_traversal();//обход в глубину
	std::vector<KeyT>traversal();//прямой обход*/
	std::vector<std::pair<KeyT, ValueT>> GetEdges();
	std::vector<KeyT> GetVertex();
	std::vector<std::pair<int, std::pair<int, int>>> _PrintGetVertex(int height);
	void preorder_traversal(BinaryNode<KeyT, ValueT>* root,std::vector<KeyT>& res);//в ширину
	void preorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res, bool flag);
	void inorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res);//симметричный обход
	void inorder_traversal(BinaryNode<KeyT, ValueT>*root, std::vector<std::pair<int, int>>& res);
	void inorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<BinaryNode<KeyT, ValueT>*>& res);
	void inorder_traversal(BinaryNode<KeyT, ValueT>*root, std::vector<int>& res,bool flag);
	void postorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res);//обход в глубину
	void traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res);//прямой обход*/
	void GetEdges(BinaryNode<KeyT, ValueT>* root, std::vector<std::pair<KeyT, KeyT>>& res, KeyT ignored);
	void GetVertex(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res);
	std::vector<int> getPrufferCode();
	void _PrintGetVertex(BinaryNode<KeyT, ValueT>* root, std::vector<std::pair<int, std::pair<int, int>>>& res, int k1, int k2,int k3);
	bool isIsomorph(BinaryTree<KeyT, ValueT>* x);
	std::vector<int> getTreeIsoCode();
	void mark();
#endif
protected:
	void Delete(BinaryNode<KeyT, ValueT> *p)
	{
		if (p != NULL)
		{
			Delete(p->left);
			Delete(p->right);
			delete p;
		}
	}
	BinaryNode<KeyT, ValueT>* next(BinaryNode<KeyT, ValueT>* x)
	{ 
		//логика такова что у элемента x(положем 12) если он имеет правого сына
		//то минимальный элемент правого сына будет следуйщим за корнем по возрастанию
		//              12
		//            /    \
		//           6     14
		//         /  \   /  \
		//        4    9 13  16
		//
		BinaryNode<KeyT, ValueT>* n;
		if (x->right != NULL)
		{
			//если справа есть вершина то ищем её минимум
			return find_min(x->right);
		}
		n = x->parent;
		while ( n!= NULL && x == n->right)
		{
			//иначе поднимемся вверх пока не встретим узел,
			//который является  левым дочерним узлом своего родителя
			x = n;
			n = n->parent;
		}
		return n;
	}
	BinaryNode<KeyT, ValueT>* prev(BinaryNode<KeyT, ValueT>* x)
	{
		//логика такова что у элемента x(положем 12) если он имеет левого сына
		//то максимвльный элемент левого сына будет предыдущий за корнем по возрастанию
		//              12
		//            /    \
		//           6     14
		//         /  \   /  \
		//        4    9 13  16
		//
		BinaryNode<Keyt, ValueT>* n;
		if (x->left != NULL)
		{
			return find_max(x->left);
		}
		n = x->parent;
		while (n != NULL && x == n->left)
		{
			x = n;
			n = n->parent;
		}
		return n;
	}

};
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::get_root()
{
	return root;
}
template <class KeyT = int, class ValueT = int>
void BinaryTree<KeyT, ValueT>::insert(const KeyT &k, const ValueT &v = 0)
{
	BinaryNode<KeyT, ValueT> * _new = new BinaryNode<KeyT, ValueT>(k, v);
	BinaryNode<KeyT, ValueT> * ptr = root;
	BinaryNode<KeyT, ValueT> * ptr1 = ptr;
	_new->parent = _new->left = _new->right = 0;
	while (ptr != 0)
	{
		ptr1 = ptr;
		if (k < ptr->get_key())
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}
	_new->parent = ptr1;
	if (ptr1 == NULL){
		root = _new;

	}
	else {
		if (k < ptr1->get_key())
			ptr1->left = _new;
		else
			ptr1->right = _new;
	}

}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::cut(BinaryNode<KeyT, ValueT> *z)
{
	BinaryNode<KeyT,ValueT>* p = z->parent;
	if (z->left == 0 && z->right == 0)
	{
		if (p == NULL)
		{
			root = NULL;
			return z;
		}
		if (p->left == z)
			p->left = NULL;
		if (p->right == z)
			p->right = NULL;
		//если удаляем лист то просто обнуляем указатели родителя
	}
	else if (z->left == 0 || z->right == 0)
	{
		//если есть ровно один сын
		if (z->left == NULL)
		{
			//если сын не левый а правый
			//соединяем родителя с сыном удаляемой вершины
			if (p == NULL)
			{
				root = z->right;
				root->parent = NULL;
				return z;
			}
			if (p->left == z)
			{
				p->left = z->right;
			}
			else
			{
				p->right = z->right;
			}
			z->right->parent = p;
			//обновляем указатель на родителя
		}
		else
		{
			//если сын левый
			if (p == NULL)
			{
				root = z->left;
				root->parent = NULL;
				return z;
			}
			if (p->left == z)
				p->left = z->left;
			else
				p->right = z->left;
			z->left->parent = p;
		}
	}
	else
	{
		BinaryNode<KeyT, ValueT>* s = next(z);
		//s- узел,который является наиболее приближенным по ключу к удалямому элементу
		//справа (например если удаляем 7,то это  самое близкое значение его сыновей,но большее
		//например 8)
		z->key = s->key;
		if (s->parent->left == s)
		{
			s->parent->left = s->right;
			if (s->right != NULL)
			{
				s->right->parent = s->parent;
			}
		}
		else
		{
			s->parent->right = s->right;
			if (s->right != NULL)
			{
				s->right->parent = s->parent;
			}
		}

	}
	
	return z;
}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find_max(BinaryNode<KeyT, ValueT> *x)
{
	while (x->right)
		x = x->right;
	return x;
}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find_max()
{
	auto x = new BinaryNode<KeyT, ValueT>;
	x = root;
	while (x->right)
		x = x->right;
	return x;
}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find_min(BinaryNode<KeyT, ValueT> *x)
{
	while (x->left)
		x = x->left;
	return x;
}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* find_min()
{
	auto x = new BinaryNode<KeyT, ValueT>;
	x = root;
	while (x->left)
		x = x->left;
	return x;
}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find(const KeyT& val)
{
	BinaryNode<KeyT, ValueT>* x = find_node(root, val);
	return x;
	/*BinaryNode<KeyT, ValueT>* y;
	if (x == 0)
		return 0;
	if (x == root)
		return x;
	if (x->right != 0)
		return find_min(x->right);
	y = x->parent;
	while ((y != 0) && (x = y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;*/
}
template <class KeyT = int, class ValueT = int>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::find_node(BinaryNode<KeyT, ValueT>* n, const KeyT & val)
{
	if (n == 0 || val == n->get_key())
		return n;
	if (val > n->get_key())
		return find_node(n->right, val);
	else
		return find_node(n->left, val);
}
template <class KeyT = int, class ValueT = int>
void BinaryTree<KeyT, ValueT>::print(BinaryNode<KeyT, ValueT>* n)
{
	if (n != 0)
	{
		print(n->left);
		std::cout << "(" << n->get_key() << "," << n->get_val() << ")";
		print(n->right);
	}
}


#ifdef _VECTOR_



//ОБХОДЫ!!!!!!!!!!!!!!!!!!//////




//ОБХОДЫ(возврат вектора с номерами ключей)
template<class KeyT,class ValueT>
std::vector<KeyT> BinaryTree<KeyT, ValueT>::preorder_traversal()//в ширину
{
	std::vector<KeyT> val;
	preorder_traversal(root, val);
	return val;
}
template<class KeyT, class ValueT>
std::vector<KeyT> BinaryTree<KeyT, ValueT>::inorder_traversal()//симметричный обход
{
	std::vector<KeyT> val;
	inorder_traversal(root, val);
	return val;
}
template<class KeyT, class ValueT>
std::vector<KeyT> BinaryTree<KeyT, ValueT>::postorder_traversal()//обход в глубину
{
	std::vector<KeyT> val;
	postorder_traversal(root, val);
	return val;
}
template<class KeyT, class ValueT>
std::vector<KeyT> BinaryTree<KeyT, ValueT>::traversal()//прямой обход
{
	std::vector<KeyT> val;
	traversal(root, val);
	return val;
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::preorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res)//в ширину
{
	std::vector<BinaryNode<KeyT,ValueT>*> queue;
	queue.push_back(root);
	while (!queue.empty())
	{
		if (queue[0]->left)
			queue.push_back(queue[0]->left);
		if (queue[0]->right)
			queue.push_back(queue[0]->right);
		res.push_back(queue[0]->key);
		queue.erase(queue.begin());
	}
}
template <class KeyT,class ValueT>
void BinaryTree<KeyT, ValueT>::preorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res,bool flag)//в ширину
{
	std::vector<BinaryNode<KeyT, ValueT>*> queue;
	BinaryNode<KeyT, ValueT>* it;
	queue.push_back(root);
	while (!queue.empty())
	{
		if (queue[0]->left)
			queue.push_back(queue[0]->left);
		if (queue[0]->right)
			queue.push_back(queue[0]->right);

		it = queue.front();
		int maxl = 0;
		int maxr = 0;
		if (it->left)
			max_height(it->left, maxl, 0);
		else
			maxl = -1;
		if (it->right)
			max_height(it->right, maxr, 0);
		else
			maxr = -1;
		res.push_back(maxl);
		res.push_back(maxr);

		queue.erase(queue.begin());
	}
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res)//симметричный обход
{
	if (root)
	{
		inorder_traversal(root->left, res);
		res.push_back(root->key);
		inorder_traversal(root->right, res);
	}
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<BinaryNode<KeyT, ValueT>*>& res)//симметричный обход
{
	if (root)
	{
		inorder_traversal(root->left, res);
		res.push_back(root);
		inorder_traversal(root->right, res);
	}
}
template <class KeyT, class ValueT>
std::vector<int> BinaryTree<KeyT, ValueT>::getTreeIsoCode()
{
	std::vector<int> res;
	preorder_traversal(root, res,true);
	return res;
}
template <class KeyT,class ValueT>
void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNode<KeyT, ValueT>*root, std::vector<std::pair<int, int> >& res)
{
	if (root)
	{
		inorder_traversal(root->left, res);
		int maxl = 0;
		int maxr = 0;
		max_height(root->left, maxl, 0);
		max_height(root->right, maxr, 0);
		res.push_back(std::make_pair(maxl,maxr));
		inorder_traversal(root->right, res);
	}
}
template <class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::inorder_traversal(BinaryNode<KeyT, ValueT>*root, std::vector<int>& res,bool flag)
{
	if (root)
	{
		inorder_traversal(root->left, res,flag);
		int maxl = 0;
		int maxr = 0;
		if (root->left)
			max_height(root->left, maxl, 0);
		else
			maxl = -1;
		if(root->right)
			max_height(root->right, maxr, 0);
		else
			maxr = -1;
		res.push_back(maxl);
		res.push_back(maxr);
		inorder_traversal(root->right, res,flag);
	}
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::postorder_traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res)//обратный(в глубину)
{
	if (root)
	{
		postorder_traversal(root->left, res);
		postorder_traversal(root->right, res);
		res.push_back(root->key);
		
	}
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::traversal(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res)//прямой обход
{
	if (root )
	{
		res.push_back(root->key);
		postorder_traversal(root->left, res);
		postorder_traversal(root->right, res);
	}
}


//КОНЕЦ ОБХОДОВ/////


template<class KeyT,class ValueT>
std::vector<std::pair<KeyT, ValueT>> BinaryTree<KeyT,ValueT>::GetEdges()
{
	std::vector<std::pair<KeyT, ValueT>> res;
	GetEdges(root, res,root->key);
	return res;
}
template<class KeyT,class ValueT>
void BinaryTree<KeyT, ValueT>::GetEdges(BinaryNode<KeyT, ValueT>* root, std::vector<std::pair<KeyT, KeyT>>& res, KeyT ignored)
{
	if (root)
	{
		if (root->key != ignored)
		{
			res.push_back(std::make_pair(root->key, root->parent->key));
		}
		GetEdges(root->left, res, ignored);
		GetEdges(root->right, res, ignored);
	}
}
template<class KeyT, class ValueT>
std::vector<KeyT> BinaryTree<KeyT, ValueT>::GetVertex()
{
	std::vector<KeyT> res;
	GetVertex(root, res);
	return res;
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::GetVertex(BinaryNode<KeyT, ValueT>* root, std::vector<KeyT>& res)
{
	if (root)
	{
		res.push_back(root->get_key());
		GetVertex(root->left, res);
		GetVertex(root->right, res);
	}
}
template<class KeyT, class ValueT>
std::vector<std::pair<int, std::pair<int, int>>> BinaryTree<KeyT, ValueT>::_PrintGetVertex(int height)
{
	std::vector<std::pair<int, std::pair<int, int>>> res;
	_PrintGetVertex(root, res,0,0,height+sqrt(height)+1);
	return res;
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::_PrintGetVertex(BinaryNode<KeyT, ValueT>* root, std::vector<std::pair<int, std::pair<int, int>>>& res,int k1,int k2,int k3)
{
	if (root)
	{
		res.push_back(std::make_pair(root->get_key(),std::make_pair(k1,k2)));
		
		_PrintGetVertex(root->left, res, ++k1, k2 - k3, k3 % 2 ? (k3 / 2) + 1 : (k3 / 2));
		--k1;
		_PrintGetVertex(root->right, res, ++k1, k2 + k3, k3 % 2 ? (k3 / 2) + 1 : (k3 / 2));
	}
}
#endif
template<class KeyT, class ValueT>
int BinaryTree<KeyT, ValueT>::min_height()
{
	int min = 9999999;
	min_height(root, min, 0);
	return min;
}

template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::min_height(BinaryNode<KeyT, ValueT>* it, int & min,int temp)
{
	if (it)
	{
		if (min>temp && it->left == NULL && it->right == NULL)
		{
			min = temp;
		}
		min_height(it->left, min, ++temp);
		temp--;
		min_height(it->right, min, ++temp);
	}
	//temp--;
}
template<class KeyT, class ValueT>
int BinaryTree<KeyT, ValueT>::max_height()
{
	int max = 0;
	max_height(root, max, 0);
	return max;
}

template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::max_height(BinaryNode<KeyT, ValueT>* it, int & max, int temp)
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
	//temp--;
}
template<class KeyT, class ValueT>
bool BinaryTree<KeyT, ValueT>::is_balanced()
{
	int min = 999999;
	int max = 0;
	is_balanced(root, min, max, 0);
	if (max == min +1)
	{
		return true;
	}
	else return false;
}
template<class KeyT, class ValueT>
void BinaryTree<KeyT, ValueT>::is_balanced(BinaryNode<KeyT, ValueT>* it, int & min, int & max, int temp)
{
	if (it)
	{
		if (min > temp && it->left == NULL && it->right == NULL)
		{
			min = temp;
		}
		if (max < temp)
		{
			max = temp;
		}
		is_balanced(it->left, min, max, ++temp);
		--temp;
		is_balanced(it->right, min, max, ++temp);
	}
	temp--;
}
#if defined( _VECTOR_) && defined (_ALGORITHM_)
template <class KeyT,class ValueT>
void BinaryTree<KeyT, ValueT>::mark()
{
	std::vector<BinaryNode<KeyT,ValueT>*> vertex;
	inorder_traversal(root,vertex);
	for (size_t i = 0; i < vertex.size(); i++)
	{
		vertex[i]->key = i;
	}
}
template <class KeyT,class ValueT>
std::vector<int> BinaryTree<KeyT, ValueT>::getPrufferCode()
{
	std::vector<std::pair<int, int>> edges = GetEdges();
	std::vector<int> pruffer;
	std::sort(edges.begin(), edges.end());
	auto it = edges.begin();
	while (edges.size() > 1)
	{

		size_t counter = 0;
		for (size_t i = 0; i < edges.size(); i++)
		{
			if (edges[i].second == it->first)
			{
				counter++;
				break;
			}
		}
		if (counter == 0)
		{
			pruffer.push_back(it->second);
			edges.erase(it);
			//    std::min_element(edges.begin(), edges.end());
			//	std::sort(edges.begin(), edges.end());
			it = edges.begin();
			continue;
		}
		it++;
	}
	return pruffer;
}
template <class KeyT,class ValueT>
bool BinaryTree<KeyT, ValueT>::isIsomorph(BinaryTree<KeyT, ValueT>* x)
{
	std::vector<std::pair<int, int>> prop1, prop2;
	inorder_traversal(root, prop1);
	inorder_traversal(x->root, prop2);
	if (prop1.size() != prop2.size() || prop1.size() == 0)
		return false;
	std::sort(prop1.begin(),prop1.end());
	std::sort(prop2.begin(),prop2.end());
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





//*********************************HAFFMAN TREE****************************************
template<class KeyT = int,class ValueT = int>
class HaffmanTree : public BinaryTree<KeyT, ValueT>{
public:
	template <class KeyT, class ValueT> friend class BianryNode;
	template <class KeyT, class ValueT>
	friend void set_key(BinaryNode<KeyT, ValueT>* tree, KeyT new_key);
	template <class KeyT, class ValueT>
	friend void set_val(BinaryNode<KeyT, ValueT>* tree, ValueT val);
	HaffmanTree() :BinaryTree(){}
	HaffmanTree(const BinaryTree<KeyT, ValueT>& x) :BinaryTree(x){}
	HaffmanTree(const BinaryNode<KeyT, ValueT>*& x) :BinaryTree(x){}
	HaffmanTree(const KeyT& k, const ValueT& v) :BinaryTree(k, v){}
	BinaryNode<KeyT, ValueT>* find_min();
	BinaryNode<KeyT, ValueT>* find_traversal(KeyT k, ValueT v);
	void find_traversal(BinaryNode<KeyT, ValueT> *it, KeyT k, ValueT v, BinaryNode<KeyT, ValueT>*& retval);
	~HaffmanTree(){};


	int InsertLeft(KeyT key1, ValueT val1, KeyT key2, ValueT val2)
	{
		BinaryNode<int, int>* x = find_traversal(key1,val1);
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
				x->left = new BinaryNode<int, int>(key2, val2);
				x->left->parent = x;
			}
		}
		else return 0;
		return 1;
	}
	int InsertRight(KeyT key1, ValueT val1, KeyT key2, ValueT val2)
	{
		BinaryNode<int, int>* x = find_traversal(key1,val1);
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
				x->right = new BinaryNode<int, int>(key2, val2);
				x->right->parent = x;
			}
		}
		else return 0;
		return 1;
	}



#ifdef BITS_H
	Bits create_bitpath(const KeyT& k, const ValueT& v)//создает битовую строку
	{
		Bits res(0);
		Bits buff(0);
		auto it = root;
		recursive_walk(k, v, buff, it, res);
		return res;
	}
	Bits create_bitpath_if_val_string(const KeyT& k, const ValueT& v)//создает битовую строку из дерева(применимо к деревьям с 
		//соблюдением принципов кучи и с ключем - строкой
	{
		Bits res(0);
		auto it = root;
		walk(k, v, it, res);
		return res;
	}
#ifdef _VECTOR_
	HaffmanTree<KeyT, ValueT>* mark()
	{
		HaffmanTree<KeyT, ValueT>* a = this;
		std::vector< BinaryNode<KeyT, ValueT>*> queue;
		queue.push_back(root);
		for (size_t i = 0; i < queue.size(); i++)
		{
			if (queue[i]->get_left())queue.push_back(queue[i]->get_left());
			if (queue[i]->get_right())queue.push_back(queue[i]->get_right());
		}
		size_t count = 1;
		for (int i = queue.size() - 1; i>=0; i--)
		{
			set_key(queue[i],count++);
		}		
		return a;
	}
	std::vector<int> tree_encode()
	{
		{
			std::vector<int> pruffer;
			HaffmanTree<KeyT, ValueT>* a = new HaffmanTree<KeyT, ValueT>;
			a->root = copy(root);
			//a->root = root;
			BinaryNode<KeyT, ValueT> *temp;
			while (a->root->get_left() || a->root->get_right())
			{
				temp = a->find_min();
				pruffer.push_back(temp->get_parent()->get_key());
				a->cut(temp);
			}
			return pruffer;
	}
#endif
protected:

	void recursive_walk(const KeyT& k, const ValueT& v, Bits res, BinaryNode<KeyT, ValueT>* it, Bits& retval)
	{
		if (it)//Если дерево сушествует
		{
			if (it->get_key() == k && it->get_val() == v){
				retval = res;
				return;
			}
			res.Add(false);
			recursive_walk(k, v, res, it->get_left(), retval);
			res.pop_back();
			res.Add(true);
			recursive_walk(k, v, res, it->get_right(), retval);
		}
	}
	void walk(const KeyT& k, const ValueT& v, BinaryNode<KeyT, ValueT>* it, Bits& retval)
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
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::copy(BinaryNode<KeyT, ValueT>* x)
{
	return copy(x,x);
}
template <class KeyT, class ValueT>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::clone()
{
	return copy(root,root);

}
template <class KeyT, class ValueT>
BinaryNode<KeyT, ValueT>* BinaryTree<KeyT, ValueT>::copy(BinaryNode<KeyT, ValueT>* x, BinaryNode<KeyT, ValueT>* pred)
{
	if (x == NULL)
		return NULL;
	BinaryNode<KeyT, ValueT>* new_node = new BinaryNode<KeyT, ValueT>(x->get_key(), x->get_val());
	new_node->parent = pred;
	new_node->left = copy(x->left,new_node);
	new_node->parent = pred;
	new_node->right = copy(x->right,new_node);
//	new_node->parent = pred;
	return new_node;
}
template <class KeyT, class ValueT>
BinaryNode<KeyT, ValueT>*  HaffmanTree<KeyT, ValueT>::find_traversal(KeyT k, ValueT v)
{
	BinaryNode<KeyT, ValueT>* retval = NULL;
	find_traversal(root, k, v, retval);
	return retval;
}
template <class KeyT, class ValueT>
void  HaffmanTree<KeyT, ValueT>::find_traversal(BinaryNode<KeyT, ValueT> *it, KeyT k, ValueT v, BinaryNode<KeyT, ValueT>*& retval)
{
	if (it)
	{
		if (it->key == k && it->value == v)
		{
			retval = it;
			return;
		}
		find_traversal(it->left, k,v,retval);
		find_traversal(it->right, k,v,retval);
	}
}

template <class KeyT,class ValueT>
BinaryNode<KeyT, ValueT>* HaffmanTree<KeyT,ValueT>::find_min()
{
	std::vector< BinaryNode<KeyT, ValueT>*> queue;
	BinaryNode<KeyT, ValueT>* min_val = new BinaryNode<KeyT, ValueT>(root->get_key(), root->get_val());
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
void set_key(BinaryNode<KeyT, ValueT>* tree, KeyT new_key)
{
	tree->key = new_key;

}
template <class KeyT, class ValueT>
void set_val(BinaryNode<KeyT, ValueT>* tree, ValueT val)
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
		AvlNode<KeyT, ValueT> *y = x->left;
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
};
#endif