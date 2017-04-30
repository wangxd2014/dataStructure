#include "head.h"
#ifndef _MinHeap_H_
#define _MinHeap_H_

/*
 1. 用vector构建的最简单的二分堆
 2. 这个堆得稍作修改
*/

void SiftUp(vector<int>& H,vector<int>&key,int loc);
void SiftDown(vector<int>& H,vector<int>&key,int loc);
void Insert(vector<int>& H,vector<int>&key,int x);
void Delete(vector<int>& H,vector<int>&key,int loc );
void DeleteMax(vector<int>& H,vector<int>&key,int& x);
void print(vector<int>&H);
bool find(vector<int>&H,const int&x,int& loc);

#endif 