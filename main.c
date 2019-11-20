#include <stdio.h>
#include <stdlib.h>
#include "bj.h"

int cardcnt;									//number of cards the player has
int n_user;										//number of users
int dollar[N_MAX_USER];							//dollars that each player has
int turn;										//turn of the players
int cardIndex = N_CARD*N_CARDSET-1;
int roundIndex = 1;	
int cardSum[N_MAX_USER];						//sum of the cards
int gameEnd;									//gameEnd flag


int main() {
	int pass;			//
	int doll = 0; 		//
	int j, i = 0;

	//set the number of players
	configUser();

	//Game initialization --------
	//1. players' dollar
	for(i=0; i < n_user; i++)
		dollar[i] = 50;
		
	//2. card tray
	mixCardTray();

	//Game start --------
	do {
		for(i=0; i<=n_user; i++)
			cardSum[i] = 0;				//cardSum setting
		
		printf("\n----------------Round %d (CardIndex : %d)----------------\n", roundIndex, cardIndex+1);
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME START --------------------------\n");
		
		//each player's turn
		for (turn = 0; turn <= n_user; turn++) //each player
		{	
			cardcnt = 2;						//intial num of cards
			
			if(turn == 0)
				printf("\n>>> my turn! -------------------\n");
			else if (turn == n_user)
				printf("\n>>> server turn! ---------------\n");
			else
				printf("\n>>> player %d turn! ------------\n", turn);
			
			printf("\n");
			
			do{	printUserCardStatus(turn); //print current card status	//check the card status :::
				pass = calcStepResult(turn, cardcnt);
				if (pass == 1)
					break;
			} while(getAction(turn) == 0); //do until the player dies or player says stop
		}
		printf("\n[[[[[[[[server result is ... %d]]]]]]]]", cardSum[n_user]);
		if (cardSum[n_user] > 21)
			printf(" --> Overflow!!!\n");
		else
			printf("\n");
		
		//result
		checkResult();
		roundIndex++;
		for (i=0; i<n_user; i++){
			if (dollar[i] != 0)
				continue;
			else{
				doll = 1;
				break;
			}
		}
	} while ((cardIndex > 2*(n_user+1)) && (doll != 1));
	
	checkWinner();
	
	return 0;
}
