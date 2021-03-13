/*
用于统计
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
	//用来统计套餐
	char mark1;//编号1
	int mark2;//编号2
	int delivetotal;//已派送总数
	int undelivetotal;//未派送总数
	int canceltotal;//已取消总数
	float totalprice;//总金额
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
	int sumd;//地点总数
	int length;
}CountDList;

bool CmpS(CountSElem a, CountSElem b);//
Status InitCountSList(CountSList &L, int n);//初始化
Status InitCountDList(CountDList &D, int n);
Status CountSet(string start, string end, OrderCountList C, SetList S, Order_LinkQueue Q);//进行统计
void Destination_Count(Order_LinkQueue Q, OrderCountList C, DestinationGraph G);//地点统计
void HeapAdjust(CountSList &L, int s, int m);//
void Heap_Sort_S(CountSList &L);//
void CreateHeap(CountSList &L);//

#endif