

#include<stdio.h>

void menu()
{//5显示6退出
	system("clear");
	printf("\n\n");
	printf("\t\t******************                        ******************\n"); 
	printf("\t\t******************** 通讯录管理系统v4.0 ********************\n");
	printf("\t\t**                     1.新建联系人                       **\n");
	printf("\t\t**                     2.删除联系人                       **\n");
	printf("\t\t**                     3.修改联系人                       **\n");
	printf("\t\t**                     4.查询联系人                       **\n");
	printf("\t\t**                     5.通讯录显示                       **\n");
	printf("\t\t**                     6.退出通讯录                       **\n");
	printf("\t\t************************************************************\n");
	printf("\t\t************************************************************\n");
	printf("\t\t                请输入你要执行的操作代码：\n");
}
void main_handler(int fd)
{
	char choice[32] = {0};
	while(1)
	{
		menu();
		scanf("%s", choice);
		switch(choice[0])
		{
			case '1':
				add_info(fd);
				break;
			case '2':
				delete_info(fd);
				break;
			case '3':
				update_info(fd);
				break;
			case '4':
				search_info(fd);
				break;
			case '5':
				show_info(fd);
				break;
			case '6':
				exit_client(fd);
				break;
			default:
				printf("iput error...\n");
		}
	}	
}
