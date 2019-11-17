#include <stdio.h>
#include <stdlib.h>
#include "bj.h"

int n_user;										//number of users 
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];		//cards that currently the players hold
int cardcnt[N_MAX_USER];							//
int turn;										//turn of the players
int cardSum[N_MAX_USER];							//sum of the cards
int gs[N_MAX_USER];								//
int gameEnd;		 								//game end flag
int cardnum;										//the actual number of the card 

//offering initial 2 cards
void offerCards(void) {
	int i;
	printf("-------------------- Card Offering--------------------\n");
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
		cardcnt[i]+=2;
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	cardcnt[n_user]+=2;
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int i, j;
	printf("\n--> server : X ");
	printCard(cardhold[n_user][1]);
	printf("\n--> you    : ");
	for (i=0; i<2; i++)
		printCard(cardhold[0][i]);
	for(i=1; i < n_user; i++){
		printf("\n--> player%d : ", i);
		for (j=0; j<2; j++)
			printCard(cardhold[i][j]);
		printf("\n");
	}
	return;
}

int getAction(int turn) {
	if (turn == 0){
		printf("Action? (0 - go, others - stay) : ");
		scanf("%d", &gs);
	}
	else{
		if (cardSum[turn] < 17)
			gs[turn] = 0;
		else 
			gs[turn] = 1;
	}
	if(gs[turn] == 0){
		cardcnt[turn]++;
		printf("::: GO!\n");
		cardhold[turn][cardcnt[turn]] = pullCard();
		gameEnd = 0;
	}
	else {
		printf("::: STAY!\n");
		
		gameEnd = 1;
	}
	return gameEnd;
}

// cardcnt : 현재 플레이어들이 가지고 있는 카드의 장수 
void printUserCardStatus(int n_user) {
	int i;
	printf("  -> card : ");
	for (i=0; i < cardcnt[turn]; i++){
		printCard(cardhold[turn][i]);
		printf(" ");
	}
	printf("\t ::: "); 
	return;
}

//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {
	int num;
	switch(cardnum % 13){
		case 1 : 
			if (cardSum[turn]+11 <= 21) {
				num = 11; break; }
			else {
				num = 1; break; }
		case 2 : num = 2; break;
		case 3 : num = 3; break;
		case 4 : num = 4; break;
		case 5 : num = 5; break;
		case 6 : num = 6; break;
		case 7 : num = 7; break;
		case 8 : num = 8; break;
		case 9 : num = 9; break;
		default : num = 10;
	}
	return num;
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) {
	switch (cardnum / 13){
		case 0 : printf("HRT"); break;
		case 1 : printf("DIA"); break;
		case 2 : printf("SPD"); break;
		case 3 : printf("CLV"); break;
	}
	switch(cardnum % 13){
		case 1 : printf("A"); break;
		case 2 : case 3 : case 4 : case 5 : case 6 : 
		case 7 : case 8 : case 9 : case 10: printf("%d", cardnum%13); break;
		case 11 : printf("Q"); break;
		case 12 : printf("J"); break;
		case 0 : printf("K"); break;
	}
	printf(" ");
}


