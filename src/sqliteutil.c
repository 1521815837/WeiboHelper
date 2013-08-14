/*
 * sqliteutil.c
 *
 *  Created on: 2013年8月15日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 */

#include "sqliteutil.h"
#include "includes.h"

int create_db(const char* database)
{
	sqlite3* db=NULL;  //sqlite3句柄
	char* errmsg=NULL; //错误输出信息
	int ret;
	ret=sqlite3_open(database,&db);
	if(ret!=SQLITE_OK)
	{
		sqlite3_close(db);
		debug("创建数据库MYDB失败!ret:%d\n",ret);
		return ret;
	}
	return ret;
}
int sql_query(const char* database,
		const char* sql,int (*Callback)(void*,int,char**,char**),
		void* argv)
{
	sqlite3* db=NULL;	//sqlite3句柄
	int ret=0;		//sqlite3返回值
	char *errMsg=NULL;
	char* result=NULL;

	ret=sqlite3_open(database,&db);	//打开数据库
	if(ret!=SQLITE_OK){
			sqlite3_close(db);	//出错也要记得关闭db
			debug("sql_query error:%s\n",strerror(ret));
			return ret;
		}

	sqlite3_busy_timeout(db,2000); //超时设置
	ret=sqlite3_exec(db,sql,Callback,argv,&errMsg);	//执行查询
	if(ret!=SQLITE_OK){	//查询有误
			debug("sql_query error:%s\n",errMsg);
			sqlite3_free(errMsg);
			sqlite3_close(db);		//关闭数据库
			return ret;
		}
	sqlite3_close(db);
	return SQLITE_OK;
}

int sql_alter(const char* database,const char* sql)
{
	sqlite3* db=NULL;	//sqlite3句柄
	int ret=0;		//sqlite3返回值
	char *errMsg=NULL;

	ret=sqlite3_open(database,&db);
	sqlite3_exec(	//开启外键约束
				db,
				"PRAGMA foreign_keys=ON",
				NULL,
				NULL,
				NULL);
	if(ret!=SQLITE_OK){
			sqlite3_close(db);
			debug("sql_alter error:%s\n",strerror(ret));
			return ret;
		}
	sqlite3_busy_timeout(db,2000);
	ret=sqlite3_exec(db,sql,NULL,NULL,&errMsg);
	if(ret!=SQLITE_OK){	//查询有误
			debug("sql_alter error:%s\n",errMsg);
			sqlite3_free(errMsg);
			sqlite3_close(db);
			return ret;
		}
	sqlite3_close(db);
	return ret;
}
