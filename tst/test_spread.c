#include<stdio.h>
#include <assert.h>
#include<string.h>
#include <math.h>
#include "../src/strategies.h"
#define MAX_NEIGHBORS 4 



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




int main() {

  printf("====STARTING FILE TESTS : %s ==== \n",__FILE__);
  test_spread_square();
  test_spread_donut();
  test_spread_hgraph();
  test_spread_torus();
  test_forbidden();
  test_forbidden_after_spread();
  test_multiple_spreads();
  printf("\n");
  printf("====TESTS PASSED====\n");
  
  return 0;
}
