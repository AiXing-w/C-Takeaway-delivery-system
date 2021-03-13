#include"order_linkqueue.h"
#include"Judge_And_Change.h"
#include<iostream>
#include<cstdio>
#include<new>
#define ERROR 0
#define OK 1
using namespace std;

Status Init_OrderQueue(Order_LinkQueue &Q){
	//��ʼ����������
	Q.front = Q.rear = new OrderQueue_Node;
	if(!Q.front ){
		cout<<"�ռ�����ʧ�ܣ�"<<endl;
		return ERROR;
	}
	Q.front -> next = NULL;
	Q.length = 0;
	return OK;
}
bool OrderQueue_Empty(Order_LinkQueue Q){
	//�ж϶��������Ƿ�Ϊ��
	return Q.length == 0; 
}
int OrderQueue_Length(Order_LinkQueue Q){
	//���ض��г���
	return Q.length;
}
Status Get_OrderQueue_Head(Order_LinkQueue Q, OrderQueue_Elem &e){
	//��ö���Ԫ��
	if(Q.front == Q.rear )
		return ERROR;
	else
	e = Q.front -> next->orderelem;
	return OK;
}
Status Delete_OrderQueue(Order_LinkQueue &Q, OrderQueue_Elem &e){
	//ɾ�����׶��������ظö���
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
	//�¶����������
	OrderQueue_Ptr p;
	p = new OrderQueue_Node;
	if(!p){
		cout<<"�ռ����ʧ��"<<endl;
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
	printf("������            �ײ�        ����            ����          �绰             �ص�            �µ�ʱ��            ״̬\n");
	while(p != NULL ){
		printf("%s\t", p->orderelem.ordernumber.c_str());//������
		printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//�ײͱ��
		printf("      %2d\t", p->orderelem.totalset);//�ײ�����
		printf("%10s\t", p->orderelem.name.c_str());//����������
		printf("  %11s\t", p->orderelem.number.c_str());//�����˵绰
		printf(" %10s\t", p->orderelem.destination.c_str());//�ص�
		printf("  %s\t", p->orderelem.ordertime.c_str());//�µ�ʱ��
		switch(p->orderelem.orderstate){
		case 0:printf("��ȡ��\n");
			break;
		case 1:printf("δ����\n");
			break;
		case 2:printf("������\n");
			break;
		case 3:printf("�ѽ���\n");
			break;
		}
		p = p->next;
	}
}
void OrderNumber_Search(Order_LinkQueue Q,string number){
	//��ѯ�����Ų����
	OrderQueue_Ptr p;
	p = Q.front -> next;
	while(p != NULL && p ->orderelem.ordernumber <= number){
		if(p ->orderelem.ordernumber == number){
			printf("������            �ײ�        ����            ����          �绰             �ص�            �µ�ʱ��           ״̬\n");
			printf("%s\t", p->orderelem.ordernumber.c_str());//������
			printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//�ײͱ��
			printf("      %2d\t", p->orderelem.totalset);//�ײ�����
			printf("%10s\t", p->orderelem.name.c_str());//����������
			printf("  %11s\t", p->orderelem.number.c_str());//�����˵绰
			printf(" %10s\t", p->orderelem.destination.c_str());//�ص�
			printf("  %s\t", p->orderelem.ordertime.c_str());//�µ�ʱ��
			switch(p->orderelem.orderstate){
			case 0:printf("��ȡ��\n");
				break;
			case 1:printf("δ����\n");
				break;
			case 2:printf("������\n");
				break;
			case 3:printf("�ѽ���\n");
				break;
			}
			break;
		}
		p = p->next;
	}
	if(p == NULL || p ->orderelem.ordernumber > number){
		cout<<"�����ڸö����򶩵����������"<<endl;
	}
}
void Traverse_UnDelivery(Order_LinkQueue Q){
	OrderQueue_Ptr p;
	p = Q.front ->next ;
	printf("������            �ײ�        ����            ����          �绰             �ص�            �µ�ʱ��           ״̬\n");
	//����δ���Ͷ���
	while(p != NULL ){
		if(p->orderelem.orderstate == 1){
			printf("%s\t", p->orderelem.ordernumber.c_str());//������
			printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//�ײͱ��
			printf("      %2d\t", p->orderelem.totalset);//�ײ�����
			printf("%10s\t", p->orderelem.name.c_str());//����������
			printf("  %11s\t", p->orderelem.number.c_str());//�����˵绰
			printf(" %10s\t", p->orderelem.destination.c_str());//�ص�
			printf("  %s\t", p->orderelem.ordertime.c_str());//�µ�ʱ��
			switch(p->orderelem.orderstate){
			case 0:printf("��ȡ��\n");
				break;
			case 1:printf("δ����\n");
				break;
			case 2:printf("������\n");
				break;
			case 3:printf("�ѽ���\n");
				break;
			}
		}
		p = p->next;
	}
}
void OrderName_Search(Order_LinkQueue Q, string name){
	//������������ѯ���������
	OrderQueue_Ptr p;
	bool Isfinded = false;
	p = Q.front -> next;
	printf("������            �ײ�        ����            ����          �绰             �ص�            �µ�ʱ��           ״̬\n");
	while(p != NULL ){
		if(p->orderelem.name == name){
			Isfinded = true;
			printf("%s\t", p->orderelem.ordernumber.c_str());//������
			printf("  %c%03d\t", p->orderelem.setmark1, p->orderelem.setmark2);//�ײͱ��
			printf("      %2d\t", p->orderelem.totalset);//�ײ�����
			printf("%10s\t", p->orderelem.name.c_str());//����������
			printf("  %11s\t", p->orderelem.number.c_str());//�����˵绰
			printf(" %10s\t", p->orderelem.destination.c_str());//�ص�
			printf("  %s\t", p->orderelem.ordertime.c_str());//�µ�ʱ��
			switch(p->orderelem.orderstate){
			case 0:printf("��ȡ��\n");
				break;
			case 1:printf("δ����\n");
				break;
			case 2:printf("������\n");
				break;
			case 3:printf("�ѽ���\n");
				break;
			}
		}
		p = p->next;
	}
	if(!Isfinded){
		cout<<"���û������ڶ�����"<<endl;
	}
}