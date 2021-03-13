/*
����ͳ��
*/
#ifndef _COUNT_ORDER_H_
#define _COUNT_ORDER_H_

#include<iostream>
#include<string>
#include<new>
#include<fstream>
#include"destination_graph.h"
#include"order_linkqueue.h"
#include"set_sqlist.h"
#include"Count_order.h"
#include"OrderCountList.h"
#define OK 1
#define ERROR 0
using namespace std;
typedef int Status;
typedef struct CountSElem{
	//����ͳ���ײ�
	char mark1;//���1
	int mark2;//���2
	int delivetotal;//����������
	int undelivetotal;//δ��������
	int canceltotal;//��ȡ������
	float totalprice;//�ܽ��
}CountSElem;
typedef struct CountSList{
	CountSElem * elem;
	int length;
}CountSList;

typedef struct CountDElem{
	string destination;
	int cnt;
}CountDElem;
typedef struct CountDList{
	CountDElem * elem;
	int sumd;//�ص�����
	int length;
}CountDList;

bool CmpS(CountSElem a, CountSElem b);//
Status InitCountSList(CountSList &L, int n);//��ʼ��
Status InitCountDList(CountDList &D, int n);
Status CountSet(string start, string end, OrderCountList C, SetList S, Order_LinkQueue Q);//����ͳ��
void Destination_Count(Order_LinkQueue Q, OrderCountList C, DestinationGraph G);//�ص�ͳ��
void HeapAdjust(CountSList &L, int s, int m);//
void Heap_Sort_S(CountSList &L);//
void CreateHeap(CountSList &L);//

#endif