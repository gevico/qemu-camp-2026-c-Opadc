#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;



int queue_is_empty(Queue *q){
    return q->count == 0;
}
void enqueue(Queue *q, People people){
    q->data[q->tail] = people;
    if(q->head == -1)
        q->head = 0;
    
    q->tail = (q->tail+1) % MAX_PEOPLE;
    q->count++;
}

People dequeue(Queue *q){
    q->count--;
    People p = q->data[q->head];
    q->head = (q->head+1) % MAX_PEOPLE;
    return p;
    
}

void init_queue(Queue *q, int total_people){
    q->tail = 0;
    q->head = -1;
    q->count = 0;
    for(int i=1; i<=total_people; i++){
        People people = {.id = i};
        enqueue(q, people);
    }
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    init_queue(&q, total_people);
    
    int curr_id = 1;
    while(q.count > 1){
        People people = dequeue(&q);
        if(curr_id == report_interval){
            printf("淘汰: %d\n", people.id);
        }else{
            enqueue(&q, people);
        }
        curr_id = curr_id + 1;
        if(curr_id > report_interval){
            curr_id = 1;
        }

    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}