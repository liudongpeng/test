#ifndef _LINK_H_
#define _LINK_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct link
{
	int data;
	struct link* next;
} Link;


Link* createHead();

void addNode(Link* head, int data);

void printLink(Link* haed);

void sortLink(Link* head);




#endif //_LINK_H_
