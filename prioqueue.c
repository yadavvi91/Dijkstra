#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "prioqueue.h"
#include "graph.h"
#include "dijkstra.h"

prioq_p create_prioq(graph_p graph_instance)
{
    int i;
    prioq_node *temp, *temp_p;
    vrtx_node *vertexTemp;
    prioq_p prioq_instance = (prioq_p) malloc(sizeof(prioq));
    prioq_instance->head = NULL;
    vertexTemp = graph_instance->vertices;

    for (i = 0; i < graph_instance->no_vert; i++) {
        temp_p = (prioq_node *) malloc(sizeof(prioq_node));
        temp_p->distance = MAX_INT;
        temp_p->vertex = vertexTemp->vertex;
        vertexTemp = vertexTemp->next;
        temp_p->next = NULL;
        // This might cause some problems
        if (prioq_instance->head == NULL) {
            prioq_instance->head = temp_p;
        } else {
            temp = prioq_instance->head;
            while (temp->next)
                temp = temp->next;
            temp->next = temp_p;
        }
    }
    return prioq_instance;
}

int isempty(prioq_p prioq_instance)
{
    if (prioq_instance->head == NULL)
        return 1;
    return 0;
}

void change_priority(prioq_p prioq_instance, char vertex, int distance)
{
    // Here comes the sorting algorithm - well not exactly
    prioq_node *pQNode,
              *pQNodePrevious,
              *pQNodeTemp,
              *pQNodeTempPrevious;
    pQNode = prioq_instance->head;
    pQNodePrevious = prioq_instance->head;

    while((pQNode->vertex != vertex) && (pQNode != NULL)) {
        pQNodePrevious = pQNode;
        pQNode = pQNode->next;
    }

    if (pQNode == NULL) {
        fprintf(stdout, "Vertex was not found");
    } else {
        pQNode->distance = distance;
        if (pQNode != prioq_instance->head) {
            pQNodePrevious->next = pQNode->next;
        } else {
            prioq_instance->head = pQNode->next;
        }
    }

    pQNodeTemp = prioq_instance->head;
    pQNodeTempPrevious = prioq_instance->head;

    while((pQNodeTemp != NULL) && (pQNodeTemp->distance < pQNode->distance)) {
        pQNodeTempPrevious = pQNodeTemp;
        pQNodeTemp = pQNodeTemp->next;
    }

    // No element was smaller than this one - pQNodeTemp
    if (pQNodeTemp == NULL) {
        if (pQNodePrevious == NULL) // This happens when the last element has been deleted
            return;
        pQNodeTempPrevious->next = pQNode;
        pQNode->next = NULL;
        return;
    }
    if (pQNodeTemp != prioq_instance->head) {
        pQNodeTempPrevious->next = pQNode;
        pQNode->next = pQNodeTemp;
    }
    if (pQNodeTemp == prioq_instance->head) {
        pQNode->next = prioq_instance->head;
        prioq_instance->head = pQNode;
    }
    return;
}

prioq_node *dequeue(prioq_p prioq_instance)
{
    prioq_node *pQNode;
    pQNode = prioq_instance->head;
    if (prioq_instance->head != NULL)
        prioq_instance->head = prioq_instance->head->next;
    return pQNode;
}
