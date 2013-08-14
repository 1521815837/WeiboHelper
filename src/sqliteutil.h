/*
 * sqliteutil.h
 *
 *  Created on: 2013年8月15日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 */

#ifndef SQLITEUTIL_H_
#define SQLITEUTIL_H_

#include <sqlite3.h>
#include "stdlib.h"

int create_db(const char* database);
/*
 * SQL查询语句
 * 第一个参数为数据库路径
 * 第二个参数为sql查询语句
 * 第三个参数为查询时的回调函数
 * 第四个为回调函数的参数
 */
int sql_query(const char* database,
		const char* sql,int (*Callback)(void*,int,char**,char**),
		void* argv);


/*
 *执行SQL修改语句，insert ,delete,update，create
 *第一个参数为数据库路径
 *第二个参数为要执行的SQL语句
 */
int sql_alter(const char* database,const char* sql);
#endif /* SQLITEUTIL_H_ */
