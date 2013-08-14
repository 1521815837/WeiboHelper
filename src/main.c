/*
 * main.c
 *
 *  Created on: 2013年8月13日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 */
#include <stdio.h>
#include "yeini.h"
#include "includes.h"

#define DEBUG

void debug(const char *fmt, ...)
{
	#ifdef DEBUG
		#include <stdarg.h>
		 va_list ap;
		 va_start(ap, fmt);
		 vprintf(fmt, ap);
		 va_end(ap);
	#endif
}
extern char access_token[];

#define MAXBUFFER	40960

int main()
{
	init_config();
	char* result=(char*)calloc(MAXBUFFER,sizeof(char));
	//get_newest_at_user(access_token,20,result);
	//debug("result's length is %d\n",strlen(result));
	//free_weibo(get_weiboes_2(result));
	free(result);
	return 0;
}
