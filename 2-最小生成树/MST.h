#include "DisjointSets.h"
#include "MinHeap.h"
#pragma once

struct Edges{ // 可以用来对边进行排序; 可以用来输出最后的结果 
	int start;
	int end;
	int weight;
};

class MST
{
public:
	MST(void);
	~MST(void);
	// max flow 
	// 从1到n
	void maxflow(int s,int d);
	void maxflowAny(int s, int d);
	void maxflowAnyCost(int s, int d,int limit);// limit表示的是服务器的成本
	void level(int s,int d);

	// 最小生成树
	void kruskal(vector<Edges>& res);
	void prim(vector<Edges>& res);


	bool readGraph(char *name);
	void printGraph(); 
	int  nNodes;
	int  nEdges;
	vector < vector<int> > edgeCost;
	vector<vector<int> >adjList;
	vector<vector<int> >weight;
	vector<Edges> allEdges; // 所有边按照非降序排列
};

void swap(Edges& x,Edges& y);
void split(vector<Edges>&A,const int& low,const int&high,int &w);
void quicksort(vector<Edges>&A,const int &low,const int&high);