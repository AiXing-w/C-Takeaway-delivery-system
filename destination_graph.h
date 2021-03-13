/*
地图信息
*/
#ifndef _DESTINATION_GRAPH_H_
#define _DESTINATION_GRAPH_H_
#include<iostream>
#define MAX_DESTINATION 15
using namespace std;

typedef struct DestinationGraph{
	string vex[MAX_DESTINATION];
	//读入地点后先对地点排序
	//这里用地点对应的角标来代表地点
	float matrix[MAX_DESTINATION][MAX_DESTINATION];
	int vexnum, arcnum;
	bool IsFinded;
	float D[MAX_DESTINATION][MAX_DESTINATION];//用经压缩后数组的储存最短距离
	int Path[MAX_DESTINATION][MAX_DESTINATION];//路短路径
}DestinationGraph;

void Sort_Destination(DestinationGraph &G);//将地点排序
int Find_Destination(DestinationGraph &G, string e);//寻找地点对应的下标（二分法）
void Init_DestinationGraph(DestinationGraph &G);//初始化图
void Traverse_Destination(DestinationGraph G);//输出地点
void Traverse_Distance(DestinationGraph G);//输出距离表
void ShortestPath(DestinationGraph &G);//佛洛依德算法求最短路径
void PrintShortedPath(DestinationGraph G, int start, int end);//打印最短路径
//int Get_subscript(int i,int j);

#endif