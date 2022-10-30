#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../src/graph_coloring.h"



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

int main(void){
  printf("%s\n", __FILE__);
  test__square_graph();
  test__hgraph();
  test__donut_graph();
  test__torus_graph();
  return 0;
}
