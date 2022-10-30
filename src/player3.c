#include <stdio.h>
#include "player.h"
#include "strategies.h"

struct graph_t *graph3;
struct graph_t *testspreadgraph;
enum color_t *colors3;
enum color_t *testspreadcolors;
struct color_set_t forbidden3[NUM_PLAYERS];
struct color_set_t dyn_forbidden3[NUM_PLAYERS];
int num;
int depth_iteration;
int id3;
struct move_t *moves_dynamic;
struct move_t *moves_static;


char const *get_player_name()
{
  return("tachtouch");
}

struct move_t play(struct move_t previous_move) {
  srand(time(0));
  struct move_t move ;
  int bool = 1;
  update__forbidden(graph3,colors3,(id3+1)%2,dyn_forbidden3);
  bool = spread__colors(graph3,previous_move,(id3+1)%2,forbidden3,dyn_forbidden3,colors3);
  update__forbidden(graph3,colors3,id3,dyn_forbidden3);
  int *tab = calloc(8,sizeof(int));
  int *score=malloc(sizeof(int));
  *(score)=0;
  int acc=0;
  if (graph3->num_vertices==36||graph3->num_vertices==6){
    depth_iteration=num;
  }
  if (graph3->num_vertices==12*12||graph3->num_vertices==12*12){
    num=7;
  }
  if (depth_iteration==-1)
  {
    moves_in_advance(graph3,colors3,num,acc,id3,moves_dynamic,moves_static,dyn_forbidden3,forbidden3,score);
    depth_iteration++;
  }

  update__forbidden(graph3,colors3,id3,dyn_forbidden3);
  if (depth_iteration<num){
    move.c=moves_dynamic[depth_iteration].c;
    if (CharNotIn(EnumToChar(move.c),dyn_forbidden3[id3].t))
    { 
      bool=spread__colors(graph3,move,id3,forbidden3,dyn_forbidden3,colors3);
      depth_iteration++;
      free(score);
      free(tab);
      return(move);
    }
    else{
      depth_iteration=num+1;
    }
  }




  enum color_t color = chose_color(graph3,
				   colors3,
				   colors3[graph3->positions[id3]],
				   graph3->positions[id3],
				   tab,
				   CLEVER,
				   dyn_forbidden3);;
  int indexe = 1;
  
 
  move.c=color;

  if (!CharNotIn(EnumToChar(color),dyn_forbidden3[id3].t)){
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
    bool=spread__colors(graph3,move,id3,forbidden3,dyn_forbidden3,colors3);
  }
  free(score);
  free(tab);
  return move;
}

void finalize()
{
  free_graph(graph3);
  free_colors(colors3);
  free(moves_dynamic);
  free(moves_static);
}

void initialize(size_t id, struct graph_t* graph,enum color_t* colors,
                struct color_set_t forbidden[NUM_PLAYERS])
{
  id3 = id;
  graph3 =  graph;
  colors3 = colors;
  depth_iteration=-1;
  num=6;
  if (id==1)
  {
    num=5;
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
      forbidden3[i].t[j] = forbidden[i].t[j];
    }
  }
  for (int i = 0; i < NUM_PLAYERS; i++){
    for (int j = 0; j < MAX_COLOR; j++){
      dyn_forbidden3[i].t[j] = forbidden[i].t[j];
    }
  } 
}
