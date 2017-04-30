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
  1. ���ʵ��hashtable ʹ�ÿ��ŵ�ַ��;
  2. ��ʵ����֤ 
    1.1  �α��ϵ�����
	1.2  letcode�����ǵ�������һ�� 
	
  3. leetcode��δͨ��
    3.1 ���ӣ�[0,3,4,0] target=0; ��hashtable��sizeȡ4 ��ʱ�򣬻���������ѭ��	
    3.2 ����ĵط�������������Hash_find�� 
	   3.2.1  while( i!=(k-1) && (node=hashmap->storage[i])) ��k=0��ʱ���ǲ��Ǿ���������ѭ���ˣ�
	   3.2.2 ��size ȡ �����С��ʱ�� 
	   3.2.3  i= hashmap->size <= i ? i+1:0; ��仰Ҳ�Ǵ����
	     ����error
		   3.2.3.1   ��i>=hashmap->size,��ʱ��i++����i< hashmap->size��ʱ�򷴶���0.��ô��i=0 ��ʱ����ѭ��������һֱ����0��
		   3.2.3.2  �����޸ĳ��� i= hashmap->size <= i ? 0:i+1; ��Ȼ��error 
		            ��i����hashmap->size-1��ʱ����ôi=i+1 ��ʱi���� hashmap->size ��ô ��ʱhashmap->storage[i]���ڲ����� 
	3.3 ��hashtable��sizeȡ�Ĺ�С��ʱ��������Ҳ����ڣ�Ч�ʾ��൱��˳������ˣ�����hashtable��size����̫С 
����ط���
   0.  hashmap->size û�г�ʼ�� 
   1. �����鿪���ڴ�ĵط���������©������û��free��	
   	
*/
/*
	�������c����c,c++�ֲ����ף���
	������������������Ҳ�鷳���˶��٣�HashNode ���������һ��ָ�� 
	
	1. Ϊʲôһ��Ҫȡabs��
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
		1.��һ��д��ʱ��Ҫ�ر�ע��
		  1.1 ��� hashmap->storage[k]==NULL
		  1.2 ��� hashmap->storage[k]!=NULL but  hashmap->storage[k]->key!=key
		  1.2 ���ҳɹ�
		  ������������ǲ�һ����
		  so
		   1.���ж�  hashmap->storage[k]�ǲ��ǿգ������ֱ�ӷ���NULL
		   2.������ǿգ����ǹؼ��ֲ���ȣ���ô��һֱ������������ҳɹ�����������ָ�� 
	
	*/
	int i=k; 
	int limit=k-1;
	if( (k-1)<0 )
		limit +=hashmap->size; 
	while( i!=limit && (node=hashmap->storage[i])) { //���ѭ���᲻�����޽�����ȥ  ����λ��ȫ������ֵ�������ǲ��Ҳ��ɹ� 
		if(node->key==key){
			break;
		}
	
		(hashmap->size-1)<=i?0:++i; 
		
		//  i= hashmap->size <= i ? i+1:0;
		// �������һ�仰������bug 
		//  + ��仰������ƺ�����ģ���i>=hashmap->size,��ʱ��i++����i< hashmap->size��ʱ�򷴶���0.��ô��i=0 ��ʱ����ѭ��������һֱ����0��
		// �����޸ĳ��� i= hashmap->size <= i ? 0:i+1; ��Ȼ��error 
		//  + ��i����hashmap->size-1��ʱ����ôi=i+1 ��ʱi���� hashmap->size ��ô ��ʱhashmap->storage[i]���ڲ����� 
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
	cout<<"ʵ��2:Ϊʲôһ��Ҫȥabs(key)"<<endl;
	
	int a=-7;
	cout<<a%5<<endl;
	cout<<0%4<<endl;
	cout<<3%4<<endl;
	/* �ʣ� ��Ϊ�����Ļ����±�Ͳ����ɸ��� ; 
	   �� �±�Ϊ���Ļ���ΪʲôҪ�������hash�� ��һ��Ԫ���� -2  ��һ��Ԫ����11 ������-2+11=9 ��Ҳ������Ҫ��ġ�   
	*/

}


