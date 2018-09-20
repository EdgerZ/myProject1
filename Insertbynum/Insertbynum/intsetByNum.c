#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <time.h>

int num = 0;

typedef struct PERSON
{
	int ID;
	int value;

	struct PERSON * pCur;
}psn;
//创建链表读取数据直到读入-1；
 psn *createLinkList()
{
	 psn * p1 = NULL;
	 //创建头结点;
	psn *HEAD=malloc(sizeof(psn));
	HEAD->pCur= malloc(sizeof(psn));	//头结点的指向为第一个节点的位置;
	p1 = HEAD->pCur;
	 while (1)
	 {
		 printf("print New value(terminate on -1) Current ID:%d\n",num+1);
		 
		 scanf("%d", &(p1->value));
		 if (p1->value != -1)								//输入的值不为-1时创建新节点;
		 {
			 num++;
			 p1->ID = num;
			 p1->pCur = malloc(sizeof(psn));
			 printf("Success!\n");
			 p1 = p1->pCur;
		 }
		 else {
			 printf("Recognized -1 stop creating! Total LinkPoint:%d\n",num);

			 p1->pCur = NULL;						//此时多创建了一个节点;
			 break;
		 }
	 }
	 return HEAD;
}

 void myPrintLinkList(psn * HEAD)
 {
	 psn *p1=HEAD->pCur;
	 for (int i = 0; i < num; i++)
	 {
		 printf("ID: %d  Value: %d\n", p1->ID, p1->value);
		 p1 = p1->pCur;
	 }
 }

 void myInsertData(psn * HEAD,int pzs,int value)
 {
	 psn *p1 = NULL;
	 psn *p2 = NULL;
	 if (pzs == 0)			//在开头插入新值;
	 {
		p1 = malloc(sizeof(psn));
		p1->pCur = HEAD->pCur;
		p1->value = value;
		p1->ID = 1;
		HEAD->pCur = p1;
		while (p1->pCur != NULL)
		{
			p1 = p1->pCur;
			p1->ID++;
		}
		p1->ID++;
		num++;
		return;
	 }
	 else if (pzs+1 >= num)	//在最后插入新值;
	 {
		 p1 = HEAD->pCur;
		 while (p1->pCur != NULL)
			 p1 = p1->pCur;
//		 p1->pCur = malloc(sizeof(psn));
		 p1->pCur = NULL;
		 p1->ID = num + 1;
		 p1->value = value;
		 num++;
		 return;
	 }
	 p1 = HEAD->pCur;
	 for (int i = 0; i < pzs-1; i++)
		 p1 = p1->pCur;
	 p2 = malloc(sizeof(psn));
	 p2->pCur = p1->pCur;
	 p1->pCur = p2;
	 p2->ID = (p2->pCur)->ID;
	 p2->value = value;
	 while (p2->pCur != NULL)
	 {
		 p2 = p2->pCur;
		 p2->ID++;
	 }
	 p2->ID++;
	 num++;
	 return;
 }

 //删除链表
 void myDeleteData(psn *HEAD, int pzs)
 {
	 psn *p1 = HEAD->pCur;
	 psn *p2 = NULL;
	 if (pzs == 0)
	 {
		 HEAD->pCur = p1->pCur;
		 free(p1);
		 num--;
		 return;
	 }
	 else
	 {
		 for (int i = 0; i < pzs-1; i++)
		 {
			 p1 = p1->pCur;
		 }
		 p2 = p1->pCur;
		 if (p2->pCur == NULL)
			 p1->pCur == NULL;
		 else p1->pCur = p2->pCur;
		 
		 free(p2);
		 num--;
		 return;
	 }
 }
 
 //释放空间
 void myFreeSpace(psn * HEAD)
 {
	 psn *p1 = HEAD->pCur;
	 psn *p2=p1->pCur ;
	 while (p1->pCur != NULL)
	 {
		 p2 = p1;
		 p1 = p1->pCur;
		 free(p2);
	 }
	 free(p1);
	 free(HEAD);
	 HEAD = NULL;
 }

int main()
{
	int pzs = 0;
	int value = 0;
	//创建链表
	psn * HEAD=createLinkList();

	//打印链表所有节点;
	myPrintLinkList(HEAD);
	
	//按位置（ID）来插入数据;
	printf("Input Insert Position(from 1 to %d):\n", num);
	scanf("%d", &pzs);
	printf("Input Insert Value:\n");
	scanf("%d", &value);
	myInsertData(HEAD,pzs-1,value);

	myPrintLinkList(HEAD);

	//按位置（ID）来删除结点；
	printf("Input Delete Position(from 1 to %d):\n", num);
	scanf("%d", &pzs);
	myDeleteData(HEAD, pzs - 1);

	myPrintLinkList(HEAD);

	//释放空间；
	myFreeSpace(HEAD);
	HEAD = NULL;

	system("pause");
	return EXIT_SUCCESS;
}