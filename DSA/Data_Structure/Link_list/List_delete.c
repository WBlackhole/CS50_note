#include <stdio.h>
#include <stdlib.h>

#define num 5
#define insert_data 3

int main(void)
{
	int List_data[num];
	typedef struct node
	{
	    int data;
	    struct node *next;
	}
	node;
	
	// input data
	for (int i = 0; i < num; i++)
	{
	    printf("Please input List data of the %d position: ", i);
	    scanf("%d", &List_data[i]);
	}
	
	node *head = malloc(sizeof(node));
	if (head == NULL)
	    return 1;
    
    node *end = head;    
	for (int i = 0; i < num; i++)
	{
	    node *p = malloc(sizeof(node));
	    if (p == NULL)
	        return 1;
	    
	    end->next = p;
        p->data = List_data[i];
	    end = p;
	}
    
    printf("Origin List:\n");
    for (node *p = head->next; p != NULL; p = p->next)
        printf("%d\n", p->data);
    
    int position;
    printf("Select delete position: ");
    scanf("%d", &position);
    
    node *p = head;
    for (int i = 0; i < position - 1 && p != NULL; i++)
        p = p->next;

    if (p == NULL)
        return 1;
   
    node *temp = p->next; 
    p->next = p->next->next;
    free(temp);

    printf("After delete:\n");
    for (node *p = head->next; p != NULL; p = p->next)
        printf("%d\n", p->data);

    return 0;
}
