//Tiffani Dutton Katie Isabel, David Zemon, Ben...
//CDC 6600 implimentation file



#include "CDC6600.h"
#include <fstream>
#include <string>


int main () {
  welcome();
  int formula = displayOptions();
  //TODO: FIX MAIN 
  calculateChart(array,formula);
  goodbye();

  return 0;
}