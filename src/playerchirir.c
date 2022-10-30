#include <stdio.h>
#include "player.h"
#include "strategies.h"

struct graph_t *graph5;
enum color_t *colors5;
struct color_set_t forbidden5[NUM_PLAYERS];
struct color_set_t dyn_forbidden5[NUM_PLAYERS];
int id5;

char const *get_player_name()
{
  return("chirir");
}

struct move_t play(struct move_t previous_move) {
  srand(time(0));
  int bool = 1;
  update__forbidden(graph5,colors5,(id5+1)%2,dyn_forbidden5);
  bool = spread__colors(graph5,previous_move,(id5+1)%2,forbidden5,dyn_forbidden5,colors5);
  update__forbidden(graph5,colors5,id5,dyn_forbidden5);
  int *tab = calloc(8,sizeof(int));
  enum color_t color = chose_color(graph5,
				   colors5,
				   colors5[graph5->positions[id5]],
				   graph5->positions[id5],
				   tab,
				   CLEVER,
				   dyn_forbidden5);;
  int indexe = 1;
  
 
  struct move_t move = {.c = color};


  if (!CharNotIn(EnumToChar(color),dyn_forbidden5[id5].t)){
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
    bool=spread__colors(graph5,move,id5,forbidden5,dyn_forbidden5,colors5);
  }
  free(tab);
  return move;
}

void finalize()
{
  free_graph(graph5);
  free_colors(colors5);
}

void initialize(size_t id, struct graph_t* graph,enum color_t* colors,
                struct color_set_t forbidden[NUM_PLAYERS])
{
  id5 = id;
  graph5 =  graph;
  colors5 = colors;
  for (int i = 0; i < NUM_PLAYERS; i++){
    for (int j = 0; j < MAX_COLOR; j++){
      forbidden5[i].t[j] = forbidden[i].t[j];
    }
  }
  for (int i = 0; i < NUM_PLAYERS; i++){
    for (int j = 0; j < MAX_COLOR; j++){
      dyn_forbidden5[i].t[j] = forbidden[i].t[j];
    }
  } 
}
