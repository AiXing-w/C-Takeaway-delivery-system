/*
订单表
*/
#include<iostream>
#include"OrderCountList.h"
#define INIT_SIZE 10
#define INCREMENT 5
#define SETOVERFLOW -2
#define OK 1

using namespace std;

void InitOrderCountList(OrderCountList &L){
	L.elem = new OrderCountElem[INIT_SIZE * sizeof(OrderCountElem)];
	if(!L.elem){
		cout<<"内存分配失败！"<<endl;
		return;
	}
	L.length = 0;
	L.maxsize = INIT_SIZE;
}
Status AppendOrderElem(OrderCountList &L, OrderCountElem e){
	if(L.length + 1 >= L.maxsize ){
		OrderCountElem * tmp;//临时存放数组中元素
		tmp = new OrderCountElem[(L.maxsize + 1) * sizeof(OrderCountElem)];
		tmp = L.elem;
		L.elem = new OrderCountElem[(L.maxsize + INCREMENT) * sizeof(OrderCountElem)];
		int i;
		for(i=1 ; i <= L.length ; i++)
			L.elem[i] = tmp[i];
		delete [] tmp;
		L.maxsize += INCREMENT;
	}
	L.elem[L.length + 1] = e;
	++ L.length; 
	return OK;
}