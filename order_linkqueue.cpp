#include"order_linkqueue.h"
#include"Judge_And_Change.h"
#include<iostream>
#include<cstdio>
#include<new>
#define ERROR 0
#define OK 1
using namespace std;

Status Init_OrderQueue(Order_LinkQueue &Q){
	//初始化订单队列
	Q.front = Q.rear = new OrderQueue_Node;
	if(!Q.front ){
		cout<<"空间申请失败！"<<endl;
		return ERROR;
	}
	Q.front -> next = NULL;
	Q.length = 0;
	return OK;
}
bool OrderQueue_Empty(Order_LinkQueue Q){
	//判断订单队列是否为空
	return Q.length == 0; 
}
int OrderQueue_Length(Order_LinkQueue Q){
	//返回队列长度
	return Q.length;
}
Status Get_OrderQueue_Head(Order_LinkQueue Q, OrderQueue_Elem &e){
	//获得队首元素
	if(Q.front == Q.rear )
		return ERROR;
	else
	e = Q.front -> next->orderelem;
	return OK;
}
Status Delete_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem &e){
	//删除队首订单并返回该订单
	if(Q.front == Q.rear)
		return ERROR;
	OrderQueue_Ptr p;
	p = Q.front -> next;
	e = p->orderelem;
	Q.front -> next = p -> next;
	if(p == Q.rear )
		Q.rear = Q.front;
	delete p;
	-- Q.length; 
	return OK;
}
Status En_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem e){
	//新订单进入队列
	OrderQueue_Ptr p;
	p = new OrderQueue_Node;
	if(!p){
		cout<<"空间分配失败"<<endl;
		return ERROR;
	}
	p -> orderelem = e;
	p -> next = NULL;
	Q.rear -> next = p;
	Q.rear = p;
	++ Q.length;
	return OK;
}
void Traverse_OrderQueue(Order_LinkQueue Q){
	OrderQueue_Ptr p;
	p = Q.front ->next ;
	printf("订单号            套餐        数量            姓名          电话             地点            下单时间            状态\n");
	while(p != NULL ){
		printf("%s\t", p->orderelem.ordernumber.c_str());//订单号
		printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//套餐编号
		printf("      %2d\t", p->orderelem.totalset);//套餐数量
		printf("%10s\t", p->orderelem.name.c_str());//订餐人姓名
		printf("  %11s\t", p->orderelem.number.c_str());//订餐人电话
		printf(" %10s\t", p->orderelem.destination.c_str());//地点
		printf("  %s\t", p->orderelem.ordertime.c_str());//下单时间
		switch(p->orderelem.orderstate){
		case 0:printf("已取消\n");
			break;
		case 1:printf("未派送\n");
			break;
		case 2:printf("已派送\n");
			break;
		case 3:printf("已接收\n");
			break;
		}
		p = p->next;
	}
}
void OrderNumber_Search(Order_LinkQueue Q,string number){
	//查询订单号并输出
	OrderQueue_Ptr p;
	p = Q.front -> next;
	while(p != NULL && p ->orderelem.ordernumber <= number){
		if(p ->orderelem.ordernumber == number){
			printf("订单号            套餐        数量            姓名          电话             地点            下单时间           状态\n");
			printf("%s\t", p->orderelem.ordernumber.c_str());//订单号
			printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//套餐编号
			printf("      %2d\t", p->orderelem.totalset);//套餐数量
			printf("%10s\t", p->orderelem.name.c_str());//订餐人姓名
			printf("  %11s\t", p->orderelem.number.c_str());//订餐人电话
			printf(" %10s\t", p->orderelem.destination.c_str());//地点
			printf("  %s\t", p->orderelem.ordertime.c_str());//下单时间
			switch(p->orderelem.orderstate){
			case 0:printf("已取消\n");
				break;
			case 1:printf("未派送\n");
				break;
			case 2:printf("已派送\n");
				break;
			case 3:printf("已接收\n");
				break;
			}
			break;
		}
		p = p->next;
	}
	if(p == NULL || p ->orderelem.ordernumber > number){
		cout<<"不存在该订单或订单号输入错误！"<<endl;
	}
}
void Traverse_UnDelivery(Order_LinkQueue Q){
	OrderQueue_Ptr p;
	p = Q.front ->next ;
	printf("订单号            套餐        数量            姓名          电话             地点            下单时间           状态\n");
	//遍历未派送订单
	while(p != NULL ){
		if(p->orderelem.orderstate == 1){
			printf("%s\t", p->orderelem.ordernumber.c_str());//订单号
			printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//套餐编号
			printf("      %2d\t", p->orderelem.totalset);//套餐数量
			printf("%10s\t", p->orderelem.name.c_str());//订餐人姓名
			printf("  %11s\t", p->orderelem.number.c_str());//订餐人电话
			printf(" %10s\t", p->orderelem.destination.c_str());//地点
			printf("  %s\t", p->orderelem.ordertime.c_str());//下单时间
			switch(p->orderelem.orderstate){
			case 0:printf("已取消\n");
				break;
			case 1:printf("未派送\n");
				break;
			case 2:printf("已派送\n");
				break;
			case 3:printf("已接收\n");
				break;
			}
		}
		p = p->next;
	}
}
void OrderName_Search(Order_LinkQueue Q, string name){
	//按订餐姓名查询订单并输出
	OrderQueue_Ptr p;
	bool Isfinded = false;
	p = Q.front -> next;
	printf("订单号            套餐        数量            姓名          电话             地点            下单时间           状态\n");
	while(p != NULL ){
		if(p->orderelem.name == name){
			Isfinded = true;
			printf("%s\t", p->orderelem.ordernumber.c_str());//订单号
			printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//套餐编号
			printf("      %2d\t", p->orderelem.totalset);//套餐数量
			printf("%10s\t", p->orderelem.name.c_str());//订餐人姓名
			printf("  %11s\t", p->orderelem.number.c_str());//订餐人电话
			printf(" %10s\t", p->orderelem.destination.c_str());//地点
			printf("  %s\t", p->orderelem.ordertime.c_str());//下单时间
			switch(p->orderelem.orderstate){
			case 0:printf("已取消\n");
				break;
			case 1:printf("未派送\n");
				break;
			case 2:printf("已派送\n");
				break;
			case 3:printf("已接收\n");
				break;
			}
		}
		p = p->next;
	}
	if(!Isfinded){
		cout<<"该用户不存在订单！"<<endl;
	}
}