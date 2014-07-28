#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
/** Graph will consist of the ADJACENCY MATRIX */
#define MAX_INT 32767
#define NUL '\0'
// Here the problem would be searching in the ADJACENCY MATRIX
// for an edge.
// for e.g. When the vertices were 'int' we could just do -
//          graph->head[source * no_vert + destination]
//          to access that particular edge.
// What would we do here?
// Of the top of my head
// When we get the input of the Vertices - s, u, v, x, y
// we can store them in an array with numbers associated with each one of them.

typedef struct edge
{
    int weight;
    char source,
         destination;
} edge;

typedef struct vrtx_node
{
    char vertex;
    int value;
    struct vrtx_node *next;
} vrtx_node;

typedef struct graph
{
    int no_vert;
    edge *head;
    vrtx_node *vertices;
} graph, *graph_p;

// Create the graph with given number of vretices - no_vert
graph_p create_graph(int no_vert);

// Initialize all the graph edges to have a source and destination
void init_graph_edges(graph_p graph_instance);

// Add Edge with the given source and destination a WEIGHT
void add_edge(graph_p graph_instance, char source, char destination, int weight);

// Print the graph vertices and edges
void printGraph(graph_p graph_instance);

int getInt(graph_p graph_instance, char vertex);
char getChar(graph_p graph_instance, int value);

#endif // GRAPH_H_INCLUDED
