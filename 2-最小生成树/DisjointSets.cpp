#include "DisjointSets.h"
  
//只有这两个操作吗？怪不得号称最简单的数据结构
void Find(vector<int>& D,const int& x,int&root){
	int y,w;
	y=x;
	while(D[y]!=-1 ){
		y=D[y];
	}
	root=y;
	y=x;
	while(D[y]!=-1 ){ //执行路径压缩 
		w=D[y];
		D[y]=root;
		y=w;
	}
} 

void Union(vector<int>& D,int *rank,const int& x,const int& y){
	int u,v;
	Find(D,x,u);
	Find(D,y,v); 
	if(rank[u]<=rank[v]){
		D[u]=v;
		if( rank[u]==rank[v] )
			++rank[v];	
	}else {
		D[v]=u;
	}
}
