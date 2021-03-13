/*
��ͼ��Ϣ
*/
#ifndef _DESTINATION_GRAPH_H_
#define _DESTINATION_GRAPH_H_
#include<iostream>
#define MAX_DESTINATION 15
using namespace std;

typedef struct DestinationGraph{
	string vex[MAX_DESTINATION];
	//����ص���ȶԵص�����
	//�����õص��Ӧ�ĽǱ�������ص�
	float matrix[MAX_DESTINATION][MAX_DESTINATION];
	int vexnum, arcnum;
	bool IsFinded;
	float D[MAX_DESTINATION][MAX_DESTINATION];//�þ�ѹ��������Ĵ�����̾���
	int Path[MAX_DESTINATION][MAX_DESTINATION];//·��·��
}DestinationGraph;

void Sort_Destination(DestinationGraph &G);//���ص�����
int Find_Destination(DestinationGraph &G, string e);//Ѱ�ҵص��Ӧ���±꣨���ַ���
void Init_DestinationGraph(DestinationGraph &G);//��ʼ��ͼ
void Traverse_Destination(DestinationGraph G);//����ص�
void Traverse_Distance(DestinationGraph G);//��������
void ShortestPath(DestinationGraph &G);//���������㷨�����·��
void PrintShortedPath(DestinationGraph G, int start, int end);//��ӡ���·��
//int Get_subscript(int i,int j);

#endif