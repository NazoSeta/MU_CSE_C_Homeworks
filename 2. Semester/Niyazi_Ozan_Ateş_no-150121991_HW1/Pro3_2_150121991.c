#include <stdio.h>
#include <stdlib.h>

// Name: Niyazi Ozan    Surname: Ateþ    no: 150121991

// The purpose of this program is to find the superdigit of a number that is concatenated k times.
int main(int argc, char *argv[]) {
	
	int number, factor, i;
	// Here we ask the user to enter the number and the times it will be concatenated.
	// After that we will print and find the superdigit using the superDigit method.
	printf("Please enter a number (n=) : ");
	scanf("%d", &number);
	printf("Please enter repetition factor (k=) : ");
	scanf("%d", &factor);
	printf("Super digit of number ");
	
	for (i = 0 ; i < factor ; i++) {
		printf("%d", number);
	}
	
	printf(" is %d.", superDigit(number, factor));
	
	return 0;
}

// We calculate the superdigit using this method.
int superDigit(int num, int x) {
	
	int totalNum = 0;
	// With this while loop we add each digit one by one. 
	while (num > 0) {
		totalNum = totalNum + (num % 10);
		num = num / 10;
	}
	// Here we multiple the total amount by the number it should have concatenated. By doing this we handle it in a much shorter way.
	totalNum = totalNum * x;
	// If the totalNum is smaller then 10 (so its a single digit) we return the totalNum.
	// Else we take the totalNum that is bigger or equal than 10 and recursively use the same method here.
	if (totalNum < 10) {
		return totalNum;
	}
	else {
		superDigit(totalNum, 1); // The second parameter here is used as 1. The reason behind that is because we already concatenated the orginal number.
	}
}
