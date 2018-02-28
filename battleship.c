/* Include libraries */

#include "battleship.h"

/* function and procedure */

/* Initialization of the chessboard with empty cases and create some boats */
void initialization_player (struct player *p){
	int column, line ;
    // Browse the table to initialize by a empty case (without boat)
	for( column = 0; column < MAX; column++){
		for( line = 0; line < MAX; line++){
			p->chessboard [line][column] = EMPTY_CASE;
        }
    }
    // Initialization of boats' size
    int index = 0;
    p->boat[index++] = 4;
    p->boat[index++] = 3;
    p->boat[index++] = 3;
    p->boat[index++] = 2;

}

bool verificate_put_boat (struct player p, int column, int line, int len, int axe){
    /* player *p is the player which want to ask the question. column and line are the coordinate of the initial position.
      The objective is to verify if cases where we want put the boat are free */

	int course; /* course is the variable used to move in the table */
	bool valid = true;
    switch(axe){
        case(VERTICAL):
            for(course = 0; (course < len)&&(line + course < MAX); course++){
                /* Stop condition: we course the lenght of the boat and the case is still inside of the chessboard */
                if ((p.chessboard[line + course][column] & EMPTY_CASE) != EMPTY_CASE)
                    valid = false;
            }
        break;
                
        case(HORIZONTAL):
            for(course = 0; (course < len)&&(column + course < MAX); course++){
                /* Stop condition: we course the lenght of the boat and the case is still inside of the chessboard  */
                if ((p.chessboard[line][column + course] & EMPTY_CASE) != EMPTY_CASE)
                    valid = false;
            }
            break;
                
        default:
            printf("The suggest axe is wrong \n");
            valid = false;
    }
	return(valid);
}


bool put_boat(struct player *p, int column, int line, int bat, int axe)
{
    
    /* Verification of the position of the boat */
	bool valid = verificate_put_boat(*p, column, line, p->boat[bat], axe);
	int course;

	if (!valid){
		printf("Impossible to put the boat here.\n");
	}
	else{
        /* Positioning the boat on the chessboard */
		switch(axe){
            case(VERTICAL):
                /* Browse the chessboard in length */
                for(course = 0; (course < p->boat[bat])&&(line + course <= MAX); course++){
                    p->chessboard[line][column + course] = FILLED_CASE; /* on place le boat sur la case, donc on passe le 5ème bit à 1 */
                }
                break; /* on retourne 1 pour dire qu'on a posé le boat */
                
            case(HORIZONTAL):
                for(course = 0; (course < p->boat[bat])&&(column + course <=MAX); course++){
                    /* Browse the chessboard in width */
                    p->chessboard[line + course][column] = FILLED_CASE;
                }
                break;
            
            default:
                printf("The suggest axe is wrong \n");
                valid = false;
			}
	}
    return(valid);
}

void display(struct player p, int mask)
/* The mask means 1 (view opponent) or 0 (view player) */
{
    int column, line;
    
     /* The top left case needs to be empty */
	printf(" ");
     /* We display the number of columns */
	for (column = 0; column < MAX; column++){
        printf("%d",column);
	}
	printf("\n");
    
	for(line = 0; line < MAX; line++){
        /* We display the number of the line */
		printf("%d",line);
        
		for(column = 0; column < MAX; column++){
            /* View opponent */
			if (mask == OPPONENT_VIEW){
				if ((p.chessboard[line][column] & TESTED_CASE) == TESTED_CASE)
                    /* Display 'X' indicate a tested case */
					printf("~");
                else if((p.chessboard[line][column] & TOUCHED_CASE) == TOUCHED_CASE)
                    printf("B");
				else
                    /* Display '-' indicate a case non already tested */
					printf("-");
			}
            /* View player */
			else{
				if ((p.chessboard[line][column] & EMPTY_CASE) == EMPTY_CASE)
                    /* Display '~' if the case is empty */
					printf("~");
				else
                    /* Display 'B' if there are a piece of boat on the case */
					printf("B");
			}
		}
    printf("\n");
	}
}

int play_gun(struct player *p, int column, int line)
{
    /* There are no boat on the case */
	if ((p->chessboard[column][line] & EMPTY_CASE) == EMPTY_CASE){
        p->chessboard[column][line] = TESTED_CASE;
        printf("Shoot in the water !\n");
		return 0;
	}
	else{
        /* There are no boat anymore on this case */
		p->chessboard[line][column] = TOUCHED_CASE;
        
        /* We decrease the lenght of boat on the target case */
		p->boat[p->chessboard[line][column] & TOUCHED_CASE]--;
        printf("%x",p->boat[p->chessboard[line][column] & TOUCHED_CASE]);
        /* We look if the lenght of boat is present on the touched case is more highest than 0 */
        if (p->boat[p->chessboard[line][column] & TOUCHED_CASE] > 0){
            printf("You have touched a boat !\n");
			return 1;
        }
        else{
            printf("You have flowed a boat !\n");
			return 2;
        }
	}
}

