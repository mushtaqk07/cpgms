/*
 * https://leetcode.com/problems/reverse-nodes-in-k-group/submissions/
 * Reverse the Nodes in Group of K, last groups of nodes which are not
 * multiple of K, must remain same.
 * Given  1 2 3 4 5  K=2
 *
 * Output 2 1 4 3 5 
 * Logic is reverse nodes in Group of K.
 * If Last group is not multiple of K, will have NULL reached before k-nodes
 * in group. This condition can be used to check if last group is not
 * multiple of k.
 * If Group is Multiple of K, return node to caller, returned node->next
 * should be assigned with current node. This way Nodes will be reversed.
 * And if Group is not multiple NULL will returned to each call in recursive
 * call stack, and as NULL is returned nodes will not be reversed.
 *
 * To track, Next head in the list address of head-pointer can be passed and 
 * when k == n, head-pointer will be assigned with cur_node->next.refer to line-47
 
 * And to link between groups keep last pointer of reversed group Node.
 * And link to next group Kth-node (first-node in next reverse list).
 *
 * Note: Last node of reverse group next pointer must be updated to NULL,
 * pgm this has been solved by assigning next of last node of reverse group
 * to NULL in loop. refer to line 86.
 *  
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
 

struct ListNode* reverse_knodes(struct ListNode* cur_node,struct ListNode** head,struct ListNode**  k_node, int k, int n) {
    struct ListNode *nnode = NULL;
	
    if (cur_node == NULL) {
        //printf("Last nodes not multiple of k\n");
        return NULL;
    }
    if (k == n) {
        *k_node = cur_node;
        *head = cur_node->next;
        return cur_node;
    }
    
    nnode = reverse_knodes(cur_node->next,head,k_node,k,n+1);
    if (nnode) {
        nnode->next = cur_node;
        return cur_node;
    }
    return NULL;    
}

struct ListNode* reverseKGroup(struct ListNode* head, int k){

    struct ListNode* prev = NULL; //previous reversed group last node
    struct ListNode* kth_node = NULL; //Kth node in next group of list, (First node in reversed list)
	struct ListNode* hd_node = NULL;
    struct ListNode* last = NULL; //Last node in reversed list
	
    hd_node = head;
    while (hd_node) {
        last = reverse_knodes(hd_node,&hd_node,&kth_node,k,1);
        if (last == NULL) {
            prev->next = hd_node;
            break;
        }
        
        if (prev) {
            prev->next = kth_node;
        } else {
            head = kth_node;
        }
        
        //printf("kth_node:%d head val:%d\n",kth_node->val,h_node->val);
        prev = last;
        prev->next = NULL;
    }
    
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
	int k,i;
	
	if (argc < 4) {
		printf("Usage:Input number of nodes, k number nodes in group to be reversed\n");
		return 1;
	}
	
	cnt = atoi(argv[1]);
	k = atoi(argv[2]);
	i = 3;
	while(cnt) {
		if (argv[i] == NULL) {
			printf("Usage:Input number of nodes, k number nodes in group to be reversed\n");
			return -1;
			//break;
		}
		val = atoi(argv[i]);
		
		i++;
		create_node(val);
		cnt--;
	}
	
	head = reverseKGroup(h_node,k);
	while(head) {
		printf("%d ",head->val);
		head = head->next;
	}
	return 0;
}