#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
#include "graph.h"
#include "prioqueue.h"

static adj_vrtx *findAdjacent(graph_p graph_instance, char vertex)
{
    int i, position;
    adj_vrtx *temp,
              *temp_p,
              *head = NULL;
    position = getInt(graph_instance, vertex);
    temp_p = head;

    for (i = 0; i < graph_instance->no_vert; i++) {
        if (graph_instance->head[position*graph_instance->no_vert + i].weight != MAX_INT) {
            temp = (adj_vrtx *) malloc(sizeof(adj_vrtx));
            temp->adjacent = graph_instance->head[position*graph_instance->no_vert + i].destination;
            temp->next = NULL;
            if (head == NULL) {
                temp_p = temp;
                head = temp;
            } else {
                while(temp_p->next)
                    temp_p = temp_p->next;
                temp_p->next = temp;
            }
        }
    }

    return head;
}

static shrt_path_p init_shortest_path(graph_p graph_instance)
{
    int i;
    shrt_path_p shrtPathInstance = (shrt_path_p) malloc(sizeof(shrt_path));
    shrtPathInstance->head = (shrt_vrtx *) malloc(graph_instance->no_vert * sizeof(shrt_vrtx));
    for (i = 0; i < graph_instance->no_vert; i++) {
        shrtPathInstance->head[i].distance = MAX_INT;
        shrtPathInstance->head[i].previous = NUL;
        shrtPathInstance->head[i].vertex = NUL;
    }
    return shrtPathInstance;
}

void find_shortest_path(graph_p graph_instance, char vertex)
{
    int i, sourceInt, destInt;
    prioq_node *pQNode, *pQNodeTemp;
    adj_arr *adjArrInstance;
    adj_vrtx *adjArrVertexTemp, *adjArrVertexTemp_p;

    // Initialize the Priority Queue
    prioq_p prioq_instance;
    prioq_instance = create_prioq(graph_instance);

    /** Intialize the Shortest Path - the data structure that stores
     *  DISTANCE and PREVIOUS of an element */
    shrt_path_p shrtPathInstance;
    shrtPathInstance = init_shortest_path(graph_instance);

    /** For the starting 'vertex' - here 's', change the 'distance' and the 'previous'
     *  in 'shortestPath' */
    i = getInt(graph_instance, vertex);
    shrtPathInstance->head[i].distance = 0;
    shrtPathInstance->head[i].vertex = vertex;
    shrtPathInstance->head[i].previous = NUL;

    /** As the DISTANCE of vertex - here 's' - has been CHANGED, we CHANGE its
     *  PRIORITY too in the PriorityQueue */
    i = getInt(graph_instance, vertex);
    change_priority(prioq_instance, vertex, shrtPathInstance->head[i].distance);

    /* Now the actual algorithm */
    adjArrInstance = (adj_arr *) malloc(sizeof(adj_arr));

    while (!isempty(prioq_instance)) {
        pQNode = dequeue(prioq_instance);
        /** What is left is Adjacent array and assigning
         *  DISTANCE and PREVIOUS to a vertex in SHORTEST PATH */
        adjArrInstance->vertex = pQNode->vertex;
        adjArrInstance->head = findAdjacent(graph_instance, adjArrInstance->vertex);

        adjArrVertexTemp = adjArrInstance->head;

        while (adjArrVertexTemp != NULL) {
            sourceInt = getInt(graph_instance, adjArrInstance->vertex);
            destInt   = getInt(graph_instance, adjArrVertexTemp->adjacent);
            if ((shrtPathInstance->head[destInt].distance) > (shrtPathInstance->head[sourceInt].distance + graph_instance->head[sourceInt*graph_instance->no_vert + destInt].weight)) {
                shrtPathInstance->head[destInt].distance = shrtPathInstance->head[sourceInt].distance + graph_instance->head[sourceInt*graph_instance->no_vert + destInt].weight;
                shrtPathInstance->head[destInt].previous = adjArrInstance->vertex;
                shrtPathInstance->head[destInt].vertex = adjArrVertexTemp->adjacent;

                //Newly added - to be removed
                pQNodeTemp = prioq_instance->head;
                fprintf(stdout, "\n\nBefore changing the priority of: %c\n", adjArrVertexTemp->adjacent);
                while (pQNodeTemp != NULL) {
                    fprintf(stdout, "\n%-10d%-10c%-10p", pQNodeTemp->distance, pQNodeTemp->vertex, pQNodeTemp->next);
                    pQNodeTemp = pQNodeTemp->next;
                }

                fprintf(stdout, "\nPriority Queue head: %c\n", prioq_instance->head->vertex);
                // Newly added - to be removed

                // For a vertex whose DISTANCE and PREVIOUS has been changed
                // its PRIORITY i.e. DISTANCE in the Priority Queue should also be changed
                change_priority(prioq_instance, shrtPathInstance->head[destInt].vertex, shrtPathInstance->head[destInt].distance);

                // Newly added - to be removed
                pQNodeTemp = prioq_instance->head;
                fprintf(stdout, "\n\nAfter changing the priority of %c\n", adjArrVertexTemp->adjacent);

                while (pQNodeTemp != NULL) {
                    fprintf(stdout, "\n%-10d%-10c%-10p", pQNodeTemp->distance, pQNodeTemp->vertex, pQNodeTemp->next);
                    pQNodeTemp = pQNodeTemp->next;
                }
                // Newly added - to be removed
            }
            // Move the 'adjArrVertexTemp' to the next ADJACENT NODE
            adjArrVertexTemp = adjArrVertexTemp->next;
        }
        // Freeing the space allocated to the Adjacent vertices
        adjArrVertexTemp = adjArrInstance->head;
        while (adjArrVertexTemp) {
            adjArrVertexTemp_p = adjArrVertexTemp;
            adjArrVertexTemp = adjArrVertexTemp->next;
            free(adjArrVertexTemp_p);
        }
        free(adjArrInstance->head);
        //free(adjArrInstance);
        free(pQNode);
    }
    free(adjArrInstance);
    fprintf(stdout, "\n\nIndex     Vertex    Distance  Previous  ");
    for (i = 0; i < graph_instance->no_vert; i++) {
        fprintf(stdout, "\n%-10d%-10c%-10d%-10c", i, shrtPathInstance->head[i].vertex, shrtPathInstance->head[i].distance, shrtPathInstance->head[i].previous);
    }
}
