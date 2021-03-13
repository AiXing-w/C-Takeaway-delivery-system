/*
订单管理系统选项 
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
	//开始上班
	bool flag = true;
	InitList(S);
	ifstream setin("setmeal.txt");
	int i=0;
	if(setin.is_open())
		cout<<"打开setmeal.txt文件成功！"<<endl;
	else{
		cout<<"打开setmeal.txt文件失败!"<<endl;
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
		cout<<"套餐加载成功！"<<endl;
	}
	Init_OrderQueue(Q);
	ifstream orderin("order.txt");
	if(orderin.is_open())
		cout<<"打开order.txt文件成功！"<<endl;
	else{
		cout<<"打开order.txt文件失败（仍可上班）"<<endl;
		//此处不改变flag的值，而是将order.txt文件不存在的情况当作不存在未派送的订单来处理
		//增加了健壮性
	}
	if(orderin.is_open() && orderin.peek() != EOF){
		while(!orderin.eof()){
			OrderQueue_Elem e;
			orderin >> e.ordernumber;//订单号
			orderin >> e.setmark1;//编号1
			orderin >> e.setmark2;//编号2
			orderin >> e.totalset;//总数
			orderin >> e.name;//姓名
			orderin >> e.number;//号码
			orderin >> e.destination;//地点
			orderin >> e.ordertime;//订餐时间
			orderin >> e.orderstate;//状态
			En_OrderQueue(Q, e);
		}
		orderin.close();
		cout<<"待派送订单加载成功！"<<endl;
	}
	InitOrderCountList(C);
	ifstream Orderlist("ordercnt.txt");
	if(Orderlist.is_open()){
		cout<<"打开ordercnt.txt文件成功！"<<endl;
	}else{
		cout<<"打开ordercnt.txt文件失败（仍可上班）"<<endl;
	}
	if(Orderlist.is_open() && Orderlist.peek() != EOF){
		while(!Orderlist.eof()){
			OrderCountElem e;
			Orderlist >>e.ordernumber>>e.setmark1>>e.setmark2>>e.totalset>>e.totalprice>>e.destination>>e.ordertime>>e.orderstate;
			AppendOrderElem(C, e);
		}
		Orderlist.close();
		cout<<"订单表加载成功！"<<endl;
	}
	//
	Init_DestinationGraph(G);
	ifstream destination("destination.txt");
	if(destination.is_open()){
		cout <<"打开destination.txt文件成功！"<<endl;
	}else{
		cout <<"打开destination.txt文件失败"<<endl;
		flag = false;
	}
	if(destination.is_open() && destination.peek() != EOF){
		while(!destination.eof()){
			//加载地点信息
			destination >> G.vex[G.vexnum];
			++G.vexnum; 
		}
		Sort_Destination(G);
		destination.close();
		cout<<"加载地点成功！"<<endl;
	}
	ifstream distance("distance.txt");
	if(distance.is_open()){
		cout <<"打开distance.txt文件成功！"<<endl;
	}else{
		cout <<"打开distance.txt文件失败！"<<endl;
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
		cout<<"加载距离成功！"<<endl;
	}
	if( !G.IsFinded ){
		//如果未求得最短路径
		ShortestPath(G);
		G.IsFinded = true;//标记已求得最短路径
	}
	if(flag){
		cout<<"开始上班！"<<endl;
	}else{
		cout<<"信息加载错误！"<<endl;
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
	//接收订单
	OrderQueue_Elem ord;
	bool flag[4];//判断输入是否合法的标记
	string mark;
	string tot;
	char mark1;//套餐编号1
	int mark2;//套餐编号2
	int total;//套餐数量
	string name;
	string number;
	string destination;
	cout<<"请输入套餐编号：";
	cin >> mark;
	cout<<"请输入套餐数量：";
	cin >> tot;
	cout<<"请输入您的姓名：";
	cin >> name;
	cout<<"请输入您的手机号：";
	cin >> number;
	cout<<"请输入送餐地址：";
	cin >> destination;
	flag[0] = Judge_SetMark(S, mark, mark1, mark2);//判断套餐编号是否合法
	flag[1] = Judge_SetTotal(tot, total);//判断套餐数是否合法
	flag[2] = Judge_SetNumber(number);//判断电话是否合法
	flag[3] = Judge_SetDestination(G, destination);//判断派送地点是否合法
	if(flag[0] && flag[1] && flag[2] && flag[3] && S.setmea[mark2].state){
		//如果输入数据均和法入队
		ord.setmark1 = mark1;
		ord.setmark2 = mark2;
		ord.totalset = total;
		ord.price = S.setmea[mark2].price;
		ord.number = number;
		ord.name = name;
		ord.destination = destination;
		Get_OccurTime(ord.ordernumber, ord.ordertime);//获取时间
		ord.orderstate = 1;//订餐状态 ： 0-已取消 1-未派送 2-已派送 3-已接收
		cout<<"您的订单为："<<endl;
		printf("订单号           套餐     数量     姓名     电话             地点            下单时间          状态\n");
		printf("%s\t", ord.ordernumber.c_str());//订单号
		printf("%c%03d\t", ord.setmark1, ord.setmark2);//套餐编号
		printf("    %d\t", ord.totalset);//套餐数量
		printf("   %s\t", ord.name.c_str());//订餐人姓名
		printf("  %s\t", ord.number.c_str());//订餐人电话
		printf("%12s\t", ord.destination.c_str());//地点
		printf("%s\t", ord.ordertime.c_str());//下单时间
		printf("%d\n", ord.orderstate);//订餐状态
		if(!En_OrderQueue(Q, ord)){
			cout<<"进队失败！"<<endl;
		}
	}else{
		//说明错误原因
		cout<<"输入数据错误！错误原因:"<<endl;
		string reasons[4] = {"|套餐编号错误|", "|套餐数目错误|", "|电话输入错误|", "|派送地址错误|"};
		int i;
		for(i = 0; i < 4 ; i++){
			if(!flag[i])
				cout<<reasons[i];
		}
		cout<<endl;
	}
}
void OrderModify(SetList S, DestinationGraph G, Order_LinkQueue &Q,bool option){
	//当option为0时取消订单，当为1 时订单状态不变
	string ordernumber;//订单编号
	cout<<"请输入订单编号"<<endl;
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
		cout<<"不存在该订单或订单号输入错误！"<<endl;
	}else{
		if(option){
			bool flag[4];//判断输入是否合法的标记
			string mark;
			string tot;
			char mark1;//套餐编号1
			int mark2;//套餐编号2
			int total;//套餐数量
			string name;
			string number;
			string destination;
			cout<<"请输入套餐编号：";
			cin >> mark;
			cout<<"请输入套餐数量：";
			cin >> tot;
			cout<<"请输入您的姓名：";
			cin >> name;
			cout<<"请输入您的手机号：";
			cin >> number;
			cout<<"请输入送餐地址：";
			cin >> destination;
			flag[0] = Judge_SetMark(S, mark, mark1, mark2);//判断套餐编号是否合法
			flag[1] = Judge_SetTotal(tot, total);//判断套餐数是否合法
			flag[2] = Judge_SetNumber(number);//判断电话是否合法
			flag[3] = Judge_SetDestination(G, destination);//判断派送地点是否合法
			if(flag[0] && flag[1] && flag[2] && flag[3]){
				//如果输入数据均和法入队
				p->orderelem.setmark1 = mark1;
				p->orderelem.setmark2 = mark2;
				p->orderelem.totalset = total;
				p->orderelem.number = number;
				p->orderelem.name = name;
				p->orderelem.destination = destination;
				cout<<"订单修改成功。"<<endl;
			}else{
			//说明错误原因
				cout<<"输入数据错误！无法进行修改！错误原因:"<<endl;
				string reasons[4] = {"|套餐编号错误|", "|套餐数目错误|", "|电话输入错误|", "|派送地址错误|"};
				int i;
				for(i = 0; i < 4 ; i++){
					if(!flag[i])
						cout<<reasons[i];
				}
				cout<<endl;
			}
		}else{
			p->orderelem.orderstate = 0;
			cout<<"订单撤销成功。"<<endl;
		}
	}
}
void OrderInquiry(Order_LinkQueue Q){
	//查询订单
	system("cls");//清屏
	while(1){
		Load_main_menu();//加载主菜单
		cout<<"您的选择是:订单管理"<<endl;
		Load_order_manage_menu();//加载订单管理菜单
		cout<<"您的选择是：查询订单"<<endl;
		Load_orderinquiry();//加载订单查询菜单
		cout<<"请输入您的选择"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '2'){
			//检查并更新
			system("cls");
			Load_main_menu();//重新加载主菜单
			cout<<"您的选项是:查询订单"<<endl;
			Load_orderinquiry();//加载订单菜单
			cout<<"选项错误，请重新选择：";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		string number;
		string name;
		switch(opt){
		case '1':cout<<"请输入待查询的订单号"<<endl;
			cin>>number;
			OrderNumber_Search(Q, number);//按订单号查询订单并输出
			break;
		case '2':cout<<"请输入待查询的订餐人姓名"<<endl;
			cin>>name;
			OrderName_Search(Q, name);//按订餐姓名查询订单并输出
			break;
		}
		system("pause");
		system("cls");
	}
}
void Order_manage(SetList S, Order_LinkQueue &Q, OrderCountList &C, DestinationGraph G){
	//订单管理
	system("cls");//清屏
	while(1){
		Load_main_menu();//加载主菜单
		cout<<"您的选择是：订单管理"<<endl;
		Load_order_manage_menu();//加载订单管理菜单
		cout<<"请输入您的选择"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '5'){
			//检查并更新
			system("cls");
			Load_main_menu();//重新加载主菜单
			cout<<"您的选项是:订单管理"<<endl;
			Load_order_manage_menu();//加载订单菜单
			cout<<"选项错误，请重新选择：";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':PrintReserveSet(S);//显示套餐
			cout<<endl;
			Traverse_Destination(G);//显示地点
			cout<<endl; 
			Receive_Orders(G, S, Q);//接收菜单
			break;
		case '2':OrderInquiry(Q);//查询订单
			break;
		case '3':cout<<"当前订单为："<<endl;
			Traverse_OrderQueue(Q);//显示订单
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
	//逐个派送
	bool isdelive = false;
	OrderQueue_Elem e;
	if(Q.length == 0){
		cout<<"暂无待派送的订单。"<<endl;
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
		//如果队空
		cout<<"暂无待派送的订单。"<<endl;
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
		cout << "快递员还未出发，请输入起始地点:";
		cin >> location;
		float d = -1;
		
		int start = Find_Destination(G, location);
		if(start == -1){
			cout<<"该地点不在派送地图内！"<<endl;
			cout << "请输入与"<<e.destination<<"(第一个地点)的距离:";
			cin >> d;

		}else{
			cout<<"该地点在派送地图内！"<<endl;
		}
		int end = Find_Destination(G, e.destination);
		if(end == -1){
			cout<<"终点("<<e.destination<<")错误或不存在！"<<endl;
		}else{
			cout<<"当前订单信息："<<endl;
			printf("订单号            套餐        数量            姓名          电话             地点            下单时间\n");
			printf("%s\t", e.ordernumber.c_str());
			printf("  %c%03d\t", e.setmark1, e.setmark2);//套餐编号
			printf("      %2d\t", e.totalset);//套餐数量
			printf("%10s\t", e.name.c_str());//订餐人姓名
			printf("  %11s\t", e.number.c_str());//订餐人电话
			printf(" %10s\t", e.destination.c_str());//地点
			printf("  %s\n", e.ordertime.c_str());//下单时间
			
			if(location == e.destination){
				cout<<"当前位置("<<location<<")为送餐地点。"<<endl;
				cout<<"送达时间：";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
			}else{
				if(d >= 0){
					cout <<location<<"到"<<e.destination<<"的最短距离为:"<<d<<"km"<<endl;
				}else{
					cout <<location<<"到"<<e.destination<<"的最短距离为:"<<G.D[start][end]<<"km"<<endl;
				}
				int days[]={31, 28, 31 ,30,31, 30, 31, 31, 30, 31, 30, 31};//储存每个月有多少天
				if(year % 400 ||(year % 4 && year % 100 != 0)){
					//闰年二月为29天
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
				cout<<"送达时间：";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
				if(d < 0){
					cout <<"最短路径为:"<<location<<"->"<<e.destination<<endl;
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
			cout<<"起点("<<location<<")错误或不存在！"<<endl;
		}
		if(end == -1){
			cout<<"终点("<<e.destination<<")错误或不存在！"<<endl;
		}
		if(start != -1 && end != -1){
			cout<<"当前订单信息："<<endl;
			printf("订单号            套餐        数量            姓名          电话             地点            下单时间\n");
			printf("%s\t", e.ordernumber.c_str());
			printf("  %c%03d\t", e.setmark1, e.setmark2);//套餐编号
			printf("      %2d\t", e.totalset);//套餐数量
			printf("%10s\t", e.name.c_str());//订餐人姓名
			printf("  %11s\t", e.number.c_str());//订餐人电话
			printf(" %10s\t", e.destination.c_str());//地点
			printf("  %s\n", e.ordertime.c_str());//下单时间
			if(location == e.destination ){
				cout<<"当前位置("<<location<<")为送餐地点。"<<endl;
				cout<<"送达时间：";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
			}else{
				cout <<location<<"到"<<e.destination<<"的最短距离为:"<<G.D[start][end]<<"km"<<endl;
				int days[] = {31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31};//储存每个月有多少天
				if(year % 400 ||(year % 4 && year % 100 != 0)){
					//闰年二月为29天
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
				cout<<"送达时间：";
				printf("%04d-%02d-%02d %02d : %02d : %02d\n", year, month, day, hour, mi , sec);
				cout <<"最短路径为:";
				PrintShortedPath(G, start, end);
				location = e.destination;
				isdelive = true;
			}
		}
	}
	if(isdelive){
		e.orderstate = 2;//修改状态
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
	//派送订单
	system("cls");//清屏
	while(1){
		Load_main_menu();//加载主菜单
		cout<<"您的选择是：派送订单"<<endl;
		Load_delivery_menu();//加载派送菜单
		cout<<"请输入您的选择：";
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '2'){
			//检查并更新
			system("cls");
			Load_main_menu();//加载主菜单
			cout<<"您的选择是：派送菜单"<<endl;
			Load_delivery_menu();//加载派送菜单
			cout<<"选项错误，请重新选择：";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':Traverse_UnDelivery(Q);//显示未派送订单
			break;
		case '2':Delive_One_By_One(S, Q, C, G,location);//逐个派送
			break;
		}
		system("pause");
		system("cls");
	}
}
void Data_maintenance(SetList &S){
	//基础数据维护
	string mark, name, describe, price, state;
	char mark1;
	int mark2;
	bool flag[3];
	SetElem e;
	system("cls");//清屏
	while(1){
		Load_main_menu();//加载主菜单
		cout<<"您的选择是：基础数据维护"<<endl;
		Load_data_maintenance_menu();//加载基础数据维护菜单
		cout<<"请输入您的选择"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '3'){
			//检查并更新
			system("cls");
			Load_main_menu();//重新加载主菜单
			cout<<"您的选项是:基础数据维护"<<endl;
			Load_data_maintenance_menu();//加载基础数据维护菜单
			cout<<"选项错误，请重新选择：";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		switch(opt){
		case '1':
			cout<<"请输入套餐名称:";
			cin >> name;
			cout<<"请输入套餐描述:";
			cin >> describe;
			cout<<"请输入套餐价格:";
			cin >> price;
			flag[0] = Judge_SetName(S, name, S.length +  1);
			flag[1] = Judge_Price(price, e.price);
			flag[2] = false;
			if(flag[0] && flag[1]){
				e.mark1 = FirstMark;
				e.mark2 = S.length + 1;
				e.name = name;
				e.describe = describe;
				e.state = 1;//默认新添加的可预订
				flag[2] = true;
				cout<<"套餐状态为可预订。"<<endl;
				AppendSet(S, e);
			}else{
				cout<<"输入错误！错误原因:";
				string reason[3] ={"套餐名称已存在","|价格错误|","|状态错误|"} ;
				for(int i = 0; i < 3 ; i++){
					if(!flag[i]){
						cout<<reason[i];
					}
				}
				cout<<endl;
			}
			break;
		case '2':cout<<"输入套餐编号:";
			cin >>mark;
			Judge_SetMark(S, mark, mark1, mark2);
			if(mark1 == 'M' && S.length >= mark2){
				cout<<"该套餐为：";
				printf("%c%03d\t", S.setmea[mark2].mark1, S.setmea[mark2].mark2);
				printf("   %10s\t", S.setmea[mark2].name.c_str());
				printf("   %10s\t", S.setmea[mark2].describe.c_str());
				printf("  %d\t", S.setmea[mark2].price);
				if(S.setmea[mark2].state == 1)
					printf("     可预订\n");
				else
				printf("   不可预订\n");
				cout<<"开始修改套餐---------------------------------->"<<endl;
				cout<<"请输入套餐名称:";
				cin >> name;
				cout<<"请输入套餐描述:";
				cin >> describe;
				cout<<"请输入套餐价格:";
				cin >> price;
				cout<<"请输入套餐状态(1-可预订 0-不可预订):";
				cin >> state;
				flag[0] = Judge_Price(price, e.price);
				flag[1] = Judge_State(state, e.state);
				if(flag[0] && flag[1]){
					S.setmea[mark2].name = name;
					S.setmea[mark2].describe = describe;
					S.setmea[mark2].price = e.price;
					S.setmea[mark2].state = e.state;
				}else{
					cout<<"输入错误！错误原因:";
					string reason[2] ={"|价格错误|","|状态错误|"} ;
					for(int i = 0; i < 2 ; i++){
						if(!flag[i]){
							cout<<reason[i];
						}
					}
					cout<<endl;
				}
			}else{
				cout<<"不存在该套餐或输入错误！"<<endl;
			}
			break;
		case '3':cout<<"输入套餐编号:";
			cin >>mark;
			if(Judge_SetMark(S, mark, mark1, mark2)){
				cout<<"该套餐为：";
				printf("%c%03d\t", S.setmea[mark2].mark1, S.setmea[mark2].mark2);
				printf("   %10s\t", S.setmea[mark2].name.c_str());
				printf("   %10s\t", S.setmea[mark2].describe.c_str());
				printf("  %d\t", S.setmea[mark2].price);
				if(S.setmea[mark2].state == 1)
					printf("     可预订\n");
				else
				printf("   不可预订\n");
				if(!S.setmea[mark2].state){
					cout<<"该套餐已经无法预定了"<<endl;
				}else{
					S.setmea[mark2].state = false;
					cout<<"删除完成"<<endl;
				}
			}else{
				cout<<"不存在该套餐或输入错误！"<<endl;
			}
			break;
		}
		system("pause");
		system("cls");
	}
}
void Date_Count(Order_LinkQueue Q, OrderCountList C, SetList S, char option){
	//进行统计（option 为'd'按天统计， option为'w'按周统计，option为'm'按月统计）
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
		//涉及到周可能有跨年的问题
		//先求出今天星期几再向前推;
		int week;
		if(em <= 2){
			//使用蔡基姆拉尔森公式要把一二月当成上一年的13，14月计算
			em += 12;
			ey --;
		}
		week = (ed + 2 * em + 3 * (em + 1) / 5 + ey + ey / 4 - ey / 100 + ey / 400) % 7;//求出来的日期是0-6
		sd = ed - week;
		int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//二月先暂定28天
		if(ey % 400 == 0 || (ey % 100 != 0 && ey % 4 == 0)){
			days[1] = 29;//更改二月日期
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
		end += Integer_To_String(31, 2);//日期不可能超过31
		start += Integer_To_String(0, 2);
		end += Integer_To_String(23, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
		start += Integer_To_String(0, 2);
		end += Integer_To_String(59, 2);
	}else{
		cout<<"选项错误！"<<endl;
		return;
	}
	CountSet(start, end, C, S, Q);
}
void Statistics(Order_LinkQueue Q, OrderCountList C, DestinationGraph G, SetList S){
	//统计
	system("cls");//清屏
	while(1){
		Load_main_menu();//加载主菜单
		cout<<"您的选择是：统计"<<endl;
		Load_statistics_menu();//加载统计菜单
		cout<<"请输入您的选择"<<endl;
		string option;
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0')
			break;
		while(opt < '0' || opt > '4'){
			//检查并更新
			system("cls");
			Load_main_menu();//重新加载主菜单
			cout<<"您的选项是:统计"<<endl;
			Load_statistics_menu();//加载统计菜单
			cout<<"选项错误，请重新选择：";
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
	//下班
	//存入套餐信息
	//存入订单信息
	int i;
	ofstream setout("setmeal.txt");
	if(!setout.is_open()){
		cout<<"打开setmeal文件失败!"<<endl;
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
		cout<<"打开order文件失败!"<<endl;
	}
	if(orderout.is_open()){
		OrderQueue_Ptr p;
		p = Q.front ->next;
		int cnt = Q.length;
		while(p != NULL ){
			orderout<<p->orderelem.ordernumber<<" ";//订单号
			orderout<<p->orderelem.setmark1<<" ";
			orderout<<p->orderelem.setmark2<<" ";//套餐编号
			orderout<<p->orderelem.totalset<<" ";//套餐数量
			orderout<<p->orderelem.name<<" ";//订餐人姓名
			orderout<<p->orderelem.number<<" ";//订餐人电话
			orderout<<p->orderelem.destination<<" ";//地点
			orderout<<p->orderelem.ordertime<<" ";//下单时间
			orderout<<p->orderelem.orderstate;
			cnt--;
			if(cnt){
				orderout<<endl;//订餐状态
			}
			p = p->next;
		}
		orderout.close();
	}
	cout<<"已下班，感谢您的使用。";
}
void Application(){
	//启动程序
	SetList S;
	Order_LinkQueue Q;
	DestinationGraph G;
	OrderCountList C;
	string location = "";
	bool isworking = false;
	while(1){
		Load_main_menu();//加载主菜单 
		cout<<"请输入您的选项：";
		string option;//主菜单选项：1-上班 2-订单管理 3-派送订单 4-基础数据维护 5-统计 0-下班
		cin>>option;
		char opt = Judge_Option(option);
		if(opt == '0'){
			if(isworking){
				Off_work(Q, S);//下班
				system("pause");
				break;
			}
		}
		while(opt < '0' || opt > '5'){
			//检查并更新错误选项
			system("cls");
			Load_main_menu();//重新加载主菜单 
			cout<<"选项不合法，请重新选择：";
			cin >> option;
			opt = Judge_Option(option);
			if(opt == '0'){
				break;
			}
		}
		if(isworking || opt == '1'){
			switch(opt){
			case '1':if(isworking){
					  cout<<"已经在上班了！"<<endl;
					 }else{
						if(Start_work(S, Q, C, G) == ERROR){
							//开始上班
							system("pause");
							return ;
						}
						isworking = true;
					 }
				break;
			case '2':Order_manage(S, Q, C, G);//订单管理
				break;
			case '3':Delivery(S, Q, C, G, location);//派送订单
				break;
			case '4':Data_maintenance(S);//基础信息维护
				break;
			case '5':Statistics(Q, C, G, S);//统计
				break;
			}
		}else{
			cout<<"请先上班再进行此操作！"<<endl;
		}
		system("pause");
		system("cls");
	}
}

