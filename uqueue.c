#include <stdio.h>
#include <stdlib.h>

#include "uqueue.h"

static UQUEUE_NODE *_uqueue_node_new(void *obj, int len)
{
    UQUEUE_NODE *node = malloc(sizeof(UQUEUE_NODE));
    if(!node)
        return NULL;

    node->obj = obj;
    node->len = len;
    node->next = NULL;
    return node;
}

static void _uqueue_node_destroy(UQUEUE_NODE *node)
{
    if(node)
    {
        node->next = NULL;
        free(node);
    }
}

static int _uqueue_enqueue(UQUEUE *queue, UQUEUE_NODE *node)
{
    if(!queue || !node)
        return UQUEUE_ERROR_INVALID_ARGS;

    if(UQUEUE_EMPTY(queue))
    {
        queue->head = node;
        queue->tail = node;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->size ++;

    return UQUEUE_ERROR_SUCCESS;
}

static UQUEUE_NODE *_uqueue_dequeue(UQUEUE *queque)
{
    if(!queque)
        return NULL;

    if(UQUEUE_EMPTY(queque))
        return NULL;

    UQUEUE_NODE *node = queque->head;
    queque->head = node->next;
    queque->size --;
    return node;
}

UQUEUE *uqueue_new()
{
    UQUEUE *q = malloc(sizeof(UQUEUE));
    if(!q)
        return NULL;

    q->head = q->tail = NULL;
    q->size = 0;

    return q;
}

void uqueue_destroy(UQUEUE *queue)
{
    if(!queue)
        return;

    while (!UQUEUE_EMPTY(queue))
    {
        void *obj = NULL;
        int len = 0;
        (void)uqueue_dequeue(queue, &obj, &len);
    }

    free(queue);
}

int uqueue_enqueue(UQUEUE *queue, void *obj, int len)
{
    if(!queue || !obj)
        return UQUEUE_ERROR_INVALID_ARGS;

    UQUEUE_NODE *node = _uqueue_node_new(obj, len);
    if(!node)
        return UQUEUE_ERROR_NO_RESOURCE;

    return _uqueue_enqueue(queue, node);
}

int uqueue_dequeue(UQUEUE *queue, void **obj, int *len)
{
    UQUEUE_NODE *node = _uqueue_dequeue(queue);
    if(!node)
        return UQUEUE_ERROR_EMPTY;

    if(obj)
        *obj = node->obj;

    if(len)
        *len = node->len;

    _uqueue_node_destroy(node);

    return UQUEUE_ERROR_SUCCESS;
}