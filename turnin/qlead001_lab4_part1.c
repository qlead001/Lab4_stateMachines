/*	Author: Quinn Leader qlead001@ucr.edu
 *      Partner(s) Name: NA
 *	Lab Section: 026
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: Toggle LEDs
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
    LED0,
    LED1,
    Release0,
    Release1,
} state;

void Tick() {
    switch(state) { // Transitions
        case Start:
            state = LED0;
            PORTB = 0x01;
            break;
        case LED0:
            if (!PINA) state = Release0;
            break;
        case LED1:
            if (!PINA) state = Release1;
            break;
        case Release0:
            if (PINA) state = LED1;
            break;
        case Release1:
            if (PINA) state = LED0;
            break;
        default:
            state = Start;
            break;
    } // Transitions

    switch(state) { // State Actions
        case Start:
            break;
        case LED0:
            PORTB = 0x01;
            break;
        case LED1:
            PORTB = 0x02;
            break;
        default:
            break;
    } // State Actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
