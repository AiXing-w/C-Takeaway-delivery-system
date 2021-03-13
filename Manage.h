/*
��������ϵͳѡ�� 
*/
#ifndef _Order_manage_H_
#define _Order_manage_H_
#include<iostream>
#include"order_linkqueue.h"
#include"set_sqlist.h"
#include"destination_graph.h"
#include"OrderCountList.h"
#include"Menu.h"
#define OK 1
#define ERROR 0
#define MAX_DESTINATION 15
typedef int Status;

using namespace std;
void Application();//��������
Status Start_work(SetList &S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph &G);//��ʼ�ϰ� 
void Order_manage(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G);//��������
void Receive_Orders(DestinationGraph G, SetList S, Order_LinkQueue &Q);//���ն���
void OrderModify(SetList S, DestinationGraph G, Order_LinkQueue &Q,bool option);//�޸Ķ���
void OrderInquiry(Order_LinkQueue Q);//��ѯ����
void Get_OccurTime(string &date1, string &date2);//��ȡ��ǰʱ�䣬��ȡ���ָ�ʽ����
void Delivery(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G, string &location);//���Ͷ���
void Data_maintenance(SetList &S);//��������ά��  
void Date_Count(Order_LinkQueue Q, OrderCountList C, SetList S, char option);//����ͳ�ƣ�option Ϊ'd'����ͳ�ƣ� optionΪ'w'����ͳ�ƣ�optionΪ'm'����ͳ�ƣ�
void Statistics(Order_LinkQueue Q, OrderCountList C, DestinationGraph G, SetList S);//ͳ��
void Off_work(Order_LinkQueue Q, SetList S);//�°� 
#endif
