#include "MST.h"

//快速排序 根据权重对边进行排序
void swap(Edges& x,Edges& y){
	swap(x.start,y.start);
	swap(x.end,y.end);
	swap(x.weight,y.weight);
}

void split(vector<Edges>&A,const int& low,const int&high,int &w){
	// high的最大值是A的size -1
	int i,j;
	int x;
	i=low;
	x=A[low].weight;
	for(j=low+1;j<=high;++j){
		if(A[j].weight<=x){
			++i;
			if(i!=j){
				swap(A[i],A[j]);
			} 
		}
		
	} 
	swap(A[low],A[i]);
	w=i;	
} 

void quicksort(vector<Edges>&A,const int &low,const int&high ){
	int w;
	if(low<high){
		split(A,low,high,w);
		quicksort(A,low,w-1);
		quicksort(A,w+1,high);
	}	
}

MST::MST(void)
{
	nNodes=0;
	nEdges=0;
}


MST::~MST(void)
{
}

bool MST::readGraph(char *name){
	ifstream file(name,ios_base::in);
	if(!file.is_open())  // 判断有没有打开
	 {
	 	printf(" readGraph()  error:there is no such file ");
	 	return false; 
	 }

	int x,y,w,cost; // 节点，节点，权重
	Edges temp; 
	string L1;
	istringstream ss; // 从L1中提取x和y
	nEdges=0;
	while(getline(file,L1))
	 {
	 	ss.clear();
	 	ss.str(L1);
	    ss>>x>>y>>w>>cost;
		if( nNodes < x || nNodes < y )
		{
			nNodes=x>y?x:y;
			adjList.resize(nNodes);
			weight.resize(nNodes);
			edgeCost.resize(nNodes);
		}
		if(x<y){//这里只存储一半的个体在edges之中
			temp.start=x-1;
			temp.end=y-1;
			temp.weight=w;
			allEdges.push_back(temp);
		}
		adjList[x-1].push_back(y-1);
		weight[x-1].push_back(w);
		edgeCost[x - 1].push_back(cost);
		++nEdges;
	 }
	nEdges=nEdges>>1;
	file.close();
	return true;
}
void MST::printGraph(){
	//输出图检验图是否正确
	cout<<"输出图"<<endl;
	cout<<"总的节点数目是: "<<nNodes<<endl;
	cout<<"总的边数是:"<<nEdges<<endl;
	for(int i=0;i<nNodes;++i){
		for(int j=0;j<adjList[i].size();++j){
			if(i>= adjList[i][j])
				continue;
			cout<<i+1<<" "<<adjList[i][j]+1<<" "<<weight[i][j]<<endl;
		}
	}

}


void MST::kruskal(vector<Edges>& res){
	// res输出最后的结果 其实里面存储的是边
	quicksort(allEdges,0,nEdges-1);
	int *rank=new int[nNodes](); // 这样就初始化为0
	vector<int> T(nNodes,-1);
	int i,s,e,root1,root2;
	for(i=0;i<nEdges;++i){
		s=allEdges[i].start;
		e=allEdges[i].end;
		Find(T,s,root1);
		Find(T,e,root2);
		//cout<<"s= "<<s<<" e= "<<e<<" root1 "<<root1<<" root2= "<<root2<<endl;;
		if( root1!=root2 || (root1==root2 && root1==-1)){
			Union(T,rank,s,e);
			res.push_back(allEdges[i]);
		}
	}
	//cout<<"输出T"<<endl;
	//for(i=0;i<T.size();++i){
	//	cout<<T[i]<<" ";
	//}
	//cout<<endl;
	delete[] rank;
}

void MST::prim(vector<Edges>& res){
	int s,x,loc;
	Edges temp;
	vector<int> X(nNodes,0);
	vector<int> N(nNodes,-1);
	vector<int> C(nNodes,-1);
	vector<int> H;
	// 从节点1开始
	s=0;
	X[s]=1;
	int i,j;
	for(i=0;i<adjList[s].size();++i){
		N[ adjList[s][i] ] = 0;
		C[ adjList[s][i] ] = weight[s][i];
		Insert(H,C,adjList[s][i]);
	}
	//print(H);
	for(i=0;i<nNodes;++i){
		if(C[i]<0) // 代价不能为负数
			C[i]=UNLIMIT;
	}
	for(i=0;i<nNodes;++i){
		if(i==s)
			continue;
		temp.weight=C[H[0]];
		DeleteMax(H,C,x);
		temp.start=x;
		temp.end=N[x];
		res.push_back(temp);
		X[x]=1;
		for(j=0;j<adjList[x].size();++j ){
			if(X[adjList[x][j]])
				continue;
			if( weight[x][ j ] < C[ adjList[x][j] ] ){
				N[ adjList[x][j] ]= x;
				C[ adjList[x][j] ]=weight[x][ j ];
			}
			loc=-1;
			if(find(H,adjList[x][j],loc)){
				SiftUp(H,C,loc);
			}else{
				Insert(H,C,adjList[x][j]);
			}

		}

	}
}

template<typename T>
void print(T* x,int _len){
	for (int i = 0; i < _len; ++i){
		cout << x[i] << "";
	}
	cout << endl;
}

void printPath(vector<int>&H){
	int i;
	for ( i = 0; i < H.size() - 2; ++i)
		cout << H[i] << '-->';
	cout << H[i] << " low=" << H[i+1]<<endl;
}

void MST::maxflow(int s, int d){
	// 节点1 到节点之间的最大流
	int **adjmatrix =(int **) malloc(sizeof(int *)*nNodes);
	bool *visit =(bool *)malloc(nNodes*sizeof(bool));
	int *father = (int *)malloc(nNodes*sizeof(int));
	int maxFlow=0;
	int i, j, k,t;
	vector<vector<int> > allpath;
	for (i = 0; i < nNodes; ++i){
		adjmatrix[i] = (int *)malloc(nNodes*sizeof(int));
	}

	for (i = 0; i < nNodes; ++i){
		for (j = 0; j < nNodes; ++j){
			adjmatrix[i][j]=0;
		}
	}

	for (i = 0; i < adjList.size(); ++i){
		for (j = 0; j < adjList[i].size(); ++j){
			t = adjList[i][j];
			adjmatrix[i][t] = weight[i][j];
		}
	}

	while (1){
		queue<int> q;
		memset(visit,0,sizeof(bool)*nNodes);
		memset(father,0,sizeof(int)*nNodes);
		vector<int> path;
		int now;
		visit[s] = 1;
		q.push(s);
		while (!q.empty()){
			now = q.front();
			q.pop();
			if (now == d) break;
			for (i = 0; i < nNodes; ++i){
				if (adjmatrix[now][i] && !visit[i]){
					father[i] = now;
					visit[i] = true;
					q.push(i);
				}
			}
		}
		if (!visit[d])
			break;

		int u, min = 0xFFFF;
		//寻找一条路径上的最小权值
		for (u = d; u; u = father[u]){
			if (adjmatrix[father[u]][u] < min){
				min = adjmatrix[father[u]][u];
			}
		}
		// 衰减权值
		for (u = d; u; u = father[u]){
			adjmatrix[father[u]][u] -= min;
			adjmatrix[u][father[u] ] += min;// 存在环的话,这句话是关键
			path.push_back(u);
		}
		path.push_back(s);
		path.push_back(min);
		maxFlow += min;
		allpath.push_back(path);
	}
	
	cout << "maxFlow " << maxFlow << endl;
	for (i = 0; i < allpath.size(); ++i){
		for (j = 0; j < allpath[i].size()-2; ++j)
			cout << allpath[i][j]<<"-->";
		cout << allpath[i][j] << " flow=" << allpath[i][j+1] << endl;
	}
	for (i = 0; i < nNodes; ++i){
		free(adjmatrix[i]);
	}
	free(father);
	free(visit);
}

void MST::maxflowAny(int s, int d){
	// 节点1 到节点之间的最大流
	int **adjmatrix = (int **)malloc(sizeof(int *)*nNodes);
	bool *visit = (bool *)malloc(nNodes*sizeof(bool));
	int *father = (int *)malloc(nNodes*sizeof(int));
	int maxFlow = 0;
	int i, j, k, t;
	vector<vector<int> > allpath;
	for (i = 0; i < nNodes; ++i){
		adjmatrix[i] = (int *)malloc(nNodes*sizeof(int));
	}

	for (i = 0; i < nNodes; ++i){
		for (j = 0; j < nNodes; ++j){
			adjmatrix[i][j] = 0;
		}
	}


	for (i = 0; i < adjList.size(); ++i){
		for (j = 0; j < adjList[i].size(); ++j){
			t = adjList[i][j];
			adjmatrix[i][t] = weight[i][j];
		}
	}
	
	while (1){
		queue<int> q;
		memset(visit, 0, sizeof(bool)*nNodes);
		memset(father, -1, sizeof(int)*nNodes);
		vector<int> path;
		int now;
		visit[s] = 1;
		q.push(s);
		while (!q.empty()){
			now = q.front();
			q.pop();
			if (now == d) break;
			cout << adjList[now].size() << endl;
 			for (i = 0; i < adjList[now].size(); ++i){
				t = adjList[now][i];
				if (adjmatrix[now][t] && !visit[t]){
					printf("t=%d \n",t);
					father[t] = now;
					visit[t] = true;
					q.push(t);
				}
			}
		}
		if (!visit[d])
			break;

		int u, min = 0xFFFF;
		//寻找一条路径上的最小权值
		for (u = d; u!=s; u = father[u]){
			if (adjmatrix[father[u]][u] < min){
				min = adjmatrix[father[u]][u];
			}
		}
		// 衰减权值
		for (u = d; u!=s; u = father[u]){
			adjmatrix[father[u]][u] -= min;
			adjmatrix[u][father[u]] += min;// 存在环的话,这句话是关键
			path.push_back(u);
		}
		path.push_back(s);
		path.push_back(min);
		maxFlow += min;
		allpath.push_back(path);
	}

	cout << "maxFlow " << maxFlow << endl;
	for (i = 0; i < allpath.size(); ++i){
		for (j = 0; j < allpath[i].size() - 2; ++j)
			cout << allpath[i][j] << "-->";
		cout << allpath[i][j] << " flow=" << allpath[i][j + 1] << endl;
	}

	for (i = 0; i < nNodes; ++i){
		free(adjmatrix[i]);
	}

	free(father);
	free(visit);

}

void MST::maxflowAnyCost(int s, int d, int limit){
	


}

void MST::level(int s, int d){
	//找层次图
	bool *visit = (bool *)malloc(nNodes*sizeof(bool));
	int *father = (int *)malloc(nNodes*sizeof(int));
	int *level = (int *)malloc(nNodes*sizeof(int));
	int maxFlow = 0;
	int i, j, k, t,now,maxLevel;
	queue<int> Que;
	visit[s] = 1;
	Que.push(s);
	maxLevel = 0;
	while (Que.size()){
		now = Que.front();
		Que.pop();
		int now;
		for (i = 0; i < adjList[now].size(); ++i){
			t = adjList[now][i];
			if (!visit[t] ){
				father[t];
			}
		}


	}

    
	free(level);
	free(father);
	free(visit);
}