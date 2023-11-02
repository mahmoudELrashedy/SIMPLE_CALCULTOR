/*
 * calculator.c
 *
 * Created: 11/1/2023 1:12:32 PM
 * Author : M
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "LCD_LIB.h"
#include "get_pressed_key.h"
int main(void)
{
	LCD_Init() ;
	
	 int x = 0  ;                            //first number
	 int z = 0  ;                           //second number
	 int result = 0 ;
	 unsigned char y = 0 ;                 //carries only one digit or sign 
	 unsigned char n = 0 ;                //carries only one digit or sign
	 
	int count  ;                        //counter to check if the loop is working properly
	char buffer[20] ;                   
	

	while (1)
	{
		count = 0 ;
		
		// this loop is entered in case you entered a digit and will break if you entered a sign
		while (((y =  Get_Pressed_key())|| (y==0)) && (y!='+') && (y!='-') && (y!='*') && (y!='/') && (y != '=')  )
		{
			
			 if (y == 'R')       // restart the calculator if (ON/c) is pressed
			 {
				 LCD_Command(CLEAR_LCD) ;                         
				 x = 0 ;
				 z = 0 ;
				 continue;
			 }
			 
			
			itoa(y,buffer,10) ;
			LCD_String(buffer) ;
			_delay_ms(300) ;
			x =  x * 10 ;        // first number calculation  by adding each digit with respect to its weight
			x = x + y  ;
		count ++ ; 
		}
		
		if (count == 0 )       // if the previous loop hasn't been entered so the previous loop wasn't entered because the first entered value was a sign so it gives a syntax error
		{
			LCD_String(" SYNTAX ERROR ! ") ;
			_delay_ms(100) ; 
			continue; 
		}
		
			
		 LCD_Char(y) ;      // print the sign after exiting the loop
		_delay_ms(300) ;
		
	
	// scanning the second number 
		while ( (y != '=') && ((n = Get_Pressed_key ())|| (n==0))  && (n != '=')  )
		{
			
			itoa(n,buffer,10) ;
			LCD_String(buffer) ; 
			z = z * 10 ;
			z = z + n  ;
			
			_delay_ms(300) ;

		}
		
		LCD_Char(n) ;  // print the '=' sign
		_delay_ms(300) ;
	
	
		switch  (y)
		{
			case '+':
			result = x+z ;
			break;
			
			case '-':
			result = x-z ;
			break;
			
			case '*':
			result = x*z ;
			break;
			
			case '/':
			
			if(z==0) // dividing by zero will give a logical error
			{
				LCD_Command(CLEAR_LCD) ; 
				LCD_String("LOGICAL ERROR !");
			}
			
			else
			{
			result = x/z ;
			}
			break;
			
			case '=':
			result = x ;
			break;
			
		}

			itoa(result,buffer,10) ; // print the result
			LCD_String(buffer) ;
			
	
		
	}
}

