/*
用于统计
*/
#include"Count_order.h"
#include<iostream>
#include<iomanip>
#define OK 1
#define ERROR 0

using namespace std;

bool CmpS(CountSElem a, CountSElem b){
	//按套餐统计时排序用到的比较方式
	//按定的次数降序，如果次数相同按总金额降序，如果总金额也相同按套餐编号升序
	if(a.delivetotal + a.undelivetotal  == b.delivetotal + b.undelivetotal){
		if(a.totalprice == b.totalprice){
			if(a.delivetotal == b.delivetotal){
				if(a.undelivetotal == b.undelivetotal){
					return a.mark2 < b.mark2;
				}else{
					return a.undelivetotal < b.undelivetotal;
				}
			}else{
				return a.delivetotal > b.delivetotal;
			}
		}else{
			return a.totalprice > b.totalprice;
		}
	}else{
		return a.delivetotal + a.undelivetotal > b.delivetotal + b.undelivetotal;
	}
}
void HeapAdjust(CountSList &L, int s, int m){
	CountSElem rc = L.elem[s];
	int j;
	for(j = 2 * s; j <= m; j *= 2){
		if(j < m && CmpS(L.elem[j], L.elem[j + 1]))
			j++;
		if(!CmpS(rc, L.elem[j]))
			break;
		L.elem[s] = L.elem[j];
		s = j;
	}
	L.elem[s] = rc;
}
void CreateHeap(CountSList &L){
	int n;
	n = L.length;
	int i;
	for(i = n / 2; i >0 ; i--){
		HeapAdjust(L, i, n);
	}
}
void Heap_Sort_S(CountSList &L){
	CreateHeap(L);
	int i;
	for(i = L.length; i > 1 ; i--){
		CountSElem tmp;
		tmp = L.elem[1];
		L.elem[1] = L.elem[i];
		L.elem[i] = tmp;
		HeapAdjust(L, 1, i - 1);
	}
}
Status InitCountSList(CountSList &e, int n){
	//初始化套餐统计表
	e.elem = new CountSElem[n + 1];
	if(e.elem == NULL)
		return ERROR;
	int i;
	for(i=1 ; i <= n; i++){
		e.elem[i].mark1 = ' ';
		e.elem[i].mark2 = i;
		e.elem[i].canceltotal = 0;
		e.elem[i].delivetotal = 0;
		e.elem[i].undelivetotal = 0;
		e.elem[i].totalprice = 0;
	}
	e.length = n;
	return OK;
}
Status InitCountDList(CountDList &D, int n){
	D.elem = new CountDElem[n + 1];
	if(D.elem == NULL)
		return ERROR;
	int i;
	D.sumd = 0;
	for(i = 0; i <= n; i++){
		D.elem[i].destination = "";
		D.elem[i].cnt = 0;
	}
	D.length = n;
	return OK;
}
void TraverseCountSet(CountSList S){
	int i; 
	cout<<"套餐编号      已取消数量    已接收数量    已派送数量       总数        总金额"<<endl;
	for(i = 1; i <= S.length ; i++){
		if(S.elem[i].canceltotal + S.elem[i].delivetotal + S.elem[i].undelivetotal != 0){
			printf("  %c%03d", S.elem[i].mark1, S.elem[i].mark2);
			cout<<std::right<<setw(14)<<S.elem[i].canceltotal;
			cout<<std::right<<setw(14)<<S.elem[i].undelivetotal;
			cout<<std::right<<setw(14)<<S.elem[i].delivetotal;
			cout<<std::right<<setw(14)<<S.elem[i].delivetotal + S.elem[i].undelivetotal + S.elem[i].canceltotal;
			printf("\t\t%.2f\n", S.elem[i].totalprice);
		}
	}
}
void TraverseCountD(CountDList D){
	int i;
	cout<<"    地点              订餐数"<<endl;
	for(i = 0; i < D.length ; i++){
		if(D.elem[i].cnt != 0){
			printf("%10s            %.2f%%\n", D.elem[i].destination.c_str(), D.elem[i].cnt * 100.0 / D.sumd);
		}
	}
}
Status CountSet(string start, string end, OrderCountList C, SetList S, Order_LinkQueue Q){
	//统计套餐
	CountSList L;
	int i;
	InitCountSList(L, S.length);
	for(i = 1; i <= C.length ; i++){
		if(C.elem[i].ordernumber >= start && C.elem[i].ordernumber <= end){
			L.elem[C.elem[i].setmark2].mark1 = C.elem[i].setmark1;
			L.elem[C.elem[i].setmark2].mark2 = C.elem[i].setmark2;
			if(C.elem[i].orderstate == 2){
				L.elem[C.elem[i].setmark2].delivetotal += C.elem[i].totalset;
			}else if(C.elem[i].orderstate == 1){
				L.elem[C.elem[i].setmark2].undelivetotal += C.elem[i].totalset;
			}else if(C.elem[i].orderstate == 0){
				L.elem[C.elem[i].setmark2].canceltotal += C.elem[i].totalset;
			}
			L.elem[C.elem[i].setmark2].totalprice += C.elem[i].totalprice;
		}
	}
	OrderQueue_Ptr p = Q.front->next;
	while(p != NULL ){
		if(p->orderelem.ordernumber >= start && p->orderelem.ordernumber <= end){
			L.elem[p->orderelem.setmark2].mark1 = p->orderelem.setmark1;
			L.elem[p->orderelem.setmark2].mark2 = p->orderelem.setmark2;
			if(p->orderelem.orderstate == 2){
				L.elem[p->orderelem.setmark2].delivetotal += p->orderelem.totalset;
			}else if(p->orderelem.orderstate == 1){
				L.elem[p->orderelem.setmark2].undelivetotal += p->orderelem.totalset;
			}else if(p->orderelem.orderstate == 0){
				L.elem[p->orderelem.setmark2].canceltotal += p->orderelem.totalset;
			}
			L.elem[p->orderelem.setmark2].totalprice += S.setmea[p->orderelem.setmark2].price * p->orderelem.totalset;
		}
		p = p->next;
	}
	Heap_Sort_S(L);//进行堆排序
	TraverseCountSet(L);//输出
	return OK;
}
void Destination_Count(Order_LinkQueue Q, OrderCountList C, DestinationGraph G){
	CountDList D;
	InitCountDList(D, G.vexnum);
	int i;
	for(i = 1; i <= C.length; i++){
		int k = Find_Destination(G, C.elem[i].destination);
		if(k != -1){
			D.elem[k].destination = C.elem[i].destination;
			++ D.elem[k].cnt;
			D.sumd ++;
		}
	}
	OrderQueue_Ptr p = Q.front->next;
	while(p != NULL ){
		int k = Find_Destination(G, p->orderelem.destination);
		if(k != -1){
			D.elem[k].destination = p->orderelem.destination;
			++ D.elem[k].cnt;
			D.sumd ++;
		}
		p = p->next;
	}
	TraverseCountD(D);
}
