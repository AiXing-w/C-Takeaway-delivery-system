/*
��������
*/
#ifndef _ORDER_LINKQUEUE_H_
#define _ORDER_LINKQUEUE_H_

#include<iostream>
#include"destination_graph.h"
#include<string>
#define OK 1
#define ERROR 0

using namespace std;
typedef int Status;

typedef struct OrderQueue_Elem{
	string ordernumber;//�������
	char setmark1;//�ײͱ��1����������ĸ��
	int setmark2;//�ײͱ��2������е����֣�
	int totalset;//�ײ�����
	int price;//�۸�
	string name;//����������
	string number;//�����˵绰
	string destination;//�ص�
	string ordertime;//�µ�ʱ�䣨�Զ����ɣ�
	int orderstate;//����״̬ �� 0-��ȡ�� 1-δ���� 2-������
}OrderQueue_Elem;

typedef struct OrderQueue_Node{
	OrderQueue_Elem orderelem;
	struct OrderQueue_Node * next;
}OrderQueue_Node, * OrderQueue_Ptr;

typedef struct{
	OrderQueue_Ptr front;
	OrderQueue_Ptr rear;
	int length;
}Order_LinkQueue;

Status Init_OrderQueue(Order_LinkQueue &Q);//��ʼ����������
bool OrderQueue_Empty(Order_LinkQueue Q);//�ж϶��������Ƿ�Ϊ��
int OrderQueue_Length(Order_LinkQueue Q);//���ض��г���
Status Get_OrderQueue_Head(Order_LinkQueue Q, OrderQueue_Elem &e);//��ö���Ԫ��
Status Delete_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem &e);//ɾ�����׶��������ظö���
Status En_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem e);//�¶����������
void Traverse_UnDelivery(Order_LinkQueue Q);//����δ���Ͷ���
void Traverse_OrderQueue(Order_LinkQueue Q);//�������������еĶ���
void OrderNumber_Search(Order_LinkQueue Q,string number);//�������Ų�ѯ���������
void OrderName_Search(Order_LinkQueue Q, string name);//������������ѯ���������

#endif