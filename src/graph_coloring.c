#include "graph_coloring.h"



int is_position_available(struct graph_t * graph, int position) {
    for (int i = 0; i < graph -> num_vertices; i++) {
        if (gsl_spmatrix_uint_get(graph -> t, i, position) == 1)
            return 1;
    }
    return 0;
}

void colors_random(struct graph_t * graph, enum color_t * colors, int num_colors) {
    srand(time(0));
    for (int i = 0; i < graph -> num_vertices; i++) {
        if (is_position_available(graph, i)) {

            unsigned int random_col = random() % num_colors;
            colors[i] = random_col;
        } else
	  colors[i] = -2;
    }
}

void colors_cyclique(struct graph_t * graph, enum color_t * colors, int num_colors) {
    int k = 0;
    for (int i = 0; i < graph -> num_vertices; i++) {
        if (is_position_available(graph, i)) {
            unsigned int cyclique_color = k % num_colors;
            colors[i] = cyclique_color;
            k++;
        } else
            colors[i] = NO_COLOR;
    }
}

void colors_pont(struct graph_t * graph, enum color_t * colors, int num_colors) {
    colors_random(graph, colors, num_colors);
    int k = sqrt(graph -> num_vertices);
    int random1 = rand() % k;
    int random3 = rand() % k;
    int random4 = rand() % k;
    int random5 = rand() % k;
    for (int i = 0; i < k - random1 && i < k; i++) {
        colors[random1 + i] = colors[random1];
    }
    for (int i = 0; i < k - random3 && i < k; i++) {
        colors[random3 + k * i] = colors[random3];
    }
    for (int i = 0; i < k - random4 && i < k; i++) {
        colors[random4 + i] = colors[random4];
    }
    for (int i = 0; i < k - random5 && i < k; i++) {
        colors[random5 + k * i] = colors[random5];
    }
}


void colors_symetrique(struct graph_t * graph, enum color_t * colors, int num_colors){
    colors_random(graph,colors,num_colors);
    int k = sqrt(graph->num_vertices);
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k-i; j++){
            colors[(k -1- i)*k + (k-1-j)] = colors[k*j +i];
        }
    }
}

void print_color(enum color_t * colors, int num_vertices) {
    int k = sqrt(num_vertices);
    int i = 0;
    while (i < num_vertices) {
        printf("%d ", colors[i]);
        if ((i + 1) % k == 0) {
            printf("\n");
        }
        i++;
    }
}

enum color_t * colors_init(struct graph_t * graph, enum color_type_t type_color, int num_colors) {
    enum color_t * colors = malloc(sizeof(enum color_t) * graph -> num_vertices);
    switch (type_color) {
    case ALEATOIRE:
        colors_random(graph, colors, num_colors);
        break;
    case CYCLIQUE:
        colors_cyclique(graph, colors, num_colors);
        break;
    case PONT:
        colors_pont(graph, colors, num_colors);
    case SYMETRIQUE:
        colors_symetrique(graph, colors, num_colors);
        break;
    default:
        break;
    }
    return colors;
}

void free_colors(enum color_t * colors) {
    free(colors);
}
