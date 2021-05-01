#include "../include/queue.h"

//#define DEBUG

static const char* logEnd = "\x1b[0m";
static const char* logDebug = "\x1b[32m";

bool printQueue(struct Queue* q)
{
    bool returnFlag = false;
    if (!isEmpty(q)) {
        returnFlag = true;
        struct QNode* temp = q->front;

        while (temp != NULL) {
            printf("%s %d\n", temp->name, temp->pid);
            if (temp->next == NULL) {
                break;
            }
            temp = temp->next;
        }
    }
    return returnFlag;
}

bool printNameFromQueue(struct Queue* q)
{
    bool returnFlag = false;
    if (!isEmpty(q)) {
        returnFlag = true;
        struct QNode* temp = q->front;

        while (temp != NULL) {
            printf("%s\n", temp->name);
            if (temp->next == NULL) {
                break;
            }
            temp = temp->next;
        }
    }
    return returnFlag;
}

bool printPidFromQueue(struct Queue* q)
{
    bool returnFlag = false;
    if (!isEmpty(q)) {
        returnFlag = true;
        struct QNode* temp = q->front;

        while (temp != NULL) {
            printf("%d\n", temp->pid);
            if (temp->next == NULL) {
                break;
            }
            temp = temp->next;
        }
    }
    return returnFlag;
}

struct Queue* findPidInQueue(struct Queue* q, int k)
{
    struct Queue* outQueue = createQueue();

    if (q->front == NULL) {
        return outQueue;
    }
    struct QNode* temp = q->front;

    while (temp != NULL) {
        if (k == temp->pid) {
            push_back(outQueue, temp->pid, temp->name);
        }
        if (temp->next == NULL) {
            break;
        }
        temp = temp->next;
    }
    return outQueue;
}

struct Queue* findNameInQueue(struct Queue* q, char* name)
{
    struct Queue* outQueue = createQueue();

    if (q->front == NULL) {
        return outQueue;
    }
    struct QNode* temp = q->front;

    while (temp != NULL) {
        if (strcmp(name, temp->name) == 0) {
            push_back(outQueue, temp->pid, temp->name);
        }
        if (temp->next == NULL) {
            break;
        }
        temp = temp->next;
    }

    return outQueue;
}

struct QNode* newNode(int k, char* name)
{
    //struct QNode* temp = (struct QNode*)malloc(sizeof(struct QNode));
    struct QNode* temp = new struct QNode();
    temp->pid = k;
    strcpy(temp->name, name);
    temp->next = NULL;
    return temp;
}

struct Queue* createQueue()
{
    //struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    struct Queue* q = new struct Queue();
    q->front = q->rear = NULL;
    q->count = 0;
    return q;
}

void push_back(struct Queue* q, int k, char* name)
{
#ifdef DEBUG
    printf("%sDEBUG: pushQueue(%d,%s)\n%s", logDebug, k, name, logEnd);
#endif
    struct QNode* temp = newNode(k, name);

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        q->count++;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
    q->count++;
}

bool isEmpty(struct Queue* q)
{
    return (q->rear == NULL);
}

void pop_front(struct Queue* q)
{
    if (q->front == NULL) {
        return;
    }

    struct QNode* temp = q->front;

    if (q->front->next == NULL) {
        q->front = NULL;
        q->count--;
        q->rear = NULL;
        delete(temp);
        return;
    }

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    q->count--;

    delete(temp);
}

bool deleteQueue(struct Queue* q)
{
#ifdef DEBUG
    printf("%sDEBUG: deleteQueue()\n%s", logDebug, logEnd);
#endif

    while (q->front != NULL) {
        pop_front(q);
    }

    if (q->rear == NULL && q->front == NULL) {
        delete(q);
        return true;
    }
    return false;
}
