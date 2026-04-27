#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void print_queue(Queue* q){
    QueueNode *qnode = q->front;
    while(qnode){
        printf("%d ", qnode->tree_node->val);
        qnode = qnode->next;
    }
    printf("\n");
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    QueueNode *qnode = malloc(sizeof(QueueNode));
    qnode->tree_node = tree_node;
    if(q->rear){
        q->rear->next = qnode;
    }
    q->rear = qnode;
    if(!q->front){
        q->front = qnode;
    }

}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    if(!q->front){
        return NULL;
    }
    QueueNode *qnode = q->front;
    TreeNode  *tnode = qnode->tree_node;
    q->front = qnode->next;
    if(q->rear == qnode){
        q->rear = NULL;
    }
    free(qnode);
    return tnode;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    // TODO: 在这里添加你的代码
    Queue *tree_queue = create_queue();
    TreeNode *root = NULL;
    for(int i = 0; i<size; i++){
        // printf("### %d \n", i);
        TreeNode *node = malloc(sizeof(TreeNode));
        node->val = level_order[i];
        node->left = NULL;
        node->right = NULL;
        if(!root){
            root = node;
        }
        
        if(tree_queue->front){
            TreeNode *parent = tree_queue->front->tree_node;
            if(!parent->left){
                parent->left = node;
            }else if(!parent->right){
                parent->right = node;
            }

            if(parent->left && parent->right){
                // printf("deque: %d, left %d, right %d\n", parent->val, parent->left->val, parent->right->val);
                dequeue(tree_queue);
            }
        }
        if(node->val != INT_MIN)
            enqueue(tree_queue, node);

        // print_queue(tree_queue);
    }
    // printf("end\n");
    return root;
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if(!root){
        return;
    }
    if(root->val != INT_MIN)
        printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if(!root){
        return;
    }
    TreeNode *stack[20] = { NULL };
    int stack_len = 0;
    #define stack_push(node) stack[stack_len++] = node;
    #define stack_pop() (stack[--stack_len])

    TreeNode *node = NULL;
    stack_push(root);
    while(1){
        if(stack_len == 0){
            break;
        }
        node = stack_pop();
        // printf("pop: %d", node->val);
        if(node){
            while(node){
                if(node->val != INT_MIN){
                    printf("%d ", node->val);
                }
                if(node->right){
                    // printf("enqueue: %d \n", node->right->val);
                    stack_push(node->right);
                }
                node = node->left;
            }
        }else{
            break;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
