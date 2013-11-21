//Tiffani Dutton Katie Isabel, David Zemon, Ben...
//CDC 6600 implimentation file




#include "generator.cpp"


int main (int argc, char *argv[]) {

//the main part of this is to generate the output
//prompt the user to enter the function? 
 //assuming  tat argv[1] is filename to open



//function to get the data
//create a struct called formula that gets the data back




struct formula = getValidData(argv[0]);

//after we have the formula we want to compute we can pass into a function that can generate the data
generateData(formula);

goodbye();

	return 0;
}