/*
��������ϵͳѡ�� 
*/ 
#include"Manage.h"
#include"set_sqlist.h"
#include"order_linkqueue.h"
#include"destination_graph.h"
#include"OrderCountList.h"
#include"Judge_And_Change.h"
#include"Count_order.h"
#include"menu.h"
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<string>
#include<fstream>

const char FirstMark = 'M';

#define OK 1
#define ERROR 0
#define MAX_DESTINATION 15

using namespace std;

Status Start_work(SetList &S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph &G){
	//��ʼ�ϰ�
	bool flag = true;
	InitList(S);
	ifstream setin("setmeal.txt");
	int i=0;
	if(setin.is_open())
		cout<<"��setmeal.txt�ļ��ɹ���"<<endl;
	else{
		cout<<"��setmeal.txt�ļ�ʧ��!"<<endl;
		flag = false;
	}
	if(setin.peek() != EOF){
		while(!setin.eof()){
			SetElem setmeal;
			setin >> setmeal.mark1;
			setin >> setmeal.mark2;
			setin >> setmeal.name;
			setin >> setmeal.describe;
			setin >> setmeal.price;		
			setin >> setmeal.state;
			AppendSet(S, setmeal);
		}
		setin.close();
		cout<<"�ײͼ��سɹ���"<<endl;
	}
	Init_OrderQueue(Q);
	ifstream orderin("order.txt");
	if(orderin.is_open())
		cout<<"��order.txt�ļ��ɹ���"<<endl;
	else{
		cout<<"��order.txt�ļ�ʧ�ܣ��Կ��ϰࣩ"<<endl;
		//�˴����ı�flag��ֵ�����ǽ�order.txt�ļ������ڵ��������������δ���͵Ķ���������
		//�����˽�׳��
	}
	if(orderin.is_open() && orderin.peek() != EOF){
		while(!orderin.eof()){
			OrderQueue_Elem e;
			orderin >> e.ordernumber;//������
			orderin >> e.setmark1;//���1
			orderin >> e.setmark2;//���2
			orderin >> e.totalset;//����
			orderin >> e.name;//����
			orderin >> e.number;//����
			orderin >> e.destination;//�ص�
			orderin >> e.ordertime;//����ʱ��
			orderin >> e.orderstate;//״̬
			En_OrderQueue(Q, e);
		}
		orderin.close();
		cout<<"�����Ͷ������سɹ���"<<endl;
	}
	InitOrderCountList(C);
	ifstream Orderlist("ordercnt.txt");
	if(Orderlist.is_open()){
		cout<<"��ordercnt.txt�ļ��ɹ���"<<endl;
	}else{
		cout<<"��ordercnt.txt�ļ�ʧ�ܣ��Կ��ϰࣩ"<<endl;
	}
	if(Orderlist.is_open() && Orderlist.peek() != EOF){
		while(!Orderlist.eof()){
			OrderCountElem e;
			Orderlist >>e.ordernumber>>e.setmark1>>e.setmark2>>e.totalset>>e.totalprice>>e.destination>>e.ordertime>>e.orderstate;
			AppendOrderElem(C, e);
		}
		Orderlist.close();
		cout<<"��������سɹ���"<<endl;
	}
	//
	Init_DestinationGraph(G);
	ifstream destination("destination.txt");
	if(destination.is_open()){
		cout <<"��destination.txt�ļ��ɹ���"<<endl;
	}else{
		cout <<"��destination.txt�ļ�ʧ��"<<endl;
		flag = false;
	}
	if(destination.is_open() && destination.peek() != EOF){
		while(!destination.eof()){
			//���صص���Ϣ
			destination >> G.vex[G.vexnum];
			++G.vexnum; 
		}
		Sort_Destination(G);
		destination.close();
		cout<<"���صص�ɹ���"<<endl;
	}
	ifstream distance("distance.txt");
	if(distance.is_open()){
		cout <<"��distance.txt�ļ��ɹ���"<<endl;
	}else{
		cout <<"��distance.txt�ļ�ʧ�ܣ�"<<endl;
		flag = false;
	}
	if(distance.is_open() && distance.peek()!=EOF){
		while(!distance.eof()){
			string d1, d2;
			int locat1, locat2;
			float dist;
			distance >> d1 >> d2>>dist;
			locat1 = Find_Destination(G, d1);
			locat2 = Find_Destination(G, d2);
			++ G.arcnum; 
			G.matrix[locat1][locat2] = G.matrix[locat2][locat1] = dist;
		}
		distance.close();
		cout<<"���ؾ���ɹ���"<<endl;
	}
	if( !G.IsFinded ){
		//���δ������·��
		ShortestPath(G);
		G.IsFinded = true;//�����������·��
	}
	if(flag){
		cout<<"��ʼ�ϰ࣡"<<endl;
	}else{
		cout<<"��Ϣ���ش���"<<endl;
		return ERROR;
	}
	return OK;
}
void Get_OccurTime(string &date1, string &date2){
	time_t nowtime;
	struct tm* p;
	time(&nowtime);
	int y, m, d, h, mi, sec;
	p = localtime(&nowtime);
	y = p->tm_year + 1900;
	m = p->tm_mon + 1;
	d = p->tm_mday;
	h = p->tm_hour;
	mi = p->tm_min;
	sec = p->tm_sec;
	date1 = date2 = Integer_To_String(y, 4);
	date2 +="-";
	date1 += Integer_To_String(m, 2);
	date2 += Integer_To_String(m, 2);
	date2 +="-";
	date1 += Integer_To_String(d, 2);
	date2 += Integer_To_String(d, 2);
	date1 += Integer_To_String(h, 2);
	date2 += Integer_To_String(h, 2);
	date2 +=":";
	date1 += Integer_To_String(mi, 2);
	date2 += Integer_To_String(mi, 2);
	date2 +=":";
	date1 += Integer_To_String(sec, 2);
	date2 += Integer_To_String(sec, 2);
}
void Receive_Orders(DestinationGraph G, SetList S, Order_LinkQueue &Q){
	//���ն���
	OrderQueue_Elem ord;
	bool flag[4];//�ж������Ƿ�Ϸ��ı��
	string mark;
	string tot;
	char mark1;//�ײͱ��1
	int mark2;//�ײͱ��2
	int total;//�ײ�����
	string name;
	string number;
	string destination;
	cout<<"�������ײͱ�ţ�";
	cin >> mark;
	cout<<"�������ײ�������";
	cin >> tot;
	cout<<"����������������";
	cin >> name;
	cout<<"�����������ֻ��ţ�";
	cin >> number;
	cout<<"�������Ͳ͵�ַ��";
	cin >> destination;
	flag[0] = Judge_SetMark(S, mark, mark1, mark2);//�ж��ײͱ���Ƿ�Ϸ�
	flag[1] = Judge_SetTotal(tot, total);//�ж��ײ����Ƿ�Ϸ�
	flag[2] = Judge_SetNumber(number);//�жϵ绰�Ƿ�Ϸ�
	flag[3] = Judge_SetDestination(G, destination);//�ж����͵ص��Ƿ�Ϸ�
	if(flag[0] && flag[1] && flag[2] && flag[3] && S.setmea[mark2].state){
		//����������ݾ��ͷ����
		ord.setmark1 = mark1;
		ord.setmark2 = mark2;
		ord.totalset = total;
		ord.price = S.setmea[mark2].price;
		ord.number = number;
		ord.name = name;
		ord.destination = destination;
		Get_OccurTime(ord.ordernumber, ord.ordertime);//��ȡʱ��
		ord.orderstate = 1;//����״̬ �� 0-��ȡ�� 1-δ���� 2-������ 3-�ѽ���
		cout<<"���Ķ���Ϊ��"<<endl;
		printf("������           �ײ�     ����     ����     �绰             �ص�            �µ�ʱ��          ״̬\n");
		printf("%s\t", ord.ordernumber.c_str());//������
		printf("%c%03d\t", ord.setmark1, ord.setmark2);//�ײͱ��
		printf("    %d\t", ord.totalset);//�ײ�����
		printf("   %s\t", ord.name.c_str());//����������
		printf("  %s\t", ord.number.c_str());//�����˵绰
		printf("%12s\t", ord.destination.c_str());//�ص�
		printf("%s\t", ord.ordertime.c_str());//�µ�ʱ��
		printf("%d\n", ord.orderstate);//����״̬
		if(!En_OrderQueue(Q, ord)){
			cout<<"����ʧ�ܣ�"<<endl;
		}
	}else{
		//˵������ԭ��
		cout<<"�������ݴ��󣡴���ԭ��:"<<endl;
		string reasons[4] = {"|�ײͱ�Ŵ���|", "|�ײ���Ŀ����|", "|�绰�������|", "|���͵�ַ����|"};
		int i;
		for(i = 0; i < 4 ; i++){
			if(!flag[i])
				cout<<reasons[i];
		}
		cout<<endl;
	}
}
void OrderModify(SetList S, DestinationGraph G, Order_LinkQueue &Q,bool option){
	//��optionΪ0ʱȡ����������Ϊ1 ʱ����״̬����
	string ordernumber;//�������
	cout<<"�����붩�����"<<endl;
	cin >>ordernumber;
	OrderQueue_Ptr p;
	p = Q.front -> next;
	while(p != NULL && p ->orderelem.ordernumber <= ordernumber){
		if(p ->orderelem.ordernumber == ordernumber){
			break;
		}
		p = p->next;
	}
	if(p == NULL || p ->orderelem.ordernumber > ordernumber){
		cout<<"�����ڸö����򶩵����������"<<endl;
	}else{
		if(option){
			bool flag[4];//�ж������Ƿ�Ϸ��ı��
			string mark;
			string tot;
			char mark1;//�ײͱ��1
			int mark2;//�ײͱ��2
			int total;//�ײ�����
			string name;
			string number;
			string destination;
			cout<<"�������ײͱ�ţ�";
			cin >> mark;
			cout<<"�������ײ�������";
			cin >> tot;
			cout<<"����������������";
			cin >> name;
			cout<<"�����������ֻ��ţ�";
			cin >> number;
			cout<<"�������Ͳ͵�ַ��";
			cin >> destination;
			flag[0] = Judge_SetMark(S, mark, mark1, mark2);//�ж��ײͱ���Ƿ�Ϸ�
			flag[1] = Judge_SetTotal(tot, total);//�ж��ײ����Ƿ�Ϸ�
			flag[2] = Judge_SetNumber(number);//�жϵ绰�Ƿ�Ϸ�
			flag[3] = Judge_SetDestination(G, destination);//�ж����͵ص��Ƿ�Ϸ�
			if(flag[0] && flag[1] && flag[2] && flag[3]){
				//����������ݾ��ͷ����
				p->orderelem.setmark1 = mark1;
				p->orderelem.setmark2 = mark2;
				p->orderelem.totalset = total;
				p->orderelem.number = number;
				p->orderelem.name = name;
				p->orderelem.destination = destination;
				cout<<"�����޸ĳɹ���"<<endl;
			}else{
			//˵������ԭ��
				cout<<"�������ݴ����޷������޸ģ�����ԭ��:"<<endl;
				string reasons[4] = {"|�ײͱ�Ŵ���|", "|�ײ���Ŀ����|", "|�绰�������|", "|���͵�ַ����|"};
				int i;
				for(i = 0; i < 4 ; i++){
					if(!flag[i])
						cout<<reasons[i];
				}
				cout<<endl;
			}
		}else{
			p->orderelem.orderstate = 0;
			cout<<"���������ɹ���"<<endl;
		}
	}
}
void OrderInquiry(Order_LinkQueue Q){
	//��ѯ����
	system("cls");//����
	while(1){
		Load_main_menu();//�������˵�
		cout<<"����ѡ����:��������"<<endl;
		Load_order_manage_menu();//���ض�������˵�
		cout<<"����ѡ���ǣ���ѯ����"<<endl;
		Load_orderinquiry();//���ض�����ѯ�˵�
		cout<<"����������ѡ��"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '2'){
			//��鲢����
			system("cls");
			Load_main_menu();//���¼������˵�
			cout<<"����ѡ����:��ѯ����"<<endl;
			Load_orderinquiry();//���ض����˵�
			cout<<"ѡ�����������ѡ��";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		string number;
		string name;
		switch(opt){
		case '1':cout<<"���������ѯ�Ķ�����"<<endl;
			cin>>number;
			OrderNumber_Search(Q, number);//�������Ų�ѯ���������
			break;
		case '2':cout<<"���������ѯ�Ķ���������"<<endl;
			cin>>name;
			OrderName_Search(Q, name);//������������ѯ���������
			break;
		}
		system("pause");
		system("cls");
	}
}
void Order_manage(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G){
	//��������
	system("cls");//����
	while(1){
		Load_main_menu();//�������˵�
		cout<<"����ѡ���ǣ���������"<<endl;
		Load_order_manage_menu();//���ض�������˵�
		cout<<"����������ѡ��"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '5'){
			//��鲢����
			system("cls");
			Load_main_menu();//���¼������˵�
			cout<<"����ѡ����:��������"<<endl;
			Load_order_manage_menu();//���ض����˵�
			cout<<"ѡ�����������ѡ��";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':PrintReserveSet(S);//��ʾ�ײ�
			cout<<endl;
			Traverse_Destination(G);//��ʾ�ص�
			cout<<endl; 
			Receive_Orders(G, S, Q);//���ղ˵�
			break;
		case '2':OrderInquiry(Q);//��ѯ����
			break;
		case '3':cout<<"��ǰ����Ϊ��"<<endl;
			Traverse_OrderQueue(Q);//��ʾ����
			break;
		case '4':OrderModify(S, G, Q,1);
			break;
		case '5':OrderModify(S, G, Q,0);
			break;
		}
		system("pause");
		system("cls");
	}
}
void Delive_One_By_One(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph &G,string &location){
	//�������
	bool isdelive = false;
	OrderQueue_Elem e;
	if(Q.length == 0){
		cout<<"���޴����͵Ķ�����"<<endl;
		return;
	}
	Delete_OrderQueue(Q, e);
	if(e.orderstate == 0){	
		OrderCountElem elem;
		elem.ordernumber = e.ordernumber;
		elem.setmark1 = e.setmark1;
		elem.setmark2 = e.setmark2;
		elem.totalset = e.totalset;
		elem.totalprice = e.totalset * e.price;
		elem.destination = e.destination;
		elem.ordertime = e.ordertime;
		elem.orderstate = e.orderstate;
		AppendOrderElem(C, elem);
		ofstream ordcnt("ordercnt.txt", ios::app);
		if(ordcnt.is_open()){
			ordcnt<<elem.ordernumber<<" "<<elem.setmark1<<" "<<elem.setmark2<<" "<<elem.totalset<<" "<<elem.totalprice<<" "<<elem.destination<<" "<<elem.ordertime<<" "<<elem.orderstate<<endl;
			ordcnt.close();
		}
		while(e.orderstate == 0 && Q.length){
			Delete_OrderQueue(Q, e);
			if(e.orderstate == 1){
				break;
			}else if(e.orderstate == 0){
				OrderCountElem elem;
				elem.ordernumber = e.ordernumber;
				elem.setmark1 = e.setmark1;
				elem.setmark2 = e.setmark2;
				elem.totalset = e.totalset;
				elem.totalprice = e.totalset * e.price;
				elem.destination = e.destination;
				elem.ordertime = e.ordertime;
				elem.orderstate = e.orderstate;
				AppendOrderElem(C, elem);
				ofstream ordcnt("ordercnt.txt", ios::app);
				if(ordcnt.is_open()){
					ordcnt<<elem.ordernumber<<" "<<elem.setmark1<<" "<<elem.setmark2<<" "<<elem.totalset<<" "<<elem.totalprice<<" "<<elem.destination<<" "<<elem.ordertime<<" "<<elem.orderstate<<endl;
					ordcnt.close();
				}
			}
		}
	}	
	if(e.orderstate == 0 && Q.length == 0){
		//����ӿ�
		cout<<"���޴����͵Ķ�����"<<endl;
		return;
	}
	string tmp;
	time_t nowtime;
	struct tm* ptr;
	time(&nowtime);
	int year, month, day, hour, mi, sec;
	ptr = localtime(&nowtime);
	year = ptr->tm_year + 1900;
	month = ptr->tm_mon + 1;
	day = ptr->tm_mday;
	hour = ptr->tm_hour;
	mi = ptr->tm_min;
	sec = ptr->tm_sec;
	if(location == ""){
		cout << "���Ա��δ��������������ʼ�ص�:";
		cin >> location;
		float d = -1;
		
		int start = Find_Destination(G, location);
		if(start == -1){
			cout<<"�õص㲻�����͵�ͼ�ڣ�"<<endl;
			cout << "��������"<<e.destination<<"(��һ���ص�)�ľ���:";
			cin >> d;

		}else{
			cout<<"�õص������͵�ͼ�ڣ�"<<endl;
		}
		int end = Find_Destination(G, e.destination);
		if(end == -1){
			cout<<"�յ�("<<e.destination<<")����򲻴��ڣ�"<<endl;
		}else{
			cout<<"��ǰ������Ϣ��"<<endl;
			printf("������            �ײ�        ����            ����          �绰             �ص�            �µ�ʱ��\n");
			printf("%s\t", e.ordernumber.c_str());
			printf("  %c%03d\t", e.setmark1, e.setmark2);//�ײͱ��
			printf("      %2d\t", e.totalset);//�ײ�����
			printf("%10s\t", e.name.c_str());//����������
			printf("  %11s\t", e.number.c_str());//�����˵绰
			printf(" %10s\t", e.destination.c_str());//�ص�
			printf("  %s\n", e.ordertime.c_str());//�µ�ʱ��
			
			if(location == e.destination){
				cout<<"��ǰλ��("<<location<<")Ϊ�Ͳ͵ص㡣"<<endl;
				cout<<"�ʹ�ʱ�䣺";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
			}else{
				if(d >= 0){
					cout <<location<<"��"<<e.destination<<"����̾���Ϊ:"<<d<<"km"<<endl;
				}else{
					cout <<location<<"��"<<e.destination<<"����̾���Ϊ:"<<G.D[start][end]<<"km"<<endl;
				}
				int days[]={31, 28, 31 ,30,31, 30, 31, 31, 30, 31, 30, 31};//����ÿ�����ж�����
				if(year % 400 ||(year % 4 && year % 100 != 0)){
					//�������Ϊ29��
					days[1] = 29;
				}
				int second;
				if(d >= 0){
					second = (int)(d / 0.5 * 60);
				}else{
					second = (int)(G.D[start][end] / 0.5 * 60);
				}
				sec += second;
				if(sec >= 60){
					mi += sec / 60;
					sec = sec % 60;
				}
				if(mi >= 60){
					hour += mi / 60;
					mi = mi % 60;
				}
				if(hour >= 24){
					day += hour / 24;
					hour = hour % 24;
				}
				if(day >= days[month]){
					day = day - days[month];
					month ++ ;
				}
				if(month >= 12){
					year += month / 12;
					month = month % 12;
				}
				cout<<"�ʹ�ʱ�䣺";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
				if(d < 0){
					cout <<"���·��Ϊ:"<<location<<"->"<<e.destination<<endl;
				}else{
					PrintShortedPath(G, start, end);
				}
				location = e.destination;
				isdelive = true;
			}
		}	
	}else{
		int start = Find_Destination(G, location);
		int end = Find_Destination(G, e.destination);
		if(start == -1){
			cout<<"���("<<location<<")����򲻴��ڣ�"<<endl;
		}
		if(end == -1){
			cout<<"�յ�("<<e.destination<<")����򲻴��ڣ�"<<endl;
		}
		if(start != -1 && end != -1){
			cout<<"��ǰ������Ϣ��"<<endl;
			printf("������            �ײ�        ����            ����          �绰             �ص�            �µ�ʱ��\n");
			printf("%s\t", e.ordernumber.c_str());
			printf("  %c%03d\t", e.setmark1, e.setmark2);//�ײͱ��
			printf("      %2d\t", e.totalset);//�ײ�����
			printf("%10s\t", e.name.c_str());//����������
			printf("  %11s\t", e.number.c_str());//�����˵绰
			printf(" %10s\t", e.destination.c_str());//�ص�
			printf("  %s\n", e.ordertime.c_str());//�µ�ʱ��
			if(location == e.destination ){
				cout<<"��ǰλ��("<<location<<")Ϊ�Ͳ͵ص㡣"<<endl;
				cout<<"�ʹ�ʱ�䣺";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
			}else{
				cout <<location<<"��"<<e.destination<<"����̾���Ϊ:"<<G.D[start][end]<<"km"<<endl;
				int days[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};//����ÿ�����ж�����
				if(year % 400 ||(year % 4 && year % 100 != 0)){
					//�������Ϊ29��
					days[1] = 29;
				}
				int second = (int)(G.D[start][end] / 0.5 * 60);
				sec += second;
				if(sec >= 60){
					mi += sec / 60;
					sec = sec % 60;
				}
				if(mi >= 60){
					hour += mi / 60;
					mi = mi % 60;
				}
				if(hour >= 24){
					day += hour / 24;
					hour = hour % 24;
				}
				if(day >= days[month]){
					day = day - days[month];
					month ++ ;
				}
				if(month >= 12){
					year += month / 12;
					month = month % 12;
				}
				cout<<"�ʹ�ʱ�䣺";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
				cout <<"���·��Ϊ:";
				PrintShortedPath(G, start, end);
				location = e.destination;
				isdelive = true;
			}
		}
	}
	if(isdelive){
		e.orderstate = 2;//�޸�״̬
		OrderCountElem elem;
		elem.ordernumber = e.ordernumber;
		elem.setmark1 = e.setmark1;
		elem.setmark2 = e.setmark2;
		elem.totalset = e.totalset;
		elem.totalprice = e.totalset * e.price;
		elem.destination = e.destination;
		elem.ordertime = e.ordertime;
		elem.orderstate = e.orderstate;
		AppendOrderElem(C, elem);
		ofstream ordcnt("ordercnt.txt", ios::app);
		if(ordcnt.is_open()){
			ordcnt<<elem.ordernumber<<" "<<elem.setmark1<<" "<<elem.setmark2<<" "<<elem.totalset<<" "<<elem.totalprice<<" "<<elem.destination<<" "<<elem.ordertime<<" "<<elem.orderstate<<endl;
			ordcnt.close();
		}
	}
}
void Delivery(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G, string &location){ 
	//���Ͷ���
	system("cls");//����
	while(1){
		Load_main_menu();//�������˵�
		cout<<"����ѡ���ǣ����Ͷ���"<<endl;
		Load_delivery_menu();//�������Ͳ˵�
		cout<<"����������ѡ��";
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '2'){
			//��鲢����
			system("cls");
			Load_main_menu();//�������˵�
			cout<<"����ѡ���ǣ����Ͳ˵�"<<endl;
			Load_delivery_menu();//�������Ͳ˵�
			cout<<"ѡ�����������ѡ��";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':Traverse_UnDelivery(Q);//��ʾδ���Ͷ���
			break;
		case '2':Delive_One_By_One(S, Q, C, G,location);//�������
			break;
		}
		system("pause");
		system("cls");
	}
}
void Data_maintenance(SetList &S){
	//��������ά��
	string mark, name, describe, price, state;
	char mark1;
	int mark2;
	bool flag[3];
	SetElem e;
	system("cls");//����
	while(1){
		Load_main_menu();//�������˵�
		cout<<"����ѡ���ǣ���������ά��"<<endl;
		Load_data_maintenance_menu();//���ػ�������ά���˵�
		cout<<"����������ѡ��"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '3'){
			//��鲢����
			system("cls");
			Load_main_menu();//���¼������˵�
			cout<<"����ѡ����:��������ά��"<<endl;
			Load_data_maintenance_menu();//���ػ�������ά���˵�
			cout<<"ѡ�����������ѡ��";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':
			cout<<"�������ײ�����:";
			cin >> name;
			cout<<"�������ײ�����:";
			cin >> describe;
			cout<<"�������ײͼ۸�:";
			cin >> price;
			flag[0] = Judge_SetName(S, name, S.length +  1);
			flag[1] = Judge_Price(price, e.price);
			flag[2] = false;
			if(flag[0] && flag[1]){
				e.mark1 = FirstMark;
				e.mark2 = S.length + 1;
				e.name = name;
				e.describe = describe;
				e.state = 1;//Ĭ������ӵĿ�Ԥ��
				flag[2] = true;
				cout<<"�ײ�״̬Ϊ��Ԥ����"<<endl;
				AppendSet(S, e);
			}else{
				cout<<"������󣡴���ԭ��:";
				string reason[3] ={"�ײ������Ѵ���","|�۸����|","|״̬����|"} ;
				for(int i = 0; i < 3 ; i++){
					if(!flag[i]){
						cout<<reason[i];
					}
				}
				cout<<endl;
			}
			break;
		case '2':cout<<"�����ײͱ��:";
			cin >>mark;
			Judge_SetMark(S, mark, mark1, mark2);
			if(mark1 == 'M' && S.length >= mark2){
				cout<<"���ײ�Ϊ��";
				printf("%c%03d\t", S.setmea[mark2].mark1, S.setmea[mark2].mark2);
				printf("   %10s\t", S.setmea[mark2].name.c_str());
				printf("   %10s\t", S.setmea[mark2].describe.c_str());
				printf("  %d\t", S.setmea[mark2].price);
				if(S.setmea[mark2].state == 1)
					printf("     ��Ԥ��\n");
				else
				printf("   ����Ԥ��\n");
				cout<<"��ʼ�޸��ײ�---------------------------------->"<<endl;
				cout<<"�������ײ�����:";
				cin >> name;
				cout<<"�������ײ�����:";
				cin >> describe;
				cout<<"�������ײͼ۸�:";
				cin >> price;
				cout<<"�������ײ�״̬(1-��Ԥ�� 0-����Ԥ��):";
				cin >> state;
				flag[0] = Judge_Price(price, e.price);
				flag[1] = Judge_State(state, e.state);
				if(flag[0] && flag[1]){
					S.setmea[mark2].name = name;
					S.setmea[mark2].describe = describe;
					S.setmea[mark2].price = e.price;
					S.setmea[mark2].state = e.state;
				}else{
					cout<<"������󣡴���ԭ��:";
					string reason[2] ={"|�۸����|","|״̬����|"} ;
					for(int i = 0; i < 2 ; i++){
						if(!flag[i]){
							cout<<reason[i];
						}
					}
					cout<<endl;
				}
			}else{
				cout<<"�����ڸ��ײͻ��������"<<endl;
			}
			break;
		case '3':cout<<"�����ײͱ��:";
			cin >>mark;
			if(Judge_SetMark(S, mark, mark1, mark2)){
				cout<<"���ײ�Ϊ��";
				printf("%c%03d\t", S.setmea[mark2].mark1, S.setmea[mark2].mark2);
				printf("   %10s\t", S.setmea[mark2].name.c_str());
				printf("   %10s\t", S.setmea[mark2].describe.c_str());
				printf("  %d\t", S.setmea[mark2].price);
				if(S.setmea[mark2].state == 1)
					printf("     ��Ԥ��\n");
				else
				printf("   ����Ԥ��\n");
				if(!S.setmea[mark2].state){
					cout<<"���ײ��Ѿ��޷�Ԥ����"<<endl;
				}else{
					S.setmea[mark2].state = false;
					cout<<"ɾ�����"<<endl;
				}
			}else{
				cout<<"�����ڸ��ײͻ��������"<<endl;
			}
			break;
		}
		system("pause");
		system("cls");
	}
}
void Date_Count(Order_LinkQueue Q, OrderCountList C, SetList S, char option){
	//����ͳ�ƣ�option Ϊ'd'����ͳ�ƣ� optionΪ'w'����ͳ�ƣ�optionΪ'm'����ͳ�ƣ�
	time_t nowtime;
	struct tm* p;
	time(&nowtime);
	int sy, sm, sd, ey, em, ed;
	string start, end;
	p = localtime(&nowtime);
	sy = ey = p->tm_year + 1900;
	sm = em = p->tm_mon + 1;
	sd =  ed = p->tm_mday;
	if(option == 'd'){
		start += Integer_To_String(sy, 4);
		end += Integer_To_String(sy, 4);
		start += Integer_To_String(sm, 2);
		end += Integer_To_String(sm, 2);
		start += Integer_To_String(sd, 2);
		end += Integer_To_String(sd, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(23, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
		ifstream orderin("ordercnt.txt");
	}else if(option == 'w'){
		//�漰���ܿ����п��������
		//������������ڼ�����ǰ��;
		int week;
		if(em <= 2){
			//ʹ�ò̻�ķ����ɭ��ʽҪ��һ���µ�����һ���13��14�¼���
			em += 12;
			ey --;
		}
		week = (ed + 2 * em + 3 * (em + 1) / 5 + ey + ey / 4 - ey / 100 + ey / 400) % 7;//�������������0-6
		sd = ed - week;
		int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//�������ݶ�28��
		if(ey % 400 == 0 || (ey % 100 != 0 && ey % 4 == 0)){
			days[1] = 29;//���Ķ�������
		}
		if(sd <= 0){
			sd += days[em - 2];
			-- sm;
		}
		if(em <= 0){
			sm += 12;
			-- sy;
		}
		start += Integer_To_String(sy, 4);
		end += Integer_To_String(ey, 4);
		start += Integer_To_String(sm, 2);
		end += Integer_To_String(em, 2);
		start += Integer_To_String(sd, 2);
		end += Integer_To_String(ed, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(23, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
	}else if(option == 'm'){
		start += Integer_To_String(sy, 4);
		end += Integer_To_String(sy, 4);
		start += Integer_To_String(sm, 2);
		end += Integer_To_String(sm, 2);
		start += Integer_To_String(1, 2);
		end += Integer_To_String(31, 2);//���ڲ����ܳ���31
		start += Integer_To_String(0, 2);
		end += Integer_To_String(23, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
	}else{
		cout<<"ѡ�����"<<endl;
		return;
	}
	CountSet(start, end, C, S, Q);
}
void Statistics(Order_LinkQueue Q, OrderCountList C, DestinationGraph G, SetList S){
	//ͳ��
	system("cls");//����
	while(1){
		Load_main_menu();//�������˵�
		cout<<"����ѡ���ǣ�ͳ��"<<endl;
		Load_statistics_menu();//����ͳ�Ʋ˵�
		cout<<"����������ѡ��"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '4'){
			//��鲢����
			system("cls");
			Load_main_menu();//���¼������˵�
			cout<<"����ѡ����:ͳ��"<<endl;
			Load_statistics_menu();//����ͳ�Ʋ˵�
			cout<<"ѡ�����������ѡ��";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':Date_Count(Q, C, S, 'd');
			break;
		case '2':Date_Count(Q, C, S, 'w');
			break;
		case '3':Date_Count(Q, C, S,'m');
			break;
		case '4':Destination_Count(Q, C, G);
		}
		system("pause");
		system("cls");
	}
}
void Off_work(Order_LinkQueue Q, SetList S){
	//�°�
	//�����ײ���Ϣ
	//���붩����Ϣ
	int i;
	ofstream setout("setmeal.txt");
	if(!setout.is_open()){
		cout<<"��setmeal�ļ�ʧ��!"<<endl;
	}
	if(setout.is_open()){
		for(i = 1; i <= S.length ; i++){
			setout << S.setmea[i].mark1<<" ";
			setout << S.setmea[i].mark2<<" ";
			setout << S.setmea[i].name<<" ";
			setout << S.setmea[i].describe<<" ";
			setout << S.setmea[i].price<<" ";		
			setout << S.setmea[i].state;
			if( i != S.length )
				setout<<endl;
		}
		setout.close();
	}
	ofstream orderout("order.txt");
	if(!orderout.is_open()){
		cout<<"��order�ļ�ʧ��!"<<endl;
	}
	if(orderout.is_open()){
		OrderQueue_Ptr p;
		p = Q.front ->next;
		int cnt = Q.length;
		while(p != NULL ){
			orderout<<p->orderelem.ordernumber<<" ";//������
			orderout<<p->orderelem.setmark1<<" ";
			orderout<<p->orderelem.setmark2<<" ";//�ײͱ��
			orderout<<p->orderelem.totalset<<" ";//�ײ�����
			orderout<<p->orderelem.name<<" ";//����������
			orderout<<p->orderelem.number<<" ";//�����˵绰
			orderout<<p->orderelem.destination<<" ";//�ص�
			orderout<<p->orderelem.ordertime<<" ";//�µ�ʱ��
			orderout<<p->orderelem.orderstate;
			cnt--;
			if(cnt){
				orderout<<endl;//����״̬
			}
			p = p->next;
		}
		orderout.close();
	}
	cout<<"���°࣬��л����ʹ�á�";
}
void Application(){
	//��������
	SetList S;
	Order_LinkQueue Q;
	DestinationGraph G;
	OrderCountList C;
	string location = "";
	bool isworking = false;
	while(1){
		Load_main_menu();//�������˵� 
		cout<<"����������ѡ�";
		string option;//���˵�ѡ�1-�ϰ� 2-�������� 3-���Ͷ��� 4-��������ά�� 5-ͳ�� 0-�°�
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0'){
			if(isworking){
				Off_work(Q, S);//�°�
				system("pause");
				break;
			}
		}
		while(opt < '0' || opt > '5'){
			//��鲢���´���ѡ��
			system("cls");
			Load_main_menu();//���¼������˵� 
			cout<<"ѡ��Ϸ���������ѡ��";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		if(isworking || opt == '1'){
			switch(opt){
			case '1':if(isworking){
					  cout<<"�Ѿ����ϰ��ˣ�"<<endl;
					 }else{
						if(Start_work(S, Q, C, G) == ERROR){
							//��ʼ�ϰ�
							system("pause");
							return ;
						}
						isworking = true;
					 }
				break;
			case '2':Order_manage(S, Q, C, G);//��������
				break;
			case '3':Delivery(S, Q, C, G, location);//���Ͷ���
				break;
			case '4':Data_maintenance(S);//������Ϣά��
				break;
			case '5':Statistics(Q, C, G, S);//ͳ��
				break;
			}
		}else{
			cout<<"�����ϰ��ٽ��д˲�����"<<endl;
		}
		system("pause");
		system("cls");
	}
}

