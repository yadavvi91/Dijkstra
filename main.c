#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "dijkstra.h"

int main(int argc, char *argv[])
{
    int no_vert,
        i;
    vrtx_node *listOfVertices,
               *node,
               *temp;
    graph_p graph_instance;
    /**
     *  Here we have initialized the 'arr[]' of all the nodes
     *  and the 'no_vert'. In improvement we have to remove
     *  this and replace it with dynamically fetched no_vert
     *  and Array Of Cities for us to find the minimum distance.
     */
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    no_vert = 8;
    /**
     *  This for-block initializes all the vertices i.e.
     *  creates a list of all the vertices - listOfVertices. Can be improved
     */
    for (i = 0; i < no_vert; i++) {
        node = (vrtx_node *) malloc(sizeof(vrtx_node));
        node->vertex = arr[i];
        node->value = i;
        node->next = NULL;
        if (i == 0) {
            temp = node;
            listOfVertices = node;
        } else {
            temp->next = node;
            temp = temp->next;
        }
    }
    // Creating the graph with all the edges NULL
    graph_instance = create_graph(no_vert);
    // The list of vertices created - listOfVertices
    // is later assigned to the graph_instance
    graph_instance->vertices = listOfVertices;
    // This adds SOURCE and DESTINATION to every edge
    init_graph_edges(graph_instance);

    add_edge(graph_instance, 'a', 'b', 9);
    add_edge(graph_instance, 'a', 'f', 6);
    add_edge(graph_instance, 'a', 'g', 13);
    add_edge(graph_instance, 'b', 'c', 10);
    add_edge(graph_instance, 'c', 'e', 6);
    add_edge(graph_instance, 'c', 'h', 19);
    add_edge(graph_instance, 'd', 'c', 6);
    add_edge(graph_instance, 'd', 'h', 6);
    add_edge(graph_instance, 'e', 'd', 11);
    add_edge(graph_instance, 'e', 'h', 16);
    add_edge(graph_instance, 'f', 'c', 18);
    add_edge(graph_instance, 'f', 'e', 30);
    add_edge(graph_instance, 'f', 'g', 8);
    add_edge(graph_instance, 'g', 'e', 20);
    add_edge(graph_instance, 'g', 'h', 25);

    printGraph(graph_instance);
	// Find the shortest path of the graph from the location 'a'
    find_shortest_path(graph_instance, 'a');

    return 0;
}
