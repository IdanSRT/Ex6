#ifndef GEN_LINKED_LIST_H_
#define GEN_LINKED_LIST_H_
/*******************************************
*  genericlinkedList.h                     *
*  ~~~~~~~~~~~~~~~~~~~                     *
*  Header file for generic linked list     *
*  data structure                          *
*******************************************/

/************************************
*    TYPE DEFINITIONS               *
************************************/ 

typedef void* Data;
typedef struct ListNode_st * ListNode;

/************************************
*    FUNCTION DECLARATIONS          *
************************************/ 

/***********************************************************
  listNodeNext
  returns the next node in list
  param
  - listNode - list node
  return
  - pointer to next list node, or NULL if listNode==NULL
***********************************************************/
ListNode listNodeNext (ListNode listNode);

/***********************************************************
  listNodeData
  returns a pointer to the data object pointed to by list node
  param
  - listNode - list node
  return
  - pointer to the data object pointed to by list node, or NULL if listNode==NULL
***********************************************************/
Data listNodeData (ListNode listNode);

/***********************************************************
  listLength
  returns number of nodes in linked list starting from head
  param
  - head - list node where counting should start
  return
  - number of nodes downstream of head node (until next==NULL)
***********************************************************/
int listLength (ListNode head);

/***********************************************************
  listNodeFind
  finds node that holds given data value
  param
  - head - list node where searching should start
  return
  - list node downstream of head whose data is equal to given data,
    or NULL if no downstream node has data value
***********************************************************/
ListNode listNodeFind (ListNode head, Data val);

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
ListNode newListNode (Data val);

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
int listNodeInsert (ListNode listNode, ListNode singleNode);

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
int listNodeDisconnect (ListNode head, ListNode listNode);

/***********************************************************
  listNodeSplit
  splits list after given list node
  param
  - listNode - node in list, after which list is to be split
  return
  - list node that was after given node in list
    (head of new list), or NULL if input is NULL
***********************************************************/
ListNode listSplit (ListNode listNode);

/***********************************************************
  listToArray
  creates array of data elements according to data held by
  list nodes downstream of given head (allocates array)
  param
  - head - head of list
  return
  - pointer to newly allocated array of data elements
***********************************************************/
Data* listToArray (ListNode head);

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
ListNode arrayToList (Data* dataArray, int arrLength);

/***********************************************************
  freeList
  frees all memory allocated by list nodes downstream of
  given list node
  param
  - head - head of linked list
***********************************************************/
void freeList (ListNode head);

/***********************************************************
  freeListAndData
  frees all memory allocated by list nodes downstream of
  given list node, together with data objects (if not null)
  param
  - head - head of linked list
***********************************************************/
void freeListAndData (ListNode head);

#endif
