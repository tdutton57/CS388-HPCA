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

void calculateChart (string data[],int formula) {
    int clockCycle = 0;
    cout<< "| N | instruction | function | opcode | issue | start | result | unit ready | fetch | store "<< endl;
    
    if(formula != 3) {
        int size = data.sizeof(); //create size 

        string *instructions;   //create string array instructions to handle the instructions for the table
        instructions = new string [size]; 

        //create opcode array to handle the opcodes for the table.
        int *opcode;
        opcode = new int [size];

        string * function;
        function = new string [size];
    } 
    else {
        //when with the vector
        int size = 23;
        string instructions[23];
        int opcode[23];
        string function[23] 
    }

    //enter data into the arrays just created 
    for(int i =0; i<size;++i) {
     function[i] = generateFunctionWords(i,formula); //generate the function part of the table (DONE)
     instructions[i] = generateInstruction(i,formula); //generate the instructions of the table (TODO)
     opcode[i] = generateOpCode(function[i]);       //generate the opCode for the table (TODO)
    }
    int clockCycles =1;

    for int(i =0; i<size+1;i++)
        outputTable(i,data,instructions,function);

    if(formula != 3)
    {
        delete [] instructions;
        delete [] function;
    }  

}


//DONE
string generateFunctionWords(int i, int formula) //DONE 
{
    switch(formula) {
        case 1:
            return generateFunctionOne(i);
            break;
        case 2:
            return generateFunctionTwo(i);
            break;
        case 3:
            return generateFunctionThree(i);
        default:
            return "-1";
    }
}


//DONE
string generateFunctionOne(int i,){
    string response = " ";
    switch(i){
        case 1:
            respone = "FETCH X";
            break;
        case 2:
            response = "FETCH A";
            break;
        case 3: 
         response = "FORM X^2";
         break;
        case 4:
            response = "FORM AX^2";
        case 5:
            response = "FETCH B";
            break;
        case 6:
            response = "FORM Y";
        case 7:
            response = "STORE Y";
            break;
        default:
            response ="-1";
            break;
    }
    return response;
}


//DONE
string generateFunctionTwo(int i,){
    string response = " ";
    switch(i){
        case 1:
            respone = "FETCH X";
            break;
        case 2:
            response = "FETCH A";
            break;
        case 3: 
         response = "FORM X^2";
         break;
        case 4:
            response = "FORM AX^2";
        case 5:
            response = "FETCH B";
            break;
        case 6:
            response = "FETCH C";
        case 7:
            response = "FORM BX";
            break;
        case 8:
            response = "FORM AX^2 +  BX";
            break;
        case 9: 
            response = "FORM Y";
            break;
        case 10:
            response = "STORE Y";
            break;
        default:
            response ="-1";
            break;
    }
    return response;
}


//DONE
string generateFunctionThree(int i,){
    string response = " ";
    switch(i){
        case 1:
            respone = "FETCH N";
            break;
        case 2:
            response = "FETCH Xn";
            break;
        case 3: 
         response = "Fetch A";
         break;
        case 4:
            response = "FORM Xn^2";
        case 5:
            response = "FORM AXn^2";
            break;
        case 6:
            response = "FETCH B";
        case 7:
            response = "FETCH C";
            break;
        case 8:
            response = "FORM BXn";
            break;
        case 9: 
            response = "FORM AXn^2 +BXn";
            break;
        case 10:
            response = "FORM Yn";
            break;
        case 11:
            response = "Store Yn";
            break;
        case 12:
            response = "DEC N";
            break;
        case 13:
            response = "Again if N!= 0";
            break;
        case 14:
            response = "FETCH Xn";
            break;
        case 15:
            response = "Form Xn^2";
            break;
        case 15:
            response = "Form Xn^2";
            break;
        case 16:
            response = "Form AXn^2";
            break;
        case 17:
            response = "Form BXn";
            break;
        case 18:
            response = "Form AXn^2 + BXn";
            break;
        case 19:
            response = "Form Yn";
            break;
        case 20:
            response = "Store Yn";
            break;
        case 21:
            response = "DEC N";
            break;
        case 22:
            response = "Again if N !=0";
            break;
        default:
            response ="-1";
            break;
    }
    return response;
}
//DONE
string generateInstruction(int i, int formula) {
    string response = " ";
    switch(formula){
        case 1:
            response = generateInstructionOne(i);
            break;
        case 2:
            response = generateInstructionTwo(i);
        case 3:
            response = generateInstructionThree(i);
        default:
            response = "-1";
    }
    return response;

}
//DONE
string generateInstructionOne(int i) {
    string response = " ";
    switch(i) {
        case 1:
            response = "A1 = A1+K1";
            break;
        case 2:
            response = "A2 = A2+K2";
            break;
        case 3:
            response = "x0=X1*X1";
            break;
        case 4:
            response = "x6 = X0*X2";
            break;
        case 5:
            response = "A3=A3+K3";
            break;
        case 6:
            response = "Ax7 = x6+x3";
            break;
        case 7:
            response = "A7 = A7 + k4";
            break;

    }
    return response;

}
//DONE
string generateInstructionTwo(int i) {
    string response = " ";
    switch(i) {
        case 1:
            response = "A1 = A1+K1";
            break;
        case 2:
            response = "A2 = A2+K2";
            break;
        case 3:
            response = "x0=X1*X1";
            break;
        case 4:
            response = "x6 = X0*X2";
            break;
        case 5:
            response = "A3=A3+K3";
            break;
        case 6:
            response = "A4 = A4+K4";
            break;
        case 7:
            response = "x3 = x3*x1";
            break;
        case 8:
            response = "x5 = x6+x3";
            break;
        case 6:
            response = "x7 = x5+x4";
            break;
        case 7:
            response = "A7 = A7 + k5";
            break;

    }
    return response;

}

string generateInstructionThree(int i,string function) {
    
    //get the instruction into an array
    int Temp = function.size();
    char functionName[5];
    for(int k=0;k<=Temp;k++) {
        functionName[k] = function[k];
    }
    
    string respose = " ";

    if(functionName[0] == 'F' && functionName[1] =='O' && functionName[2] == 'R' && functionName[3] == 'M') //form
    {
        //dealing with the first time of power
        if(functionName[7] == '^')
        {
            response = "x0 = x1*x1";

        }
        else if(functionName[7] == 'A' && functionName[8] == 'X') {
            response = "x6 = x0*x2";
        }
        else if(functionName[10] == '+'){
            response = "x5 = x6+x3"; //where x3 is what is used to form BX
        }
    }
    else if(functionName[0] == 'F' && functionName[1] =='E' && functionName[2] == 'T' && functionName[3] == 'C' && functionName[4] == 'H') //fetch
    {

    }
    else if(functionName[0] == 'S' && functionName[1] =='T' && functionName[2] == 'O' && functionName[3] == 'R' && functionName[4] == 'E')//store
    {

    }
    else if(functionName[0] == 'A' && functionName[1] =='G' && functionName[2] == 'A' && functionName[3] == 'I' && functionName[4] == 'N') // again
    {

    }
    else if(functionName[0] == 'D' && functionName[1] =='E' && functionName[2] == 'C') //dec

    //get lines that are forms
    //get lines that are others 

}

//DONE
void outputTable(int i, string data[], string instructions[], string function[], int opCode []) //DONE 
{   
    cout<<"N"<<i<<" |  "<<instructions[i]<<" | "<<function[i]<<" | "
    if(opCode[i] == 0)
        <<"Long"<<" | ";
    else
        <<opCode[i]<<" | ";

        cout<<clockCycles<<" | "<<clockCycles<<" | ";
        clockCycles = clockCycles+3;
        cout<<" | "<<clockCycles;
        clockCycle++;
        cout<<" | "<<clockCycles<<" | ";
        clockCycles = clockCycles+2;
        cout<<" | "<<clockCycles<<" | ";
        clockCycles = clockCycles+4;
        cout<<" | "<<clockCycles<<" | "<<endl;

}

//DONE
int generateOpCode(string function[i]) {
    int opCode = -1;
    int TempNumOne=function.size();
    char *Codes;
    Codes = new char[TempNumOne];
    for (int a=0;a<=TempNumOne;a++)
        {
            Codes[a]=function[a];
        }
    //form // Fetch
    if(Codes[0] == 'F')
    {  
        if(Codes[1] == 'E') // Fetch
            opCode = 50;
        else if(Codes[7] == '^' || Codes[8] == '^' || (Codes[6] == 'B' && Codes[7] == 'X')) //multiplication
            opCode = 40;
        else //opcode Addition
            opCode = 30;

    }
    //Store
    else if(Codes[0] == 'S') {
        opCode = 50;
    }
    //DEC
    else if(Codes[0] == 'D') {
        opCode = 31;
    }
    //AGAIN
    else if(Codes[0] == 'A') {
        //again LONG 
        opCode = 0;

    }
    return opCode;
   
} 

