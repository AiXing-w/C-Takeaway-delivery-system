/*
�����ݽ����жϻ�ת���ɺ����ʽ
*/
#ifndef _JUDGE_AND_CHANGE_H_
#define _JUDGE_AND_CHANGE_H_

#include<iostream>
#include<string>
#include"set_sqlist.h"
#include"destination_graph.h"

using namespace std;

char Judge_Option(string opt);
bool Judge_SetMark(SetList S, string mark, char &mark1, int &mark2);//�ж��ײͱ���Ƿ����
bool Judge_SetTotal(string tot, int &total);//�ж��ײ������Ƿ����
bool Judge_SetNumber(string number);//�жϵ绰�Ƿ����
bool Judge_SetDestination(DestinationGraph G, string destination);//�ж����͵�ַ�Ƿ����
bool Judge_SetName(SetList S, string name, int locat);//�ж�������ײ��Ƿ���� 
bool Judge_Price(string price, int &p);//�жϼ۸��Ƿ����
bool Judge_State(string state, bool &st);//�ж�״̬�Ƿ����
string Integer_To_String(int x, int length);//��������ת�����ַ���������

#endif
