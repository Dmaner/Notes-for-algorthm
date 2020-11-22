#include <bits/stdc++.h>

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* slow = head;
        ListNode* fast = head->next;

        // find mid point
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* mid = slow->next;
        slow->next = nullptr;

        // recursive
        ListNode* left = sortList(head);
        ListNode* right = sortList(mid);
        
        ListNode* merge = new ListNode(-1);
        ListNode* ans = merge;
        while (left && right){
            if (left->val < right->val){
                merge->next = left;
                left = left->next;
            }
            else{
                merge->next = right;
                right = right->next;
            }
            merge = merge->next;
        }
        merge->next = left ? left : right;
        
        return ans->next;
    }
};