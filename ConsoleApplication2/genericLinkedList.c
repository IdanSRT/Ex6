/*******************************************
*  genericlinkedList.c                     *
*  ~~~~~~~~~~~~~~~~~~~                     *
*  Implementation of generic linked list   *
*  data structure                          *
*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include "genericLinkedList.h"

/************************************
*    TYPE DEFINITIONS               *
************************************/ 

struct ListNode_st {
   Data data;
   ListNode next;
};

/************************************
*    FUNCTION DEFINITIONS           *
************************************/ 



/***********************************************************
  listNodeNext
  returns the next node in list
  param
  - listNode - list node
  return
  - pointer to next list node, or NULL if listNode==NULL
***********************************************************/
ListNode listNodeNext (ListNode listNode) {
   if(!listNode) return NULL;
   return listNode->next;
}

/***********************************************************
  listNodeData
  returns a pointer to the data object pointed to by list node
  param
  - listNode - list node
  return
  - pointer to the data object pointed to by list node, or NULL if listNode==NULL
***********************************************************/
Data listNodeData (ListNode listNode) {
   if(!listNode) return NULL;
   return listNode->data;
}

/***********************************************************
  listLength
  returns number of nodes in linked list starting from head
  param
  - head - list node where counting should start
  return
  - number of nodes downstream of head node (until next==NULL)
***********************************************************/
int listLength (ListNode head) {
   int count=0;
   /*** scan list until end (next==NULL) ***/
   while(head) {
      head = head->next;
      count++;
   }
   return count;
}

/***********************************************************
  listNodeFind
  finds node that holds given data value
  param
  - head - list node where searching should start
  return
  - list node downstream of head whose data is equal to given data,
    or NULL if no downstream node has data value
***********************************************************/
ListNode listNodeFind (ListNode head, Data val) {
   while (head) {
      if (head->data == val)
         return head;
      head = head->next;
   }
   /*** reach here only if val was not found ***/
   return NULL;
}

/***********************************************************
  newListNode
  creates new list node sith given data (allocation of node struct)
  param
  - val - data to initialize node with
  return
  - newly allocated list node, or NULL if allocation is not
	successful.
	Newly created node is a list of length 1 (next==NULL)
***********************************************************/
ListNode newListNode (Data val) {
   ListNode newElement = malloc (sizeof (struct ListNode_st));


   /*** set structure members ***/
   if (newElement) {
      newElement->data = val;
      newElement->next = NULL;
   }

   /*** return NULL if allocation failed ***/
   return newElement;
}

/***********************************************************
  listNodeInsert
  inserts single node into list in given place
  param
  - listNode   - node in list, after which insertion takes place
  - singleNode - node (list of length 1) to insert after listNode
  return
  - 1 if insertsion is successful
	0 if one of the given nodes is NULL
	  or if singleNode has nodes donwstream of it.
***********************************************************/
int listNodeInsert (ListNode listNode, ListNode singleNode) {
   if (!listNode || !singleNode || singleNode->next)
      return 0;

   singleNode->next  = listNode->next;
   listNode->next = singleNode;

   return 1;
}

/***********************************************************
  listNodeDisconnect
  removes node from list downstream of given head
  param
  - head       - head node of given list 
  - listNode   - node downstream of head to be removed from list
  return
  - 1 if removal is successful
	0 if one of the given nodes is NULL
      or if listNode is not downstream of head
***********************************************************/
int listNodeDisconnect (ListNode head, ListNode listNode) {
   ListNode curr = head, prev = NULL;

   /*** scan list, keeping pointer to previous node ***/   
   while (curr != NULL && curr != listNode) {
      prev = curr;
      curr  = curr->next;
   }

   /*** here is where we check input ***/
   /*** why do we check prev here?   ***/
   if (!curr || !prev) return 0;

   /*** disconnect ***/
   prev->next = curr->next;
   curr->next = NULL;

   return 1;
}

/***********************************************************
  listNodeSplit
  splits list after given list node
  param
  - listNode - node in list, after which list is to be split
  return
  - list node that was after given node in list
    (head of new list), or NULL if input is NULL
***********************************************************/
ListNode listSplit (ListNode listNode) {
   ListNode nextNode;

   if(!listNode) return NULL;
   nextNode = listNode->next;
   listNode->next = NULL;
   return nextNode;
}

/***********************************************************
  listToArray
  creates array of data elements according to data held by
  list nodes downstream of given head (allocates array)
  param
  - head - head of list
  return
  - pointer to newly allocated array of data elements
***********************************************************/
Data* listToArray (ListNode head) {
   int i, listLen;
   Data* dataArray;
   
   /*** if list is empty, return NULL ***/
   if (!head) return NULL;

   /*** allocate array ***/
   listLen= listLength(head);
   dataArray = malloc (listLen * sizeof (Data));
   if (!dataArray) return NULL;

   for (i = 0; i < listLen; i++) {
      dataArray[i] = head->data;
      head = head->next;
   }
   return dataArray;
}

/***********************************************************
  arrayToList
  creates a linked list with data elements taken from array
  (allocates list nodes)
  param
  - dataArray - array of data elements
  - arrLength - length of data array
  return
  - head of newly allocated list
	NULL if data array is empty, or if allocation failed
***********************************************************/
ListNode arrayToList (Data* dataArray, int arrLength) {
   ListNode head, listNode;
   int i;
   /*** empty array --> empty list (NULL) ***/
   if (!dataArray || arrLength <= 0) return NULL;

   /*** create first node ***/
   head = listNode = newListNode (dataArray[0]);
   if(!listNode) return NULL;
   /*** iteratively create and connect additional nodes ***/
   for (i = 1; i < arrLength; i++) {
      listNode->next = newListNode (dataArray[i]);
      if(!listNode->next) {
         freeList (head);    // to be implemented...
         return NULL;     
      }
      listNode = listNode->next;
   }
   return head;
}

/***********************************************************
  freeList
  frees all memory allocated by list nodes downstream of
  given list node
  param
  - head - head of linked list
***********************************************************/
void freeList (ListNode head) {
   ListNode curr = head, prev = NULL;

   while (curr) {
      prev = curr;
      curr = curr->next;
     free(prev);
   }
}

/***********************************************************
  freeListAndData
  frees all memory allocated by list nodes downstream of
  given list node, together with data objects (if not null)
  param
  - head - head of linked list
***********************************************************/
void freeListAndData (ListNode head) {
   ListNode curr = head, prev = NULL;

   while (curr) {
      prev = curr;
      curr = curr->next;
	  if(prev->data) free (prev->data);
      free(prev);
   }
}

