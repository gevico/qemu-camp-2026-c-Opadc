#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    // TODO: 在这里添加你的代码
    Node *node = NULL;
    Node *head = NULL;
    for(int i=0; i<n; i++){
        if(node){
            Node *new_node = malloc(sizeof(Node));
            new_node->id = i+1;
            node->next = new_node;
            node = new_node;
        }else{
            node = malloc(sizeof(Node));
            node->id = i+1;
            head = node;
        }
    }
    node->next = head;
    return head;
}

void free_list(Node* head) {
    // TODO: 在这里添加你的代码
    Node *node = head;
    Node *next_node;

    while(node){
        next_node = node->next;
        free(node);
        node = next_node;
    }
}
