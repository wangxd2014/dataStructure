#include "MST.h"
/*
	// �����ڵ�֮���Ȩ�ز���Ϊ����������ǳ����ȱ��

	����: ��Ȩ����ͼ
	���: ��С������

	1. �ò��ཻ�����ݽṹʵ��kruskal�㷨
	2. ����С�����ݽṹʵ��prim�㷨

	3.�������ñ߱�ʾ������ô���Ҳ��һ������.����Ľ���������һ���ߡ�

ʱ�䣺 2017-4-2
   1. �������ڵ�֮�����������⣿�ڵ�1���ڵ�n֮��������
   2. �����������ڵ�֮���������� 

*/

int main(){
	MST mst;
	vector<Edges> res;

	// ʵ��1
	if(!mst.readGraph("example2.txt")){ // ʵ��example.txt example2.txt
		printf("the file is not accept\n");
		return 0;
	}
	//mst.printGraph();
	//quicksort(mst.allEdges,0,mst.nEdges-1);

	mst.kruskal(res);
	//for(int i=0;i<mst.allEdges.size();++i){
	//	cout<<mst.allEdges[i].start+1<<" "<<mst.allEdges[i].end+1<<" "<<mst.allEdges[i].weight<<endl;
	//}
	cout<<"kruskal:�����С������"<<endl;
	for(int i=0;i<res.size();++i){
		cout<<res[i].start+1<<" "<<res[i].end+1<<" "<<res[i].weight<<endl;
	}

	// primʵ��

	MST mst1;
	vector<Edges> res1;
	if(!mst1.readGraph("example2.txt")){ // ʵ��example.txt example2.txt
		printf("the file is not accept\n");
		return 0;
	}
	mst1.prim(res1);
	cout<<"Prim:�����С������"<<endl;
	for(int i=0;i<res1.size();++i){
		cout<<res1[i].start+1<<" "<<res1[i].end+1<<" "<<res1[i].weight<<endl;
	}

	// max flow
	cout << "ʵ��3�����������" << endl;
	MST mst2;
	if (!mst2.readGraph("example3.txt")){ // ʵ��example.txt example2.txt
		printf("the file is not accept\n");
		return 0;
	}
	mst2.printGraph();
	mst2.maxflowAny(0,mst2.nNodes-4);

	system("pause");
	return 0;
}