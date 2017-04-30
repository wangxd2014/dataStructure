#include "MinHeap.h"

void SiftUp(vector<int>& H,vector<int>&key,int loc){
	bool done=true; 
	int i,t;
	i=loc;
	//printf("i=%d\n",i);
	if(i==0) 
		return;
	while(i!=0 && done ){
		t=(i-1)>>1; // 这个并不会改变i 
		if( key[ H[i] ] < key[ H[t]] )
			swap(H[i],H[t]);
		else
			done=false;
		i=t; 
	/*	printf("t=%d ",t);
		if(i<=0)
			break; */
	}
}

void SiftDown(vector<int>& H,vector<int>&key,int loc){
	bool done=true;
	int i=loc,t;
	if( H.size()<(2*i+2) )
		return;
	while( (2*i+2)<=H.size() && done ){
		i=2*i+1; // 如果i从0开始呢？   
		if( (i+1)< H.size() && key[ H[i+1] ] < key[ H[i] ] ) 
			++i;
		t=(i-1)>>1; //向左平移一位是除以2 
		if( key[ H[t] ] > key[ H[i] ] ) 
			swap(H[i],H[t]);
		else
			done=false;
		//printf("i=%d,t=%d \n",i,t);
	}
}

void Insert(vector<int>& H,vector<int>&key,int x){
	H.push_back(x); // H的长度增加1 
	SiftUp(H,key,H.size()-1);
}

void Delete(vector<int>& H,vector<int>&key,int loc ){
	int x,y;
	x=H[loc];
	y=H[H.size()-1];
	H.pop_back(); // 删除最后一个元素
	if( loc== H.size()) // 表明是最后一个元素 
		return;
	H[loc]=y;
	if( key[y] <= key[x] )
		SiftUp(H,key,loc); 
	else
		SiftDown(H,key,loc);	
}

void DeleteMax(vector<int>& H,vector<int>&key,int& x){
	// x是返回值 所以必须使用引用 
	x=H[0];
	Delete(H,key,0); 
} 

bool find(vector<int>&H,const int&x,int& loc){
	for(int i=0;i<H.size();++i){
		if(H[i]==x){
			loc=i;
			return true;
		}
	}
	return false;
}

void print(vector<int>&H){
	for(int i=0;i<H.size();++i){
		cout<<H[i]<<" ";
	}
	cout<<endl;
} 