#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

string randWalk()
{
	double ratio = (double) rand()/(RAND_MAX);
	string keyPress;
	if (ratio <0.25){
		keyPress = "w";
	}
	else if(ratio>=0.25 && ratio<0.5){
		keyPress = "s";
	}
	else if(ratio>=0.5 && ratio<0.75){
		keyPress = "a";
	} 
	else if(ratio>=0.75 && ratio<1){
		keyPress = "d";
	}
	return keyPress;
	
}
