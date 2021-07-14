#include "link.h"






int main()
{
	srand((unsigned int) time(NULL));
	
	Link* head = createHead();
	if(!head)
	{
		return -1;
	}
	
	int i = 0;
	for(i = 0; i < 10; i++)
	{
		addNode(head, rand() % 100);
	}
	

	printLink(head);
	putchar('\n');
	
	sortLink(head);
	
	printLink(head);
	putchar('\n');
	
	return 0;
}
