/*
判断数据是否合理或者将数据转换成需要的格式
*/
#include"Judge_And_Change.h"
#include"destination_graph.h"
#include<iostream>
#include<string>
#define firstmark 'M'
#define MAX 10//用于整形转换字符型，字符串的最大长度
using namespace std;

char Judge_Option(string opt){
	if(opt.size() != 1){
		return '#';
	}
	return opt[0];
}
bool Judge_SetMark(SetList S, string mark, char &mark1, int &mark2){
	//判断套餐编号是否合理
	if(mark[0] != firstmark)
		return false;
	else
		mark1 = mark[0];
	int i, cnt = 0;
	for(i = 1; i < mark.size(); i++){
		if(mark[i] > '9' || mark[i] < '0')
			return false;
		cnt *= 10;
		cnt += mark[i] - '0';
	}
	if(cnt < 0 || cnt >999)
		return false;
	mark2 = cnt;
	if(mark1 == firstmark && S.length >= mark2 ){
		if(S.setmea[mark2].state == 1){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
bool Judge_SetName(SetList S, string name, int locat){
	//判断套餐名称是否正确
	int i;
	for(i = 1; i <= S.length ; i++){
		if(S.setmea[i].name == name && locat != i){
			//考虑到修改功能名称可能不变，所以查找时当且仅当查找到套餐且其位置与位置locat不同时视为查找成功
			//查找成功说明输入的套餐名称不合法，故返回false 
			return false;
		}
	}
	return true;
}
bool Judge_SetTotal(string tot, int &total){
	//判断套餐数量是否合理
	int i;
	int cnt = 0;
	for(i = 0; i < tot.size(); i++){
		if(tot[i] > '9' || tot[i] <'0')
			return false;
		cnt *= 10;
		cnt += tot[i] - '0';
	}
	total = cnt;
	return true;
}
bool Judge_SetNumber(string number){
	//判断电话是否合理
	if(number.size() != 11){
		return false;
	}
	int i;
	for(i = 0; i < number.size(); i++){
		if(number[i] < '0' || number[i] > '9'){
			return false;
		}
	}
	return true;
}
bool Judge_SetDestination(DestinationGraph G, string destination){
	//判断派送地址是否合理
	int i;
	for(i = 0; i < G.vexnum ; i++){
		if(destination == G.vex[i])
			return true;
	}
	return false;
}
bool Judge_Price(string price, int &p){
	//判断价格是否合理
	int i;
	p = 0;
	for(i = 0; i <price.size(); i++){
		if(price[i] < '0'||price[i] > '9'){
			return false;
		}else{
			p *= 10;
			p += price[i] - '0';
		}
	}
	return true;
}
bool Judge_State(string state, bool &st){
	//判断状态是否合适
	if(state.size() == 1){
		if(state[0] == '1'){
			st = true;
			return true;
		}else if(state[0] == '0'){
			st = false;
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}
string Integer_To_String(int x, int length){
	int tmp = x;
	int i = 0, j = 0;
	int cnt = 0;
	char s[MAX];
	char ss[MAX];
	while(tmp > 0){
		s[i++] = tmp % 10 + '0';
		tmp /= 10;
		++cnt;
	}
	while(cnt != length){
		s[i++] = '0';
		++cnt;
	}
	s[i] = '\0';
	i = i - 1;
	while(i >= 0){
		ss[j++] = s[i--];
	}
	ss[j] = '\0';
	return ss;
}
