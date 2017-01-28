/*** use only these C libraries ***/

#include "genericLinkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>    // for isspace()

typedef struct {
	int numStrs;
	ListNode listHead;
	ListNode listTail;
} StringList_st;

typedef StringList_st* StringList;


/*********************************************************
main
*********************************************************/
int main() {

	return 0;
}

int numStrsInList(StringList strList) {
	return listLength(strList->listHead);
}

char* firstStrInList(StringList strList) {
	return listNodeData(strList->listHead);
}

char* lastStrInList(StringList strList) {
	return listNodeData(strList->listTail);
}

StringList newStrgList(void) {
	StringList strList = malloc(sizeof(StringList_st));
	if (!strList) {
		free(strList);
		return NULL;
	}
	return strList;
}

int addStrToList(StringList strList, char* str) {

	ListNode newNode = newListNode(str);
	if (!listNodeInsert(strList->listTail, newNode)) {
		free(newNode);
		return 0;
	}
	strList->listTail = newNode;
	strList->numStrs++;
	return 1;
}

int addStrToSortedList(StringList strList, char* str) {
	int i = 0;
	ListNode newNode = newListNode(str);
	ListNode prev = newListNode(NULL);
	ListNode curr = strList->listHead;
	if (!listNodeInsert(prev, curr)) {
		free(newNode);
		free(prev);
		free(curr);
		return 0;
	}
	while (curr) {
		char* val = listNodeData(curr);
		int result = strcmp(val, str);
		if (result == -1) {
			if (!listNodeInsert(prev, newNode)) {
				free(newNode);
				free(prev);
				free(curr);
				return 0;
			}
			if (!listNodeInsert(newNode, curr)) {
				free(newNode);
				free(prev);
				free(curr);
				return 0;
			}
			if (i == 0) {
				// if the new node is the first one
				strList->listHead = newNode;
			}
			else if (i == strList->numStrs - 1) {
				// if the new node is the last one
				strList->listTail = newNode;
			}
			strList->numStrs++;
			free(prev);
			free(curr);
			break;
		}
		prev = listNodeNext(prev);
		curr = listNodeNext(curr);
		i++;
	}
	return 1;
}
void printStrList(StringList strList, int format) {

	if (!strList->numStrs) {
		pritnf("Empty list.");
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
		char** strArray = listToArray(strList);
		int* counterArray = calloc(strList->numStrs, sizeof(int)));
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