#include <stdio.h>
#include <stdlib.h>
#include "bj.h"

int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];		//cards that currently the players hold
int cardSum[N_MAX_USER];							//sum of the cards
int n_user;										//number of users
int roundIndex;								//
int bet[N_MAX_USER];								//current betting 
int dollar[N_MAX_USER];							//dollars that each player has
int cardcnt[N_MAX_USER];							//


// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(turn) {
	int temp, j; 
	int sum = 0;
	for(j=0; j < cardcnt[turn]; j++){
			temp = getCardNum(cardhold[turn][j]);
			sum += temp;
	}
	cardSum[turn] = sum;
	return sum;
}

int checkResult() {
	int i;
	printf("-------------------- ROUND %d result ---------------------\n", roundIndex);
	for (i=0; i < n_user; i++){
		if(i==0)
			printf(" -> your result : ");
		else
			printf(" -> player%d''s result : ", i);
			
		if (cardSum[i] < cardSum[n_user]){
			printf("lose! ");
			dollar[i] -= bet[i];
		}
		else if (cardSum[i] > 21){
			printf("lose due to overflow! ");
			dollar[i] -= bet[i];
		}
		else 
			printf("win! ");
			
		if (dollar[i] < 0)
			dollar[i] = 0;
			
		printf("(sum : %d) --> $%d\n", cardSum[i], dollar[i]);
	}
}

int checkWinner() {
	int i, max = -100, winner;
	for (i=0; i <= n_user; i++){
		if (max < cardSum[i]){
			max = cardSum[i];
			winner = i;
		}
	}
	printf("Game End! Your money : $%d, players'' money : ", dollar[0]);
	for(i=1; i<n_user; i++)
		printf("$%d", dollar[i]);
	printf("\n\n");
	
	if (winner == 0){
		printf("You win");
	}
	else {
		printf("player %d''s win", winner);
	}
	return winner;
}

