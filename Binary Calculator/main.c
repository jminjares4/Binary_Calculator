/*
Author: Jesus Minjares
        Master of Science in Computer Engineering
Date:   03/01/21
*/
#include "msp.h"
#include "binary_calculator.h"

void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	/*initialize LCD*/
	lcdInit();
	lcdClear();
	/*Display Message*/
	lcdSetText("Go Miners!!!",0,0);
   	 delay_ms(5000); //delay for 5 seconds

   	 led_init(LED); //intialize LED
    	/*Initialize Inputs for Operand, BCD and Enter buttons*/
	operand_button_setup(SW1|SW2);
	bcd_button_setup(B0|B1|B2|B3);
	enter_button_setup(ENTER);

	/*local variables to store input data*/
	uint8_t operand = 0, number1 = 0, number2 = 0, enter = 0;

	while(1){
	    wait(); //wait for enter to be pressed
	    //read BCD, store in number and display in LCD
	    number1  = read_bcd(); lcdSetInt(number1, 0,0);
	    wait();
	    //read operand, store in operand and display in LCD
	    operand = read_operand(); lcdSetText((char*)get_operand(operand), 2,0);
	    wait();
	    //read BCD for number 2
        number2  = read_bcd(); lcdSetInt(number2,3,0);
        //read enter
        enter = read_enter();
        if(enter){
           lcdSetText("enter",8,0); //display enter
           display(number1, number2, operand); //display output to LCD
        }
        else{
            wait();
            lcdSetText("enter",8,0); //display enter
            display(number1, number2, operand); //display output to LCD
        }
        number1 = number2 = operand = enter = 0; //set all varaibles to 0
	}
}
