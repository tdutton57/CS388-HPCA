//Tiffani Dutton, Katie Isabel, David Zemon, Ben


#ifndef GENERATOR_H
#define GENERATOR_H



class Generator {


	public:
	Generator();
	Generator(char firstValue, char secondValue, char thirdValue, int operation);
	~Generator(); 

	//get valid data will take in the first arguement of the program
	//and translate it into data.
	void getValidData(char value);

	//generate data
	//needs to take in a struct 
	//will generate the table and do the calculations 
	void generateData(Generator formula); 


	//says goodbye to the user
	//void function
	void goodbye();


	char mFirstValue;
	char mSecondValue;
	char mThirdValue;
	int mOperation; //will be 1 if + 2 if - 3 if * 4 if / and 5 if % 

};

#endif 

