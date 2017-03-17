//Demo program for the "intal" library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.
//This code will execute the exponentiation function only if the power is positive

#include <stdio.h>
#include "intal.h"
#include <stdlib.h>
#include <string.h>

int main(void){
	char ch;
	char *str = (char *)calloc(sizeof(char), 1);
	int len = 0;
	int flag = 0;
	intal *num1 = create_intal();
	intal *num2 = create_intal();
	while((ch = getchar()) && ch != '\n' && (ch == '+' || ch == '-' || ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4'|| ch == '5'|| ch == '6'|| ch == '7'|| ch == '8'|| ch == '9' || '\0')){		//Input taken for num1
		str[len++] = ch;
		str = (char *)realloc(str,sizeof(char)*(len + 1));
	}
	str[len] = '\0';
	read_intal(num1, str);

	str = (char *)realloc(str, sizeof(char));
	str[0] = 0;
	len = 0;
	while((ch = getchar()) && ch != '\n'){		//Input taken for num2
		str[len++] = ch;
		str = (char *)realloc(str,sizeof(char)*(len + 1));
	}
	str[len] = '\0';
	read_intal(num2, str);

	num1 = remove_leading_zeros(num1);
	num2 = remove_leading_zeros(num2);
	
	intal *resultadd = create_intal();		//Intals to store the result
	intal *resultsub = create_intal();
	intal *resultmul = create_intal();
	intal *resultdiv = create_intal();
	intal *resultpow = create_intal();

	resultadd = add_intal(num1, num2);		//addition
	printf("\n\nAddition : ");				//print the results
	print_intal(resultadd);
	resultsub = subtract_intal(num1, num2);	//subtraction
	printf("\n\nSubtraction : ");
	print_intal(resultsub);
	resultmul = multiply_intal(num1, num2);	//multiplication
	printf("\n\nMultiplication : ");
	print_intal(resultmul);
	//printf("\n\nPlease wait while the division and Exponentiation functions are carried out.\n");
	resultdiv = divide_intal(num1, num2);	//division
	if(!(resultdiv->s[1] == '?')){
		printf("\n\nDivision : ");
		print_intal(resultdiv);
	}
	printf("\n");

	if(num2->s[0] == '+'){					//exponentiation is done if and only if the power is positive
		printf("\nPlease wait while the Exponentiation function is carried out.\n");
		flag = 1;
		resultpow = pow_intal(num1, num2);	
	}
	if(flag){
		printf("\nExponentiation : ");
		print_intal(resultpow);
	}
	else{
		printf("\n\nNegative Exponent. Please enter a positive exponent!");
	}

	printf("\n\n");
	delete_intal(&resultadd);
	delete_intal(&resultsub);
	delete_intal(&resultmul);
	delete_intal(&resultdiv);
	delete_intal(&resultpow);

	return 0;
}
