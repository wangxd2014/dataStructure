#include "MST.h"
/*
	// 两个节点之间的权重不能为负数，这就是程序的缺陷

	输入: 加权无向图
	输出: 最小生成树

	1. 用不相交集数据结构实现kruskal算法
	2. 用最小堆数据结构实现prim算法

	3.输出结果用边表示，树怎么输出也是一个难题.这里的结果的输出是一条边。

时间： 2017-4-2
   1. 求两个节点之间的最大流问题？节点1到节点n之间的最大流
   2. 求任意两个节点之间的最大流？ 

*/

int main(){
	MST mst;
	vector<Edges> res;

	// 实验1
	if(!mst.readGraph("example2.txt")){ // 实验example.txt example2.txt
		printf("the file is not accept\n");
		return 0;
	}
	//mst.printGraph();
	//quicksort(mst.allEdges,0,mst.nEdges-1);

	mst.kruskal(res);
	//for(int i=0;i<mst.allEdges.size();++i){
	//	cout<<mst.allEdges[i].start+1<<" "<<mst.allEdges[i].end+1<<" "<<mst.allEdges[i].weight<<endl;
	//}
	cout<<"kruskal:输出最小生成树"<<endl;
	for(int i=0;i<res.size();++i){
		cout<<res[i].start+1<<" "<<res[i].end+1<<" "<<res[i].weight<<endl;
	}

	// prim实验

	MST mst1;
	vector<Edges> res1;
	if(!mst1.readGraph("example2.txt")){ // 实验example.txt example2.txt
		printf("the file is not accept\n");
		return 0;
	}
	mst1.prim(res1);
	cout<<"Prim:输出最小生成树"<<endl;
	for(int i=0;i<res1.size();++i){
		cout<<res1[i].start+1<<" "<<res1[i].end+1<<" "<<res1[i].weight<<endl;
	}

	// max flow
	cout << "实验3：最大流问题" << endl;
	MST mst2;
	if (!mst2.readGraph("example3.txt")){ // 实验example.txt example2.txt
		printf("the file is not accept\n");
		return 0;
	}
	mst2.printGraph();
	mst2.maxflowAny(0,mst2.nNodes-4);

	system("pause");
	return 0;
}