/*
订单队列
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
	string ordernumber;//订单编号
	char setmark1;//套餐编号1（编号里的字母）
	int setmark2;//套餐编号2（编号中的数字）
	int totalset;//套餐数量
	int price;//价格
	string name;//订餐人姓名
	string number;//订餐人电话
	string destination;//地点
	string ordertime;//下单时间（自动生成）
	int orderstate;//订餐状态 ： 0-已取消 1-未派送 2-已派送
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

Status Init_OrderQueue(Order_LinkQueue &Q);//初始化订单队列
bool OrderQueue_Empty(Order_LinkQueue Q);//判断订单队列是否为空
int OrderQueue_Length(Order_LinkQueue Q);//返回队列长度
Status Get_OrderQueue_Head(Order_LinkQueue Q, OrderQueue_Elem &e);//获得队首元素
Status Delete_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem &e);//删除队首订单并返回该订单
Status En_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem e);//新订单进入队列
void Traverse_UnDelivery(Order_LinkQueue Q);//遍历未派送订单
void Traverse_OrderQueue(Order_LinkQueue Q);//遍历队列中已有的订单
void OrderNumber_Search(Order_LinkQueue Q,string number);//按订单号查询订单并输出
void OrderName_Search(Order_LinkQueue Q, string name);//按订餐姓名查询订单并输出

#endif