#include <stdio.h>
#include <stdlib.h>
#include "bj.h"

int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];		//cards that currently the players hold
int cardSum[N_MAX_USER];						//sum of the cards
int n_user;										//number of users
int roundIndex;									//
int CardIndex;
int bet[N_MAX_USER];							//current betting 
int dollar[N_MAX_USER];							//dollars that each player has
int cardcnt;									//


// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult(turn, cardcnt) {
	int temp, j; 
	
	if (cardcnt > 2){
		temp = getCardNum(turn, cardhold[turn][cardcnt-1]);
		cardSum[turn] += temp;
	}
	
	if (cardSum[turn] > 21){
		if(turn < n_user){
			printf("DEAD (sum : %d)", cardSum[turn]);
			dollar[turn] -= bet[turn];
			printf("  -->  -$%d ($%d)\n", bet[turn], dollar[turn]);
		}
		return 1;
	}
	else if (cardSum[turn] == 21){
			printf("::: Blackjack!!!");
			if (turn < n_user){
			dollar[turn] += 2*bet[turn];
			printf(" -->  +$%d ($%d)\n", 2*bet[turn], dollar[turn]);
		}
		return 1;
	}
	else
		return 0;
}

int checkResult() {
	int i;
	printf("\n-------------------- ROUND %d result ---------------------\n", roundIndex);
	for (i=0; i < n_user; i++){
		if(i==0)
			printf("\n -> your result : ");
		else
			printf("\n -> player%d's result : ", i);
			
	
		if (cardSum[i] > 21)
			printf("lose due to overflow! ");
		else if(cardSum[i] == 21){
			printf("win!");
		}
		else if (cardSum[n_user] > 21){
			dollar[i] = dollar[i] + bet[i];
			printf("win!");
	}
		else if (cardSum[i] < cardSum[n_user]){
			dollar[i] = dollar[i] - bet[i];
			printf("lose!  ");
		}
		else {
			dollar[i] = dollar[i] + bet[i];
			printf("win! ");
		}
			
		if (dollar[i] < 0)
			dollar[i] = 0;
			
		printf("(sum : %d) --> $%d\n", cardSum[i], dollar[i]);
	}
}

int checkWinner() {
	int i, max = -100, winner;
	for (i=0; i < n_user; i++){
		if (max < dollar[i]){
			max = dollar[i];
			winner = i;
		}
	}
	printf("\nGame End! Your money : $%d, players' money : ", dollar[0]);
	for(i=1; i<n_user; i++)
		printf("$%d  ", dollar[i]);
	printf("\n\n");
	
	if (winner == 0){
		printf("\nYou win!!!\n");
	}
	else {
		printf("\nplayer %d's win!!!\n", winner);
	}
	return winner;
}

