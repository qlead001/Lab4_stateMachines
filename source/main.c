/*	Author: Quinn Leader qlead001@ucr.edu
 *      Partner(s) Name: NA
 *	Lab Section: 026
 *	Assignment: Lab 4  Exercise 5
 *	Exercise Description: Combination toggle lock door with longer combo
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {
    Start,
    Press,
    Release,
} state;

typedef enum Buttons {
    X = 1,
    Y = 2,
    ENTER = 4,
} Buttons;

unsigned char unlocked, comboIndex;
const unsigned char comboLen = 4;
const Buttons combo[] = {ENTER, X, Y, X};

void Tick() {
    switch(state) { // Transitions
        case Start:
            state = Release;
            unlocked = 0;
            comboIndex = 0;
            break;
        case Press:
            if (PINA&0x87) {
                state = Release;
                if ((PINA&0x87) == 0x80) unlocked = 0;
                else if ((PINA&0x07) == combo[comboIndex]) {
                    if (++comboIndex >= comboLen) {
                        unlocked = !unlocked;
                        comboIndex = 0;
                    }
                }
                else if ((PINA&0x07) == ENTER) comboIndex = 1;
                else comboIndex = 0;
            }
            break;
        case Release:
            if (!(PINA&0x87)) state = Press;
            break;
        default:
            state = Start;
            break;
    } // Transitions

    switch(state) { // State Actions
        case Start:
            break;
        default:
            break;
    } // State Actions

    PORTB = unlocked;
    PORTC = state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
