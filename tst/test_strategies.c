#include <stdio.h>
#include <assert.h>
#include "../src/strategies.h"

struct move_t moves[8] = {{.c=0}, {.c=1}, {.c=2}, {.c=3}, {.c=4}, {.c=5}, {.c=6}, {.c=7}};
struct color_set_t forbidden1[1]={{{'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'}}};
struct color_set_t forbidden2[1]={{{'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'}}};

void test_get_neighbors() {
  printf("    %s\n", __func__);

  struct graph_t * graph = graph_init(9, SQUARE);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, ALEATOIRE, MAX_COLOR);
  int tab[4] = {
    0
  };
  get_neighbors(graph, tab, 0);

  assert(tab[0] == 3);
  assert(tab[1] == 1);
  assert(tab[2] == -1);
  assert(tab[3] == -1);

  get_neighbors(graph, tab, graph -> num_vertices - 1);
  assert(tab[0] == 5);
  assert(tab[1] == 7);
  assert(tab[2] == -1);
  assert(tab[3] == -1);

  printf("\n   ====OK==== \n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_p0() {
  printf("    %s\n", __func__);
  struct graph_t * graph = graph_init(9, SQUARE);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);
  int passed_neighbors[99] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  
  spread__colors(graph, moves[1], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[2], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 0, forbidden1, forbidden2, colors);
  get_Ctab_neighbors(graph, colors, passed_neighbors, 0, 5, color_neighbors, 0);

  assert(color_neighbors[0] == 1);
  assert(color_neighbors[1] == 0);
  assert(color_neighbors[2] == 0);
  assert(color_neighbors[3] == 1);
  assert(color_neighbors[4] == 1);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 0);
  assert(color_neighbors[7] == 0);

  printf("\n   ====OK==== \n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_p0_v2() {
  printf("    %s\n", __func__);

  struct graph_t * graph = graph_init(16, SQUARE);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);

  int passed_neighbors[16] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  spread__colors(graph, moves[1], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[2], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 0, forbidden1, forbidden2, colors);
  get_Ctab_neighbors(graph, colors, passed_neighbors, 0, 5, color_neighbors, 0);

  assert(color_neighbors[0] == 0);
  assert(color_neighbors[1] == 1);
  assert(color_neighbors[2] == 0);
  assert(color_neighbors[3] == 1);
  assert(color_neighbors[4] == 1);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 1);
  assert(color_neighbors[7] == 0);
  printf("\n    ====OK==== \n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_p0_v3() {
  printf("    %s\n", __func__);
  struct graph_t * graph = graph_init(25, SQUARE);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);

  int passed_neighbors[25] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  for (int i = 1; i < 8; i++) {
    spread__colors(graph, moves[i], 0, forbidden1, forbidden2, colors);

  }
  spread__colors(graph, moves[4], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 0, forbidden1, forbidden2, colors);
  get_Ctab_neighbors(graph, colors, passed_neighbors, 0, 5, color_neighbors, 0);

  assert(color_neighbors[0] == 1);
  assert(color_neighbors[1] == 2);
  assert(color_neighbors[2] == 2);
  assert(color_neighbors[3] == 1);
  assert(color_neighbors[4] == 0);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 1);
  assert(color_neighbors[7] == 0);

  printf("\n    ====OK==== \n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_p1() {
  printf("    %s\n", __func__);
  struct graph_t * graph = graph_init(9, SQUARE);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);
  graph_compressed_init(graph);

  int passed_neighbors[99] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  spread__colors(graph, moves[1], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[2], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 1, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[3], 1, forbidden1, forbidden2, colors);

  get_Ctab_neighbors(graph, colors, passed_neighbors, 1, 3, color_neighbors, graph -> num_vertices - 1);
  
  assert(color_neighbors[0] == 0);
  assert(color_neighbors[1] == 0);
  assert(color_neighbors[2] == 0);
  assert(color_neighbors[3] == 0);
  assert(color_neighbors[4] == 1);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 1);
  assert(color_neighbors[7] == 1);

  free_colors(colors);
  free_graph(graph);
  printf("\n    ====OK==== \n");

}


void test_get_Ctab_neighbors_donut_p0() {
  printf("    %s\n", __func__);
  struct graph_t * graph = graph_init(9, DONUT);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);
  int passed_neighbors[99] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  
  spread__colors(graph, moves[1], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[2], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 0, forbidden1, forbidden2, colors);
  get_Ctab_neighbors(graph, colors, passed_neighbors, 0, 5, color_neighbors, 0);
  
  assert(color_neighbors[0] == 0);
  assert(color_neighbors[1] == 0);
  assert(color_neighbors[2] == 0);
  assert(color_neighbors[3] == 1);
  assert(color_neighbors[4] == 1);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 0);
  assert(color_neighbors[7] == 0);

   free_graph(graph);
  printf("\n    ====OK==== \n");
}



void test_get_Ctab_neighbors_donut_p1() {
  printf("    %s\n", __func__);
  struct graph_t * graph = graph_init(9, DONUT);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);
  int passed_neighbors[99] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  
  spread__colors(graph, moves[6], 1, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[4], 1, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 1, forbidden1, forbidden2, colors);

  get_Ctab_neighbors(graph, colors, passed_neighbors, 0, 5, color_neighbors, graph->num_vertices - 1);
  assert(color_neighbors[0] == 0);
  assert(color_neighbors[1] == 0);
  assert(color_neighbors[2] == 1);
  assert(color_neighbors[3] == 1);
  assert(color_neighbors[4] == 0);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 0);
  assert(color_neighbors[7] == 0);

  free_graph(graph);
  printf("\n    ====OK==== \n");
}


void test_get_Ctab_neighbors_torus_p0() {
  printf("    %s\n", __func__);
  struct graph_t * graph = graph_init(16, TORUS);
  graph_compressed_init(graph);
  enum color_t * colors = colors_init(graph, CYCLIQUE, MAX_COLOR);
  int passed_neighbors[99] = {
    SENTINEL
  };
  enum color_t color_neighbors[MAX_COLOR] = {
    0
  };
  
  spread__colors(graph, moves[4], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[5], 0, forbidden1, forbidden2, colors);
  spread__colors(graph, moves[1], 0, forbidden1, forbidden2, colors);
  get_Ctab_neighbors(graph, colors, passed_neighbors, 0, 1, color_neighbors, graph->num_vertices - 1);

  assert(color_neighbors[0] == 1);
  assert(color_neighbors[1] == 0);
  assert(color_neighbors[2] == 2);
  assert(color_neighbors[3] == 2);
  assert(color_neighbors[4] == 0);
  assert(color_neighbors[5] == 0);
  assert(color_neighbors[6] == 2);
  assert(color_neighbors[7] == 1);

  free_colors(colors);
  free_graph(graph);
  printf("\n    ====OK==== \n");
}



int main() {
  printf("===%s===\n", __FILE__);

  test_get_neighbors();
  test_get_Ctab_neighbours_p0();
  test_get_Ctab_neighbours_p0_v2();
  test_get_Ctab_neighbours_p0_v3();
  test_get_Ctab_neighbours_p1();
  test_get_Ctab_neighbors_donut_p0();
  test_get_Ctab_neighbors_donut_p1();
  test_get_Ctab_neighbors_torus_p0();
  test_get_Ctab_neighbors_torus_p1();
  
  printf("===%s TESTS PASSED===\n", __FILE__);

  return 0;
}
