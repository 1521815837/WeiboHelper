/*
 * weiboutil.c
 *
 *  Created on: 2013年8月9日
 *      Author: yeso
 *  		QQ:	272288813
 *		e-mail: cheng@yeso.me
 *		version:	0.1
 */
#include "weiboutil.h"
#include "string.h"

//struct weibo* get_weibos(const char* strings)
//{
//	struct weibo* weibo=NULL;
//	struct weibo* next_weibo=NULL;
//
//
//	char* p_str=strstr(strings,"{\"created_at");
//	//循环开始：查找字符串"created_at": " ，
//	while(p_str){
//		if(NULL == weibo){
//			weibo=(struct weibo*)calloc(sizeof(struct weibo),sizeof(char));
//			next_weibo=weibo;
//		}else{
//			struct weibo* temp=(struct weibo*)calloc(sizeof(struct weibo),sizeof(char));
//			next_weibo->next=temp;
//			next_weibo=temp;
//		}
//
//		int n;
//		n=strcspn(p_str,":");
//		p_str+=n+2;		//这时指针指向创建时间的首位
//	//	n=strcspn(p_str,"\"");	//获取时间字符串的长度
//		strncpy(next_weibo->create_time,p_str,30);		//提取时间
//		printf("time:%s\t",next_weibo->create_time);
//
//		p_str=strstr(p_str,"id");
//		p_str+=4;
//		n=strcspn(p_str,",");
//		strncpy(next_weibo->id,p_str,16);		//提取ID
//		printf("id:%s\t",next_weibo->id);
//
//		p_str=strstr(p_str,"text");
//		p_str+=7;
//		n=strcspn(p_str,",");				//规定内容中不能出现,
//		strncpy(next_weibo->text,p_str,n-1);
//		printf("content:%s\n",next_weibo->text);		//提取微博内容
//
//		p_str=strstr(p_str,"{\"created_at");
//	}
//
//	return weibo;
//}

struct weibo* get_weibos_2(const char* strings)
{
	struct weibo* weibo=NULL;
	struct weibo* next_weibo=NULL;
	char* p_str=strstr(strings,"{\"created_at");
	while(p_str){
		if(NULL == weibo){
			weibo=(struct weibo*)calloc(sizeof(struct weibo),sizeof(char));
			next_weibo=weibo;
		}else{
			struct weibo* temp=(struct weibo*)calloc(sizeof(struct weibo),sizeof(char));
			next_weibo->next=temp;
			next_weibo=temp;
		}

		sscanf(p_str,"%*[^A-Z]%[^\"]",next_weibo->create_time);	//提取时间戳

		p_str=strstr(p_str,"id");
		char *c_id=(char*)malloc(sizeof(char)*20);
		sscanf(p_str,"id\":%[^,]",c_id);	//提取ID
		sscanf(c_id,"%lld",&next_weibo->id);
		free(c_id);

		char* tail;
		p_str=strstr(p_str,"text");
		p_str+=7;	//指向微博内容
		tail=strstr(p_str,"\",\"source\"");
		int n=tail-p_str;
		strncpy(next_weibo->text,p_str,n);	//提取微博内容

		p_str=strstr(p_str,"\"screen_name\"");
		p_str+=15;
		sscanf(p_str,"%[^\"]",next_weibo->username);	//提取微博用户昵称

		printf("微博创建时间：%s\n",next_weibo->create_time);
		printf("微博ID: %lld\n",next_weibo->id);
		printf("微博内容:%s\n",next_weibo->text);
		printf("微博作者：%s\n",next_weibo->username);


		p_str=strstr(p_str,"{\"created_at");	//指向下一条微博的信息

	}
	return weibo;
}

void free_weibo(struct weibo* weibo)
{
	struct weibo* temp;
	do{
		temp=weibo->next;
	//	printf("free:%s\n",weibo->id);
		free(weibo);
		weibo=temp;
	}while(weibo);
}
