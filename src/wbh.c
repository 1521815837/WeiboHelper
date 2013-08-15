/*
 * wbh.c
 *
 *  Created on: 2013年8月16日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 */

#include "wbh.h"

#define MAXBUFFER	40960

/*
 * 最好等好程序处理完一条微博指令后再发新的指令。否则BUG 。。。。。。。。。。。。。
 */
int weiBoHelper()
{
	extern char access_token[];
	int unread=0;
	char* unread_result=(char*)malloc(sizeof(char)*256);
	char* result=(char*)malloc(sizeof(char)*MAXBUFFER);
	char* orderName=(char*)malloc(sizeof(char)*128);
	char* orderExec=(char*)malloc(sizeof(char)*512);
	struct weibo* weiboes=NULL;
	while(1){
		memset(unread_result,'\0',sizeof(char)*256);
		while(get_unread_count(access_token,unread_result)){	//获取各种未读数出错
			memset(unread_result,'\0',sizeof(char)*256);
			sleep(2);
		}
		unread=get_unread_mention_status(unread_result);
		debug("unread count is :%d\n",unread);

		if(unread){	//未读数不为零
			//对未读数清零
//			while(reset_unread_mention_status(access_token)){	//清零失败？重试
//				sleep(2);
//			};

			memset(result,'\0',sizeof(char)*MAXBUFFER);
			while(get_newest_at_user(access_token,unread,result)){	//获取数据失败？重试
				memset(result,'\0',sizeof(char)*MAXBUFFER);
				sleep(2);
			}

			weiboes=get_weiboes_2(result);
			struct weibo* next=weiboes;

			while(next){
				memset(orderName,'\0',sizeof(char)*128);
				get_orderName_by_weiboContent(next,orderName);	//从微博内容中分离出指令
				memset(orderExec,'\0',sizeof(char)*512);
				get_orderExec_by_orderName(orderName,orderExec);	//根据指令从数据库中查出命令
				if(strlen(orderExec)){	//指令存在
					debug("指令存在!\n");
				}else{//指令不存在
					debug("指令不存在!\n");
				}

				next=next->next;	//指向下一条微博
			}

			free_weibo(weiboes);weiboes=NULL;
		}

		sleep(2);
	}
	free(unread_result);
	free(result);
	free(orderName);
}
