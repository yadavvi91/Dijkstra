#ifndef PRIOQUEUE_H_INCLUDED
#define PRIOQUEUE_H_INCLUDED
#include "graph.h"
typedef struct prioq_node
{
    int distance;
    char vertex;
    struct prioq_node *next;
} prioq_node;

typedef struct prioq
{
    prioq_node *head;
} prioq, *prioq_p;

prioq_p create_prioq(graph_p graph_instance);
int isempty(prioq_p prioq_instance);
void change_priority(prioq_p prioq_instance, char vertex, int distance);
prioq_node *dequeue(prioq_p prioq_instance);

#endif // PRIOQUEUE_H_INCLUDED
