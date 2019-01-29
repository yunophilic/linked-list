#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Allocate memory for a node of type nodeStruct_t and initialize
 * it with the value item. Return a pointer to the new node.
 */
nodeStruct_t* List_createNode(int item)
{
	nodeStruct_t* nodePtr = malloc(sizeof(nodeStruct_t));
	if(nodePtr!=NULL)
	{
		nodePtr->item = item;
		nodePtr->next = NULL;
	}
	return nodePtr;
}

/*
 * Insert node at the head of the list.
 */
void List_insertHead(nodeStruct_t** headRef, nodeStruct_t* node)
{
	if( (*headRef)==NULL ) //empty list
	{
		(*headRef) = node;
		return;
	}
	node->next = (*headRef);
	(*headRef) = node;
}

/*
 * Insert node after the tail of the list.
 */
void List_insertTail(nodeStruct_t** headRef, nodeStruct_t* node)
{
	if( (*headRef)==NULL ) //empty list
	{
		(*headRef) = node;
		return;
	}
	nodeStruct_t* tmpPtr = (*headRef);
	while(tmpPtr->next!=NULL) //iterate thru stop until last node
		tmpPtr = tmpPtr->next;
	tmpPtr->next = node;
}

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes(nodeStruct_t *head)
{
	int counter = 0;
	nodeStruct_t* tmpPtr = head;
	while(tmpPtr!=NULL) //iterate all the way
	{
		counter++;
		tmpPtr = tmpPtr->next;
	}
	return counter;
}

/*
 * Return the first node holding the value item, return NULL if none found
 */
nodeStruct_t* List_findNode(nodeStruct_t* head, int item)
{
	nodeStruct_t* retPtr = head;
	while(retPtr!=NULL && retPtr->item!=item) //iterate till item found or all the way if not found
		retPtr = retPtr->next;
	return retPtr;
}

#include <stdio.h>

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node 
 * in the list. For example, the client code may have found it by calling 
 * List_findNode(). If the list contains only node, the head of the list 
 * should be set to NULL.
 */
void List_deleteNode(nodeStruct_t** headRef, nodeStruct_t* node)
{
	nodeStruct_t* tmpPtr = (*headRef);
	if((*headRef)==node) //if head is the node to be deleted
	{
		(*headRef) = (*headRef)->next;
		free(tmpPtr);
		return;
	}
	while(tmpPtr->next!=NULL) //iterate and delete
	{
		if(tmpPtr->next==node)
		{
			tmpPtr->next = tmpPtr->next->next;
			free(node);
			return;
		}
		tmpPtr = tmpPtr->next;
	}
}

//=======================MERGE SORT CODE=======================

//"merge" sorted subarray indexed start to mid and sorted subarray indexed mid+1 to end into a sorted array
void merge(int* arr, int start, int mid, int end) 
{
	int l = start;
	int r = mid+1;
	int len = end-start+1;
	
	int* tmp = malloc(sizeof(int)*len); //equivalent to "int* temp = new int[len];" in C++

	int i = 0;
	while(l<mid+1 && r<=end)
		tmp[i++] = arr[l]<arr[r] ? arr[l++]:arr[r++];

	// copy remaining elements
	if(l < mid+1)
		for(int j=i; j<len; j++)
			tmp[j] = arr[l++];
	else
		for(int j=i; j<len; j++)
			tmp[j] = arr[r++];

	// copy tmp back into arr
	for(int n=start,k=0; k<len; k++,n++)
		arr[n] = tmp[k];

	free(tmp); // before exiting the function, free allocated memory (equivalent to "delete[] temp;" in C++)
}

//sort elements at index start to end
void recursiveMergeSort(int* arr, int start, int end)
{
	if(start == end-1) // size 2 array, base case. What about size 1 array?
	{
		// swap the two elements if they are out of order
		if(arr[start] > arr[end])
		{
			int tmp = arr[start];
			arr[start] = arr[end];
			arr[end] = tmp;
		}
	}
	else if(start < end-1) // size > 2 array
	{
		int mid = (start+end)/2; // "cut" the array in half
		recursiveMergeSort(arr, start, mid); // sort the first half
		recursiveMergeSort(arr, mid+1, end); // sort the 2nd half
		merge(arr, start, mid, end); // merge them back together
	}
}

//sort array arr using merge sort
void mergeSort(int* arr, const int size)
{
	recursiveMergeSort(arr, 0, size-1);
}

//=============================================================

/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort(nodeStruct_t** headRef)
{
	//sort by merge sort
	int i=0, listLen=List_countNodes(*headRef), tmpArr[listLen];
	if(listLen==1)
		return;
	for(nodeStruct_t* tmp=(*headRef); tmp!=NULL; tmp=tmp->next)
		tmpArr[i++] = tmp->item;
	mergeSort(tmpArr, listLen);
	int j=0;
	for(nodeStruct_t* tmp=(*headRef); tmp!=NULL; tmp=tmp->next)
		tmp->item = tmpArr[j++];
	/*printf("List after sort:");
	List_print(*headRef);*/
}

//print all elements in the list (useful for debugging)
void List_print(nodeStruct_t* head)
{
	nodeStruct_t* tmpPtr = head;
	printf("{ ");
	while(tmpPtr!=NULL) //iterate till item found or all the way if not found
	{
		printf("%d", tmpPtr->item);
		if(tmpPtr->next!=NULL)
			printf(", ");
		tmpPtr = tmpPtr->next;
	}
	printf(" }\n");
}