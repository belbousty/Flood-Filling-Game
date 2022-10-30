#ifndef _GRAPH_MAKER_H_
#define _GRAPH_MAKER_H_

#include "graph.h"

/**
 * 
  Function that initializes a graph
*/
struct graph_t *graph_init(int num_vertices, enum graph_type_t type);

// The following functions specify the form of the graph

void square(struct graph_t *graph);

void hgraph(struct graph_t *graph);

void donut(struct graph_t *graph);

void torus(struct graph_t *graph);

/**
 * 
  returns an array full of forbidden color for each player 
 */

struct color_set_t* forbidden_colors(struct graph_t *graph);


void graph_compressed_init(struct graph_t *graph);

/**
 * Function that displays a graph
*/
void print_graph(const struct graph_t *graph);



/**
 * free the graph at the end  
*/
void free_graph(struct graph_t *graph);


#endif  //_GRAPH_MAKER_H_
