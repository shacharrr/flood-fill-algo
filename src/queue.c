#include "queue.h"
#include <stdlib.h>

queue_t *init_queue(int limit) {
  queue_t *q = (queue_t *)malloc(sizeof(queue_t));
  if (q == NULL) {
    return NULL;
  }
  if (limit <= 0) {
    limit = 65535;
  }

  q->limit = limit;
  q->size = 0;
  q->head = NULL;
  q->back = NULL;

  return q;
}

void free_queue(queue_t *q) {
  node_t *n;
  while (!is_empty(q)) {
    n = dequeue(q);
    free(n);
  }
  free(q);
}

int enqueue(queue_t *q, node_t *n) {
  if ((q == NULL) || (n == NULL)) {
    return 0;
  }
  if (q->size >= q->limit) {
    return 0;
  }

  n->next = NULL;
  if (q->size == 0) {
    q->head = n;
    q->back = n;
  } else {
    q->back->next = n;
    q->back = n;
  }
  q->size++;
  return 1;
}

node_t *dequeue(queue_t *q) {
  node_t *n;
  if (is_empty(q)) {
    return NULL;
  }
  n = q->head;
  q->head = (q->head)->next;
  q->size--;
  return n;
}

int is_empty(queue_t *q) {
  if (q == NULL) {
    return 0;
  }
  if (q->size == 0) {
    return 1;
  } else {
    return 0;
  }
}
