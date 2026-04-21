#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    // TODO: 在这里添加你的代码
    link node = malloc(sizeof(struct node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void free_node(link p) {
    // TODO: 在这里添加你的代码
    free(p);
}

link search(int key) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while(p != tail){
        if(p->data == key){
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void insert(link p) {
    // TODO: 在这里添加你的代码
    p->next = head->next;
    p->prev = head;
    if(head->next){
        head->next->prev = p;
    }
    head->next = p;
    
}

void delete(link p) {
    // TODO: 在这里添加你的代码
    link pprev = p->prev;
    link pnext = p->next;

    if(pprev){
        pprev->next = pnext;
    }
    if(pnext){
        pnext->prev = pprev;
    }
}

void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while(p != tail){
        visit(p);
        p = p->next;
    }
}

void destroy(void) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    link pnext;
    while(p != tail){
        pnext = p->next;
        free_node(p);
        p = pnext;
    }
    head->next = tail;
    tail->prev = head;
}
