/*
Author: Jesus Minjares
        Master of Science in Computer Engineering
Date:   03/01/21
*/
#ifndef BINARY_CALCULATOR_H_
#define BINARY_CALCULATOR_H_
#include "msp.h"
#include "lcdLib_432.h"
/*Macros*/
#define SW1 BIT1
#define SW2 BIT4
#define B0  BIT4
#define B1  BIT5
#define B2  BIT6
#define B3  BIT7
#define ENTER BIT0
#define LED ENTER
/*set operand inputs*/
void operand_button_setup(uint8_t button);
/*set BCD inputs*/
void bcd_button_setup(uint8_t buttons);
/*set Enter input*/
void enter_button_setup(uint8_t button);
/*read operand input*/
uint8_t read_operand(void);
/*read BCD input*/
uint8_t read_bcd(void);
/*read enter input*/
uint8_t read_enter(void);
/*get char operand*/
char get_operand(uint8_t button);
/*get num1 operand num2 as a float*/
float get_result(uint8_t num1, uint8_t num2, char op);
/*wait until enter has been pressed*/
void wait(void);
/*initialize external LED*/
void led_init(uint8_t led);
/*display to LCD*/
void display(uint8_t number1, uint8_t number2, uint8_t operand);
#endif /* BINARY_CALCULATOR_H_ */
