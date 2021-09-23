#include<iostream>
using namespace std;

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
public:
    Node* flatten(Node* head) {
        if(head == nullptr) return nullptr;
        Node* p = new Node();
        p->val = head->val;
        Node* resc = nullptr;
        Node* resn = nullptr;
        if(head->child != nullptr) {
            resc = flatten(head->child);
        }
        if(head->next != nullptr) {
            resn = flatten(head->next);
        }
        if(resc != nullptr) {
            p->next = resc;
            resc->prev = p;
            if(resn != nullptr) {
                while(resc->next != nullptr) {
                    resc = resc->next;
                }
                resc->next = resn;
                resn->prev = resc;
            }
        } else {
            if(resn != nullptr) {
                p->next = resn;
                resn->prev = p;
            } else {
                p->next = nullptr;
            }
        }
        return p;
    }
};