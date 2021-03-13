/*
订单统计表
*/
#ifndef _ORDERCOUNTLIST_H_
#define _ORDERCOUNTLIST_H_

#include<iostream>

using namespace std;

typedef int Status;
typedef struct OrderCountElem{
	string ordernumber;//订单编号
	char setmark1;//套餐编号1（编号里的字母）
	int setmark2;//套餐编号2（编号中的数字）
	int totalset;//套餐数量
	int totalprice;//总金额
	string destination;//地点
	string ordertime;//下单时间
	int orderstate;//订餐状态 ： 0-已取消 1-未派送 2-已派送
}OrderCountElem;
typedef struct OrderCountList{
	OrderCountElem * elem;
	int maxsize;
	int length;
}OrderCountList;

void InitOrderCountList(OrderCountList &L);//初始化
Status AppendOrderElem(OrderCountList &L, OrderCountElem e);//添加套餐

#endif