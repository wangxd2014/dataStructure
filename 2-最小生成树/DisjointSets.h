#include "head.h"
#ifndef _DisjointSets_H_
#define _DisjointSets_H_
//其实这里使用数组也是可以的
void Find(vector<int>& D,const int& x,int&root);
void Union(vector<int>& D,int *rank,const int& x,const int& y);

#endif 