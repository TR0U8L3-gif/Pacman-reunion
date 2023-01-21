#include "animation.h"
#include "../lcd/lcd.h"

void menuAnimation(char animationCounter, char animationCounterLast){
    if(animationCounter != animationCounterLast){
        switch (animationCounter%4)
        {
            case 0: 
                sendString("1: PLAY      ", 1, 0);
            break;
            case 1:

                sendString("2: AUTHORS   ", 1, 0);
            break;
            case 2:
                sendString("3: RULES     ", 1, 0);
            break;
            case 3:
                sendString("4: MAX SCORES", 1, 0);
            break;
        }
    }
}

void authorsAnimation(char animationCounter, char animationCounterLast){
  if(animationCounter != animationCounterLast){
        switch (animationCounter%4)
        {
            case 1:
                sendString("Radoslaw   ", 0, 0);
                sendString("Sienkiewicz", 1, 0);
            break;
            case 2:
                sendString("Jan        ", 0, 0);
                sendString("Rydzewski  ", 1, 0);
            break;
            case 3:
                sendString("Kamil      ", 0, 0);
                sendString("Trofimczuk ", 1, 0);
            break;
            default:
                sendString("PAC-AUTHORS", 0, 0);
                sendString("           ", 1, 0);
            break;
        }
    }
}

void rulesAnimation(char animationCounter, char animationCounterLast){
    if(animationCounter != animationCounterLast){
        switch (animationCounter%5)
        {
            case 1:
                sendString("Use buttons 3,4 ", 0, 0);
                sendString("to move up, down", 1, 0);
            break;
            case 2:
                sendString("To get score    ", 0, 0);
                sendString("catch points (", 1, 0);
                sendChar(12); 
                sendChar(')');
            break;
            case 3:
                sendString("To power'up (", 0, 0);
                sendChar(13); 
                sendChar(')');
                sendChar(' ');
                sendString("use 2 and eat ", 1, 0);
                sendChar(9);
                sendChar(' ');
            break;
            case 4:
                sendString("Try not to die  ", 0, 0);
                sendString("and have fun!!! ", 1, 0);
            break;
            default:
                sendString("PAC-RULES       ", 0, 0);
                sendString("                ", 1, 0);
            break;
        }
    }
}

void scoreAnimation(char animationCounter, char animationCounterLast, unsigned short int maxScores[3]){
    if(animationCounter != animationCounterLast){
        switch (animationCounter%3)
        {
            case 0:
                sendString("EASY:        ",1,0);
                sendPoints(maxScores[0],1,5);
            break;
            case 1:
                sendString("MEDIUM:       ",1,0);
                sendPoints(maxScores[1],1,7);
            break;
            case 2:
                sendString("HARD:         ",1,0);
                sendPoints(maxScores[2],1,5);
            break;
        }
    }
}

void levelAnimation(char animationCounter, char animationCounterLast){
    if(animationCounter != animationCounterLast){
        switch (animationCounter%4)
        {
            case 1:
                sendString("2: MEDIUM  ", 1, 0);
            break;
            case 2:
                sendString("3: HARD    ", 1, 0);
            break;
            case 3:
                sendString("4: GO BACK ", 1, 0);
            break;
            default:
                sendString("1: EASY    ", 1, 0);
            break;
        }
    }
}
