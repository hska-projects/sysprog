#include "../includes/Automat.h"
#include <iostream>

int main (int argc, char* argv[]){
	Automat* automat;

	automat = new Automat();


	automat->determineState('=');
	std::cout << automat->getState() << std::endl;
	if (automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState(':');
	std::cout << automat->getState() << std::endl;
	if (automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('=');
	std::cout << automat->getState() << std::endl;
	if (automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	if(automat->isGoBack()) {
		std::cout << "GoBack" << std::endl;
	}
	automat->determineState('&');
	std::cout << automat->getState() << std::endl;
	if (automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('&');
	std::cout << automat->getState() << std::endl;
	if (automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('2');
		std::cout << automat->getState() << std::endl;
		if (automat->isFinalState()) {
			std::cout << "Final" << std::endl;
			automat->initAutomat();
		}
	/*	
	while(!automat->isFinalState()) {
		automat->determineState(c[i]);
		i++;
	}*/

/*
	automat->determineState(':');
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('*');
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('a');
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('b');	
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('*');
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState(':');
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('2');	
		std::cout << automat->getState() << std::endl;
		if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState(':');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	
	automat->determineState(':');
			std::cout << automat->getState() << std::endl;
			if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('=');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('a');
			std::cout << automat->getState() << std::endl;
			if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('1');
			std::cout << automat->getState() << std::endl;
			if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState(' ');
			std::cout << automat->getState() << std::endl;
			if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
			
	automat->determineState('1');
			std::cout << automat->getState() << std::endl;
			if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('!');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	
	automat->determineState('h');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('1');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('a');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('!');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}
	automat->determineState('!');
		std::cout << automat->getState() << std::endl;
	if(automat->isFinalState()) {
		std::cout << "Final" << std::endl;
		automat->initAutomat();
	}

 */
}
