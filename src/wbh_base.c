/*
 * wbh_base.c
 *
 *  Created on: 2013年8月15日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 *		WeiboHelper_base
 */
#include "wbh_base.h"
#include <stdio.h>
extern char db_file_url[];	//数据库路径，从配置文件中读取

int get_orderExec_CallBack(void*,int,char**,char**);
int init_weh_DB(){
	//create DB file
	create_db(db_file_url);

	//create table
	char* sql_cteate_tb="Create table tb_order(order_id INTEGER PRIMARY KEY AUTOINCREMENT, order_name nvarchar(64) not null unique, order_exec nvarchar(256) not null)";
	sql_alter(db_file_url,sql_cteate_tb);

	//create test data
	char* sql_insert_tb="insert into tb_order(order_name,order_exec) values('天王盖地虎',\"echo '宝塔镇河妖' > /home/yeso/order.log\")";
	sql_alter(db_file_url,sql_insert_tb);
	return 0;
}

/*
 * 	char* content1="@Yeso test1";  			order:test1
	char* content2="@Yeso test2 @Ye ttt";	order:test2
	char* content="test3 @yeso @Ye";		order:test3
 */
int get_orderName_by_weiboContent(const struct weibo* weibo,char* orderName)
{
	char* p=weibo->next;
	if(*p=='@'){
			sscanf(weibo->next,"%*s%s",orderName);
		}else{
			sscanf(weibo->next,"%s%*s",orderName);
		}
	return 0;
}


int get_orderExec_by_orderName(const char* orderName,char* orderExec)
{
	extern char db_file_url[];
	char sql[128]="";
	sprintf(sql,"select order_exec from tb_order where order_name='%s'",orderName);
	sql_query(db_file_url,sql,get_orderExec_CallBack,(void*)orderExec);
}

int get_orderExec_CallBack(void* argv,int col_count,char** col_values ,char** col_Name)
{
	strcat((char*)argv,col_values[0]);
	return 0;
}
