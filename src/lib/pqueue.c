#include "pqueue.h"

struct pqueue* pqueue_init(comparator_func* func)
{
	struct pqueue* queue = malloc(sizeof(struct pqueue));
	queue->list = NULL;
	queue->cmp = func;

	return queue;
}

void pqueue_add(struct pqueue* queue,void* elem)
{
	struct node* new_node = malloc(sizeof(struct node));
	new_node->elem = elem;
	new_node->next = NULL;
	new_node->prev = NULL;

	if(queue->list == NULL)
	{
		queue->list = new_node;
		return;
	}

	struct node* curr = queue->list;
	while(curr->next != NULL && queue->cmp(curr->elem,elem) > 0) curr = curr->next;

	if(queue->cmp(curr->elem,elem) < 0)
	{
		new_node->prev = curr;
		curr->next = new_node;
	}
	else
	{
		new_node->next = curr;
		new_node->prev = curr->prev;
		if(curr->prev != NULL) curr->prev->next = new_node;
		else queue->list = new_node;
		curr->prev = new_node;
	}
}

void* pqueue_remove(struct pqueue* queue)
{
	if (queue->list == NULL) {
	  return;
	}	
	void* elem = queue->list->elem;
	struct node* to_remove = queue->list;
	if(queue->list->next != NULL) queue->list->next->prev = NULL;
	queue->list = queue->list->next;
	free(to_remove);
	return elem;
}

void* pqueue_peek(struct pqueue* queue)
{
	if(queue->list == NULL) {
		return NULL;
	} else {
		return queue->list->elem;
	}
}
/*
#include <stdio.h>

bool address_compare (void* a, void* b) {
if (*(int*)a > *(int*)b) {
return true;
} else {
return false;
}
}
int main() {
struct pqueue* queue = malloc(sizeof(struct pqueue));
queue = pqueue_init(&address_compare);
int a = 6;
int b = 4;
int c = 5;
int d = 10;
int e = 5;
int f = 4;
int g = 8;
pqueue_add(queue,&a);
pqueue_add(queue,&b);
pqueue_add(queue,&c);
pqueue_add(queue,&d);
pqueue_add(queue,&e);
pqueue_add(queue,&f);
pqueue_add(queue,&g);
printf("%d\n", *(int*)pqueue_peek(queue));
printf("%d\n", *(int*)pqueue_remove(queue));
printf("%d\n", *(int*)pqueue_peek(queue)); 
return 0; 
}*/
