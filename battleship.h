

/* Include libraries */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>

/* variable define */

#define MAX        8 /* max size of columns/lines in the chessboard */
#define MAXBOAT    4 /* max number of boat */
#define VERTICAL   0 /* vertical axe of a boat */
#define HORIZONTAL 1 /* horizontal axe of a boat  */

#define OPPONENT_VIEW 1 /* opponent view mode */

#define EMPTY_CASE   0x10 /* empty case on the chessboard */
#define TESTED_CASE  0x80 /* tested case on the chessboard */
#define FILLED_CASE  0x00 /* case with a boat */
#define TOUCHED_CASE 0x0F /* case touched by the opponent */

/* structure declarations */
struct player{
    
    unsigned char boat [MAXBOAT];
    /* represente the number of cases not smitten for each boat*/
    
    unsigned char chessboard [MAX][MAX];
    /* bit of strong weight indicate if the case is already tested
       4 bit of low weight indicate the number of boat
       The 5th bit indicate if a boat is present or not on the case. */
};

/* prototypes */

/* Initialization of the chessboard with empty cases and create some boats */
void initialization_player (struct player *p);

/* Verification of the suggest position's boat */
bool verificate_put_boat (struct player p, int column, int line, int len,int axe);

/* Put boat on the chessboard */
bool put_boat(struct player *p, int column, int line, int bat, int axe);

/* display the chessboard */
void display(struct player p, int mask);

/* shoot on a case to play and try to find a boat */
int play_gun(struct player *p, int column, int line);



