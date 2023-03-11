#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 10

// Name: Niyazi Ozan    Surname: Ateþ    no: 150121991

// The purpose of this program is to suggest the best route based on a starting and fishing point.
// The route will be given with help of some metrostations.

/* NOT: The functions 13.a and 13.b are incomplete.
		I found it hard to do it and I had kind of a lack of time for it.
		The recursive part does not work as i wanted it to.
*/

// Here we struct our metrostation with the name and coordinates.
typedef struct MetroStation {
	char name[20];
	double x;
	double y;
}MetroStation;
// Here we struct our metroline with the metrostation it got and the color the line got.
typedef struct MetroLine {
	char color[20];
	MetroStation MetroStations[SIZE];
}MetroLine;
// Here we struct our metrosystem this will hold all the mtrolines in the city.
typedef struct MetroSystem {
	char name[20];
	MetroLine MetroLines[SIZE];
}MetroSystem;

// Here we define the metrosystem of the city it is in.
MetroSystem istanbul = {"istanbul", '\0'};

// The equals function checks whenever two metrostations are the same or not.
int equals(MetroStation s1, MetroStation s2) { // 1
	if (strcmp(s1.name, s2.name) == 0) {
		return 1;
	}
	return 0;
}

// With the addStation function we add a metrostation to a metroline.
void addStation(MetroLine *ml, MetroStation ms) { // 2
	int i;
	
	for (i = 0 ; i < SIZE ; i++) {
		if (strlen(ml->MetroStations[i].name) == 0) {
			ml->MetroStations[i] = ms;
			break;
		}
	}
}

// hasStation method is used to check whenever a metrostation is inside the given metroline.
int hasStation(MetroLine ml, MetroStation ms) { // 3
	int i;
	for (i = 0 ; i < SIZE ; i++) {
		if (strcmp(ms.name, ml.MetroStations[i].name) == 0) {
			return 1;
		}
	}
	return 0;
}

// Here we get the first stop of a metroline.
MetroStation getFirstStop(MetroLine ml) { // 4
	MetroStation empty = {'\0'};
	if (strlen(ml.MetroStations[0].name) > 0) {
		return ml.MetroStations[0];
	}
	return empty;
}

// With help of this function we try to find the previous stop of a metrostation in a metroline.
MetroStation getPreviousStop(MetroLine ml, MetroStation ms) { // 5
	int i, index = 0;
	MetroStation empty = {'\0'};
	for (i = 0 ; i < SIZE ; i++) {
		if (strcmp(ms.name, ml.MetroStations[i].name) == 0) {
			index = i;
		}
	}
	if (index != 0) {
		return ml.MetroStations[index-1];
	}
	return empty;
}

// With help of this function we try to find the next stop of a metrostation in a metroline.
MetroStation getNextStop(MetroLine ml, MetroStation ms) { // 6
	int i, index = 0;
	MetroStation empty = {'\0'};
	for (i = 0 ; i < SIZE ; i++) {
		if (strcmp(ms.name, ml.MetroStations[i].name) == 0) {
			index = i;
		}
	}
	if (index != SIZE-1) {
		return ml.MetroStations[index+1];
	}
	return empty;
}

// With the addLine function we add a metroline to a metrosystem.
void addLine(MetroSystem *ms, MetroLine ml) { // 7
	int i;
	
	for (i = 0 ; i < SIZE ; i++) {
		if (strlen(ms->MetroLines[i].color) == 0) {
			ms->MetroLines[i] = ml;
			break;
		}
	}
}

// The printLine function will print a metroline to the output.
void printLine(MetroLine ml) { // 8
	int i, j = 0;
	printf("Metroline %s:   ", ml.color);
	while (strlen(ml.MetroStations[j].name) > 0) {
		j++;
	}
	for (i = 0 ; i < j-1 ; i++) {
		printf(" %s,", ml.MetroStations[i].name);
	}
	printf(" %s", ml.MetroStations[j-1].name);
	printf(".\n");
	return;
}
// The printPath function will print a path of metrostations to the output.
void printPath(MetroStation ms[SIZE]) { // 9
	int i, j = 0;
	while (strlen(ms[j].name) > 0) {
		j++;
	}
	for (i = 0 ; i < j-1 ; i++) {
		printf("%s ", ms[i].name);
	}
	printf("%s ", ms[j-1].name);
	printf("\n");
	return;
}

// The getDistanceTravelled function will find the total distance between a path of metrostations 
double getDistanceTravelled(MetroStation path[SIZE]) { // 10
	int j = 0;
	double total = 0;
	
	if (path[1].name == 0) {
		return 0;
	}
	
	while (strlen(path[j+1].name) > 0) {
		total += sqrt(pow(path[j].x-path[j+1].x, 2) + pow(path[j].y-path[j+1].y, 2));
		j++;
	}
	return total;
}

// With the help of the findNearestStation function we will find the nearest station based on the metrosystem and coordinates that are given.
MetroStation findNearestStation(MetroSystem msm, double x, double y){ // 11
    int i, j, tempDistance = 0;
    int indexml = 0;
    int indexms = 0;
    for (i = 0 ; i < SIZE ; i++) {
        if (strcmp(msm.MetroLines[i].color, "") == 0) {
            break;
        }
        else {
            for (j = 0 ; j < SIZE ; j++) {
                if (strcmp(msm.MetroLines[i].MetroStations[j].name, "") == 0) {
                    break;
                }
				else {
                    double a = pow((msm.MetroLines[i].MetroStations[j].x-x), 2);
                    double b = pow((msm.MetroLines[i].MetroStations[j].y-y), 2);
                    if (tempDistance == 0) {
                        tempDistance = sqrt(a+b);
                        indexml = i;
                        indexms = j;
                    }
                    else if (sqrt(a+b) < tempDistance) {
                        tempDistance = sqrt(a+b);
                        indexml = i;
                        indexms = j;
                    }
                }
            }
        }
    }
    return msm.MetroLines[indexml].MetroStations[indexms];
}

// In this function we get the neighbor station of a given metrostation in a metrosystem.
void getNeighboringStations(MetroSystem msm, MetroStation ms, MetroStation neigboringStations[SIZE]) { // 12
	int i=0, j=0, k=0;
	
	while (strlen(msm.MetroLines[i].color) > 0) {
		while (strlen(msm.MetroLines[i].MetroStations[j].name) > 0) {
			if (strcmp(msm.MetroLines[i].MetroStations[j].name, ms.name) == 0) {
				neigboringStations[k] = msm.MetroLines[i].MetroStations[j+1];
				k++;
				neigboringStations[k] = msm.MetroLines[i].MetroStations[j-1];
				k++;
			}
			j++;
		}
		i++;
	}
}

// This is the place where we try to find the shortest path. We do this with help of the recursiveFindPath function.
void findPath(MetroStation start, MetroStation finish, MetroStation path[SIZE]) { // 13.a
	int i = 0;
	MetroStation partialPath[SIZE];
	recursiveFindPath(start, finish, path, partialPath);
	for (i = 0 ; i < SIZE ; i++) {
		if (strlen(partialPath[i].name) > 0) {
			printf("%d.  %s\n", (i+1), partialPath[i].name);
		}
	}
}

// In this function we will find the shortest path with help of recursion.
int recursiveFindPath(MetroStation start, MetroStation finish, MetroStation partialPath[SIZE], MetroStation bestPath[SIZE]) { // 13.b
	int i, j, k, l;
	
	for (i = 0 ; i < SIZE ; i++) {
		if (strcmp(partialPath[i].name, start.name) == 0) {
			return;
		}
	}
	
	if (strcmp(start.name, finish.name) == 0) {
		
		for (i = 0 ; i < SIZE ; i++) {
		bestPath[i].x = partialPath[i].x;
		bestPath[i].y = partialPath[i].y;
		strcpy(bestPath[i].name, partialPath[i].name);
		}
		
		for (i = 0 ; i < SIZE ; i++) {
			if (strlen(bestPath[i].name) == 0) {
				bestPath[i] = finish;
				return;
			}
		}
		
		return;
	}
	
	MetroStation neighbors[SIZE] = {"\0"};
	getNeighboringStations(istanbul, start, neighbors);
	
	for (i = 0 ; i < SIZE ; i++) {
		if (strlen(neighbors[i].name) != 0) {
				
		MetroStation duplicatePath[SIZE]= {"\0"};
		MetroStation currentPath[SIZE] = {"\0"};
		
		for (j = 0 ; j < SIZE ; j++) {
			duplicatePath[j].x = partialPath[j].x;
			duplicatePath[j].y = partialPath[j].y;
			strcpy(duplicatePath[j].name, partialPath[j].name);
		}
	
		for (k = 0 ; k < SIZE ; k++) {
			if (strlen(duplicatePath[k].name) == 0) {
				duplicatePath[k] = start;
				break;
			}
		}
		
		for (l = 0 ; l < SIZE ; l++) {
		currentPath[l].x = bestPath[l].x;
		currentPath[l].y = bestPath[l].y;
		strcpy(currentPath[l].name, bestPath[l].name);
		}
				recursiveFindPath(neighbors[l], finish, duplicatePath, bestPath);
			}
		}
	
	if (bestPath[0].name != '\0') {
		return getDistanceTravelled(bestPath);
	}
	
}

// The main function is created based on the teacher.
int main(int argc, char *argv[]) {
	int i;
	double myX=1, myY=2; 
	double goalX=62, goalY=45; 
	
	// define 3 metro lines, 9 metro stations, and an empty myPath
	MetroLine red={'\0'}, blue={'\0'}, green={'\0'};
	MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
	MetroStation myPath[SIZE]={'\0'};
	
	strcpy(red.color, "red"); 
	strcpy(blue.color, "blue");
	strcpy(green.color, "green");

	
	strcpy(s1.name, "Haydarpasa"); 		s1.x=0; 	s1.y=0;
	strcpy(s2.name, "Sogutlucesme"); 	s2.x=10; 	s2.y=5;
	strcpy(s3.name, "Goztepe"); 		s3.x=20; 	s3.y=10;
	strcpy(s4.name, "Kozyatagi"); 		s4.x=30; 	s4.y=35;
	strcpy(s5.name, "Bostanci"); 		s5.x=45; 	s5.y=20;
	strcpy(s6.name, "Kartal"); 			s6.x=55; 	s6.y=20;
	strcpy(s7.name, "Samandira"); 		s7.x=60; 	s7.y=40;
	strcpy(s8.name, "Icmeler"); 		s8.x=70; 	s8.y=15;
	
	//Add several metro stations to the given metro lines.
	addStation(&red, s1); addStation(&red, s2); addStation(&red, s3); addStation(&red, s4); addStation(&red, s5); addStation(&red, s8);
	
	addStation(&blue, s2); addStation(&blue, s3); addStation(&blue, s4); addStation(&blue, s6); addStation(&blue, s7);
	
	addStation(&green, s2); addStation(&green, s3); addStation(&green, s5); addStation(&green, s6); addStation(&green, s8);
	
	// Add red, blue, green metro lines to the Istanbul metro system.
	addLine(&istanbul, red);
	addLine(&istanbul, blue);
	addLine(&istanbul, green);
	
	// print the content of the red, blue, green metro lines
	printLine(red);
	printLine(blue);
	printLine(green);
		
	// find the nearest stations to the current and target locations
	MetroStation nearMe = findNearestStation(istanbul, myX, myY);
	MetroStation nearGoal = findNearestStation(istanbul, goalX, goalY);
	
	printf("\n");
	
	printf("The best path from %s to %s is:\n", nearMe.name, nearGoal.name);
	
	// if the nearest current and target stations are the same, then print a message and exit.
	if(equals(nearMe, nearGoal)){
		printf("It is better to walk!\n");
		return 0;
	}
	
	// Calculate and print the myPath with the minimum distance travelled from start to target stations.
	findPath(nearMe, nearGoal, myPath);
	
	if(strlen(myPath[0].name) == 0)
		printf("There is no path on the metro!\n");
	else{
		printPath(myPath);
	}
	return 0;
}
