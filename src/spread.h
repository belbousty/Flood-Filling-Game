#ifndef _SPREAD_H
#define _SPREAD_H

#include<stdio.h>
#include<string.h>
#include "graph_coloring.h"
#include "strategies.h" 
#include <math.h>

#define MAX_NEIGHBORS 4 
#define SENTINEL -1

/*
  -Takes in argument an array of 4 integers and fills it wih -1's
*/

void init__neighbors(int tab[]);


/* 
   -Takes in argument an array of colors and a position
   -Returns the color of that position in the array of colors
*/

enum color_t get__color(enum color_t* colors, int position) ;

/*
-Takes in argument a graph, a move, an id referring to a player (either 0 or 1), an array of forbidden color sets for each player and an array of colors
-Extracts from the color array the color of the starting position and calls "visit__and_color" on it
-Returns:    - The new score of the player (>=1), if the chosen color was spread successfully
             - 0 if the color is forbidden
*/

int spread__colors(struct graph_t*, struct move_t, int, struct color_set_t forbidden[NUM_PLAYERS],struct color_set_t forbidden2[NUM_PLAYERS], enum color_t*);



/*Takes in argument a graph, a move, an int referring to a cell a color, an array of colors, an array of booleans and an accumulator
Remark: Recursive function that applies the in-depth browsing to the graph starting from a position and changes the color of the cells that need to be changed. (Adjacency + color suitability)  
*/

void visit__and_color(struct graph_t* grid, struct move_t color, int position, enum color_t old, enum color_t* colors);


/*
  -Takes in argument a graph, an array of colors and an int referring to a player (either 0 or 1)
  -Returns the score of the player
 */
int score__of_player(struct graph_t* graph, enum color_t* colors, int player);

/*
  -Takes in argument a graph, an array of colors, a position, a pointer to an accumulator(defined in score__of_player), the color of the player and a memory of visiting.
  Remark: This function is recursive, it keeps updating the accumulator through iterations.
*/
void calculate__score(struct graph_t* graph, enum color_t* colors, int position, int* score, enum color_t old, int grey[]);

/* 
   -Takes in argument a graph, an array of colors that defines the grid of the game, the id of the player, an array of forbidden colors for both players
   -Updates the array of forbidden colors of the player
*/

void update__forbidden(struct graph_t* graph, enum color_t* colors, int player, struct color_set_t forbidden[]);

/* 
   -Takes in argument a color as an enum
   -Returns the first letter of that color as a char
*/

char EnumToChar(enum color_t color);

/* 
   -Takes in argument a graph, an array of colors, the position of the player, and an array of ints
   -Fills the array with the indexes of the cells that belong to the player
*/

void relatedComponentSmart(struct graph_t* g, enum color_t* colors, int position, int related[]);

/* 
   -Takes in argument the graph, two int arrays
   -Returns 1 if one of the elements of the 2nd array is a neighbor of one of the elements of the 1st array, returns 0 otherwise
*/

int connectionexists(struct graph_t* g, int related1[], int related2[]);

/* 
   -Takes in argument the graph, and an array of colors
   -Returns 1 if the areas of both the players are connecting, returns 0 otherwise
*/

int areConnected(struct graph_t* g, enum color_t* colors);

/* 
   -Takes in argument a char and a string whose length is greater or equal to 8
   -Returns 0 if the string contains the char, otherwise returns 1
*/

int CharNotIn(char x, char tab[]);

/* 
   -Takes in argument the forbidden colors
   -Returns a random color which is not in the forbidden colors given in entry
*/

struct move_t available_move(char forbidden[],char forbidden2[]);

/* 
   -Takes in argument an array and its size
   -Returns the number of elements that are different from -1
*/

int Depth(int tableau[],int size);


/* 
   -Takes in argument an array of forbidden colors for the player and an array of colors tab
   -Updates the array tab with elements that doesn't belong to the forbidden
*/

void colorsNotInForbidden(struct color_set_t forbidden,int tab[]);

#endif

