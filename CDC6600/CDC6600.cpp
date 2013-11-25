//Tiffani Dutton Katie Isabel, David Zemon, Ben...
//CDC 6600 implimentation file



#include "CDC6600.h"
#include <fstream>
#include <string>


int main () {
  int max=8;
  string array[max];
  int value = 0;

  string line;
  ifstream myfile ("info.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      array[value] = line;
      value++;
    }
    myfile.close();
  }
  else {
  	cout<<"unable to open file"<<endl;
  }

  outputVariables(array);
  calculateChart(array);
  goodbye();


  return 0;
}