#include "heap.h"
#include "binaryHeap.h"
#include <vector>
#include <set>
#pragma once
template <class T>
class Graph
{
	std::vector<std::vector<T> > _data;


	//в sources есть как минимум одна вершина, которая связана со всеми из destinies
	bool includesAtLeastOneAttachedToAll(std::vector<int>& sources, std::vector<int>& destinies)
	{
		for (auto it = sources.begin(); it != sources.end(); it++)
		{
			if (isAttachedToall(*it, destinies))
				return true;
		}
		return false;
	}

	//создает новый вектор из вершин из множества old, не связанных с v
	std::vector<int> removeNotAttachedVertexes(Graph<int>& gr, std::vector<int> &old, int v)
	{
		std::vector<int> rez;
		for (auto it = old.begin(); it != old.end(); it++)
		{
			if (gr[*it][v])
				rez.push_back(*it);
		}
		return rez;
	}

	//Функция рекурсивно ищет клики
	void findCliques(std::vector<int> cand, std::vector<int> not, std::vector<int> comp, std::vector<int>& result)
	{
		//Алгоритм выполняетяс до тех пор пока множество кандидат не пусто
		//и как минимум одна вершина из уже пройденных свазана со всеми кандидатами
		while (!cand.empty() && !includesAtLeastOneAttachedToAll(not, cand))
		{
		//1) удаляем из кандидаты вершину и добавляем ее в текущюю клику
			int v = cand.back();
			comp.push_back(v);
		//2) формируем новые кандидаты, удаляя из старых все вершины, не связные с удаленной
		// тоже самое проделываем и с уже пройденными ( исключаем заведомо ложные варианты)
			std::vector<int> new_candidates = removeNotAttachedVertexes(cand, v);
			std::vector<int> new_not = removeNotAttachedVertexes(not, v);
			if (new_not.empty() && new_candidates.empty())
			{
				if (comp.size() > result.size())
					result = comp;
			}
			else
			{
				findCliques(new_candidates, new_not, comp, result);
			}
			comp.pop_back();
			cand.pop_back();
			not.push_back(v);
		}
	}



public:

	Graph()
	{
	}

	Graph(std::vector<std::vector<T> > data)
	{
		_data = data;
	}

	Graph(int size, T ini = T())
	{
		_data.resize(size, std::vector<T>(size, ini));
	}

	std::vector<T> at(int i) const
	{
		return _data[i];
	}

	//возвращает вес по индексам. В отличие от getNode не 
	//проверяет на переполнение не кидает исключения
	T at(int i, int j) const
	{
		return _data[i][j];
	}

	//возвращает количетсво вершин в графе
	size_t size() const
	{
		return _data.size();
	}

	bool isEmpty()const
	{
		return size() == 0
	}

	void clear()
	{
		_data.clear();
	}

	void resize(int size)
	{
		_data.resize(size, std::vector<T>(size));

	}

	//Вставляет ребро x y веса w .
//Если or = false то также добавляет ребро y x
	void addArc(int x, int y, T w = T(), bool or = true )
	{
		if (x >= size() || y >= size())
			throw("out of range");
	
		_data[x][y] = w;
		if (!or)
		{
				_data[y][x] = w;
		}
	}

	void removeArc(int x, int y)
	{
		addArc(x, y, T(), false);
	}

	//возвращает вес элемента
	T getNode(int x, int y) const
	{
		if (x >= size() || y >= size())
			throw("out of range");

		return _data[x][y];

	}

	std::vector<T>& operator[](size_t i)
	{
		if (i >= size())
			throw("out of range");
		return _data[i];
	}

	//проверяет связаны ли две вершины
	//возвращает вес связи или ноль если отсутствует
	T isConnected(int x, int y)
	{
		if (x >= size() || y >= size())
			throw("out of range");
		if (_data[x][y] == 0)
			return T();
		else
			return _data[x][y];
	}

	std::vector<std::vector<T> > getTable()
	{
		return _data;
	}
	
	//возвращает множество вершин
	std::set<T> getSet()
	{
		std::set<T> rez;
		for (int i = 0; i < _data.size(); i++)
		{
			for (int j = 0; j < _data[i].size(); j++)
			{
				rez.insert(data[i][j]);
			}
		}
		return data[i][j];
	}

	//возвращает множество ребер
	//set < пара < вес, пара < начало, конец > > >
	std::set<std::pair<T, std::pair<size_t, size_t> > > getArcs()
	{
		std::set<std::pair<T, std::pair<size_t, size_t> > > rez;
		for (size_t i = 0; i < _data.size(); i++)
		{
			for (size_t j = 0; j < _data[i].size(); j++)
			{
				if (_data[i][j] != 0)
					rez.insert(std::make_pair(_data[i][j], std::make_pair(i,j)));
			}
		}
		return rez;
	}

	//Ищет кратчайший путь между вершинами start и finish
	//возвращает пару < длинна пути, путь >
	std::pair<int, std::vector<int> > shortPath(int start, int finish)
	{
		//1) Инициализация графа , кучи, вспомогательных элементов
		std::vector<int> d(size(), INF);
		std::vector<int> p(_data.size());
		d[start] = 0;
		Heap<int> q;
		HeapNode<int>* temp;
		q.insert(0, start);
		//2)Пока куча не пуста достаем из нее самый приоритетный элемент
		while (!q.isEmpty())
		{
			temp = q.extract();
			int v = temp->value(), cur_d = temp->key();
			delete temp;
			//3)Если ранее найденный путь короче то на новую итерацию
			if (cur_d > d[v])
			{
				continue;
			}
			//4)Проходим из найденной вершины по всем другим вершинам графа
			for (size_t j = 0; j < _data[v].size(); ++j)
			{
				int to = j,//вершина куда идем
					len = _data[v][j];//путь который проходим
				//5) Если новый путь короче предыдущего, то запоминаем его
				// а также ложим в кучу новую запись : ключ - длинна пути, значение - номер вершины
				if (d[v] + len < d[to])
				{
					d[to] = d[v] + len;
					p[j] = v;
					q.insert(d[to], to);
				}
			}
		}
		std::vector<int> path;
		for (int v = finish; v != start; v = p[v])	
			path.push_back(v);
		path.push_back(start);
		reverse(path.begin(), path.end());
		return std::make_pair(d[finish],path);//вернем путь до третьего пункта
	}

	//Вычисляет длинну достаточно оптимального гамильтонова цикла( жадный алгоритм)
	//возвращает пару < длинна , путь>
	std::pair<int, std::vector<int> > gamiltonLoop(int start = 0)
	{
		std::vector<bool> check(size(), false);
		check[start] = false;
		std::vector<int> cur(size());
		cur[0] = start;
		BinaryNode<T> temp;
		BinaryNode<T> temp2;
		std::vector<BinaryHeap<T> > table(size());
		for (size_t i = 0; i < size(); i++)
		{
			for (size_t j = 0; j < size(); j++)
			{
				table[i].insert(_data[i][j], j);
			}
		}
		int it = start;
		int it2 = start;
		int counter = 0;
		int back = size() - 1;
		int front = 1;
		while (counter < size() - 1)
		{
			temp = table[it].extract();
			if (check[temp.value()] == false)
			{
				cur[front++] = temp.value();
				check[temp.value()] = true;
				it = temp.value();
				counter++;
			}
			temp2 = table[it2].extract();
			if (check[temp2.value()] == false)
			{
				cur[back--] = temp2.value();
				check[temp2.value()] = true;
				it2 = temp2.value();
				counter++;
			}
		}
		int sum = 0;
		for (int i = 0; i < cur.size(); i++)
		{
			sum += _data[cur[i]][cur[i + 1]];
		}
		sum += _data[cur.back()][0];
		return std::make_pair(sum,cur);
	}

	//Находит минимальное остовое дерево
	//возвращает пару (сумма всех путей, вектор ребер>
	std::pair<int,std::vector<std::pair<int, int> > >  shortSubTree(int start = 0)
	{
		int sum = 0;
		int n = size();
		vector<int> min_e(n, INF), sel_e(n, -1);
		min_e[0] = 0;
		Heap < int > q;
		HeapNode < int >* temp;
		std::vector<int> used(n, false);
		std::vector<std::pair<int, int> > res;
		q.insert(0, 0);
		for (int i = 0; i<n; ++i) {
			if (q.isEmpty())
			{
				return std::make_pair(0, std::vector<std::pair<int, int> >());
			}
			temp = q.extract();
			int v = temp->value();
			delete temp;
			if (used[v])
			{
				i--;
				continue;
			}
			else
				used[v] = true;

			if (sel_e[v] != -1)
			{
				sum += _data[v][sel_e[v]];
				res.push_back(std::make_pair(v, sel_e[v]));
			}

			for (size_t j = 0; j<_data[v].size(); ++j)
			{
				int to = j,
					cost = _data[v][j];
				if (cost == 0)
					cost = INF - 1;
				if (cost < min_e[to] && !(used[v] && used[j]))
				{
					min_e[to] = cost;
					sel_e[to] = v;
					q.insert(min_e[to], to);
				}
			}
		}
		return std::make_pair(sum,res);
	}

	//проверяет связана ли вершина со всеми из множества
	bool isAttachedToAll(int source, std::vector<int>& dest)
	{
		for (auto it = dest.begin(); it != dest.end(); it++)
		{
			if (!_data[source][*it])
				return false;
		}
		return true;
	}

	//функция ищет максимальный полный подграф и возвращает номера вершин, которые он включает
	std::vector<int> findCliques()
	{
		std::vector<int> comp, not, cand, rez;
		for (int i = 0; i < size(); i++)
			cand.push_back(i);
		int v = 0;
		std::vector<int>::iterator it = cand.begin();
		findCliques(cand, not, comp, rez);
		return rez;
	}

	//Функция определяет есть ли в графе отрицательный цикл
	//если есть то true
	bool isNegotiveCycles()
	{
		std::vector<int> d(gr.size());
		int start = 0;
		for (int i = 0; i < gr.size(); i++)
			d[i] = INF;
		d[start] = 0;
		auto edge = gr.getArcs();
		int x;
		for (int i = 0; i < gr.size(); ++i)
		{
			x = -1;
			for (auto j = edge.begin(); j != edge.end(); ++j)
			{
				if (d[(*j).second.first]< INF)
				{
					if (d[(*j).second.second] > d[(*j).second.first] + (*j).first)
					{
						d[(*j).second.second] = max(-INF, d[(*j).second.first] + (*j).first);
						x = (*j).second.second;
					}
				}
			}
		}
		if (x == -1)
			return false;
		else
			return true;
	}

	//определяет есть ли ребра отрицательного веса
	bool isNegotive()
	{
		for (int i = 0; i < _data.size(); i++)
		{
			for (int j = 0; j < _data.size(); j++)
			{
				if (_data[i][j] < 0)
					return true;
			}
		}
		return false;
	}

	//вычисляет степень вершины
	//возвращает степень, или -1 если вершины нет в графе
	int degree(int vertex)
	{
		if (vertex > size())
			return -1;
		int retval = 0;
		for (int i = 0; i < size(); i++)
		{
			if (_data[vertex][i] != 0)
				retval++;
		}
		return retval;
	}

	private:

	struct compareMax
	{
		bool operator()(int s1, int s2) const
		{
			return s1 > s2;
		}
	};


	//true если данная вершина не связана с вершиной такого же цвета как currColor
	bool isAcceptedToColoring(int index,const std::vector<int>& rez,int currColor)
	{
		for (int i = 0; i < size(); i++)
		{
			if ((_data[index][i] != 0 || _data[i][index] != 0) && rez[i] == currColor)
			{
				return false;
			}
		}
		return true;
	}

	public:

	std::vector<int> minColoring()
	{
		std::multimap<int, int, compareMax> vert;
		std::vector<int> rez(size());
		int currColor = 0;
		
		do
		{
			currColor++;
			vert.clear();
			for (int i = 0; i < size(); i++)
			{
				if (rez[i] == 0)
					vert.insert(std::make_pair(degree(i), i));
			}
			if (vert.size() == 0)
				break;

			multimap<int, int>::iterator it = vert.begin();
			int index = it->second;
			it++;
			rez[index] = currColor;
			for (; it != vert.end(); it++)
			{
				if (isAcceptedToColoring(it->second, rez, currColor))
				{
					rez[it->second] = currColor;
				}
			}
		
		
		/*	for each(auto it in vert)
			{
				int index = it.second;
				if (rez[index] == 0)
				{
					currColor++;
					rez[index] = currColor;
					for (int i = 0; i < size(); i++)
					{
						if (_data[index][i] == 0 && isAcceptedToColoring(i,rez,currColor) && rez[i] == 0)
						{
							rez[i] = currColor;
						}
					}
				}
			}*/
		}
		while (vert.size() != 0);
		return rez;

	}

	~Graph()
	{
	}
};



static std::vector<int> removeNotAttachedVertexes(Graph<int>& gr, std::vector<int> &old, int v)
{
	std::vector<int> rez;
	for (auto it = old.begin(); it != old.end(); it++)
	{
		if (gr[*it][v])
			rez.push_back(*it);
	}
	return rez;
}



