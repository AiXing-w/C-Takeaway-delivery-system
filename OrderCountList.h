/*
����ͳ�Ʊ�
*/
#ifndef _ORDERCOUNTLIST_H_
#define _ORDERCOUNTLIST_H_

#include<iostream>

using namespace std;

typedef int Status;
typedef struct OrderCountElem{
	string ordernumber;//�������
	char setmark1;//�ײͱ��1����������ĸ��
	int setmark2;//�ײͱ��2������е����֣�
	int totalset;//�ײ�����
	int totalprice;//�ܽ��
	string destination;//�ص�
	string ordertime;//�µ�ʱ��
	int orderstate;//����״̬ �� 0-��ȡ�� 1-δ���� 2-������
}OrderCountElem;
typedef struct OrderCountList{
	OrderCountElem * elem;
	int maxsize;
	int length;
}OrderCountList;

void InitOrderCountList(OrderCountList &L);//��ʼ��
Status AppendOrderElem(OrderCountList &L, OrderCountElem e);//����ײ�

#endif