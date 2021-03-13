/*
对数据进行判断或转换成合理格式
*/
#ifndef _JUDGE_AND_CHANGE_H_
#define _JUDGE_AND_CHANGE_H_

#include<iostream>
#include<string>
#include"set_sqlist.h"
#include"destination_graph.h"

using namespace std;

char Judge_Option(string opt);
bool Judge_SetMark(SetList S, string mark, char &mark1, int &mark2);//判断套餐编号是否合理
bool Judge_SetTotal(string tot, int &total);//判断套餐数量是否合理
bool Judge_SetNumber(string number);//判断电话是否合理
bool Judge_SetDestination(DestinationGraph G, string destination);//判断派送地址是否合理
bool Judge_SetName(SetList S, string name, int locat);//判断输入的套餐是否合理 
bool Judge_Price(string price, int &p);//判断价格是否合理
bool Judge_State(string state, bool &st);//判断状态是否合理
string Integer_To_String(int x, int length);//整型数据转换成字符串并返回

#endif
