#include "head.h"
#ifndef _MinHeap_H_
#define _MinHeap_H_

/*
 1. ��vector��������򵥵Ķ��ֶ�
 2. ����ѵ������޸�
*/

void SiftUp(vector<int>& H,vector<int>&key,int loc);
void SiftDown(vector<int>& H,vector<int>&key,int loc);
void Insert(vector<int>& H,vector<int>&key,int x);
void Delete(vector<int>& H,vector<int>&key,int loc );
void DeleteMax(vector<int>& H,vector<int>&key,int& x);
void print(vector<int>&H);
bool find(vector<int>&H,const int&x,int& loc);

#endif 