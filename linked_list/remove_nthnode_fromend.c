/*
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 * Removes the nth from linked list from the End.
 * Logic is goto end of string in recursive function
 * call, from end check for the nth node and delete the 
 * same. While returning just assign node->next with returned
 * point from function call, which will return the same node
 * or node->next incase that nodeis to be deleted
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

 struct ListNode {
      int val;
      struct ListNode *next;
 };
 
struct ListNode* remove_node_fromend(struct ListNode* node, int *n) {
    struct ListNode* nnode;
    if (node->next == NULL) {
        (*n)--;
        if (*n == 0) {
            free(node);
            return NULL;
        }
        return node;
    } 
    
    nnode = remove_node_fromend(node->next,n);
    
    if (*n == 0) {
        node->next = nnode;
        return node;
    } else {
        (*n)--;
        if(*n == 0) {
            free(node);
            return nnode;
        } else {
            return node;
        }
    }
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if (n < 1) {
        return head;
    }
    head = remove_node_fromend(head,&n);
    return head;
}

struct ListNode* h_node = NULL,*t_node = NULL;

struct ListNode* create_node (int val) {
	struct ListNode* node = NULL;
	
	node = (struct ListNode*) malloc(sizeof(struct ListNode));
	
	if (node == NULL) {
		return NULL;
	}
	
	if (t_node) {
		t_node->next = node;
		t_node = node;
	} else {
		t_node = node;
	}
	
	if (!h_node) {
		h_node = node;
		printf("head:%x\n",node);
	}
	
	node->val = val;
	node->next = NULL;
	printf("n:%x:%d\n",node,node->val);
	return node;
}

int main (int argc, char **argv)
{
	struct ListNode* head = NULL;
	int val = 0;
	int cnt = 0;
	int n,i;
	
	if (argc < 4) {
		printf("Usage:Input number of nodes, nth node to delete and values of Nodes\n");
		return 1;
	}
	
	cnt = atoi(argv[1]);
	n = atoi(argv[2]);
	i = 3;
	printf("Cnt:%d n:%d\n",cnt,n);
	while(cnt) {
		if (argv[i] == NULL) {
			printf("Usage:Input number of nodes, nth node to delete and values of Nodes\n");
			return -1;
			//break;
		}
		val = atoi(argv[i]);
		
		i++;
		create_node(val);
		cnt--;
	}
	
	head = removeNthFromEnd(h_node,n);
	while(head) {
		printf("%d ",head->val);
		head = head->next;
	}
	return 0;
}