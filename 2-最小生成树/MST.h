#include "DisjointSets.h"
#include "MinHeap.h"
#pragma once

struct Edges{ // ���������Ա߽�������; ��������������Ľ�� 
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
	// ��1��n
	void maxflow(int s,int d);
	void maxflowAny(int s, int d);
	void maxflowAnyCost(int s, int d,int limit);// limit��ʾ���Ƿ������ĳɱ�
	void level(int s,int d);

	// ��С������
	void kruskal(vector<Edges>& res);
	void prim(vector<Edges>& res);


	bool readGraph(char *name);
	void printGraph(); 
	int  nNodes;
	int  nEdges;
	vector < vector<int> > edgeCost;
	vector<vector<int> >adjList;
	vector<vector<int> >weight;
	vector<Edges> allEdges; // ���б߰��շǽ�������
};

void swap(Edges& x,Edges& y);
void split(vector<Edges>&A,const int& low,const int&high,int &w);
void quicksort(vector<Edges>&A,const int &low,const int&high);