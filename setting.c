#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_MAX_USER			5

//card tray object
int CardTray[N_CARDSET*N_CARD];
int dollar[N_MAX_USER];		
int cardIndex;
int n_user;						

//player info


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
	
	for(i=0; i < n_user; i++)
		dollar[i] = 50;
		
	return n_user;
}

//mix the card sets and put in the array
int mixCardTray(void) {
	int i, j, temp, num;
	srand((unsigned int)time(NULL));
	
	for(i=0; i<(N_CARDSET*N_CARD); i++){
		CardTray[i] = i;
	}
	
	for(j=0; j<(N_CARDSET*N_CARD); j++){
		num = rand()%(N_CARDSET*N_CARD-j)+j;
		temp = CardTray[j];
		CardTray[j] = CardTray[num];
		CardTray[num] = temp;
	}
	
	printf("  --> Card is mixed and put into the tray\n");
	return CardTray;
}

//get one card from the tray
int pullCard(void) {
	int card;
	card = CardTray[cardIndex];
	cardIndex--;
	return card;
}
