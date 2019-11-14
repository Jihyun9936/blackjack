#include <stdio.h>
#include <stdlib.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30

//play yard information
extern int roundIndex = 1;								//
extern int turn;										//turn of the players
extern int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];		//cards that currently the players hold
extern int cardSum[N_MAX_USER];							//sum of the cards
extern int bet[N_MAX_USER];								//current betting 
extern int dollar[N_MAX_USER];							//dollars that each player has
extern int cardnum;										//the actual number of the card 
extern int cardcnt[N_MAX_USER];							//
extern int cardSum[N_MAX_USER];							//
extern int gameEnd = -1; 								//game end flag
extern int n_user;										//number of users
extern int cardIndex = N_CARDSET * N_CARD - 1;


int main() {
	int max_user;
	int i = 0;
	

	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
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
		for (turn=0; turn < n_user+1; turn++) //each player
		{
			if(turn == 0)
				printf(">>>my turn! -------------------\n");
			else if (turn == n_user)
				printf(">>>server turn! ---------------\n");
			else
				printf(">>>player %d turn! ------------\n", turn);
			while (gameEnd == 0) //do until the player dies or player says stop
			{
				printUserCardStatus(); //print current card status
				calcStepResult(); //check the card status ::: 
				getAction(); //GO? STOP? ::: 
				//check if the turn ends or not
			}
			printf("[[[[[[[[server result is ... %d]]]]]]]]\n", cardSum[n_user]);
			i++;
		}
		
		//result
		checkResult();
		roundIndex++;
	} while ((cardIndex >= 0) || (cardSum[i] == 0));
	
	checkWinner();
	
	
	return 0;
}
