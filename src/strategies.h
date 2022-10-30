#ifndef _STRATEGIES_H_
#define _STRATEGIES_H_

#include <stdlib.h>
#include "spread.h"


enum status_t {
	       STUPID=0, INTERMEDIATE=5, CLEVER=10
};


/*
 * Input : array of matrix colors, and position 
 * RETURNS position's color
*/
enum color_t get__color(enum color_t* colors, int position) ;

/*
 * INPUT :  Tab to fill, neighbors_colors and it's length 
 * PRECEDURE : count the occurrence of i-th color and put its value in Tab[i] 
*/
void count_colors(int Tab[], enum color_t *neighbours_colors, unsigned int length) ;


/*
 * INPUT: an array
 * OUTPUT: returns the index with the maximum value for Tab
 */
int get_max(int Tab[]);


/* 
 * INPUT: grid, array of neighbors(4 elements) and the position.
 * PROCEDURE: fill `neighbors` with `position`'s neighbors.  
 */
void get_neighbors(struct graph_t *graph, int neighbors[], int position);

/* 
 * INPUT: array of Grey elements (neighbors_passed) and a the position.
 * neighbors_passed should end with SENTINEL.
 * OUTPUT: returns if `neighbor` is in neighbors passed.
 */
int passed(int *neighbors_passed, int neighbor);


/* 
 * INPUT: array of Grey elements (neighbors_passed) and a the position.
 * neighbors_passed should start  with SENTINEL.
 * PROCEDURE: adds `neighbor` exactly before SENTINEL in `neighbors_passed`
 */
void add_to_passed(int *neighbors_passed, int neighbor);


/* 
 * INPUT: grid, 
          array of colors,
	  neighbors_passed is an array with one element SENTINEL,
	  i  should always be equal to 0 (for recursive purpose),
	  player_color, 
	  color_neighbors an array with MAX_COLOR elements.
	  Position of the player.
 * 
 * PROCEDURE: fills color_neighbors with occurence of each color around the border of a player.
 */

void get_Ctab_neighbors(struct graph_t *graph,
			enum color_t* colors,
			int *neighbors_passed,
			int i,
			enum color_t player_color,
			enum color_t color_neighbors[],
		       int position);
			   
void get_Ctab_neighbors_smart(struct graph_t *graph,
			enum color_t* colors,
			int *neighbors_passed,
			int i,
			enum color_t player_color,
			enum color_t color_neighbors[],
		       int position);

enum color_t chose_color(struct graph_t *graph,
			 enum color_t* colors,
			 int player_color,
			 int position,
			 int *tab,
			 enum status_t intelligence,
			 struct color_set_t forbidden[]);


/* 
 * INPUT: grid, 
          array of colors,
		  num is the number of moves we're spreading ahead,
	  id  ,
	  acc is an accumulator that gives information on which depth of moves we're at,
	  moves_dynamic is an array of moves of size num, 
	  moves_static is an array of moves of size num,
	  forbidden1,
	  forbidden2,
	  Position of the player.
	  score,
 * 
 * PROCEDURE: fills moves_dynamic with the best possible moves that will give the player the best score after a number num of moves.
 */


void moves_in_advance(struct graph_t * graph,
  enum color_t * colors,
  int num,
  int acc,
  int id,
  struct move_t moves_dynamic[],
  struct move_t moves_static[],
  struct color_set_t forbidden1[],
  struct color_set_t forbidden2[],
  int *score);


#endif // _STRATEGIES_H_
