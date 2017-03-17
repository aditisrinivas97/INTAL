//intal.c is a library of integers of arbitrary length.
//intal stands for "int"eger of "a"rbitrary "l"ength.

// intal is an integer of arbitrary length. It has two fields; s and n.
// Field s stores a null-terminated string of decimal digits preceded by
// a + or sign indicating positive and negative integers.
// Field n represents the number of decimal digits excluding the sign.
// n is always greater than zero.
// Eg: Zero is represented with s as "+0" and n == 1.
// Eg: 2017 is represented with s as "+2017" and n == 4.
// Eg: -272 is represented with s as "-272" and n == 3.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"


// Creates and returns a pointer to a new intal initialized to zero.
// Initial values of i would be "+0" and n == 1.
intal* create_intal(){
	intal* i;

	i = (intal*) malloc(sizeof(intal));
	if(i == NULL) {
		return NULL; //malloc failed
	}

	//alloc 3 chars for a null-terminated string "+0".
	i->s = (char *) malloc(3 * sizeof(char));
	if(i->s == NULL) {
		free(i);
		return NULL; //malloc failed
	}

	strcpy(i->s, "+0"); 
	i->n = 1;

	return i;
}

// Deletes an intal, especially the memory allocated to it.
// i is a pointer to an intal to be deleted. It also resets *i to null.
void delete_intal(intal** i){

	if (i == NULL) {
		return;
	}

	if (*i == NULL) {
		return;
	}

	if( (*i)->s != NULL ) {
		free( (*i)->s );
	}

	free(*i);
	*i = NULL;
	return;
}

intal* remove_leading_zeros(intal *num){
	int i, j;
	int count = 0;
	for(i = 1; i < num->n; i++){		//remove leading zeros
		if(num->s[1] != '0'){
			break;
		}
		if(num->s[1] == '0' && i != (num->n)){
			for(j = 1; j <= num->n + 1; j++){
				num->s[j] = num->s[j + 1];
			}
			count++;
		}
	}

	num->s = (char *)realloc(num->s, sizeof(char)*(num->n + 2 - count));
	num->n -= (count);
	return num;
}

// Reads an intal from str into intal struct.
// str should be a null-terminated string just like s inside intal except that
// a postive integer could start without a + sign.
// str is unmodified.
void read_intal(intal* i, char* str){
	int n;

	if(i == NULL) {
		//printf("HELLO\n");
		return; //use create_intal before calling read_intal
	}
	if(str == NULL) {
		return; //invalid str
	}

	n = strlen(str);
	//printf("%d\n",n);

	if( (str[0] == '+') || (str[0] == '-') ) {
		//it has a sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	strcpy(i->s, str);
	 	i->n = n - 1;
	} 
	else {
		//it doesn't have a sign and hence it's positive
		n++; //one extra for the + sign
	 	i->s = realloc(i->s, n + 1); //one extra char for null termination
	 	i->s[0] = '+';
	 	strcpy((i->s + 1), str);
	 	i->n = n-1;
	}
	return;
}

// Prints the integer into stdout.
// It's just printf of s in intal (with format specifier %s) except that 
// it doesn't print the sign in case of positive integer.

void print_intal(intal* i){
	if(i == NULL) {
		return; //no intal to print
	}

	if(i->s != NULL) {
		if(i->s[0] == '+') {
			printf("%s", i->s + 1);
		} else {
			printf("%s", i->s);
		}
	}
	return;
}
//Creates a deep copy of the intal
//Parameter a is not modified while a1 is modified and returned
intal deep_copy(intal a1, intal *a){
	int i;
	a1.n = a->n;
	a1.s = (char *)malloc(sizeof(char)*(a1.n + 2));
	for(i = 0; i < a1.n+2; i++){
		a1.s[i] = a->s[i];
	}
	return a1;
}

// Adds two intals a and b, and returns the sum.
// Parameters a and b are not modified. Sum is a new intal.
intal* add_intal(intal* a, intal* b){
	int len, loop, carry = 0, ans, i, flag = 0;
	intal temp;
	intal *result = (intal *)malloc(sizeof(intal));

	intal a1; //copies to work with
	intal b1;

	a1.n = 0;
	a1.s = NULL;

	b1.n = 0;
	b1.s = NULL;

	a1 = deep_copy(a1, a); //create deep copy
	b1 = deep_copy(b1, b);

	if((a1.s[0] == '+' && b1.s[0] == '+') || (a1.s[0] == '-' && b1.s[0] == '-')){ //addition happens between numbers having same sign
		if(a1.s[0] == '-'){		// (-) + (-) = (-). Result is negative  
			flag = 1;
		}
		if(a1.n > b1.n){		
			len = a1.n;
			loop = b1.n;
		}
		else{
			len = b1.n;
			loop = a1.n;
		}
		result->s = (char *)malloc(sizeof(char)*(len+3)); //contains the result of the addition
		for(i = 0; i < (len + 3); i++){
			result->s[i] = '0';
		}
		result->n = len + 1;
		int index = len + 2;
		result->s[index--] = '\0';
		while(loop > 0){
			if(a1.n > b1.n){
				ans = (a1.s[len] - '0') + (b1.s[loop] - '0') + carry;
			}
			else{
				ans = (a1.s[loop] - '0') + (b1.s[len] - '0') + carry;
			}
			if(carry != 0){		//set carry = 0 after using it
				carry = 0;
			}
			if(ans >= 10){
				result->s[index--] = ((ans % 10) + '0');
				carry = ans/10;
			}
			else{
				result->s[index--] = ans + '0';
			}
			loop--;
			len--;
		}
		while(len > 0){
			if(a1.n > b1.n){
				ans = (a1.s[len] - '0') + carry;
			}
			else{
				ans = (b1.s[len] - '0') + carry;
			}
			if(carry != 0){
				carry = 0;
			}
			if(ans >= 10){
				result->s[index--] = ((ans % 10) + '0');
				carry = ans/10;
			}
			else{
				result->s[index--] = ans + '0';
			}
			len--;
		}
		if(carry != 0){
			result->s[index] = carry + '0';
		}
		if(result->s[1] == '0'){
			for(i = 0; i <= (result->n) ; i++){			//remove leading zeros in the result
				result->s[i] = result->s[i + 1];
			}
			if(flag == 1){
				result->s[0] = '-';
			}
			else{
				result->s[0] = '+';
			}
			result->s = (char *)realloc(result->s,sizeof(char)*((result->n) + 1));
			result->n = result->n - 1;
		}
		else{
			if(flag == 1){
				result->s[0] = '-';
			}
			else{
				result->s[0] = '+';
			}
		}
	}
	else if((a1.s[0] == '+' && b1.s[0] == '-')){	// A + (-B) = A - B. Forward the call to subtract_intal for subtraction.
		b1.s[0] = '+';
		result = subtract_intal(&a1, &b1);
	}
	else if((a1.s[0] == '-' && b1.s[0] == '+')){	// (-A) + (B) = B - A. Forward the call to subtract_intal for subtraction.
		if(a1.n > b1.n){
			flag = 1;
		}
		else if(a1.n == b1.n){
			for(i = 1; i <= a1.n; i++){
				if(a1.s[i] != '0' || b1.s[i] != '0'){
					if((a1.s[i] - '0') < (b1.s[i] - '0')){
						temp = a1;
						a1 = b1;
						b1 = temp;
						break;
					}
					else if((a1.s[i] - '0') > (b1.s[i] - '0')){
						flag = 1;
						break;
					}
				}
				
			}
		}
		else{
			flag = 0;
		}
		a1.s[0] = '+';
		b1.s[0] = '+';
		result = subtract_intal(&a1, &b1);
		if(flag == 1){
			result->s[0] = '-';
		}
		else{
			result->s[0] = '+';
		}
	}
	return result;
}
// Subtracts intal b from intal a. That is, finds a-b and returns the answer.
// Parameters a and b are not modified. a-b is a new intal.
intal* subtract_intal(intal* a, intal* b){
	int len, loop, ans, flag = 0, i, j, prev;
	intal temp;
	if(a->n > b->n){
		len = a->n;
		loop = b->n;
	}
	else{
		len = b->n;
		loop = a->n;
	}

	intal a1;	//copies to work with
	intal b1;

	a1.n = 0;
	a1.s = NULL;

	b1.n = 0;
	b1.s = NULL;

	a1 = deep_copy(a1, a);		//create deep copies
	b1 = deep_copy(b1, b);

	intal *result = (intal *)malloc(sizeof(intal));		//contains the result of the subtraction

	if((a1.s[0] == '+' && b1.s[0] == '+') || (a1.s[0] == '-' && b1.s[0] == '-')){
		result->s = (char *)malloc(sizeof(char)*(len + 2));
		for(i = 0; i < (len + 2); i++){
			result->s[i] = '0';
		}
		result->n = len;
		int index = len + 1;
		result->s[index--] = '\0';
		if((a1.s[0] == '+' && b1.s[0] == '+')){
			if(a->n < b->n){
				flag = 1;
				temp = a1;
				a1 = b1;
				b1 = temp;
			}
			else if(a->n == b->n){
				for(i = 1; i <= a->n; i++){
					if(a->s[i] != '0' || b->s[i] != '0'){
						if((a->s[i] - '0') < (b->s[i] - '0')){
							flag = 1;
							temp = a1;
							a1 = b1;
							b1 = temp;
							break;
						}
						else{
							break;
						}
					}
				}
			}
		}
		else if((a1.s[0] == '-' && b1.s[0] == '-')){
			if(a->n < b->n){
				temp = a1;
				a1 = b1;
				b1 = temp;
			}
			else if(a->n == b->n){
				for(i = 1; i <= a->n; i++){
					if(a->s[i] != '0' || b->s[i] != 0){
						if((a->s[i] - '0') < (b->s[i] - '0')){
							temp = a1;
							a1 = b1;
							b1 = temp;
							break;
						}
						else{
							flag = 1;
							break;
						}	
					}
				}
			}
			else{
				flag = 1;
			}
		}
		while(loop > 0){
			ans = (a1.s[len] - '0') - (b1.s[loop] - '0');
			if(ans < 0){
				a1.s[len] = (((a1.s[len] - '0') + 10) + '0');
				j = len - 1;
				prev = ((a1.s[j] - '0') - 1); 
				while(prev < 0){
					a1.s[j] = (((a1.s[j] - '0') + 9) + '0');
					prev = ((a1.s[--j] - '0') - 1);
				}
				a1.s[j] = (((a1.s[j] - '0') - 1) + '0');
				result->s[index--] =  (((a1.s[len] - '0') - (b1.s[loop] - '0')) + '0');
			}
			else{
				result->s[index--] = (ans + '0');
			}
			len--;
			loop--;
		}
		while(len > 0){
			result->s[index--] = a1.s[len--];
		}
		int count = 0;
		for(i = 0; i < result->n; i++){		//remove leading zeros
			if(result->s[0] != '0'){
				break;
			}
			if(result->s[0] == '0' && result->s[1] == '0' && i != (result->n - 1)){
				for(j = 0; j <= result->n; j++){
					result->s[j] = result->s[j + 1];
				}
				count++;
			}
		}
		result->s = (char *)realloc(result->s, sizeof(char)*(result->n + 2 - count));
		result->n -= (count);
		if(flag == 1){
			result->s[0] = '-';
		}
		else{
			result->s[0] = '+';
		}
	}
	else if(a1.s[0] == '+' && b1.s[0] == '-'){	// (+A) - (-B) = A + B. Forward call to add_intal for addition.
		b1.s[0] = '+';
		result = add_intal(&a1, &b1);
		b1.s[0] = '-';
	}
	else if(a1.s[0] == '-' && b1.s[0] == '+'){ 	// (-A) - (B) = -(A + B). Forward call to add_intal for addition. 
		a1.s[0] = '+';
		b1.s[0] = '+';
		result = add_intal(&a1, &b1);
		result->s[0] = '-';
		a1.s[0] = '-';
	}
	return result;
}

//Multiplies the given intal a by 10^exp
//a is not modified a*10^exp is a new intal
intal* multiply_byten(intal *a, int exp){
	int i, j;
	intal *result = (intal *)malloc(sizeof(intal));
	result->s = (char *)malloc(sizeof(char)*(a->n + exp) + 2);
	result->n = a->n + exp;
	for (i = 0; i <= a->n; i++){
		result->s[i] = a->s[i];
	}
	for(j = a->n + 1 ; j < result->n+2; j++){
		result->s[j] = '0';
	}
	result->s[result->n + 1] = '\0';
	return result;
}
//Pads the given array a with leading zeros upto the length 'num'
//Example : padding array containing +2 where num = 4 gives, +0002.
//a is not modified and the padded array is a new intal
intal* padarray(intal* a, int num){
	int padval = num - a->n;
	intal *new = (intal *)malloc(sizeof(intal));
	new->s = (char *)malloc(sizeof(char)*(num + 2));
	new->s[0] = a->s[0];
	new->n = num;
	int i = 1, j = 1;
	while(i <= new->n){
		while(padval != 0){
			new->s[i++] = '0';
			padval--;
		}
		new->s[i++] = a->s[j++];
	}
	new->s[new->n + 1] = '\0';
	return new;
}

// Multiplys two intals a and b, and returns the product.
// Parameters a and b are not modified. Product is a new intal.
//Multiplication done using karatsuba algorithm.
intal* multiply_intal(intal* a, intal* b){
	if(a->n == 1 && b->n == 1){		//base case if number has only 1 digit
		intal *result = (intal *)malloc(sizeof(intal));
		int res = (a->s[1] - '0')*(b->s[1] - '0');		//multiply the numbers
		int rescpy = res;
		int len = 0, i;
		char temp;
		if(res == 0){
			len++;
		}
		while(rescpy != 0 ){
			len++;
			rescpy = rescpy/10;
		}
		result->s = (char *)malloc(sizeof(char)*(len + 2));
		result->n = len;
		for(i = 1; i <= len; i++){
			result->s[i] = ((res % 10) + '0');
			res = res/10;
		}
		if(len == 2){
			temp = result->s[1];
			result->s[1] = result->s[2];
			result->s[2] = temp;
		}
		if((a->s[0] == '-' && b->s[0] == '+') || (a->s[0] == '+' && b->s[0] == '-')){ //choose appropriate sign
			result->s[0] = '-';
		}
		else{
			result->s[0] = '+';
		}
		return result;
	}
	int i;
	intal *result = (intal *)malloc(sizeof(intal));	//result to be returned
	intal a1;	//copies to work with
	intal b1;

	a1.n = 0;
	a1.s = NULL;

	b1.n = 0;
	b1.s = NULL;

	a1 = deep_copy(a1, a);	//create deep copies
	b1 = deep_copy(b1, b);

	if(a1.n > b1.n){
		b1 = *padarray(&b1, a1.n);	//equalize the array sizes
	}
	else if(b1.n > a1.n){
		a1 = *padarray(&a1, b1.n);
	}
	if(a1.n % 2 == 1){				//if length is odd, padd 1 zero to make the array size even
		a1 = *padarray(&a1, a1.n+1);
		b1 = *padarray(&b1, b1.n+1);
	}
	
	int m = a1.n/2, j, tlen;	//calculate the mid value
	if(m == 1){
		tlen = m + 1;
	}
	else{
		tlen = m + 2;
	}
	intal *c1 = (intal *)malloc(sizeof(intal));
	intal *c2 = (intal *)malloc(sizeof(intal));
	intal *d1 = (intal *)malloc(sizeof(intal));
	intal *d2 = (intal *)malloc(sizeof(intal));
	intal *c3 = (intal *)malloc(sizeof(intal));
	intal *d3 = (intal *)malloc(sizeof(intal));

	c1->s = (char *)malloc(sizeof(char)*(m + 2));	//create the sub-arrays
	c2->s = (char *)malloc(sizeof(char)*(m + 2));
	d1->s = (char *)malloc(sizeof(char)*(m + 2));
	d2->s = (char *)malloc(sizeof(char)*(m + 2));
	c3->s = (char *)malloc(sizeof(char)*(tlen + 2));
	d3->s = (char *)malloc(sizeof(char)*(tlen + 2));

	for(i = 0; i <= m; i++){
		c1->s[i] = a1.s[i];
		d1->s[i] = b1.s[i];
	}
	c1->s[i] = '\0';
	d1->s[i] = '\0';
	c1->n = m;
	d1->n = m;

	c2->s[0] = a1.s[0];
	d2->s[0] = b1.s[0];
	c2->n = m;
	d2->n = m;

	j = 1;

	for(i = m+1; i < (a1.n + 2); i++){
		c2->s[j] = a1.s[i];
		d2->s[j++] = b1.s[i];
	}

	c3 = add_intal(c1, c2);		//c3 = c1 + c2
	d3 = add_intal(d1, d2);		//d3 = d1 + d2

	if(c3->n != d3->n){			//equalize array size
		if(c3->n > d3->n){
			d3 = padarray(d3, c3->n);
		}
		else{
			c3 = padarray(c3, d3->n);
		}	
	}

	if(c3->n % 2 == 1 && c3->n != 1){	//if array size if odd, pad one zero to make array size even.
		c3 = padarray(c3, c3->n+1);
		d3 = padarray(d3, d3->n+1);
	}

	c3->s[0] = c1->s[0];
	d3->s[0] = d1->s[0];

	intal* p1 = (intal *)malloc(sizeof(intal));
	intal* p2 = (intal *)malloc(sizeof(intal));
	intal* p3 = (intal *)malloc(sizeof(intal));

	p1 = multiply_intal(c1, d1);	//p1 = c1[0...m] * b1[0...m]
	p2 = multiply_intal(c2, d2);	//p2 = c2[m+1...n] * d2[m+1...n]
	p3 = multiply_intal(c3, d3);	//p3 = c3[0...m+1] * d3[0...m+1]

	intal* p1c = (intal *)malloc(sizeof(intal));
	intal* p3c = (intal *)malloc(sizeof(intal));	

	p1c = multiply_byten(p1, (2*m));	//p1c = p1*(10^n)

	p3c = subtract_intal(p3, p2);		//p3c = (p3 - p2 - p1)*(10^m)
	p3c = subtract_intal(p3c, p1);
	p3c = multiply_byten(p3c, m);
	result = add_intal(p1c, p2);
	result = add_intal(result, p3c);	//result = p1c + p3c + p2
	int count = 0;
	for(i = 0; i < result->n; i++){		//remove leading zeros
		if(result->s[1] != '0'){
			break;
		}
		if(result->s[1] == '0' && i != (result->n - 1)){
			for(j = 1; j <= result->n; j++){
				result->s[j] = result->s[j + 1];
			}
			count++;
		}
	}
	result->s = (char *)realloc(result->s, sizeof(char)*(result->n + 2 - count)); //reallocate after removing leading zeros.
	result->n -= (count);
	return result;
}

//compares 2 intals a1 and b1. Returns -1 if a1 < b1, +1 if a1 > b1 and 0 if a1 == b1
//parameters are not modified
int compare_intal(intal a1, intal b1){
	int i;
	if(a1.n < b1.n){		//if b has more digits b > a
		return -1;
	}
	if(a1.n > b1.n){		//if a has more digits a > b
		return 1;
	}
	for(i = 1; i <= a1.n; i++){
		if(a1.s[i] != 0 || b1.s[i] != 0){	
			if(a1.s[i] < b1.s[i]){		//if the first non-zero digit of a1 is less then b1 => a1 < b1 => return -1
				return -1;
			}
			else if(a1.s[i] > b1.s[i]){	//if the first non-zero digit of b1 is less then a1 => b1 < a1 => return +1 
				return 1;
			}
		}
	}
	return 0;	//if both are equal return 0
}

// Divides intal a from intal b and returns the quotient. 
// That is, finds floor(a/b), which is aka integer division.
// Parameters a and b are not modified. Floor(a/b) is a new intal.
// The following division algorithm reduces the number of subtractions and is hence faster than the traditional repeated subrtractions.
intal* divide_intal(intal* a, intal* b){
	intal *result = create_intal();		//stores the result. Initially 0.
	intal a1;			//copy to work with
	intal b1;			//copy to work with

	a1.n = 0;
	a1.s = NULL;

	b1.n = 0;
	b1.s = NULL;

	a1 = deep_copy(a1, a);
	b1 = deep_copy(b1, b);
	
	intal *zero = create_intal();

	intal res;		//copy of b1
	int count;		//used to keep track of the number of subtrations in each iteration
	int len = 1;	//regulate the length of the result array

	res.n = 0;
	res.s = NULL;

	if((a1.s[0] == '-' || b1.s[0] == '-') && !(a1.s[0] == '-' && b1.s[0] == '-')) {
		result->s[0] = '-';
	}
	a1.s[0] = '+';
	b1.s[0] = '+';

	if(compare_intal(b1, *zero) == 0){
		result->s[1] = '?';
		printf("\n\nDivision by zero is not possible!");
		return result;
	}

	res = deep_copy(res, &b1);

	while(compare_intal(a1, res) >= 0){		//mutiply res by 10 as many times as possible such that res < a1
		res = *multiply_byten(&res, 1);
	}
	res.s[res.n] = res.s[res.n + 1];
	res.s = (char *)realloc(res.s, sizeof(char)*(res.n + 1));
	res.n = res.n-1;

	while(compare_intal(res, b1) >= 0){		
		count = 0;
		while(compare_intal(a1, res) >= 0){		//loop runs as long as a1 >= res
			a1 = *subtract_intal(&a1, &res);	//subtract a1 by res
			count++;		//number of subtractions
		}
		result->s = (char *)realloc(result->s, sizeof(char)*(len + 2)); 
		result->n = len;
		len++;
		result->s[result->n] = count + '0';			//append count to result
		res.s[res.n] = res.s[res.n + 1];			
		res.s = (char *)realloc(res.s, sizeof(char)*(res.n + 1));	//strip one zero off of res and repeat.
		res.n = res.n-1;
	}
	return result;
}

// Finds a^b, which a to the power of b and returns the result. 
// The result could be undefined if the intal b is negative.
// Parameters a and b are not modified. The result is a new intal.
intal* pow_intal(intal* a, intal* b) {
	intal bcpy; 
	intal acpy; 

	acpy.n = 0;
	acpy.s = NULL;

	bcpy.n = 0;
	bcpy.s = NULL;

	bcpy = deep_copy(bcpy, b);
	acpy = deep_copy(acpy, a);

	intal *strone = create_intal();		//stores 1 to decrement bcpy by 1 in every iteration
	strone->s[1] = '1';
	intal *result = create_intal();		//result is initially 1
	result->s[1] = '1';
	
	intal base;
	base.s = (char *)malloc(sizeof(char)*3);	//used to compare with bcpy. If bcpy = 0, loop terminates
	base.s[0] = '+';
	base.s[1] = '0';
	base.s[2] = '\0';
	base.n = 1;
	while(compare_intal(bcpy, base) != 0){		
		result = multiply_intal(result,&acpy);	//multiply the existing result by acpy
		bcpy = *subtract_intal(&bcpy, strone);	//decrement bcpy
	}
	return result;
}
