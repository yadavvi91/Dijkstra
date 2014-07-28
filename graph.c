#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph_p create_graph(int no_vert)
{
    int i,
        noOfEdges;
    noOfEdges = no_vert * no_vert;
    graph_p graph_instance = (graph_p) malloc(sizeof(graph));
    graph_instance->no_vert = no_vert;
    graph_instance->head = (edge *) malloc(noOfEdges * noOfEdges);
    graph_instance->vertices = NULL;

    for (i = 0; i < noOfEdges; i++) {
        graph_instance->head[i].weight = MAX_INT;
        graph_instance->head[i].source = NUL;
        graph_instance->head[i].destination = NUL;
    }

    return graph_instance;
}

int getInt(graph_p graph_instance, char vertex)
{
    vrtx_node *node = graph_instance->vertices;
    while (node) {
        if (node->vertex == vertex)
            return node->value;
        node = node->next;
    }

    return -1;
}

char getChar(graph_p graph_instance, int value)
{
    vrtx_node *node = graph_instance->vertices;
    while (node) {
        if (node->value == value)
            return node->vertex;
        node = node->next;
    }

    return NUL;
}

// This adds SOURCE and DESTINATION TO every edge.
void init_graph_edges(graph_p graph_instance)
{
    int i,
        vertex,
        value,
        no_vert;
    vrtx_node *node;
    no_vert = graph_instance->no_vert;
    node = graph_instance->vertices;

    while (node) {
        vertex = node->vertex;
        value = node->value;
        for (i = 0; i < no_vert; i++) {
            graph_instance->head[value*no_vert + i].source = vertex;
            if (i == value)
                graph_instance->head[value*no_vert + i].destination = vertex;
            else
                graph_instance->head[value*no_vert + i].destination = getChar(graph_instance, i);
        }

        node = node->next;
    }
}

void add_edge(graph_p graph_instance, char source, char destination, int weight)
{
    int sourceInt,
        destinationInt,
        no_vert;
    sourceInt = getInt(graph_instance, source);
    destinationInt = getInt(graph_instance, destination);
    no_vert = graph_instance->no_vert;
    graph_instance->head[sourceInt*no_vert + destinationInt].weight = weight;
}

void printGraph(graph_p graph_instance)
{
    int i, j, no_vert;
    no_vert = graph_instance->no_vert;

    for (i = 0; i < no_vert; i++) {
        fprintf(stdout, "Vertex: %c\nEdges: ", graph_instance->head[i].source);
        for (j = 0; j < no_vert; j++) {
            if (graph_instance->head[i*no_vert + j].weight != MAX_INT)
                fprintf(stdout, "%c-%c %-8d", graph_instance->head[i*no_vert + j].source,
                            graph_instance->head[i*no_vert + j].destination,
                            graph_instance->head[i*no_vert + j].weight);
            else
                fprintf(stdout, "%c-%c NUL     ", graph_instance->head[i*no_vert + j].source,
                            graph_instance->head[i*no_vert + j].destination);
        }
        fprintf(stdout, "\n");
    }
}
