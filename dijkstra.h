#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#include "graph.h"

#define NUL '\0'

/** Adjacent is a data structure for holding
 * all the ADJACENT VERTEX of the given VERTEX - vertex */
typedef struct adj_vrtx
{
    char adjacent;
    struct adj_vrtx *next;
} adj_vrtx;

typedef struct adj_arr
{
    adj_vrtx *head;
    char vertex;            // The vertex whose adjacent array we are finding
} adj_arr;

/** SHORTESTPATH is a data structure for holding
 *  the PREVIOUS NODE and the DISTANCE FROM SOURCE of a VERTEX - vertex */
typedef struct shrt_vrtx
{
    int distance;
    char previous,
         vertex;
} shrt_vrtx;

typedef struct shrt_path
{
    shrt_vrtx *head;
} shrt_path, *shrt_path_p;

void find_shortest_path(graph_p graph_instance, char vertex);

#endif // DIJKSTRA_H_INCLUDED
