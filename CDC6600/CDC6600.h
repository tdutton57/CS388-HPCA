#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>
void outputVariables(string data[]) {
	for(int i =0, length = sizeof(data); i< length+3;i++) {
		cout<<data[i];
	}
	cout<<endl;
}

void goodbye() {
	cout<<"goodbye"<<endl;
}


int calculateNumberofInstructions(string data[])
{
	int value 5;
	return value;
}

void calculateChart(string data[]) {
	int clockCycle = 0;
	cout<<"| N | instruction | function | opcode | issue | start | result | unit ready | fetch | store "<<endl;
	int instructions = calculateNumberofInstructions(data);
	
	int wordNumber = 1;

	for(i =0; i<instructions;i++)
	{
		printf("| N%d |",wordNumber);
		printf("%s",instructionStrings)
	}

}