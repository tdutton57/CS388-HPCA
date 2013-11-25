//Tiffani Dutton Katie Isabel David Zemon Ben
//CS 388 HPCA Project
//Due December 3rd

#include "generator.h"
#include <fstream>
#include <iostream>
using namespace std; 

void Generator::getValidData(char value) {
	//this will take in the value that we are given, splice it at the spaces throw it 
	//into a character array
	//once we have the character array, you will assign firstValue operation, 
	//second value, operation, third value etc. all of the even numbers 
	//should be  values, all of the odd numbers should be the operations
	cout<<"hello world!"<<endl; 



	//return generator; 
}


Generator::Generator(char firstValue,char secondValue, char thirdValue, int operation) {
	mFirstValue = firstValue;
	mSecondValue = secondValue;
	mThirdValue = thirdValue;
	mOperation = operation;
}

/*
void Generator::generateData(generator value) {

}


void Generator::goodbye()
{
	cout<<"thank you for using the CDC 6600 :)"<<endl;
}

*/