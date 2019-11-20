#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bj.h"

int cardIndex;
int turn;										//turn of the players
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];		//cards that currently the players hold
int CardTray[N_CARD*N_CARDSET];					//
int bet[N_MAX_USER];							//current betting
int dollar[N_MAX_USER];							//dollars that each player has
int n_user;										//number of users
int cardnum;									//the actual number of the card 
int cardcnt;									//number of cards the player has

//player settiing
int configUser(void) {
	int i;
	while(1){
		printf("Input the number of the players(MAX : 5) : ");
		scanf("%d", &n_user); 
		if ((n_user > 0) && (n_user <= N_MAX_USER)){
			break;
		}
		else 
			printf("unappropriate number. input again.\n");
	}
	return n_user;
}

//betting
int betDollar(void) {
	int mybet, i = 0;
	printf("\n------------------------BETTING STEP--------------------------\n");
	printf(" -> your betting (total : $%d): ", dollar[0]);
	scanf("%d", &mybet);
	bet[i] = mybet;
	srand((unsigned int)time(NULL));
	for(i=1; i < n_user; i++){
		bet[i] = (rand()%5)+1;
		printf(" -> player%d bets $%d (out of $%d)\n", i, bet[i], dollar[i]);
	}
	return 0;
}

//mix the card sets and put in the array 			use pointer
int mixCardTray(void) {
	int i, j, temp, num;
	
	for(i=0; i<(N_CARDSET*N_CARD); i++){
		CardTray[i] = i;
	}
	srand((unsigned int)time(NULL));
	for(j=0; j<(N_CARDSET*N_CARD); j++){
		num = rand()%(N_CARDSET*N_CARD-j)+j;
		temp = CardTray[j];
		CardTray[j] = CardTray[num];
		CardTray[num] = temp;
	}
	
	printf("  --> Card is mixed and put into the tray\n");
	return 0;
}
