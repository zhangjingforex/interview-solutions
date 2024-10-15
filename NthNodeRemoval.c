/*
Remove Nth Node From End of List
Given the head of a linked list, remove the nth node from the end of the list and return its head.

Example 1:


Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]
 

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if (!head)
        return NULL;
    struct ListNode anchor = {0, head};
    struct ListNode* left = &anchor;
    struct ListNode* right = &anchor;
    
    for (int i = 0; i < n && right; i++) {
        right = right->next;
    }
    
    while (right && right->next) {
        left = left->next;
        right = right->next;
    }
    
    // remove the node after left
    struct ListNode* temp = left->next;
    left->next = temp->next;
    free(temp);
    
    return anchor.next;
}
