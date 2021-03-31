
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define  RED  "\033[31m"
#define YELLOW "\033[33m"
#define  NONE  "\033[0m"



typedef struct carroom
{
	int rongliang;
	int shengyu;

	float rate;	
	
} P;

typedef struct car
{
	char name[32];
	char carid[16];
	char telnum[16];
	
	float time;
	float money;
	
	struct car* next;
} CAR;



void menu();
P* initCarroom();
CAR* createCarHead();
int shengyu(CAR* head, P* room);
long addCar(CAR* head, P* room);
int xianyou(P* room);
void jiesuan(CAR* head, P* room, long time);
CAR* searchCar(CAR* head);
void printCar(CAR* find, P* room, long times);

void readFile();
void writeFile();




void menu()
{
	printf("*********     \033[32m欢迎使用车库管理系统"NONE"   ************\n");
	printf("-------------------------------------------------\n");
	printf("*********      1.  车位余量          ************\n");
	printf("*********      2.  现有车辆数        ************\n");
	printf("*********      3.  客户登记          ************\n");
	printf("*********      4.  客户信息查询      ************\n");
	printf("*********      5.  客户金额结算      ************\n");
	printf("*********      0.  退出管理系统      ************\n");
	printf("-------------------------------------------------\n");
	
}



P* initCarroom()
{
	P* room  = (P*)malloc(sizeof(P));
	if(room == NULL)
	{
		return NULL;
	}
	memset(room, 0, sizeof(P));
	printf(""YELLOW"设置车库容量："NONE"");
	scanf("%d", &room->rongliang);
	room->shengyu = room->rongliang;

	printf(""YELLOW"设置车库费率："NONE"");
	scanf("%f", &room->rate);
	
	return room;
}



CAR* createCarHead()
{
	CAR* head = (CAR*)malloc(sizeof(CAR));
	if(head == NULL)
	{
		return NULL;
	}
	memset(head, 0, sizeof(CAR));
	
	return head;
}



int shengyu(CAR* head, P* room)
{
	if(head == NULL)
	{
		puts("车链表不存在！");
		return -1;
	}
	if(room == NULL)
	{
		puts("车库结构体异常！");
		return -2;
	}
	
	CAR* ptr = head;
	int count = 0;
	
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
		count++;
	}
	room->shengyu = room->rongliang - count;
	
	return room->shengyu;
}



int xianyou(P* room)
{
	if(room == NULL)
	{
		puts("车库结构体异常！");
		return -1;
	}
	
	return room->rongliang - room->shengyu;
}



long addCar(CAR* head, P* room)
{
	if(head == NULL)
	{
		puts("车链表不存在！");
		return -3;
	}
	if(room->shengyu == 0)
	{
		puts(""RED"车库已满！"NONE"");
		return -2;
	}
	CAR* new = (CAR*)malloc(sizeof(CAR));
	if(new == NULL)
	{
		puts("添加新节点失败！");
		return -1;
	}
	memset(new, 0, sizeof(CAR));
	
	printf(""YELLOW"请输入客户姓名："NONE"");
	scanf("%s", new->name);
	
	printf(""YELLOW"请输入客户电话号码："NONE"");
	scanf("%s", new->telnum);
	
	printf(""YELLOW"请输入客户车牌号："NONE"");
	scanf("%s", new->carid);
	
	long timenow = 0;
	timenow = time(NULL);
	
	
	new->next = head->next;
	head->next = new;

	room->shengyu--;
	
	return timenow;
}



CAR* searchCar(CAR* head)
{
	if(head == NULL)
	{
		puts("车链表不存在！");
		return NULL;
	}
	CAR* find = head;
	char name[32];
	printf(""YELLOW"请输入要查询的客户姓名："NONE"");
	scanf("%s", name);
	while(find->next != NULL)
	{
		find = find->next;
		if(strcmp(find->name, name) == 0)
		{
			return find;
		}
	}
	return NULL;
	
}



void printCar(CAR* head,P* room, long timeago)
{
	if(head == NULL)
	{
		puts("车链表不存在！");
		return;
	}
	if(room == NULL)
	{
		puts("车库信息异常！");
		return;
	}
	CAR* find = searchCar(head);
	if(find == NULL)
	{
		puts(""RED"查无此人！"NONE"");
		return;
	}
	long timenow = 0;
	timenow = time(NULL);
	
	find->money = (timenow - timeago) * room->rate;
	find->time = timenow - timeago;
	
	printf("姓名：%s  电话号码：%s  车牌号：%s  停车时间：%.1f  应缴费金额：%.1f\n", find->name, find->telnum, find->carid, find->time * 1.0, find->money);

}



void jiesuan(CAR* head, P* room, long timeago)
{
	if(head == NULL)
	{
		puts("车链表不存在！");
		return;
	}
	if(room == NULL)
	{
		puts("车库结构体异常！");
		return;
	}	
	
	CAR* ptr = searchCar(head);
	if(ptr == NULL)
	{
		puts(""RED"查无此人！"NONE"");
		return;
	}
	
	long timenow = 0;
	long timenum = 0;
	timenow = time(NULL);
	timenum = timenow - timeago;
	
	ptr->money = timenum * room->rate;
	ptr->time = timenum;
	
	//printf("请输入顾客车辆停放时间：");
	//scanf("%f", &ptr->time);
	printf("%s先生的车辆停放了%.1f小时，需缴费%.1f元\n", ptr->name, ptr->time * 1.0, ptr->money);
	
	float money = 0;

	printf(""YELLOW"顾客缴费金额： "NONE"");
	scanf("%f", &money);
	printf("\033[1A\033[20C "YELLOW"元"NONE"\n");

	printf("收取%.1f元，找零%.1f元，感谢您的光临！\n", money, money - ptr->money);
	
	CAR* flag = head;
	while(flag->next != ptr)
	{
		flag = flag->next;
		if(flag->next == ptr)
		{
			break;
		}
	}
	flag->next = ptr->next;
	ptr->next = NULL;
	free(ptr);

}



int main()
{
	
	int choose = 0;
	int num = 0;
	long times = 0;
	
	P* room = initCarroom();
	if(room == NULL)
	{
		return -1;
	}
	CAR* head = createCarHead();
	if(head == NULL)
	{
		return -2;
	}
	
	
	
	do
	{
	
	    putchar('\n');
	    menu();
    	printf(""YELLOW"请选择操作："NONE"");
		scanf("%d", &choose);
		
		switch(choose)
		{
			case 1:
				num = shengyu(head, room);
				printf("车位余量：%d\n\n", num);
				break;
			
			case 2:
			    num = xianyou(room);
	            printf("现有车辆数：%d\n\n", num);
			    break;
			
			case 3:
			    times = addCar(head, room);
			    break;
			
			case 4:
			    printCar(head, room, times);
			    break;
			
			case 5:
			    jiesuan(head, room, times);
			    break;
			
			case 0:
			printf(""RED"退出管理系统！"NONE"\n");
			exit(0);
			
		}
		
	} while(choose);


	return 0;
}