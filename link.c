#include "link.h"

Link* createHead()
{
	Link* head = malloc(sizeof(Link));
	if(!head)
	{
		return NULL;
	}
	memset(head, 0, sizeof(Link));
	return head;
}

void addNode(Link* head, int data)
{
	if(!head)
	{
		return;
	}
	Link* new = malloc(sizeof(Link));
	if(!new)
	{
		return;
	}
	memset(new, 0, sizeof(Link));
	new->data = data;
	new->next = head->next;
	head->next = new;
}

void printLink(Link* head)
{
	if(!head)
	{
		return;
	}
	Link* tmp = head;
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
		printf("%d ", tmp->data);
	}
}



void sortLink(Link* head)
{
	Link* p = NULL ;
	Link* a = NULL ;
	Link* b = NULL ;
	Link* t = NULL ;
	int flag = 1;
	while(flag)
	{
		p = head;
		a = head->next;
		flag = 0;
		while(a != NULL)
		{
			b = a->next;
			if(b == NULL)
			{
				break;
			}
			else if(a->data > b->data)
			{
				t = b->next;
				a->next = t;
				b->next = a;
				p->next = b;
				p = b;
				a = p->next;
				b = a->next;
				flag = 1;
			}
			else
			{
				p = a;
				a = p->next;
			}
		}
	}
}



