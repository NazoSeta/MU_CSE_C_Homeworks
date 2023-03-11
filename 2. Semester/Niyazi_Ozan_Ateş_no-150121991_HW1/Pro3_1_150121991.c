#include <stdio.h>
#include <stdlib.h>

// Name: Niyazi Ozan    Surname: Ateþ    no: 150121991

// The purpose of this program is to show the number of ears based of the number of bunnies in a line.
// We do this by counting the number of ears of the odd bunnies in line by 2 and the even bunnies in line by 3.
int main(int argc, char *argv[]) {
	
	int bunnies = 0;
	// Here we ask the user to enter the number of lines.
	printf("Please enter the number of lines (n=): ");
	scanf("%d", &bunnies);
	// We use the ears method to display the number of ears in each line.
	ears(0, 0, bunnies);
	
	return 0;
}

// With this method we show the number od ears in each line recursively.
int ears(int index, int totalEars, int bunnies){
	// We control the number of ears with the index of the line.
	// Based on the index we add 2 or 3 ears to the total amount of ears and print a proper message to the screen.
	// When the index is bigger then the amount of bunnies the total bunny ears will be returned.
	if (index == 0) {
		printf("bunnyEars%d(%d) -> %d\n", bunnies, index, totalEars);
		ears(index + 1, totalEars, bunnies);
	}
	else if (index <= bunnies) {
		if (index%2 == 1) {
			totalEars += 2;
			printf("bunnyEars%d(%d) -> %d\n", bunnies, index, totalEars);
		}
		else {
			totalEars += 3;
			printf("bunnyEars%d(%d) -> %d\n", bunnies, index, totalEars);
		}
		ears(index + 1, totalEars, bunnies);
	}
	else {
		return totalEars;
	}
}
