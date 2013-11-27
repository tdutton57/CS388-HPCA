#include <iostream>
using namespace std;
#include <string>
#include <stdio.h>

void outputVariables (string data[]) {
    for (int i = 0, length = sizeof(data); i < length + 3; i++) {
        cout << data[i];
    }
    cout << endl;
}

void goodbye () {
    cout << "goodbye" << endl;
}

int calculateNumberofInstructions (string data[]) {
    int value =5;
    return value;
}

void calculateChart (string data[]) {
    int clockCycle = 0;
    cout<< "| N | instruction | function | opcode | issue | start | result | unit ready | fetch | store "<< endl;
    char formula = calculateFormula(data);
    int instructions = calculateNumberofInstructions(data);

    switch(formula) {
        case 'P': //power and addition
        cout<<formula<<endl;
        cout<<"In Case P"<<endl;
        gernerateTablePower(data,instruction);
        break;
        case 'M'://multiplication and addition
        cout<<formula<<endl;
        cout<<"In case M"<<endl;
        generateTableMultiplicationAddition(data,instruction);
        break;
        case 'D': //division
        cout<<formula<<endl;
        cout<<"In case D"<<endl;
        generateTableDivision(data,instruction);
        break;
        case 'S': //subtraction
        cout<<formula<<endl;
        cout<<"In case S"<<endl;
        generateTableSubtraction(data,instruction);
        break;
        default:
            cout<<"No matching cases formula is: "<<formula<<endl;
    }

}

//generate the formula 
char calculateFormula(string data[]) {
    char formula = 'Z';
    /*if(data[0] == "A" && data[1] == "A")
    {    
        formula = 'M';
       
    }
    else if(data[2] == "^")
    {
        formula = 'P'; 
    }
    else if(data[2] == "/" || data[5] == "/" ){
        formula = 'D';
    }
    else if(data[2] == "-" || data[5] == "-"){
        formula = 'S';
    }
    else
        cout<<"no matches"<<endl;*/
    return formula;

}


void gernerateTablePower(string data[], int instruction) {

    //First two setps are always fetch 
    string instructions[7];
    for(int i =0; i<7;++i) {
     instructions[i] = i;//generateInstruction(data);
     function[i] = i;
    }
    int clockCycles =1;
    //generateFunction(data)
    for int(i =0; i<7;i++)
        cout<<"N"<<i<<" "<<instructions[i]<<" "<<function[i]<<" "<<opCode<<" ";
        cout<<clockCycles<<" "<<clockCycles<<" ";
        clockCycles = clockCycles+3;
        cout<<" "<<clockCycles;
        clockCycle++;
        cout<<" "<<clockCycles<<" ";
        clockCycles = clockCycles+2;
        cout<<" "<<clockCycles<<" ";
        clockCycles = clockCycles+4;
        cout<<" "<<clockCycles<<" "<<endl;

}

void generateTableSubtraction(string data[],int instruction) {

}

void generateTableDivision(string data[], int instruction) {

}

void generateTableMultiplicationAddition(string data[], int instruction) {

}
