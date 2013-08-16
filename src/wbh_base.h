/*
 * wbh_base.h
 *
 *  Created on: 2013年8月15日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 *		WeiboHelper_base
 */

#ifndef WBH_BASE_H_
#define WBH_BASE_H_

#include "weiboutil.h"
#include "sqliteutil.h"


/*
 * 创建程序所需的数据库、数据标和测试数据,函数执行后会在程序所在的目录下
 * 生成数据库文件wbh.db,如果文件已存在则创建失败
 */
int init_weh_DB();

/*
 * 从微博内容中分离出指令
 */
int get_orderName_by_weiboContent(const struct weibo* weibo,char* orderName);

/*
 * 在数据库中通过指令查询出要执行的命令
 */
int get_orderExec_by_orderName(const char* orderName,char* orderExec);


/*
 * 读出tb_lastread表中保存的微博ID
 */
long long get_lastRead_WeiboID();

int set_lastRead_WeiboID(long long id);

#endif /* WBH_BASE_H_ */
