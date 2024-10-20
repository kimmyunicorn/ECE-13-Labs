// Standard libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif



double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Tangent(double operand);
double Round(double operand)



void CalculatorRun(void)
{
    
    char operator;
    double operand1;
    double operand2;
    double result;
    
    printf("\n\nWelcome to Ian's & Kimmy's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);
    printf("\nPlease enter an operator ( + - * / m a c f t q r): ");
    scanf("%c", &operator);
    
    printf("\nEnter number 1: ");
    scanf("%lf", &operand1);
    
    printf("\nEnter number 2: ");
    scanf("%lf", &operand2);
    
    while (1);
}



//Below is the addition function

  double Add(double operand1, double operand2);
  {
   return (operand1 + operand2);
  }
 


//Below is the subtraction function
  
 double Subtract(double operand1, double operand2);
  {
   return (operand1 - operand2);
 }






//Below is the multiplication function

  double Multiply(double operand1, double operand2);
  {
   return (operand1 * operand2);
  }



//Below is the division function
  
  double Divide(double operand1, double operand2)
  {
   return (operand1 / operand2);
  }





//Below is the Absolute Value function

double AbsoluteValue(double operand);
{
    if (num < 0)
        return -num;
    else
        return num;
}


//Below is the main program for the absolute value function

double AbsoluteValue(double operand);

printf("Enter a number: ");
scanf("%d", &num);

abs_value = absolute(num);

printf("Absolute value: %d\n", abs_value);


  
//Below is the Fahrenheit to Celsius function
  double FahrenheitToCelsius(double operand);
  {
      return (fahrenheit - 32) * 5/9;
  }
  
  
//Below is the main program for Fahrenheit to Celsius function
  
  printf("Enter temperature in Fahrenheit: ");
  scanf("%lf", &fahrenheit);
  
  celsius = FahrenheitToCelsius(fahrenheit);
  printf("%.2lf Fahrenheit is equal to %.2lf Celsius\n", fahrenheit, celsius);
  
  
  
  
//Below is the Celsius to Fahrenheit function
  
  double CelsiusToFahrenheit(double operand);
  {
      return (celsius * 9/5) +32
  }
  
  
  //Below is the main value for Celsius to Fahrenheit function
  double celsius, fahrenheit;
  
  printf("\n Enter Temperature in Celsius: ");
  scanf("%lf", &celsius);
  
  fahrenheit = CelsiusToFahrenheit(celsius);
  printf("%.2f Celsius is equal to %.2f Fahrenheit\n", celsius, fahrenheit);
  
  





/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/

//Below is the tan function
  double Tangent(double operand);
  {
      double radians = degrees * (M_PI / 180.00);
      return tan(radians);
  }
  
  
//Below is the main program for the tan function
  double degrees, result;
  
  printf("Enter angle in degrees: ");
  scanf("%lf", &degrees);
  
  result = Tangent(degrees);
  printf("Tangent of %.2f degrees is %.2f\n", degrees, result);

  
  
//Below is the round function
  double Round(double operand)
  {
      if (num -(int)num >=0.5)
          return (int)num + 1;
      else
          return (int) num;
  }
  
  
//Below is the main programff for the round function
  printf("Enter a number: ");
  scanf("%lf", &num);
  
  rounded_num = custom_round(num);
  printf("Rounded number: %.Of\n", Round);
  
  







