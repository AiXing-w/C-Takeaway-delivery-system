/*
套餐表
*/
#ifndef _SET_SQLIST_H_
#define _SET_SQLIST_H_

#include<iostream>
#include<string>
#include"destination_graph.h"
#include"order_linkqueue.h"
#define SETOVERFLOW -2
#define OK 1
#define ERROR 0

typedef int Status;

using namespace std;

typedef struct SetElem{
	char mark1;//套餐第一位:字符
	int mark2;//套餐第二位:编号
	string name;//套餐名称
	string describe;//描述
	int price;//价格
	bool state;//状态：1为可预订，0为不可预订
}SetElem;
typedef struct SetList{
	SetElem * setmea;
	int maxelem;
	int length;
}SetList;
void InitList(SetList &L);//初始化
Status AppendSet(SetList &L, SetElem e);//添加套餐
void TraverseSet(SetList L);//遍历套餐表
void PrintReserveSet(SetList L);//便利可预订套餐 
#endif
