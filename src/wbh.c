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
	long long lastread_weiboId=0;
	char* unread_result=(char*)malloc(sizeof(char)*256);
	char* result=(char*)malloc(sizeof(char)*MAXBUFFER);

	char* orderName=(char*)malloc(sizeof(char)*128);
	char* orderExec=(char*)malloc(sizeof(char)*512);

	char* comment=(char*)malloc(sizeof(char)*512);

	struct weibo* weiboes=NULL;
	while(1){
		lastread_weiboId=get_lastRead_WeiboID();	//获取上一次循环时最后最新的的微博ID
		if(0 == lastread_weiboId){
		memset(unread_result,'\0',sizeof(char)*256);
		while(get_unread_count(access_token,unread_result)){	//获取各种未读数出错
			memset(unread_result,'\0',sizeof(char)*256);
			usleep(1000);
		}
		unread=get_unread_mention_status(unread_result);
		debug("unread count is :%d\n",unread);

		if(0 == unread){
			continue;
		}

		//对未读数清零
		while(reset_unread_mention_status(access_token)){	//清零失败？重试
			sleep(2);
		};

		memset(result,'\0',sizeof(char)*MAXBUFFER);
		while(get_newest_at_user(access_token,lastread_weiboId,unread,result)){	//获取数据失败？重试
			memset(result,'\0',sizeof(char)*MAXBUFFER);
			usleep(1000);
		}

		}
		else{
			memset(result,'\0',sizeof(char)*MAXBUFFER);
			while(get_newest_at_user(access_token,lastread_weiboId,20,result)){	//获取数据失败？重试
				memset(result,'\0',sizeof(char)*MAXBUFFER);
				usleep(1000);
			}
		}
			weiboes=get_weiboes_2(result);
			struct weibo* next=weiboes;
			if(NULL == weiboes){
				continue;
			}
			//保存此次循环最后最新的的微博ID
			set_lastRead_WeiboID(weiboes->id);

			while(next){
				memset(orderName,'\0',sizeof(char)*128);
				get_orderName_by_weiboContent(next,orderName);	//从微博内容中分离出指令
				memset(orderExec,'\0',sizeof(char)*512);
				get_orderExec_by_orderName(orderName,orderExec);	//根据指令从数据库中查出命令

				if(strlen(orderExec)){	//指令存在
					debug("指令存在!\n");
					sprintf(comment,"主人，指令已收到,接下来将会执行：\"%s\"",orderExec);
					new_comments_post(access_token,comment,next->id);
				}
				else{//指令不存在
					debug("指令不存在!\n");
					sprintf(comment,"主人，指令：\"%s\" 未录入数据库！请先将指令录入或者下达新的指令。",orderName);
					new_comments_post(access_token,comment,next->id);
				}

				next=next->next;	//指向下一条微博
			}
		free_weibo(weiboes);weiboes=NULL;
		//usleep(1000);
		//对未读数清零
		while(reset_unread_mention_status(access_token)){	//清零失败？重试
			sleep(2);
		};
	}
	free(unread_result);
	free(result);
	free(orderName);
	free(comment);
}
