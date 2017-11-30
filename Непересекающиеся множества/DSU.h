#include<vector>
#include "func.h"
using namespace std;
#define FIND_ERROR -1
 template <typename _Type = int>
 /*нумерация элементов начинается с 1*/
class DSU{
	vector<_Type> u;
	vector<int>  parrent;
	vector<size_t> rank;
public:
	DSU(){}
	~DSU(){}
	DSU(int i){
		for(size_t a = 0;a<i;a++){
			Make(a+1);
		}
	}
	void Make(_Type v){
		/*
		Создает множество с одним элементом
		*/
		parrent.push_back(parrent.size()+1);
		u.push_back(v);
		rank.push_back(0);

	}
	void Union(int x,int y){
		/*
		Объединяет элементы множества х с элементами множества у
		*/
		x = Find(x);
		y = Find(y);


		if (x != y) {
			if (rank[x-1] < rank[y-1])
				swap (x, y);
			parrent[y-1] = x;
			if (rank[x-1] == rank[y-1])
				++rank[x-1];
		}
	}
	int Find (int v) {
		if(v>parrent.size())return FIND_ERROR;
		/*
		ищет к какому множеству принадлежит v подможество
		*/
		if (v == parrent[v-1])
			return v;
		return parrent[v-1] = Find (parrent[v-1]);
	}
	int FindElem (_Type v) {
		/*
		ищет к какому множеству принадлежит v элемент
		универсума.Если таких несколько то выводит первый.
		*/
		for(size_t i=0;i<u.size();i++){
			if(v == u[i])return parrent[i];
		}
		return FIND_ERROR;
	}
	bool IsValue(int a1,int a2){
		/*
		проверка находяться ли два элемента  множества в одном подмножестве
		*/
		return Find(a1) == Find(a2);
	}
	bool IsValueElem(_Type a,_Type b){
		return FindElem(a) == FindElem(b);
	}
	int Quantity(){
		size_t quant = 0;
		bool* base;
		base = new bool[parrent.size()];
		for(size_t i=0;i<parrent.size();i++){
			base[parrent[i]-1] = false;
		}
		for(size_t i=0;i<parrent.size();i++){
			if(!base[i])quant++;
		}
		return quant;
	}
};