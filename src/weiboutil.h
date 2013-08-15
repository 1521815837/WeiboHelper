/*
 * weiboutil.h
 *微博工具类：对从微博上获取到的Json数据进行处理，获取有用的数据
 *
 *  Created on: 2013年8月9日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 *		version:	0.1
 */

#ifndef WEIBOUTIL_H_
#define WEIBOUTIL_H_

typedef long long int64;
#include <stdlib.h>

struct weibo{
	long long id			;	//微博ID
	char 	create_time[32];	//微博的创建时间
	char	text[425];			//微博内容
	char	username[50];		//微博用户昵称
	struct weibo* next;	//指向下一条微博
};

/*
 * 从字符串中获取微博
 */
struct weibo* get_weiboes(const char* strings);

/*
 * 从字符串中获取微博,与get_weiboes不同的主要是这个以使用sscanf为主
 */
struct weibo* get_weiboes_2(const char* strings);

//新提及我的微博数
int get_unread_mention_status(const char* json_result);

//对新提及我的微博数清零
int reset_unread_mention_status(const char* access_token);

/*
 * 清空申请的空间
 */
void free_weibo(struct weibo* weibo);

#endif /* WEIBOUTIL_H_ */
