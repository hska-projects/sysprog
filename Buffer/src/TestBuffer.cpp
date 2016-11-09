#include "../includes/Buffer.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

	Buffer*  buffer;
	buffer = new Buffer();
//	printf(buffer->next);
	printf("_\n");
	char c;
	int end=400;
	c=buffer->getChar();
	while(c!=NULL){
		if(buffer->endfile()){
			printf("ende erreicht");
		}
//	for(int i=0;i<end;i++){
		c=buffer->getChar();
		if (c==NULL){
			printf(" NULL ");
//			i=end;
		}else{
		printf("%c",c);
	//	printf("_\n");
		}
		printf(" Line %i",buffer->getLine());
		printf(" Collumn %i \n",buffer->getCollumn());
	}

	printf("_\n");
	c=buffer->unGetChar();
	while(c!=NULL){

//	for(int i=0;i<end;i++){
		c=buffer->unGetChar();
		if (c==NULL){
			printf(" NUlL ");
//			i=end;
		}else{
		printf("%c",c);
		}
	}
		printf("_\n");
}
