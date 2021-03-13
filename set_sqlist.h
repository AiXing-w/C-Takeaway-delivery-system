/*
�ײͱ�
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
	char mark1;//�ײ͵�һλ:�ַ�
	int mark2;//�ײ͵ڶ�λ:���
	string name;//�ײ�����
	string describe;//����
	int price;//�۸�
	bool state;//״̬��1Ϊ��Ԥ����0Ϊ����Ԥ��
}SetElem;
typedef struct SetList{
	SetElem * setmea;
	int maxelem;
	int length;
}SetList;
void InitList(SetList &L);//��ʼ��
Status AppendSet(SetList &L, SetElem e);//����ײ�
void TraverseSet(SetList L);//�����ײͱ�
void PrintReserveSet(SetList L);//������Ԥ���ײ� 
#endif
