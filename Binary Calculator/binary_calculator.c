/*
Author: Jesus Minjares
        Master of Science in Computer Engineering
Date:   03/01/21
*/
#include "binary_calculator.h"
/*set operand inputs*/
void operand_button_setup(uint8_t button){
    /*Pull-up configuration*/
    P1->DIR &= ~button; //set as input
    //clear select registers
    P1->SEL0 &= ~button;
    P1->SEL1 &= ~button;
    P1->REN |= button; //enable resistor
    P1->OUT |= button; //set for Pull-up
}
/*set BCD inputs*/
void bcd_button_setup(uint8_t buttons){
    /*Pull-up configuration*/
    P2->DIR &= ~buttons; //set as input
    P2->OUT |= buttons; //set for Pull-up
    //clear select registers
    P2->SEL0 &= ~buttons;
    P2->SEL1 &= ~buttons;
    P2->REN |= buttons; //enable resistor
}
/*set Enter input*/
void enter_button_setup(uint8_t button){
    /*Pull-up configuration*/
    P3->DIR &= ~button; //set as input
    //clear select registers
    P3->SEL0 &= ~button;
    P3->SEL1 &= ~button;
    P3->REN |= button;//enable resistor
    P3->OUT |= button; //set for Pull-up
}
/*read operand input*/
uint8_t read_operand(void){
    delay_ms(500); //delay .5 seconds
    uint8_t result = P1->IN; //store IN register into result
    uint8_t value = 0;
    if((result & SW1) == 0) value +=1;
    if((result & SW2) == 0) value +=2;
    return value;
}
/*read BCD input*/
uint8_t read_bcd(void){
    delay_ms(500);
    uint8_t result = P2->IN; //store IN register into result
    uint8_t value = 0;
    //check each bit and store into value
    if((result & B0)== 0)  value += 1;
    if((result & B1) == 0) value += 2;
    if((result & B2) == 0) value += 4;
    if((result & B3) == 0) value += 8;
    return value;
}
/*read enter input*/
uint8_t read_enter(void){
    delay_ms(500);
    uint8_t result = P3->IN; //store IN register into result
    //check if enter has been pressed
    if((result & ENTER) == 0) return 1;
    else return 0;
}
/*get char operand*/
char get_operand(uint8_t button){
    char op; //local variable to store operand
    //use a switch case and store into op
    switch(button){
        case 0: op ='+'; break;
        case 1: op = '-'; break;
        case 2: op = 'x'; break;
        case 3: op ='/'; break;
        default: op ='e'; break;
    }
    return op; //return operand as a char
}
/*get num1 operand num2 as a float*/
float get_result(uint8_t num1, uint8_t num2, char op){
    float ans =0; //store ans
    //check operand and do its operation
    switch(op){
        case '+': ans = num1 + num2; break;
        case '-': ans = num1 - num2; break;
        case 'x': ans = num1 * num2; break;
        case '/': ans = num1 / num2; break;
        default: ans = -1; break;
    }
    return ans; //return ans
}
/*wait until enter has been pressed*/
void wait(void){
    //read until enter has been
    while(read_enter() == 0){
        P6->OUT = LED; //display button unpressed with LED
    }
    P6->OUT ^= LED; //toggle led
    delay_ms(1000); //wait 1 second
}
/*initialize external LED*/
void led_init(uint8_t led){
    P6->DIR |= led; //set as output
    P6->OUT &= ~led; //set LEDs as off
    /*Clear Select Pins*/
    P6->SEL0 &= ~led;
    P6->SEL1 &= ~led;
}
/*display to LCD*/
void display(uint8_t number1, uint8_t number2, uint8_t operand){
    lcdClear();// clear LCD
    char buffer[2][16]; //temp buffer
    if(number1 > 0x09 || number2 > 0x09){ //check for boundary
        //store strings into buffer
        sprintf(buffer[0], "%d%c%d",number1, get_operand(operand), number2);
        sprintf(buffer[1], "ERROR!!");
    }
    else{
        //get result and store it
        float result = get_result(number1,number2,get_operand(operand));
        //store strings into buffer
        sprintf(buffer[0], "%d%c%d",number1, get_operand(operand), number2);
        sprintf(buffer[1], "= %.4f", result);
    }
    //display to LCD
    lcdSetText(buffer[0],0,0);
    lcdSetText(buffer[1],0,1);
    delay_ms(2000); //2 second delay
}
