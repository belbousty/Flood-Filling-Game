#ifndef __GRAPH_COLORING__
#define __GRAPH_COLORING__

#include <stdio.h>
#include "graph_generator.h"
#include "time.h"

enum color_type_t { CYCLIQUE=0, ALEATOIRE=1, PONT=2, SYMETRIQUE=3 };

#define coloration_form(s) ((s == CYCLIQUE) ? "cyclique" : \
                           ((s == ALEATOIRE) ? "aleatoire" : "pont"))

/**
 - Input : graph, coloring type, number of colors
 - Output : a unidimentional table of colors 
*/
enum color_t *colors_init(struct graph_t *graph,
                              enum color_type_t type_color, int num_colors);

/**
 - Input : graph, position
 - Output : boolean; True if position is available in the graph
 */
int is_position_available(struct graph_t *graph, int position);

/**
 returns a table of colors colored randomly
 */
void colors_random(struct graph_t *graph, enum color_t *colors, int num_colors);

/**
 * returns a table of colors that follows a pattern
 */ 
void colors_cyclique(struct graph_t *graph, enum color_t *colors, int num_colors);

/**
 * returns a table of colors that contains bridges
 */ 
void colors_pont(struct graph_t *graph, enum color_t *colors, int num_colors);


/**
 * returns a table of colors that contains bridges
 */ 
void colors_symetrique(struct graph_t *graph, enum color_t *colors, int num_colors);

/**
 * free tha table of colors
 */ 
void free_colors(enum color_t* colors);

/**
 * Displays the table of colors
 */ 
void print_color(enum color_t *colors,int num_vertices);

#endif