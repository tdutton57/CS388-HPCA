//Tiffani Dutton Katie Isabel David Zemon Ben
//CS 388 HPCA Project
//Due December 3rd

#include "generator.h"
#include <fstream>
#include <iostream>
using namespace std; 

Generator Generator::getValidData(char argv[]) {
	//this will take in the value that we are given, splice it at the spaces throw it 
	//into a character array
	//once we have the character array, you will assign firstValue operation, 
	//second value, operation, third value etc. all of the even numbers 
	//should be  values, all of the odd numbers should be the operations
	FILE *file = fopen(argv[1], "r");

	if(file == 0) {
		printf("Could not open the file\n");
		exit(1);
	}
	char array[50];
	while ( (x = fgetc(file)) != EOF) {

	//put info from file into an array
		if(x != ' ') {
			array[x] = x;
			printf("%c",x);
		}
	}
	//close the file
	fclose(file);
	return generator; 
}


void Generator::generateData(generator value) {

}


void Generator::goodbye()
{
	cout<<"thank you for using the CDC 6600 :)"<<endl;
}

