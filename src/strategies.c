#include "strategies.h"


enum color_t get__color(enum color_t * colors, int position) {
  return colors[position];
}

void count_colors(int Tab[], enum color_t * neighbours_colors, unsigned int length) {
  for (int i = 0; i < MAX_COLOR; i++) {
    for (int j = 0; j < length; j++) {
      if (neighbours_colors[j] == i) {
        Tab[i]++;
      }
    }
  }
}

int get_max(int Tab[]) {
  int k = 0;
  for (int i = 1; i < 8; i++) {
    if (Tab[i] >= Tab[k]) {
      k = i;
    }
  }
  return k;
}

void get_neighbors(struct graph_t * grid, int neighbors[], int position) {
  int count = 0;
  int j = grid -> t -> p[position];
  if (position == grid -> t -> size2 + 1) {
    neighbors[count] = grid -> t -> i[j];
    count;
  } else {
    while (j < grid -> t -> p[position + 1]) {
      neighbors[count] = grid -> t -> i[j];
      j++;
      count++;
    }
  }
  while (count < 4) {
    neighbors[count] = -1;
    count++;
  }
}

int passed(int * neighbors_passed, int neighbor) {
  while ( * neighbors_passed != SENTINEL) {
    if ( * neighbors_passed == neighbor) return 1;
    neighbors_passed++;
  }
  return 0;
}

void add_to_passed(int * neighbors_passed, int neighbor) {
  while ( * neighbors_passed != SENTINEL) {
    neighbors_passed++;
  }
  * neighbors_passed = neighbor;
  neighbors_passed++;
  * neighbors_passed = SENTINEL;
}

void get_Ctab_neighbors(struct graph_t * graph,
  enum color_t * colors,
  int * neighbors_passed,
  int i,
  enum color_t player_color,
  enum color_t color_neighbors[],
  int position) {
  int neighbors[4] = {
    0
  };
  add_to_passed(neighbors_passed, position);
  get_neighbors(graph, neighbors, position);
  for (int k = 0; k < 4; k++) {
    if (neighbors[k] != -1 &&
      get__color(colors, neighbors[k]) != player_color &&
      !passed(neighbors_passed, neighbors[k])) {

      add_to_passed(neighbors_passed, neighbors[k]);
      color_neighbors[get__color(colors, neighbors[k])] = color_neighbors[get__color(colors, neighbors[k])] + 1;
    } else if (neighbors[k] != -1 &&
      get__color(colors, neighbors[k]) == player_color &&
      !passed(neighbors_passed, neighbors[k])) {

      get_Ctab_neighbors(graph, colors, neighbors_passed, i, player_color, color_neighbors, neighbors[k]);
    }
  }
}

void get_Ctab_neighbors_smart(struct graph_t * graph,
  enum color_t * colors,
  int * neighbors_passed,
  int i,
  enum color_t player_color,
  enum color_t color_neighbors[],
  int position) {
  int neighbors[4] = {
    0
  };
  add_to_passed(neighbors_passed, position);
  get_neighbors(graph, neighbors, position);
  for (int k = 0; k < 4; k++) {
    if (neighbors[k] != -1 &&
      get__color(colors, neighbors[k]) != player_color &&
      !passed(neighbors_passed, neighbors[k])) {

      int related[graph -> num_vertices];
      for (int k = 0; k < graph -> num_vertices; k++) {
        related[k] = -1;
      }
      relatedComponentSmart(graph, colors, neighbors[k], related);
      color_neighbors[get__color(colors, neighbors[k])] = color_neighbors[get__color(colors, neighbors[k])] + Depth(related, graph -> num_vertices);
      for (int k = 0; k < graph -> num_vertices; k++) {
        if (related[k] != -1) {
          add_to_passed(neighbors_passed, related[k]);
        }
      }
    } else if (neighbors[k] != -1 &&
      get__color(colors, neighbors[k]) == player_color &&
      !passed(neighbors_passed, neighbors[k])) {

      get_Ctab_neighbors_smart(graph, colors, neighbors_passed, i, player_color, color_neighbors, neighbors[k]);
    }
  }
}


void moves_in_advance(struct graph_t * graph,
  enum color_t * colors,
  int num,
  int acc,
  int id,
  struct move_t moves_dynamic[],
  struct move_t moves_static[],
  struct color_set_t forbidden1[],
  struct color_set_t forbidden2[],
  int *score) 
{
  struct move_t amove;
  struct move_t shallow_copy_moves[num];
  for (int j=0;j<acc;j++){
    shallow_copy_moves[j]=moves_static[j];
  }
  update__forbidden(graph,colors,id,forbidden1);
  enum color_t testspreadcolors[graph->num_vertices];
  int new_score;
  int tab[MAX_COLOR];
  colorsNotInForbidden(forbidden1[id],tab);
  for (int i=0;i<MAX_COLOR;i++){
    if (tab[i]==1) 
      {
        for (int j=0;j<acc;j++){
          shallow_copy_moves[j]=moves_static[j];
        }

        update__forbidden(graph,colors,id,forbidden1);
        for (int k=0;k<graph->num_vertices;k++)
          testspreadcolors[k]=colors[k];
        if (acc<(num-1))
        {
          amove.c=i;
          spread__colors(graph,amove,id,forbidden1,forbidden2,testspreadcolors);
          shallow_copy_moves[acc]=amove;
          moves_in_advance(graph,testspreadcolors,num,acc+1,id,moves_dynamic,shallow_copy_moves,forbidden1,forbidden2,score);
        }
        if (acc==(num-1))
        {
          amove.c=i;
          spread__colors(graph,amove,id,forbidden1,forbidden2,testspreadcolors);
          new_score=score__of_player(graph,testspreadcolors,id); 
          if ((*score)<=new_score)
          {
              for (int j=0;j<acc;j++){
                moves_dynamic[j]=shallow_copy_moves[j];
              }
              moves_dynamic[acc]=amove;
              *score=new_score;
          }
        }
      }
  }
  
}




// add function that doesn't count in the colors inside of the spread. ..


enum color_t chose_color(struct graph_t * graph,
  enum color_t * colors,
  int player_color,
  int position,
  int * tab,
  enum status_t intelligence,
  struct color_set_t forbidden[]) {
  int neighbors_passed[graph -> num_vertices+1];
  enum color_t color = 0;
  neighbors_passed[0] = SENTINEL;
  if (intelligence == STUPID) {
    return rand() % 8;
  }
  if (intelligence == INTERMEDIATE) {
    get_Ctab_neighbors(graph,
      colors,
      neighbors_passed,
      0,
      player_color,
      tab,
      position);
  }
  if (intelligence == CLEVER) {
    get_Ctab_neighbors_smart(graph,
      colors,
      neighbors_passed,
      0,
      player_color,
      tab,
      position);
  }
  for (int i = 1; i < 8; i++) {
    printf("%d ", tab[i]);
    if (tab[i] >= tab[color]) {
      color = i;
    }
  }
  if (tab[color] == 0) {
    return NO_COLOR;
  }
  return color;
}
