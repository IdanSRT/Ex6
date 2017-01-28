/*******************************************
*  stringList.h                            *
*  ~~~~~~~~~~~~~~~~~~~                     *
*  Implementation of stringList            *
*  data structure                          *
*******************************************/



/*** use only these C libraries ***/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>    // for isspace()
#include "genericLinkedList.h"


struct StringList_st {
	int numStrs;
	ListNode listHead;
	ListNode listTail;
};

typedef struct StringList_st* StringList;


int numStrsInList(StringList strList);
char* firstStrInList(StringList strList);
char* lastStrInList(StringList strList);
StringList newStrList(void);
int addStrToList(StringList strList, char* str);
int addStrToSortedList(StringList strList, char* str);
void printStrList(StringList strList, int format);
void freeStrList(StringList strList);


/************************************
*               MAIN                *
************************************/

int main() {
	/*** array of string pointers to add to lists ***/
	char* listOfStrings[] = { "Hello, ","Hello world", "I", "am", "very", "very", "fine", ", I", "am","." };

	int i, numStrs = sizeof(listOfStrings) / sizeof(listOfStrings[0]);
	StringList strList1, strList2;

	printf(" 1. Creating empty string lists strList1 and strList2\n");
	strList1 = newStrList();
	strList2 = newStrList();
	if (!strList1) {
		fprintf(stderr, "OOM strList1\n");
		return 1;
	}
	if (!strList2) {
		fprintf(stderr, "OOM strList2\n");
		freeStrList(strList1);
		return 1;
	}
	printf(" 2. Making sure that strList1 is empty\n");
	if (numStrsInList(strList1) == 0 && !firstStrInList(strList1) && !lastStrInList(strList2)) {
		printf("      okay\n");
	}
	else {
		printf("      strList1 is not truly empty. Please check!\n");
	}

	printf(" 3. Printing both string lists:\n");
	printf("     strList1: ");
	printStrList(strList1, 0);
	printf("     strList2: ");
	printStrList(strList2, 0);

	printf(" 4. Adding strings one by one to lists. Strings in strList1 are added to tail, and strings in strList2 are added sorted:\n");
	for (i = 0; i<numStrs; i++) {
		printf("     adding string %s\n", listOfStrings[i]);
		addStrToList(strList1, listOfStrings[i]);
		addStrToSortedList(strList2, listOfStrings[i]);
		printf("     strList1 has %d strings: first: %s |last: %s\n", numStrsInList(strList1), firstStrInList(strList1), lastStrInList(strList1));
		printf("     strList2 has %d strings: first: %s |last: %s\n", numStrsInList(strList2), firstStrInList(strList2), lastStrInList(strList2));
	}

	printf(" 5. Making sure that list does not point to source string, by modifying first source string to \"Something new\":\n");
	listOfStrings[0] = "Something new";
	printf("     first string in strList1 his still \"%s\" \n", firstStrInList(strList1));


	for (i = 0; i<4; i++) {
		printf("%2d. Printing strList1 using format=%d:\n", 6 + 2 * i, i);
		printStrList(strList1, i);
		printf("%2d. Printing strList2 using format=%d:\n", 7 + 2 * i, i);
		printStrList(strList2, i);
	}
	printf("%2d. Freeing both lists.\n", 6 + 2 * i);
	freeStrList(strList1);
	freeStrList(strList2);

	return 0;
}
/*** end of main ***/



int numStrsInList(StringList strList) {
	return strList->numStrs;
}

char* firstStrInList(StringList strList) {
	return listNodeData(strList->listHead);
}

char* lastStrInList(StringList strList) {
	return listNodeData(strList->listTail);
}


/**********************************************
* function newStrgList(void)
* ~~~~~~~~~~~~~~~~~~~~~~~~~
* - initializes a new empty string list
**********************************************/
StringList newStrList(void) {

	StringList str = malloc(sizeof(struct StringList_st));
	if (!str)
		return NULL;
	return NULL;
}



/**********************************************
* function addStrToList(StringList strList, char* str)
* ~~~~~~~~~~~~~~~~~~~~~~~~~
*
*
*
* return 1 if and 0 if
**********************************************/
int addStrToList(StringList strList, char* str) {

	ListNode newNode = newListNode(str);

	if (strList->numStrs == NULL) {
		/* if it is the first node in the list */
		strList->listHead = newNode;
		strList->numStrs = 0;		
	}
	else if (!listNodeInsert(strList->listTail, newNode)) {
		free(newNode);
		return 0;
	}
	strList->listTail = newNode;
	strList->numStrs++;
	return 1;
}

int addStrToSortedList(StringList strList, char* str) {

	ListNode curr = strList->listHead;
	ListNode newNode = newListNode(str);

	/* special case  */
	if (curr == NULL || strcmp(listNodeData(curr), str) >= 0) {

		listNodeInsert(newNode, curr);
		strList->listHead = newNode;
	}
	else {

		/* locate the node before the point of insertion */
		while (listNodeNext(curr) != NULL &&
			strcmp(listNodeData(listNodeNext(curr)), str) == -1) {

			curr = listNodeNext(curr);
		}
		
		ListNode tmp = newNode;
		ListNode currNext= listNodeNext(curr);
		ListNode newNodeNext = listNodeNext(newNode);
		
		newNodeNext = currNext;
		currNext = tmp;

	}
	return 1;
}


void printStrList(StringList strList, int format) {

	if (strList->numStrs == NULL) {
		printf("Empty list.");
		return;
	}

	if (!format) {
		ListNode curr = strList->listHead;
		while (curr) {
			char* str = listNodeData(curr);
			printf(str);
			printf("\n");
			curr = listNodeNext(curr);
		}
		free(curr);
	}
	else if (format == 1 || format == 2) {
		char** strArray = listToArray(strList->listHead);
		int* counterArray = (int*)calloc(strList->numStrs, sizeof(int));
		int i, j;
		for (i = 0; i < strList->numStrs; i++) {
			for (j = 0; strList->numStrs; j++) {
				if (i != j && !strcmp(strArray[i], strArray[j])) {
					if (format == 2) {
						counterArray[j]++;
					}
					strArray[j] = NULL;
				}
			}
		}

		for (i = 0; i < strList->numStrs; i++) {
			if (strArray[i] != NULL) {
				if (format == 2) {
					printf("%d %s\n", counterArray[i], strArray);
				}
				else {
					printf("%s\n", strArray);
				}
			}
		}
		free(counterArray);
		free(strArray);
	}
}

void freeStrList(StringList strList) {
	ListNode curr = strList->listHead;
	ListNode copyCurr = strList->listHead;

	while (curr) {
		curr = listNodeNext(curr);
		free(copyCurr);
		copyCurr = curr;
	}
	free(curr);
	free(copyCurr);
}