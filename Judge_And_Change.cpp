/*
�ж������Ƿ������߽�����ת������Ҫ�ĸ�ʽ
*/
#include"Judge_And_Change.h"
#include"destination_graph.h"
#include<iostream>
#include<string>
#define firstmark 'M'
#define MAX 10//��������ת���ַ��ͣ��ַ�������󳤶�
using namespace std;

char Judge_Option(string opt){
	if(opt.size() != 1){
		return '#';
	}
	return opt[0];
}
bool Judge_SetMark(SetList S, string mark, char &mark1, int &mark2){
	//�ж��ײͱ���Ƿ����
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
	//�ж��ײ������Ƿ���ȷ
	int i;
	for(i = 1; i <= S.length ; i++){
		if(S.setmea[i].name == name && locat != i){
			//���ǵ��޸Ĺ������ƿ��ܲ��䣬���Բ���ʱ���ҽ������ҵ��ײ�����λ����λ��locat��ͬʱ��Ϊ���ҳɹ�
			//���ҳɹ�˵��������ײ����Ʋ��Ϸ����ʷ���false 
			return false;
		}
	}
	return true;
}
bool Judge_SetTotal(string tot, int &total){
	//�ж��ײ������Ƿ����
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
	//�жϵ绰�Ƿ����
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
	//�ж����͵�ַ�Ƿ����
	int i;
	for(i = 0; i < G.vexnum ; i++){
		if(destination == G.vex[i])
			return true;
	}
	return false;
}
bool Judge_Price(string price, int &p){
	//�жϼ۸��Ƿ����
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
	//�ж�״̬�Ƿ����
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
