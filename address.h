

#ifndef ADDRESS_H
#define ADDRESS_H

#define ADDINFO         1000
#define DELINFO         1001
#define UPDATEINFO      1002
#define SEARCHINFO      1003
#define SHOWINFO        1004
#define EXIT            1005

struct ChatInfo
{
	int cmd;
	char name[32];
	char tel[32];
	int result;	//用于保存服务器返回结果
};
typedef struct ChatInfo Chat;

#endif
