#include "queue.h"

void queueInit(Queue *queue)
{
    queue->queueSize = 0;
    queue->startIndex = 0;
}

bool queueAdd(Queue *queue, QueueItem item)
{
    if(queueIsFull(queue))
        return false;

    int index = (queue->startIndex + queue->queueSize) % QUEUE_SIZE;
    ++(queue->queueSize);

    queue->data[index] = item;
    return true;
}

bool queueGet(Queue *queue, QueueItem *output)
{
    if(queueIsEmpty(queue))
        return false;

    *output = queue->data[queue->startIndex];

    queue->startIndex = (queue->startIndex + 1) % QUEUE_SIZE;
    --(queue->queueSize);
    
    return true;
}

bool queueIsEmpty(Queue *queue)
{
    return queue->queueSize == 0;
}

bool queueIsFull(Queue *queue)
{
    return queue->queueSize == QUEUE_SIZE;
}
