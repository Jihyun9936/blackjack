#include <stdio.h>
#include <stdlib.h>
#include "bj.h"

int cardcnt[N_MAX_USER];							//
int n_user;										//number of users
int cardIndex;
int dollar[N_MAX_USER];							//dollars that each player has
int turn;										//turn of the players
int cardIndex = N_CARD*N_CARDSET;
int roundIndex = 1;								//
int cardSum[N_MAX_USER];							//sum of the cards
int gameEnd;


int main() {
	int max_user;
	int i = 0;
	

	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	for(i=0; i < n_user; i++)
		dollar[i] = 50;
		
	for(i=0; i < n_user; i++)
		cardcnt[i] = 0;
				
	//2. card tray
	mixCardTray();

	//Game start --------
	do {
		
		printf("----------------Round %d (CardIndex : %d)----------------\n", roundIndex, cardIndex);
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME START --------------------------\n");
		
		//each player's turn
		for (turn = 0; turn <= n_user; turn++) //each player
		{
			if(turn == 0)
				printf(">>>my turn! -------------------\n");
			else if (turn == n_user)
				printf(">>>server turn! ---------------\n");
			else
				printf(">>>player %d turn! ------------\n", turn);
				
			printf("\n");
			
			getAction(turn);
			do {	printUserCardStatus(n_user); //print current card status
					calcStepResult(turn); //check the card status ::: 
					getAction(turn); //GO? STOP? ::: 
					//check if the turn ends or not
			} while (getAction(turn) == 0); //do until the player dies or player says stop
			printUserCardStatus(n_user, cardcnt[turn]);
			i++;
		}
		printf("[[[[[[[[server result is ... %d]]]]]]]]\n", cardSum[n_user]);
		
		//result
		checkResult();
		roundIndex++;
	} while ((cardIndex >= 0) || (cardSum[i] == 0));
	
	checkWinner();
	
	
	return 0;
}
