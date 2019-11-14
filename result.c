#include <stdio.h>
#include <stdlib.h>

#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_CARDSET			1
#define N_CARD				52

int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD], dollar[N_MAX_USER];
int cardSum[N_MAX_USER], bet[N_MAX_USER], cardSum[N_MAX_USER];
int turn, n_user, roundIndex;

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	int temp, j; 
	int num, sum=0;
	for(j=0; cardhold[turn][j]!='0'; j++){
			temp = cardhold[turn][j];
			sum += temp;
	}
		sum = cardSum[turn];
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
	for (i=0; i<=n_user; i++){
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

