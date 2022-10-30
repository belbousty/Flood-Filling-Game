#include "graph_generator.h"
#include <math.h>


void square(struct graph_t * graph) {
    int num_vertices = graph -> num_vertices;
    int length = sqrt(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        if (i < (num_vertices - length)) {
            gsl_spmatrix_uint_set(graph -> t, i, sqrt(num_vertices) + i, 1);
            gsl_spmatrix_uint_set(graph -> t, sqrt(num_vertices) + i, i, 1);
        }
        if ((i + 1) % length != 0) {
            gsl_spmatrix_uint_set(graph -> t, i, i + 1, 1);
            gsl_spmatrix_uint_set(graph -> t, i + 1, i, 1);
        }
    }
}

void donut(struct graph_t * graph) {
    int num_vertices = graph -> num_vertices;
    num_vertices = sqrt(num_vertices);
    for (int i = 0; i < num_vertices * num_vertices; i++) {
        if (i + 1 < num_vertices * num_vertices && ((i + 1) % num_vertices != 0)) {
            gsl_spmatrix_uint_set(graph -> t, i, i + 1, 1);
        }
        if (i + num_vertices < num_vertices * num_vertices) {
            gsl_spmatrix_uint_set(graph -> t, i, i + num_vertices, 1);
        }
        if (i - num_vertices >= 0) {
            gsl_spmatrix_uint_set(graph -> t, i, i - num_vertices, 1);
        }
        if (i - 1 >= 0 && i % num_vertices != 0) {
            gsl_spmatrix_uint_set(graph -> t, i, i - 1, 1);
        }
    }
    for (int k = 0; k < num_vertices * num_vertices; k++) {
        for (int i = 0; i < num_vertices / 3; i++) {
            for (int j = 0; j < num_vertices / 3; j++) {

                gsl_spmatrix_uint_set(graph -> t,
                    k,
                    (num_vertices - 1) * (num_vertices / 3) + (num_vertices - 1) + j - (num_vertices / 3) + 1 + num_vertices * i,
                    0);
                gsl_spmatrix_uint_set(graph -> t,
                    (num_vertices - 1) * (num_vertices / 3) + (num_vertices - 1) + j - (num_vertices / 3) + 1 + num_vertices * i,
                    k,
                    0);
            }
        }
    }
}

void hgraph(struct graph_t * graph) {
    int num_vertices = graph -> num_vertices;
    num_vertices = sqrt(num_vertices);
    for (int i = 0; i < num_vertices * num_vertices; i++) {
        if (i + 1 < num_vertices * num_vertices && ((i + 1) % num_vertices != 0)) {
            gsl_spmatrix_uint_set(graph -> t, i, i + 1, 1);
        }
        if (i + num_vertices < num_vertices * num_vertices) {
            gsl_spmatrix_uint_set(graph -> t, i, i + num_vertices, 1);
        }
        if (i - num_vertices >= 0) {
            gsl_spmatrix_uint_set(graph -> t, i, i - num_vertices, 1);
        }
        if (i - 1 >= 0 && i % num_vertices != 0) {
            gsl_spmatrix_uint_set(graph -> t, i, i - 1, 1);
        }
    }
    for (int k = 0; k < num_vertices * num_vertices; k++) {
        for (int i = 0; i < num_vertices / 3; i++) {
            for (int j = 0; j < num_vertices / 3; j++) {
                gsl_spmatrix_uint_set(graph -> t, k, (num_vertices / 3) + j + num_vertices * i, 0);
                gsl_spmatrix_uint_set(graph -> t, (num_vertices / 3) + j + num_vertices * i, k, 0);
            }
        }
    }
    for (int k = 0; k < num_vertices * num_vertices; k++) {
        for (int i = 0; i < num_vertices / 3; i++) {
            for (int j = 0; j < num_vertices / 3; j++) {
                gsl_spmatrix_uint_set(graph -> t, k, (num_vertices - 1) * (2 * num_vertices / 3) + (num_vertices) + j + num_vertices * i, 0);
                gsl_spmatrix_uint_set(graph -> t, (num_vertices - 1) * (2 * num_vertices / 3) + (num_vertices) + j + num_vertices * i, k, 0);
            }
        }
    }
}

void torus(struct graph_t * graph) {
    int vertices = (int) graph -> num_vertices;
    int rows = sqrt(vertices);
    graph -> positions[0] = 0;
    graph -> positions[1] = (int) vertices / 2 + rows/2;
    for (int k = 0; k < vertices; k++) {
        gsl_spmatrix_uint_set(graph -> t, k, k + 1 - rows * ((k + 1) % rows == 0), 1); //eastern neighbor
        gsl_spmatrix_uint_set(graph -> t, k, (k == 0) ? rows - 1 : k - 1 + (k % rows == 0) * rows, 1); //western neighbor
        gsl_spmatrix_uint_set(graph -> t, k, (k + rows) % vertices, 1); //southern neighbor
        gsl_spmatrix_uint_set(graph -> t, k, (k - rows + vertices) % vertices, 1); //northern neighbor
    }
}

/*
 *
 */
struct graph_t * graph_init(int num_vertices, enum graph_type_t type) {
    struct graph_t * graph = malloc(sizeof(struct graph_t));
    graph -> num_vertices = num_vertices;
    num_vertices = sqrt(num_vertices);
    graph -> t = gsl_spmatrix_uint_alloc(num_vertices * num_vertices, num_vertices * num_vertices);
    graph -> positions[0] = 0;
    graph -> positions[1] = num_vertices * num_vertices - 1;
    switch (type) {
    case SQUARE:
        square(graph);
        break;
    case DONUT:
        // m multiple de 3
        donut(graph);
        break;
    case HGRAPH:
        // m multiple de 3
        hgraph(graph);
        break;
    case TORUS:
        torus(graph);
        break;
    default:
        break;
    }
    return graph;
}

void graph_compressed_init(struct graph_t * graph) {
    gsl_spmatrix_uint * tmp = graph -> t;
    graph -> t = gsl_spmatrix_uint_compress(graph -> t, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_free(tmp);
}

void print_graph(const struct graph_t * graph) {
    for (int i = 0; i < graph -> num_vertices; i++) {
        printf("\n");
        for (int j = 0; j < graph -> num_vertices; j++) {
            printf("%d ", gsl_spmatrix_uint_get(graph -> t, i, j));
        }
    }
    printf("\n");
}

void free_graph(struct graph_t * graph) {
    gsl_spmatrix_uint_free(graph -> t);
    free(graph);
}
