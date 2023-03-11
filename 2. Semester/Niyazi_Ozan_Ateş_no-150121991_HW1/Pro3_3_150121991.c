#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Name: Niyazi Ozan    Surname: Ateþ    no: 150121991

// The purpose of this program is to print some amount of triangle based on the number of interations given.
// With each interation the amount of triangles will be multiplied by three (3^interations many triangles).
int main(int argc, char *argv[]) {
	
	char array[32][63] = {};
	int interations, i, j;
	// Here we ask the user to enter the number of interations.
	printf("Enter the number of interations: ");
	scanf("%d", &interations);
	// We make an empty plot to create the triangle on.
	for (i = 0 ; i < 32 ; i++) {
		for (j = 0 ; j < 63 ; j++) {
			array[i][j] = '_';
		}
	}
	// We create here the orginal triangle without any interations applied on it.
	for (i = 0 ; i < 32 ; i++) {
		for (j = i ; j < 32 ; j++) {
			array[j][31+i] = '1';
			array[j][31-i] = '1';
		}
	}
	// We use here the createTriangles method to create to proper amount of triangles to show on the screen.
	createTriangles(array, interations);
	// Here we print our triangle to the screen.
	for (i = 0 ; i < 32 ; i++) {
		for (j = 0 ; j < 63 ; j++) {
				printf("%c", array[i][j]);
		}
			printf("\n");
	}
	return 0;
}

// This is the place were the the amount of triangles will be shaped based on the interations recursively.
void createTriangles(char arr[32][63], int inter) {
	
	int startingRowValue, startingColumnValue, jump, midPoint, loops, i, j, k, l;
	// We first define some data flieds that we will use to create the triangles.
	startingRowValue = 32/pow(2, inter);
	jump = 32/pow(2, inter);
	startingColumnValue = 63/2;
	midPoint = 63/2;
	// If there are no interations left the triangles are then create and we will leave the createTriangles method.
	// Otherwise we will find the midPoint of the empty spots to interate the triangles with a offset called jump based on the empty spot that will be created.
	// After each empty spot we will move the midPoint to create the next empty spot in row.
	// The j variable will create offsets in each empty spot to give it a upside down triagle figure.
	// the i variable that is based on the startingRowValue and jump offset given use the row where we need to clear out the triangle.
	if(inter != 0) {
		for (k = 0 ; k < pow(2, inter-1) ; k++) {
			midPoint = 63/2 - jump*k*2;
			for (l = 0 ; l < k+1 ; l++) {
				for (j = 0 ; j < jump ; j++) {
					for (i = jump + startingRowValue - 1 - j ; i >= startingRowValue ; i--) {
						arr[i][midPoint + j] = '_';
						arr[i][midPoint - j] = '_';
			}
		}
				midPoint = midPoint + jump*4; // We update the midPoint so the next empty spot in row can we created.
	}
		startingRowValue = startingRowValue + jump*2; // We update the startingRowValue so the next row is chosen to create new empty upside down triangles.
	}
	createTriangles(arr, inter - 1); // Here we go to the next interation to interate the triangles more if needed.
}
	else {
		return;
	}
}
