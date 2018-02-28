/**
 Battleship game : Project for the school ESISAR GRENOBLE INP
 
 @author :Chaput Marine
 created in march 2014
 updated in february 2018 (translation program in english)
 **/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "bataillenavale.h"

/* declarations */
int num_boat;

/* position of the boat valid = 1
   position of the boat not valid = 0 */
bool valid;

int main(void)
{
    /* Initialization */
    int column, line, axe ;
    int life = 1;
	int actual_player = 1;
   	struct player player1, player2;
	initialization_player(&player1);
	initialization_player(&player2);
    
    /* Put boats on the chessboard */
	num_boat = 0;

    /* Loop for each boat */
	while (num_boat < MAXBOAT)
	{
        /* Display the appropriate chessboard and the boat which need to be put */
		if (actual_player == 1)
		{
			display(player1, 0);
			printf(" It is the turn of the player 1 to put the boat on %d cases \n", player1.boat[num_boat]);
		}
		else
		{
			display(player2, 0);    /* affiche l'échiquier de player2 */
			printf("It is the turn of the player 2 to put the boat on %d cases \n", player2.boat[num_boat]);
		}
        
        /* Choose the axe of the boat */
        while(true){

            printf("Choose the axe of the boat. \n 0 = horizontal, 1 = vertical : ");
            scanf("%d", &axe);
            
            /* Case : axe choosen doesn't exist */
            if (axe != 0 && axe != 1){
                printf("! impossible axe !\n");
                continue;
            }
            else
                break;
        }
    
        /* Choose coordinate for the top of the boat */
        while(true){
            
            printf("Number of the column : ");
            scanf("%d", &column);
            printf("Number of the line : ");
            scanf("%d", &line);
            
            /* Case : coordinate choosen doesn't exist */
            if (line < 0 || line >= MAX || column < 0 || column >= MAX){
                printf("! non-existent case !\n");
                printf("Choose again the coordinate of the boat \n");
                continue;
            }
            else
                break;
            system("clear");
        }
    
        /* Verification of the position and put the boat on the chessboard */
		if (actual_player == 1)
			valid = put_boat(&player1, column, line, num_boat, axe);
		else
			valid = put_boat(&player2, column, line, num_boat, axe);
        
		if (valid) /* If the position has been checked and the boat put */
			num_boat++;
        printf(" %d", num_boat);
        /* If player 1 has finished to put boats, it is the turn of the player 2 */
		if (num_boat == MAXBOAT && actual_player == 1)
		{
            /* Initialization */
			num_boat = 0;
            actual_player = 2;
			printf(" It is soon the turn of the player 1 ... \n Validate to continue when you are ready ");
			scanf(" %d", &column);
            /* Clear the screen to avoid the new player
             to see the chessboard on his opponent */
			system("clear");
		}
	} /* When the number of boat is reached for the both players,
       we can move on in the actual game */

    /* Game continue until one of the player die by lack of boats */
	actual_player = 1;

	while (life > 0)
	{
        printf(" It is the turn of player %d ! \n Validate to continue when you are ready. \n", actual_player);
        scanf(" %d", &column);
        system("clear");
        printf("Player %d : \n", actual_player );
        
        /* Display the chessboard of the actual player with the player view */
        display(player1,(actual_player-1));
        /* Display the chessboard of the opponent with the opponent view */
        display(player2, actual_player%2);

        /* Choose coordinate for the shoot */
        while(true){
            printf("Where do you want shoot ? \n");
            printf("Number of column : ");
            scanf("%d", &column);
            printf("Number of line : ");
            scanf("%d", &line);
            /* Case : coordinate choosen doesn't exist */
            if (line < 0 || line >= MAX || column < 0 || column >= MAX){
                printf("! non-existent case !\n");
                continue;
            }
            else
                break;
        }
        
		system("clear");

        /* Shoot in the coordinate of the opponent's chessboard choosen previously */
		if (actual_player == 1)
			play_gun(&player2,  column, line);
		else
			play_gun(&player1,  column, line);

        /* Change the actual player */
        actual_player = actual_player % 2 + 1;
 
        /* Check if the player is dead by looking if he has still boat on his chessboard */
		life = 0;
		for (column = 0; column < MAXBOAT; column++)
		{ 
			if (actual_player == 1)
				life += player1.boat[column];
			else
				life += player2.boat[column];
		} 
	}
    printf("The player %d has won !\n", (actual_player % 2 + 1));
	return EXIT_SUCCESS;
}

