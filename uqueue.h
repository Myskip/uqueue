#ifndef __UQUEUE_H__
#define __UQUEUE_H__

typedef enum _uqueue_err
{
    UQUEUE_ERROR_SUCCESS = 0,
    UQUEUE_ERROR_INVALID_ARGS = 0x01010001,
    UQUEUE_ERROR_NO_RESOURCE = 0x01010002,
    UQUEUE_ERROR_EMPTY = 0x01010002,
}UQUEUE_ERROR_E;

typedef struct _UQUEUE_NODE
{
    void *obj;
    unsigned int len;
    struct _UQUEUE_NODE *next;
}UQUEUE_NODE;

typedef struct
{
    UQUEUE_NODE *head;
    UQUEUE_NODE *tail;
    unsigned int size;
}UQUEUE;

#define UQUEUE_SIZE(q)  (q->size)
#define UQUEUE_EMPTY(q) (UQUEUE_SIZE(q) == 0)

UQUEUE *uqueue_new();
void uqueue_destroy(UQUEUE *queue);
int uqueue_enqueue(UQUEUE *queue, void *obj, int len);
int uqueue_dequeue(UQUEUE *queue, void **obj, int *len);

#endif