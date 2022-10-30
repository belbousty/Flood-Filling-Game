#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<string.h>
#include <math.h>
#include "../src/strategies.h"
#define MAX_NEIGHBORS 4 



unsigned int square1[9][9] = {{0,1,0,1,0,0,0,0,0},{1,0,1,0,1,0,0,0,0},{0,1,0,0,0,1,0,0,0},{1,0,0,0,1,0,1,0,0},{0,1,0,1,0,1,0,1,0},
			     {0,0,1,0,1,0,0,0,1},{0,0,0,1,0,0,0,1,0},{0,0,0,0,1,0,1,0,1},{0,0,0,0,0,1,0,1,0}};

unsigned int donut1[9][9] = {{0,1,0,1,0,0,0,0,0},{1,0,1,0,0,0,0,0,0},{0,1,0,0,0,1,0,0,0},{1,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,0,0},
			 {0,0,1,0,0,0,0,0,1},{0,0,0,1,0,0,0,1,0},{0,0,0,0,0,0,1,0,1},{0,0,0,0,0,1,0,1,0}};

unsigned int hgraph1[9][9] = {{0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0,0},{1,0,0,0,1,0,1,0,0},{0,0,0,1,0,1,0,0,0},
			     {0,0,1,0,1,0,0,0,1},{0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,1,0,0,0}};

unsigned int torus1[9][9] = {{0,1,1,1,0,0,1,0,0},{1,0,1,0,1,0,0,1,0},{1,1,0,0,0,1,0,0,1},{1,0,0,0,1,1,1,0,0},{0,1,0,1,0,1,0,1,0},
			 {0,0,1,1,1,0,0,0,1},{1,0,0,1,0,0,0,1,1},{0,1,0,0,1,0,1,0,1},{0,0,1,0,0,1,1,1,0}};

static void test__square_graph(void){
  printf("%s", __func__);
  struct graph_t* square = graph_init(9, SQUARE);
  for(int k = 0; k<9; k++){
    for(int j = 0; j<9; j++){
      assert(gsl_spmatrix_uint_get(square->t,k,j)==square1[k][j]);
    }
  }
  printf("\t OK\n");
  free_graph(square);
}

static void test__donut_graph(void){
  printf("%s", __func__);
  struct graph_t* donut = graph_init(9, DONUT);
  for(int k = 0; k<9; k++){
    for(int j = 0; j<9; j++){
      assert(gsl_spmatrix_uint_get(donut->t,k,j)==donut1[k][j]);
    }
  }
  printf("\t OK\n");
  free_graph(donut);
}

static void test__hgraph(void){
  printf("%s", __func__);
  struct graph_t* hgraph = graph_init(9, HGRAPH);
  for(int k = 0; k<9; k++){
    for(int j = 0; j<9; j++){
      assert(gsl_spmatrix_uint_get(hgraph->t,k,j)==hgraph1[k][j]);
    }
  }
  printf("\t \t OK\n");
  free_graph(hgraph);
}

static void test__torus_graph(void){
  printf("%s", __func__);
  struct graph_t* torus = graph_init(9, TORUS);
  for(int k = 0; k<9; k++){
    for(int j = 0; j<9; j++){
      assert(gsl_spmatrix_uint_get(torus->t,k,j)==torus1[k][j]);
    }
  }
  printf("\t OK\n");
  free_graph(torus);
}

static void test_forbidden (void){
  printf("%s", __func__);
  struct move_t move1={.c=1};

  struct graph_t * graph = graph_init(9, SQUARE);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2[2]={no_color_forbidden,no_color_forbidden};
  
  update__forbidden(graph,colors,0,forbidden1);
  assert(CharNotIn('Y',forbidden1[0].t));
  assert(CharNotIn('R',forbidden1[0].t));
  
  printf("\t OK\n");
  free_colors(colors);
  free_graph(graph);
}


static void test_forbidden_after_spread (void) {
  printf("%s", __func__);
  struct move_t move1={.c=1};

  struct graph_t * graph = graph_init(9, SQUARE);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2statique[2]={no_color_forbidden,no_color_forbidden};
 
  update__forbidden(graph,colors,0,forbidden1);
  assert(CharNotIn('Y',forbidden1[0].t));
  assert(CharNotIn('R',forbidden1[0].t));

  spread__colors(graph,move1,0,forbidden1, forbidden2statique, colors);
  update__forbidden(graph,colors,0,forbidden1);
  assert(CharNotIn('Y',forbidden1[0].t));
  assert(CharNotIn('G',forbidden1[0].t));
  assert(CharNotIn('O',forbidden1[0].t));
  
  printf("\t OK\n");
  free_colors(colors);
  free_graph(graph);
}




static void test_spread_square (void) {
  printf("%s", __func__);
  struct move_t move1={.c=1};

  struct graph_t * graph = graph_init(9, SQUARE);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2[2]={no_color_forbidden,no_color_forbidden};
 

  assert(colors[0] == 0);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);

  spread__colors(graph,move1,0,forbidden1, forbidden2, colors);


  assert(colors[0] == 1);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);
   
  printf("\t OK\n");
  
  free_colors(colors);
  free_graph(graph);
}


static void test_spread_donut (void) {
  printf("%s", __func__);
  struct move_t move1={.c=1};

  struct graph_t * graph = graph_init(9, DONUT);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2[2]={no_color_forbidden,no_color_forbidden};
 
  assert(colors[0] == 0);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == -1);
  assert(colors[5] == 4);
  assert(colors[6] == 5);
  assert(colors[7] == 6);
  assert(colors[8] == 7);

  spread__colors(graph,move1,0,forbidden1, forbidden2, colors);


  assert(colors[0] == 1);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == -1);
  assert(colors[5] == 4);
  assert(colors[6] == 5);
  assert(colors[7] == 6);
  assert(colors[8] == 7);
   
  printf("\t OK\n");
  
  free_colors(colors);
  free_graph(graph);
}


static void test_spread_hgraph (void) {
  printf("%s", __func__);
  struct move_t move1={.c=1};

  struct graph_t * graph = graph_init(9, HGRAPH);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2[2]={no_color_forbidden,no_color_forbidden};
 
  assert(colors[0] == 0);
  assert(colors[1] == -1);
  assert(colors[2] == 1);
  assert(colors[3] == 2);
  assert(colors[4] == 3);
  assert(colors[5] == 4);
  assert(colors[6] == 5);
  assert(colors[7] == -1);
  assert(colors[8] == 6);

  spread__colors(graph,move1,0,forbidden1, forbidden2, colors);

  assert(colors[0] == 1);
  assert(colors[1] == -1);
  assert(colors[2] == 1);
  assert(colors[3] == 2);
  assert(colors[4] == 3);
  assert(colors[5] == 4);
  assert(colors[6] == 5);
  assert(colors[7] == -1);
  assert(colors[8] == 6);

   
  printf("\t OK\n");
  
  free_colors(colors);
  free_graph(graph);
}



static void test_spread_torus (void) {
  printf("%s", __func__);
  struct move_t move1={.c=1};

  struct graph_t * graph = graph_init(9, TORUS);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2[2]={no_color_forbidden,no_color_forbidden};

  assert(colors[0] == 0);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);
  spread__colors(graph,move1,0,forbidden1, forbidden2, colors);

  assert(colors[0] == 1);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);
  
  printf("\t OK\n");  
  
  free_colors(colors);
  free_graph(graph);
}


static void test_multiple_spreads (void) {
  printf("%s", __func__);
  struct move_t move1={.c=1};
  struct move_t move2={.c=2};
  struct move_t move3={.c=3};
  struct move_t move5={.c=5};

  struct graph_t * graph = graph_init(9, SQUARE);
  graph_compressed_init(graph);
  enum color_t *colors=colors_init(graph,CYCLIQUE,MAX_COLOR);
  struct color_set_t no_color_forbidden;
  for (int i=0;i<MAX_COLOR;i++){
    no_color_forbidden.t[i]='N';
  }
  struct color_set_t forbidden1[2]={no_color_forbidden,no_color_forbidden};
  struct color_set_t forbidden2[2]={no_color_forbidden,no_color_forbidden};
 

  assert(colors[0] == 0);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);
  update__forbidden(graph,colors,0,forbidden1);
  spread__colors(graph,move1,0,forbidden1, forbidden2, colors);


  assert(colors[0] == 1);
  assert(colors[1] == 1);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);
   
  update__forbidden(graph,colors,0,forbidden1);
  spread__colors(graph,move2,0,forbidden1, forbidden2, colors);


  assert(colors[0] == 2);
  assert(colors[1] == 2);
  assert(colors[2] == 2);
  assert(colors[3] == 3);
  assert(colors[4] == 4);
  assert(colors[5] == 5);
  assert(colors[6] == 6);
  assert(colors[7] == 7);
  assert(colors[8] == 0);
  
  printf("\t OK\n");
  
  free_colors(colors);
  free_graph(graph);
}


struct move_t moves[8] = {{.c=0}, {.c=1}, {.c=2}, {.c=3}, {.c=4}, {.c=5}, {.c=6}, {.c=7}};
struct color_set_t forbidden1[2]={{'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'},{'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'}};
struct color_set_t forbidden2[2]={{'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'},{'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N'}};

void test_get_neighbors() {
  printf("%s", __func__);

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

  printf("\t OK\n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_player0() {
  printf("%s", __func__);
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

  printf("\t OK\n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_player0_v2() {
  printf("%s", __func__);

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
  printf("\t OK\n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_player0_v3() {
  printf("%s", __func__);
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

  printf("\t OK\n");

  free_colors(colors);
  free_graph(graph);
}

void test_get_Ctab_neighbours_player1() {
  printf("%s", __func__);
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
  printf("\t OK \n");

}

int main() {
    printf("===%s===\n", __FILE__);

    test__square_graph();
    test__hgraph();
    test__donut_graph();
    test__torus_graph();
    test_get_neighbors();
    test_spread_square();
    test_spread_donut();
    test_spread_hgraph();
    test_spread_torus();
    test_forbidden();
    test_forbidden_after_spread();
    test_multiple_spreads();
    test_get_Ctab_neighbours_player0();
    test_get_Ctab_neighbours_player0_v2();
    test_get_Ctab_neighbours_player0_v3();
    test_get_Ctab_neighbours_player1();

    printf("===%s TESTS PASSED===\n", __FILE__);

  return 0;
}

