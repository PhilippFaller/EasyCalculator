#include "at89s8253.h"

#define IN P0
#define OUT_H P1
#define OUT_L P2

#define FAIL 0xFFFF

#define DIVIDE 0x10
#define MULTIPLY 0x11
#define SUBTRACT 0x12
#define ADD 0x13
#define CLEAR 0x14
#define EQUALS 0x15
#define NO_OPERATION 0
#define EMPTY 0xFF

void read();
int calculate();
void show(int parameter);

unsigned char getFromIn();

void reset();

unsigned char leftOperand = 0;
unsigned char operator = 0;
unsigned char rightOperand = 0;

main(){
    while(1){
        read();
        show(calculate());
    }
}

void read(){
    int i;
    for(i = 0; i < 4; i++){
        unsigned char temp = getFromIn();
        if(temp <= 0xF){
            leftOperand <<= 4;
            leftOperand |= temp;
            show(leftOperand);
        }

        else{
            switch(temp){
            case CLEAR: reset();
                	return;
            case EQUALS: operator = NO_OPERATION;
                	return;
            default: 	operator = temp;
            		show(operator);
                	goto secondInput;
            }
        }
    }

    unsigned char temp = getFromIn();
    show(temp);
    if(temp > 0xF && temp < CLEAR) operator = temp;
    else {
	leftOperand = FAIL;
	operator = NO_OPERATION;
	return;
    }

secondInput:for(i = 0; i < 4; i++){
        unsigned char temp = getFromIn();
        if(temp <= 0xF){
            rightOperand <<= 4;
            rightOperand |= temp;
            show(rightOperand);
        }
        else{
            switch(temp){
            case CLEAR: reset();
                return;
            case EQUALS: return;
            default: leftOperand = FAIL; 
                     operator = NO_OPERATION;
                     return;
            }
        }
    }
}

int calculate(){
    switch(operator){
    case DIVIDE: return leftOperand / rightOperand;
    case MULTIPLY: return leftOperand * rightOperand;
    case SUBTRACT: return leftOperand - rightOperand;
    case ADD: return leftOperand + rightOperand;
    case NO_OPERATION: return leftOperand;
    default: //Fehler
        return FAIL;
    }
}

void show(int parameter){
    OUT_L = parameter;
    OUT_H = parameter >> 8;
}

unsigned char getFromIn(){
    while(IN == EMPTY);
    unsigned char temp = IN;
    while(IN == temp);
    return temp;
}

void reset(){
    leftOperand = 0;
    operator = 0;
    rightOperand = 0;
}