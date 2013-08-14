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
	char 	create_time[32];	//微博的创建时间
	long long id			;	//微博ID
	char	text[300];			//微博内容
	char	username[31];		//微博用户昵称
	struct weibo* next;	//指向下一条微博
};

/*
 * 从字符串中获取微博
 */
//struct weibo* get_weibos(const char* strings);

struct weibo* get_weibos_2(const char* strings);

/*
 * 清空申请的空间
 */
void free_weibo(struct weibo* weibo);

#endif /* WEIBOUTIL_H_ */
