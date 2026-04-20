#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    // TODO: 在这里添加你的代码
    link node = malloc(sizeof(struct node));
    node->item = item;
    node->next = NULL;
    return node;

}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while(p){
        if(p->item == key){
            return p;
        }
        p = p->next;
    }
}

// 在链表头部插入节点
void insert(link p) {
    // TODO: 在这里添加你的代码
    push(p);
}

// 删除指定节点
void delete(link p) {
    // TODO: 在这里添加你的代码
    link list = head;
    link next_p;
    while(list){
        if(list->next == p){
            next_p = p->next;
            list->next = next_p;
            free(p);
            return;
        }
        list = list->next;
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    while(p){
        visit(p);
        p = p->next;
    }
}

// 销毁整个链表
void destroy(void) {
    // TODO: 在这里添加你的代码
    link p = head;
    link next_p;

    while(p){
        next_p = p->next;
        free(p);
        p = next_p;
    }
    head = NULL;
}

// 在链表头部推入节点
void push(link p) { 
    // TODO: 在这里添加你的代码
    if(!head){
        head = make_node(-1);
    }
    p->next = head->next;
    head->next = p;
 }

// 从链表头部弹出节点
link pop(void) {
    // TODO: 在这里添加你的代码
    link p = head->next;
    head->next = p->next;
    return p;
}

// 释放链表内存
void free_list(link list_head) {
    // TODO: 在这里添加你的代码
    link p = list_head;
    link next_p;
    while(p){
        next_p = p->next;
        free(p);
        p = next_p;
    }
}
