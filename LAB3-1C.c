#include "msp430fg4618.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//reference function
unsigned char INCHAR_UART(void){
do{
}while ((IFG2&0x01)==0);
return (UCA0RXBUF);
}

//reference function
void Init_UART(void){
    P2SEL=0x30;
    UCA0CTL0=0;
    UCA0CTL1= 0x41;
    UCA0BR1=0;
    UCA0BR0=3;
    UCA0MCTL=0x06;
    UCA0STAT=0;
    UCA0CTL1=0x40;
    IE2=0;
}


//reference function
void OUTA_UART(unsigned char A){
	do{
    }while ((IFG2&0x02)==0);
    UCA0TXBUF =A;
}

//string input function
void send(char* str)
{
    unsigned int i = 0;
    while (str[i] != 0x00) 	//while string not equal null character
    {
        OUTA_UART(str[i]); 	//calling UART function to print
        i++;
    }
    OUTA_UART(0x0A);		//new line
    OUTA_UART(0x0D);		//carriage return
}

//function containing logic for conversion of ASCII char to 8-bit binary number
char convert(char a)
{
    char b = ' ';					//empty character for result
    if (a >= 0x30 && a <= 0x39)		//boolean logic; if character is 0-9
        b = a - 0x30;				//8-bit binary result to be printed in hyperterminal as the corresponding character

    if (a >= 0x41 && a <=0x46)		//boolean logic; if character is A-F
        b = a - 0x37;               //8-but binary result to be printed as character

    return b;						//return result
}

int main (void)
{
    WDTCTL = WDTPW + WDTHOLD; //stop watchdog timer
    Init_UART();              //initalize UART

    for(;;)
    {
        char character1, character2;
        character1 = INCHAR_UART(); 	//character input1 from user
        OUTA_UART(character1);      	//echo input1 to UART
        character2 = INCHAR_UART(); 	//character input2 from user
        OUTA_UART(character2);      	//echo input2 to UART
        OUTA_UART(0x0A);				//new line
        OUTA_UART(0x0D);				//carriage return

        character1 = convert(character1); 		//calling logic function to convert ASCII to binary value
        character2 = convert(character2); 		//calling logic function to convert ASCII to binary value
        character1 *= 16;              	  		//shift binary left by 4
        character1 = character1+character2;  	//add binary values of each letter
        OUTA_UART((int)character1);    			//output converted ASCII character to hyperterminal

        OUTA_UART(0x0A);						//new line
        OUTA_UART(0x0D);						//carriage return

    }

}
