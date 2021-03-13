/*
�ײͱ�
*/
#include"set_sqlist.h"
#include"Judge_And_Change.h"
#include<iostream>
#include<string>
#include<malloc.h>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#define INIT_SIZE 10
#define INCREMENT 5

using namespace std;

void InitList(SetList &L){
	L.setmea = new SetElem[INIT_SIZE * sizeof(SetElem)];
	if(!L.setmea){
		cout<<"�ڴ����ʧ�ܣ�"<<endl;
		exit(SETOVERFLOW);
	}
	L.length = 0;
	L.maxelem = INIT_SIZE;
}
Status AppendSet(SetList &L, SetElem e){
	//�����ײͣ�����Զ����ɣ�������Ĭ��������ӣ�
	if(L.length + 1 >= L.maxelem ){
		SetElem * tmp;//��ʱ���������Ԫ��
		tmp = new SetElem[(L.maxelem + 1) * sizeof(SetElem)];
		tmp = L.setmea;
		L.setmea = new SetElem[(L.maxelem + INCREMENT) * sizeof(SetElem)];
		int i;
		for(i=1 ; i <= L.length ; i++)
			L.setmea[i] = tmp[i];
		delete [] tmp;
		L.maxelem += INCREMENT;
	}
	L.setmea[L.length + 1] = e;
	++ L.length; 
	return OK;
}
void TraverseSet(SetList L){
	//�����ײͱ�
	int i;
	printf("�ײͱ��       �ײ�����                 �ײ�����          �ײͼ۸�        ״̬\n");
	for(i = 1; i <= L.length ; i++){
		printf("%c%03d\t", L.setmea[i].mark1, L.setmea[i].mark2);
		cout<<std::right<<setw(15)<<L.setmea[i].name;
		cout<<std::right<<setw(30)<<L.setmea[i].describe;
		cout<<std::right<<setw(8)<<L.setmea[i].price;
		if(L.setmea[i].state == 1)
			cout<<std::right<<setw(18)<<"��Ԥ��"<<endl;
		else
			cout<<std::right<<setw(18)<<"����Ԥ��"<<endl;
	}
}
void PrintReserveSet(SetList L){
	int i;
	printf("�ײͱ��       �ײ�����                 �ײ�����          �ײͼ۸�        ״̬\n");
	for(i = 1; i <= L.length ; i++){
		if(L.setmea[i].state == 1){
			printf("%c%03d\t", L.setmea[i].mark1, L.setmea[i].mark2);
			cout<<std::right<<setw(15)<<L.setmea[i].name;
			cout<<std::right<<setw(30)<<L.setmea[i].describe;
			cout<<std::right<<setw(8)<<L.setmea[i].price;
			cout<<std::right<<setw(18)<<"��Ԥ��"<<endl;
		}	
	}
} 
