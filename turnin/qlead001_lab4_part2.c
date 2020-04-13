/*	Author: Quinn Leader qlead001@ucr.edu
 *      Partner(s) Name: NA
 *	Lab Section: 026
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: Counter
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

unsigned char count;

void Tick() {
    switch(state) { // Transitions
        case Start:
            state = Press;
            count = 7;
            break;
        case Press:
            if (PINA&0x03) {
                state = Release;
                if ((PINA&0x03) == 0x03) count = 0;
                else if ((PINA&0x03) == 0x01 && count < 9) count++;
                else if ((PINA&0x03) == 0x02 && count > 0) count--;
            }
            break;
        case Release:
            if ((PINA&0x03) == 0x03) count = 0;
            if (!(PINA&0x03)) state = Press;
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

    PORTC = count;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
