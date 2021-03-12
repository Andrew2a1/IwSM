#if !defined(QUEUE_H)
#define QUEUE_H

#include <stdbool.h>
#include <stdint.h>

#define QUEUE_SIZE 32
typedef uint8_t QueueItem;

typedef struct {
    QueueItem data[QUEUE_SIZE];

    unsigned queueSize;
    unsigned startIndex;
} Queue;

void queueInit(Queue *queue);

bool queueAdd(Queue *queue, QueueItem item);
bool queueGet(Queue *queue, QueueItem *output);

bool queueIsEmpty(Queue *queue);
bool queueIsFull(Queue *queue);

#endif // QUEUE_H
