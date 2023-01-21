#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "engine.h"
#include "animation.h"
#include "../lcd/lcd.h"
#include "../lcd/portyLcd.h"
#include "../input/input.h"

char gameState = 0;
char initializedState = 6;
char gameLevel = 0;

time_t realTime = 0;
time_t delayTime = 0; 

char animationCounter = 0;
char animationCounterLast = 125;

char health = 0;
char powerUp = 0;
char maxPlayerValues = 0;

char playerPosition = 1;
char isPowerActivated = 0;
unsigned short int distance = 0;
unsigned short int powerDistance = 0;
unsigned short int tickRate = 0;
unsigned short int playerScore = 0;
unsigned short int maxScores[3] = {0,	0,	0}; 

unsigned char map[2][VISIBLE_MAP_DISTANCE] = {{0},{0}};

void resetValues(void){
	initializedState = gameState;
	delayTime = realTime;
	animationCounterLast = 125;
	animationCounter = 0;
	clearDisplay();
}

void startGame(){
	if(playerScore >= 9999 || distance >= 65530){
		delayx1s(2);
		sendString("Well done you...", 0, 0);
		sendString("beat the game...", 1, 0);
		delayx1s(30);
		gameState = 6;
	}
	if(tickRate >= 10 - (gameLevel + 2)){
		sendHealth(health); 
		sendPowerUp(powerUp);
		tickRate = 0;
		sendPoints(playerScore,0,0);
		distance++;
		if(powerUp < maxPlayerValues && distance%(10 - (2 * gameLevel)) == 0 && isPowerActivated == 0){
			powerUp++;
			sendPowerUp(powerUp);
		}
		if(isPowerActivated && distance > powerDistance){
			isPowerActivated = 0;
			sendString(" ",playerPosition?0:1,13);
			sendCmd((playerPosition?DD_RAM_ADDR2:DD_RAM_ADDR)+ 13);
			sendChar(isPowerActivated? 3 : 2);
		}
		switch (map[playerPosition][0])
		{
		case 1:
			playerScore++;
			sendPoints(playerScore,0,0);
		break;
		case 2:
			if(isPowerActivated){
				playerScore += 10;
				sendPoints(playerScore,0,0);
			} else {
				health -= 1;
				sendHealth(health);
			}
		break;
		}
        for(char j = 0; j < VISIBLE_MAP_DISTANCE - 1; j++){
            map[0][j] = map[0][j+1];
			sendCmd(DD_RAM_ADDR + 12 - j);
			if(map[0][j] == 2){
				sendChar(isPowerActivated? 1: 0);
			} else if(map[0][j] == 1) {
				sendChar(4);
			} else {
				sendChar(' ');
			}
			map[1][j] = map[1][j+1];
			sendCmd(DD_RAM_ADDR2 + 12 - j);
			if(map[1][j] == 2){
				sendChar(isPowerActivated? 1: 0);
			} else if(map[1][j] == 1) {
				sendChar(4);
			} else {
				sendChar(' ');
			}
        }
		char fate = rand()%10 + 1;
		map[0][VISIBLE_MAP_DISTANCE-1] = fate%3==0? 2 :(fate%2 == 0? 1: 0);
		if(map[0][VISIBLE_MAP_DISTANCE-1] == 2){
			map[1][VISIBLE_MAP_DISTANCE-1] = fate>4 ? 1 : 0;
		} else if(map[0][VISIBLE_MAP_DISTANCE-1] == 1) {
			map[1][VISIBLE_MAP_DISTANCE-1] = fate>6 ? 2 : 0;
		} else {
			map[1][VISIBLE_MAP_DISTANCE-1] = fate>6 ? 2 : 1;
		}
		if(health<=0){
			delayx1s(2);
			gameState = 6;
		} 
	}
}

void app()
{
	realTime = time(NULL);

	switch(gameState){
		case 0:
			if(gameState != initializedState){
				resetValues();
				sendString("PAC-MENU     ", 0, 0);
			}
			menuAnimation(animationCounter, animationCounterLast);
			if(buttonDown(1)){
				gameState = 4;
			}
			else if (buttonDown(2)){
				gameState = 1;
			}
			else if (buttonDown(3)){
				gameState = 2;
			}
			else if (buttonDown(4)){
				gameState = 3;
			}
		break;
		case 1:
			if(gameState != initializedState){
				resetValues();
			}
			authorsAnimation(animationCounter, animationCounterLast);
			if(buttonDown(4)) gameState = 0;
		break;
		case 2:
			if(gameState != initializedState){
				resetValues();
			}
			rulesAnimation(animationCounter, animationCounterLast);
			if(buttonDown(4)) gameState = 0;
		break;
		case 3:
			if(gameState != initializedState){
				resetValues();
				sendString("PAC-MAX-SCORE", 0, 0);
			}
			scoreAnimation(animationCounter, animationCounterLast, maxScores);
			if(buttonDown(4)) gameState = 0;
		break;
		case 4:
			if(gameState != initializedState){
				resetValues();
				sendString("DIFFICULTY LEVEL", 0, 0);
			}
			levelAnimation(animationCounter, animationCounterLast);
			if(buttonDown(1)){
				gameLevel = 0;
				gameState = 5;
			}
			else if (buttonDown(2)){
				gameLevel = 1;
				gameState = 5;
			}
			else if (buttonDown(3)){
				gameLevel = 2;
				gameState = 5;
			}
			else if (buttonDown(4)){
				gameLevel = 0;
				gameState = 0;
			}
		break;
		case 5:
			if(gameState != initializedState){
				resetValues();
				playerScore = 0;
				distance = 0;
				tickRate = 0;
				maxPlayerValues = 4 - gameLevel; 
				health = maxPlayerValues;
				powerUp = maxPlayerValues;
				srand(time(NULL));
				playerPosition = 1;
				sendString("  ",0,13);
				sendCmd(DD_RAM_ADDR2 + 13);
				sendChar(isPowerActivated? 3 : 2);
				for(char i = 0; i < 3; i++){
				map[0][i] = 0;
				map[1][i] = 0;
				}
				for(char i = 3; i < VISIBLE_MAP_DISTANCE; i++){
					char fate = rand()%10 + 1;
					map[0][i] = fate%3==0? 2 :(fate%2 == 0? 1: 0);
					if(map[0][i] == 2){
						map[1][i] = fate>4 ? 1 : 0;
					} else if(map[0][i] == 1) {
						map[1][i] = fate>6 ? 2 : 0;
					} else {
						map[1][i] = fate>6 ? 2 : 1;
					}
				}
			}
			if (buttonDown(1))gameState = 6;
			if (buttonDown(2) && powerUp>0 && isPowerActivated == 0){
				isPowerActivated = 1;
				powerDistance = distance + 2 * (gameLevel + 2);
				powerUp--;
				sendPowerUp(powerUp);	
				sendString(" ",playerPosition?0:1,13);
				sendCmd((playerPosition?DD_RAM_ADDR2:DD_RAM_ADDR)+ 13);
				sendChar(isPowerActivated? 3 : 2);
			}
			if (buttonDown(3)){
				playerPosition = 0;
				sendString(" ",1,13);
				sendCmd(DD_RAM_ADDR + 13);
				sendChar(isPowerActivated? 3 : 2);
			}
			if (buttonDown(4)){
				playerPosition = 1;
				sendString(" ",0,13);
				sendCmd(DD_RAM_ADDR2 + 13);
				sendChar(isPowerActivated? 3 : 2);
			}
			tickRate++;
			startGame();
		break;
		case 6:
			if(gameState != initializedState){
				resetValues();
				if(maxScores[gameLevel] < playerScore){
					maxScores[gameLevel] = playerScore;
				} 
				sendString("GAME OVER ", 0, 0);
				sendString("YOUR SCORE: ", 1, 0);
				sendPoints(playerScore , 1, 11);
			}
			if(anyButtonDown()) gameState = 0;
		break;
	}
	if(realTime >= delayTime + ((gameState == 2) ? DELAY_5S : DELAY_3S)){
		delayTime = realTime;
		animationCounterLast = animationCounter;
		animationCounter++;
	}
	if(animationCounter >= 125) animationCounter = 0;
}