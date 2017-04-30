#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <list> 

using namespace std;
/*
  1. 编程实现hashtable 使用开放地址法;
  2. 用实验验证 
    1.1  课本上的例题
	1.2  letcode上面那道题再做一遍 
	
  3. leetcode上未通过
    3.1 例子：[0,3,4,0] target=0; 当hashtable的size取4 的时候，会陷入无限循环	
    3.2 错误的地方有两个：函数Hash_find中 
	   3.2.1  while( i!=(k-1) && (node=hashmap->storage[i])) 当k=0的时候，是不是就陷入无限循环了？
	   3.2.2 当size 取 数组大小的时候， 
	   3.2.3  i= hashmap->size <= i ? i+1:0; 这句话也是错误的
	     两个error
		   3.2.3.1   当i>=hashmap->size,的时候，i++；当i< hashmap->size的时候反而是0.那么当i=0 的时候，在循环中岂不是一直都是0？
		   3.2.3.2  就算修改成了 i= hashmap->size <= i ? 0:i+1; 依然有error 
		            当i等于hashmap->size-1的时候，那么i=i+1 此时i等于 hashmap->size 那么 此时hashmap->storage[i]存在不存在 
	3.3 当hashtable的size取的过小的时候，如果查找不存在，效率就相当于顺序查找了，所以hashtable的size不能太小 
错误地方：
   0.  hashmap->size 没有初始化 
   1. 有三块开辟内存的地方，但是遗漏了两块没有free。	
   	
*/
/*
	代码评语：c不像c,c++又不彻底，渣
	就算是拉链法，估计也麻烦不了多少，HashNode 里面得增加一个指针 
	
	1. 为什么一定要取abs？
	2.  
	
*/ 

struct HashNode{
	int key;
	int val;
}; 

struct HashMap{
	int size;
	HashNode **storage;
	HashMap():size(0),storage(NULL){
	};
};

void Hash_create(HashMap* hashmap,int size);
HashNode* Hash_find(HashMap* hashmap,int key);
void Hash_insert(HashMap* hashmap,int key,int val);
void Hash_free(HashMap* hashmap);

void Hash_create(HashMap* hashmap,int size){
	hashmap->size=size;
	hashmap->storage=( HashNode**)calloc(size,sizeof(HashNode*));	
} 

void Hash_insert(HashMap* hashmap,int key,int val){
	int k=abs(key)%hashmap->size;
	HashNode *node=(HashNode*)malloc(sizeof(HashNode));
	node->key=key;
	node->val=val;
	while( hashmap->storage[k]){
		k++;
		if( hashmap->size<=k ){
			k=0;
		}
	}
	hashmap->storage[k]=node;
} 

HashNode* Hash_find(HashMap* hashmap,int key){
	int k=abs(key)%hashmap->size;
	HashNode *node=NULL;
	/*
		1.这一段写的时候要特别注意
		  1.1 如果 hashmap->storage[k]==NULL
		  1.2 如果 hashmap->storage[k]!=NULL but  hashmap->storage[k]->key!=key
		  1.2 查找成功
		  上述三种情况是不一样的
		  so
		   1.先判断  hashmap->storage[k]是不是空，如果是直接返回NULL
		   2.如果不是空，但是关键字不相等，那么就一直往后遍历，查找成功或者遇到空指针 
	
	*/
	int i=k; 
	int limit=k-1;
	if( (k-1)<0 )
		limit +=hashmap->size; 
	while( i!=limit && (node=hashmap->storage[i])) { //这段循环会不会无限进行下去  所有位置全部都有值，但就是查找不成功 
		if(node->key==key){
			break;
		}
	
		(hashmap->size-1)<=i?0:++i; 
		
		//  i= hashmap->size <= i ? i+1:0;
		// 就上面的一句话有两个bug 
		//  + 这句话本身就似乎错误的，当i>=hashmap->size,的时候，i++；当i< hashmap->size的时候反而是0.那么当i=0 的时候，在循环中岂不是一直都是0？
		// 就算修改成了 i= hashmap->size <= i ? 0:i+1; 依然有error 
		//  + 当i等于hashmap->size-1的时候，那么i=i+1 此时i等于 hashmap->size 那么 此时hashmap->storage[i]存在不存在 
	}
	return node;
} 

void Hash_free(HashMap* hashmap){
	for(size_t i=0;i<hashmap->size;++i){
		if(hashmap->storage[i])
			free(hashmap->storage[i]);
	}
	free(hashmap->storage); 
}

int main(){
	//int nums[4]={2,7,11,15};
	int nums[4]={0,4,3,0};
	int target=0;
	int size=4;
	HashMap *pHead=(HashMap*)malloc(sizeof(HashMap));
	Hash_create(pHead,size);   
	for(int i=0;i<size;++i){
		int res = target - nums[i];
		HashNode *p=Hash_find(pHead,res);
		if(p){
			printf("the result is (location,key): (%d,%d),(%d,%d)\n",i,nums[i],p->val,p->key);
			break;
		}else{
			Hash_insert(pHead,nums[i],i);
		}
	}
	
	Hash_free(pHead);
	free(pHead);
	cout<<"实验2:为什么一定要去abs(key)"<<endl;
	
	int a=-7;
	cout<<a%5<<endl;
	cout<<0%4<<endl;
	cout<<3%4<<endl;
	/* 问： 因为这样的话，下标就不会变成负的 ; 
	   答： 下标为负的话，为什么要将其插入hash表？ 若一个元素是 -2  另一个元素是11 ，则其-2+11=9 它也是满足要求的。   
	*/

}


