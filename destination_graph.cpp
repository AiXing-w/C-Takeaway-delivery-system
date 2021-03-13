/*
地图
*/
#include"destination_graph.h"
#include<iostream>
#include<cstdio>
#include<string>

using namespace std;
#define MAX_DESTINATION 15
#define INFINITY 3000.0//
void Sort_Destination(DestinationGraph &G){
	//对地图中的地点按字典序排序
	int m = G.vexnum - 1, j;
	bool flag = true;//用来观察当前趟数有没有发生交换
	while((m > 0) && flag){
		flag = false;
		for(j = 0; j < m; j++){
			if(G.vex[j] > G.vex[j+1]){
				flag = true;
				string tmp;
				tmp = G.vex[j];
				G.vex[j] = G.vex[j+1];
				G.vex[j+1] = tmp;
			}
		}

	}
}
int Find_Destination(DestinationGraph &G, string e){
	//查找地点(二分查找:查到了返回下标，查不到返回-1）
	int low = 0, mid, high = G.vexnum - 1;
	while(low <= high){
		mid = (low + high) / 2;
		if(G.vex[mid] == e)
			return mid;
		else if(e < G.vex[mid]){
			high = mid - 1;
		}else {
			low = mid + 1;
		}
	}
	return -1;
}
void Init_DestinationGraph(DestinationGraph &G){
	//初始化图
	G.vexnum = 0;
	G.arcnum = 0;
	G.IsFinded = false;
	int i, j;
	for(i=0 ; i < MAX_DESTINATION; i++)
		for(j=0; j < MAX_DESTINATION; j++){
			G.matrix[i][j] = G.matrix[j][i] = INFINITY;
			G.D[i][j] = G.D[j][i] = INFINITY;
		}
}
void Traverse_Destination(DestinationGraph G){
	//遍历
	int i;
	cout << "可选送餐地点:"<<endl;
	for(i=0; i < G.vexnum ;i++){
		cout << G.vex[i] << " ";
	}
	cout <<endl;
}
void Traverse_Distance(DestinationGraph G){
	cout<<"距离表："<<endl;
	int i, j;
	int cnt = 0;
	for(i=0; i < G.vexnum ;i++){
		for(j=0; j<= i ;j++){
			if(G.matrix[i][j]!= INFINITY){
				printf("%12s ->%10s : %.2f",G.vex[i].c_str(), G.vex[j].c_str(), G.matrix[i][j]);
				++cnt;
				if(cnt % 3 == 0)
					cout<<endl;
			}
			
		}
	}
	cout<<endl;
}
void ShortestPath(DestinationGraph &G){
	int i,j,k;
	if(G.IsFinded)
		return ;
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++){
			G.D[i][j]=G.matrix[i][j];
			if((G.D[i][j]<INFINITY)&&(i!=j))
				G.Path[i][j]=i;
			else
				G.Path[i][j] = -1;
		}
	}
	for(k=0;k<G.vexnum;k++)
	for(i=0;i<G.vexnum;i++)
	for(j=0;j<G.vexnum;j++)
	if((G.D[i][k] + G.D[k][j] < G.D[i][j]) && i != j){
		G.D[i][j]=G.D[i][k]+G.D[k][j];
		G.Path[i][j]=G.Path[k][j];
	} 
	G.IsFinded = true;
}
void PrintShortedPath(DestinationGraph G, int end, int start){
	//打印最短路径
	int j;
	for(j=end; j !=-1; j=G.Path[start][j]){
		if(G.Path[start][j] != -1){
			cout<<G.vex[j]<<"->";
		}else{
			cout<<G.vex[j]<<endl;
		}
	}
	cout<<endl;
}
