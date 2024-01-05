#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
  int x;
  int y;
} point_t;

typedef struct node {
  point_t p;
  struct node *next;
} node_t;

typedef struct queue {
  node_t *head;
  node_t *back;
  int size;
  int limit;
} queue_t;

queue_t *init_queue(int limit);
void free_queue(queue_t *q);
int enqueue(queue_t *q, node_t *n);
node_t *dequeue(queue_t *q);
int is_empty(queue_t *q);

#endif // !QUEUE_H
