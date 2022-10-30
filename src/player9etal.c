#include <stdio.h>
#include "player.h"
#include "strategies.h"

struct graph_t *graph1;
struct graph_t *testspreadgraph;
enum color_t *colors1;
enum color_t *testspreadcolors;
struct color_set_t forbidden1[NUM_PLAYERS];
struct color_set_t dyn_forbidden1[NUM_PLAYERS];
int num;
int depth_iteration;
int id1;
struct move_t *moves_dynamic;
struct move_t *moves_static;


char const *get_player_name()
{
  return("9etal");
}

struct move_t play(struct move_t previous_move) {
  srand(time(0));
  struct move_t move ;
  int bool = 1;
  update__forbidden(graph1,colors1,(id1+1)%2,dyn_forbidden1);
  bool = spread__colors(graph1,previous_move,(id1+1)%2,forbidden1,dyn_forbidden1,colors1);
  update__forbidden(graph1,colors1,id1,dyn_forbidden1);
  int *tab = calloc(8,sizeof(int));
  int *score=malloc(sizeof(int));
  *(score)=0;
  int acc=0;
  if (graph1->num_vertices==36||graph1->num_vertices==6){
    depth_iteration=num;
  }
  if (depth_iteration==-1)
  {
    moves_in_advance(graph1,colors1,num,acc,id1,moves_dynamic,moves_static,dyn_forbidden1,forbidden1,score);
    //printf("le score dans ce cas est %d",*score);
    depth_iteration++;
  }

  update__forbidden(graph1,colors1,id1,dyn_forbidden1);
  if (depth_iteration<num){
    move.c=moves_dynamic[depth_iteration].c;
   // printf("le move est wtf ? :%d",move.c);
    if (CharNotIn(EnumToChar(move.c),dyn_forbidden1[id1].t))
    { 
      //printf("encore ici?");
      bool=spread__colors(graph1,move,id1,forbidden1,dyn_forbidden1,colors1);
      depth_iteration++;
      free(score);
      free(tab);
      return(move);
    }
    else{
      depth_iteration=num+1;
    }
  }




  enum color_t color = chose_color(graph1,
				   colors1,
				   colors1[graph1->positions[id1]],
				   graph1->positions[id1],
				   tab,
				   CLEVER,
				   dyn_forbidden1);;
  int indexe = 1;
  
 
  move.c=color;

  if (!CharNotIn(EnumToChar(color),dyn_forbidden1[id1].t)){
    tab[move.c]=0;
    for (int i = 0; i < 8; i++) {
      if (tab[i] >= tab[color]) {
        color = i;
      }
    }
    if (tab[color]==0)
      color=NO_COLOR;
  }
  move.c = color;

  if(bool == 1){
    bool=spread__colors(graph1,move,id1,forbidden1,dyn_forbidden1,colors1);
  }
  free(score);
  free(tab);
  return move;
}

void finalize()
{
  free_graph(graph1);
  free_colors(colors1);
  free(moves_dynamic);
  free(moves_static);
}

void initialize(size_t id, struct graph_t* graph,enum color_t* colors,
                struct color_set_t forbidden[NUM_PLAYERS])
{
  id1 = id;
  graph1 =  graph;
  colors1 = colors;
  depth_iteration=-1;
  num=5;
  if (id==1)
  {
    num=4;
  }
  moves_dynamic=malloc(num*sizeof(struct move_t));
  moves_static=malloc(num*sizeof(struct move_t));

  for (int i=0;i<num;i++)
  {
      moves_dynamic[i].c=NO_COLOR;
      moves_static[i].c=NO_COLOR;
  }  
  for (int i = 0; i < NUM_PLAYERS; i++){
    for (int j = 0; j < MAX_COLOR; j++){
      forbidden1[i].t[j] = forbidden[i].t[j];
    }
  }
  for (int i = 0; i < NUM_PLAYERS; i++){
    for (int j = 0; j < MAX_COLOR; j++){
      dyn_forbidden1[i].t[j] = forbidden[i].t[j];
    }
  } 
}
