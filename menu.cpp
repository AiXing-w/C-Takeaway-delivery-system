#include"menu.h"

void Load_main_menu(){
	//加载主菜单
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"               \" 宅 急 送 \" 订 餐 管 理 系 统          "<<endl;
	cout<<"1-上班 2-订单管理 3-派送订单 4-基础数据维护 5-统计 0-下班"<<endl;
	cout<<"---------------------------------------------------------"<<endl; 
}
void Load_start_word_menu(){
	//加载开始工作菜单 
	cout<<"--------------------------"<<endl;
	cout<<"开始上班->->->->->->->->->"<<endl;
	cout<<"--------------------------"<<endl;
	cout<<"信息加载->->->->->->->->->"<<endl;
	cout<<"--------------------------"<<endl;
}
void Load_order_manage_menu(){
	//加载订单管理菜单
	cout<<"------------------------订单管理-----------------------------"<<endl;
	cout<<"1-接收订单 2-查询订单 3-显示订单 4-订单编辑 5-订单撤销 0-退出"<<endl;
	cout<<"-------------------------------------------------------------"<<endl; 
}
void Load_orderinquiry(){
	//加载订单查询菜单
	cout<<"--------------------------------------"<<endl;
	cout<<"1-按订单号查询 2-按订餐姓名查询 0-退出"<<endl;
	cout<<"--------------------------------------"<<endl;
}
void Load_delivery_menu(){
	//加载派送订单菜单
	cout<<"-------------派送订单-------------"<<endl;
	cout<<"1-显示未派送订单 2-逐个派送 0-退出"<<endl;
	cout<<"----------------------------------"<<endl; 
} 
void Load_data_maintenance_menu(){
	//加载基础数据维护菜单
	cout<<"---------------------------------------"<<endl;
	cout<<"1-添加套餐 2-修改套餐 3-删除套餐 0-退出"<<endl;
	cout<<"---------------------------------------"<<endl; 
}
void Load_statistics_menu(){
	//加载统计菜单
	cout<<"------------------------------------------------------------------------------------"<<endl;
	cout<<"1-当天订单信息统计 2-本周订单信息统计 3-当月套餐订购信息统计 4-按派送地点统计 0-退出"<<endl;
	cout<<"------------------------------------------------------------------------------------"<<endl; 
} 
