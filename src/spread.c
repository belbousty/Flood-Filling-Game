#include "spread.h"


int NotIn(enum color_t color, enum color_t carray[MAX_COLOR]){
  for(int k = 0; k < MAX_COLOR; k++){
    if(carray[k] == color){
      return 0;
    }
  }
  return 1;
}

int CharNotIn(char x, char tab[]){
  int k = 0;
  while(k < 8){
    if(tab[k]==x)
      return 0;
    k++;
  }
  return 1;
}

void init__neighbors(int tab[]){
  for(int k =0; k<MAX_NEIGHBORS; k++){
    tab[k]=-1;
  }
}

int not__visited(int pos, int grey[]){
  return grey[pos]==0;
}

void change__color(enum color_t* colors, int position, enum color_t new){
  *(colors+position)=new;
}

void visit__and_color(struct graph_t* grid, struct move_t color, int position, enum color_t old, enum color_t* colors){
  int neighbors[MAX_NEIGHBORS]={-1,-1,-1,-1};
  get_neighbors(grid, neighbors, position);
  for(int k =0; k<MAX_NEIGHBORS; k++){
    if(neighbors[k]!=-1 && get__color(colors, neighbors[k])==old){
      change__color(colors, neighbors[k], color.c);
      visit__and_color(grid, color, neighbors[k], old, colors);
    }
    else if(neighbors[k]!=-1 && get__color(colors, neighbors[k])!=old){
      ;
    }
  }
}

int spread__colors(struct graph_t* grid, struct move_t color, int player, struct color_set_t forbidden[], struct color_set_t forbidden2[], enum color_t* colors){
  if(color.c==NO_COLOR) //The player decides to pass his turn 
    return 1;
  for(int k =0; k<MAX_COLOR; k++){
    if(color_to_string(color.c)[0]==forbidden[player].t[k] || color_to_string(color.c)[0]==forbidden2[player].t[k]){
      return 0;    }  }
  int position = grid->positions[player];
  enum color_t initial_color = get__color(colors, position);
  change__color(colors, position, color.c);
  visit__and_color(grid, color, position, initial_color, colors);
  return 1;
}

void calculate__score(struct graph_t* graph, enum color_t* colors, int position, int* score, enum color_t old, int grey[]){
  int neighbors[MAX_NEIGHBORS] = {-1, -1, -1, -1};
  get_neighbors(graph, neighbors, position);
  for(int i = 0; i<MAX_NEIGHBORS; i++){
    if(neighbors[i] != -1 && get__color(colors, neighbors[i])==old && not__visited(neighbors[i], grey)){
	grey[neighbors[i]]=1;
	(*score)++;
	calculate__score(graph, colors, neighbors[i], score, old, grey);
    }
    }
}

int score__of_player(struct graph_t* graph, enum color_t* colors, int player){
  int score = 0;
  int position = graph->positions[player];
  enum color_t oldc = colors[position];
  int grey[graph->num_vertices];
  for(int k = 0; k<graph->num_vertices; k++){
    grey[k]=0;
  }
  calculate__score(graph, colors, position, &score, oldc, grey);
  return (score==0)?1:score;
}

char EnumToChar(enum color_t color){
  return color_to_string(color)[0];
}

void update__forbidden(struct graph_t* graph, enum color_t* colors, int player, struct color_set_t forbidden2[]){
  for(int k = 0; k<MAX_COLOR; k++){
    forbidden2[player].t[k] = '-';
  }
  int position = graph->positions[player];
  int count = 0;
  enum color_t allcolors[MAX_COLOR] = {0, 1, 2, 3, 4, 5, 6, 7};
  enum color_t oldcolor = colors[position];
  int vertices = graph->num_vertices;

  enum color_t NeighboringColors[MAX_COLOR];
  for(int k = 0; k<MAX_COLOR; k++){
    NeighboringColors[k] = 0;
  }

  int grey[graph->num_vertices+1]; 

  for(int k = 0; k<graph->num_vertices; k++){
    grey[k]=0;
  }
  grey[0] = SENTINEL;
  get_Ctab_neighbors(graph, colors, grey, 0, oldcolor, NeighboringColors, position);
  for(int k = 0; k<MAX_COLOR; k++){
    if(NeighboringColors[k]==0){
      forbidden2[player].t[count] = EnumToChar(k);
      count++;
    }
  }
  if(areConnected(graph, colors) && CharNotIn(EnumToChar(colors[graph->positions[(player+1)%2]]), forbidden2[player].t)){
    forbidden2[player].t[count]=EnumToChar(colors[graph->positions[(player+1)%2]]);
  }
}

void get_adjascent(struct graph_t* g, enum color_t* colors, int position, int related[], int *amount, int grey[], enum color_t oldcolor){
  int neighbors[4] = {-1, -1, -1, -1};
  get_neighbors(g, neighbors, position);
  for(int k = 0; k<4; k++){
    if(neighbors[k]!=-1 && get__color(colors, neighbors[k])==oldcolor && not__visited(neighbors[k], grey)){
      related[*amount]=neighbors[k];
      grey[neighbors[k]]=1;
      (*amount)++;
      get_adjascent(g,colors,neighbors[k],related,amount,grey,oldcolor);
      }
  }
}
     
void relatedComponentSmart(struct graph_t* g, enum color_t* colors, int position, int related[]){
  enum color_t oldcolor = colors[position];
  related[0]=position;
  int amount = 1;
  int grey[g->num_vertices+1];
  for(int k = 0; k < g->num_vertices; k++){
    grey[k]=0;
  }
  grey[position]=1;
  get_adjascent(g,colors,position,related,&amount,grey,oldcolor);
}

int connectionexists(struct graph_t* g, int related1[], int related2[]){
  int neighbors[4];
  for(int k = 0; k<g->num_vertices; k++){
    if(related1[k]==-1){
      break;
    }
    else
    {
      for (int i=0;i<4;i++){
        neighbors[i]=0;
      }
      get_neighbors(g, neighbors,related1[k]);
      for(int j = 0; j<g->num_vertices; j++){
        if (related2[j]==-1){
          break;
        }
        else
        {
          for (int i=0;i<4;i++)
          {
            if (neighbors[i]==related2[j])
              return 1;
          }
        }  
      }
    }

  }
  return 0;
}

int areConnected(struct graph_t* g, enum color_t* colors){
  int related1[g->num_vertices];
  int related2[g->num_vertices];
  for(int k = 0; k<g->num_vertices; k++){
    related1[k]=-1;
    related2[k]=-1;
  }
  relatedComponentSmart(g, colors, g->positions[0], related1);
  relatedComponentSmart(g, colors, g->positions[1], related2);
  return connectionexists(g, related1, related2);
}

struct move_t available_move(char forbidden[],char forbidden2[]){
  struct move_t move = {.c = NO_COLOR};
  enum color_t tab[MAX_COLOR];
  int count  = 0;
  for (int i = 0; i < MAX_COLOR; i++){
    if (CharNotIn(EnumToChar(i),forbidden) && CharNotIn(EnumToChar(i),forbidden2)){
      tab[count] = i;
      count ++;
    }
  }
  if (count > 0){
    int j = rand()%count;
    move.c = tab[j];
  }
  return move;
}

int Depth(int tableau[],int size){
  int acc=0;
  for (int i=0;i<size;i++){
    if (tableau[i]!=-1){
      ++acc;
    }
  }
  return acc;
}

void colorsNotInForbidden(struct color_set_t forbidden,int tab[]){
  for (int i=0;i<MAX_COLOR;i++){
    tab[i]=0;
  }
  for (int i=0;i<MAX_COLOR;i++){  
      if (CharNotIn(EnumToChar(i),forbidden.t)){
        tab[i]=1;
      }
  } 
}