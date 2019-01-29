#ifndef LIST_H   
#define LIST_H

//node struct
typedef struct nodeStruct
{
	int item;
	struct nodeStruct* next;
} nodeStruct_t;

/* FUNCTION PROTOTYPES */
nodeStruct_t* List_createNode(int item);
void List_insertHead(nodeStruct_t** headRef, nodeStruct_t* node);
void List_insertTail(nodeStruct_t** headRef, nodeStruct_t* node);
int List_countNodes(nodeStruct_t* head);
nodeStruct_t* List_findNode(nodeStruct_t* head, int item);
void List_deleteNode(nodeStruct_t** headRef, nodeStruct_t* node);
void List_sort(nodeStruct_t** headRef);
void List_print();

#endif
