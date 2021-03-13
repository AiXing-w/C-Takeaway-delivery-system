/*
订单管理系统选项 
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
void Application();//启动程序
Status Start_work(SetList &S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph &G);//开始上班 
void Order_manage(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G);//订单管理
void Receive_Orders(DestinationGraph G, SetList S, Order_LinkQueue &Q);//接收订单
void OrderModify(SetList S, DestinationGraph G, Order_LinkQueue &Q,bool option);//修改订单
void OrderInquiry(Order_LinkQueue Q);//查询订单
void Get_OccurTime(string &date1, string &date2);//获取当前时间，获取两种格式返回
void Delivery(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G, string &location);//派送订单
void Data_maintenance(SetList &S);//基础数据维护  
void Date_Count(Order_LinkQueue Q, OrderCountList C, SetList S, char option);//进行统计（option 为'd'按天统计， option为'w'按周统计，option为'm'按月统计）
void Statistics(Order_LinkQueue Q, OrderCountList C, DestinationGraph G, SetList S);//统计
void Off_work(Order_LinkQueue Q, SetList S);//下班 
#endif
