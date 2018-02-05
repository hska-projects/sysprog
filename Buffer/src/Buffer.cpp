/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#include "../includes/Buffer.h"
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

using std::cerr;

static int openFileReadOnly(const char* name)
{
  int fd;
  if ((fd = open(name, O_RDONLY | O_DIRECT)) < 0) {
    printf("Could not open '%s'", name);
  }
  return fd;
}

static int openFileWrite() {
	int fd = open("code.txt", O_RDWR);
	return fd;
}


Buffer::Buffer(const char *const fileName){
	end = false;
	line = 1;
	collumn = 1;
	buf2WasReload = false;
	buf1WasReload = false;
	wasEndOfFile = false;
	prevCol = 1;
	int err1 = posix_memalign((void**) &buf1, 512, 512);
	if (err1) {
		cerr << "Buffer Error 1.";
	}
	int err2 = posix_memalign((void**) &buf2, 512, 512);
	if (err2) {
		cerr << "Buffer Error 2.";
	}

	file_ = openFileReadOnly(fileName);

	if(file_<0){
		cerr << "File not found.\n";
	} else {
		nbytes = 512;
		counter = 0;
		//printf("%i",nbytes);
		readbytes = read(file_, buf1, nbytes);
		next = buf1;
	}


	write_ = openFileWrite();
}


void Buffer::writeCode(char* c){
	int nbyte = 0;
		while (c[nbyte] != '\0'){
			nbyte++;
		}
	write(write_, c, nbyte);
}


void Buffer::closeFile(){
	free (buf1);
	free (buf2);
	close(file_);
}

Buffer::~Buffer() {
	free (buf1);
	free (buf2);
	close (file_);
}
int Buffer::getLine(){
	return line;
}
int Buffer::getCollumn(){
	return collumn;
}
bool Buffer::endfile(){
//	return file_.eof();	
	return end;
}

int Buffer::reload(char* buf){
	counter = nbytes+1;

	for(int i = 0;i < nbytes;i++){
		buf[i]='\0';
	}
	readbytes = read(file_, buf, nbytes);
	//printf("\n | \n");
	return readbytes;
}
//gibt das Naechste Zeichen aus;
// gibt NULL zurück wenn des Ende der File erreicht ist
char Buffer::getChar() {
	counter++;
	char c = next[0];

	if (c == '\0') {
		if (readbytes == nbytes) {

			if (next == &buf1[nbytes]) {
				if (buf2WasReload == false) {
					reload(buf2);
					buf2WasReload = true;
					buf1WasReload = false;
				} else {
					buf2WasReload = false;
				}
				next = buf2;
			}

			if (next == &buf2[nbytes]) {
				if (buf1WasReload == false) {
					reload(buf1);
					buf1WasReload = true;
					buf2WasReload = false;
				} else {
					buf1WasReload = false;
				}
				next = buf1;
			}

		} else {

//			printf("oEOF");
		}

	} else {
		//printf("NichtNuLL\n");
	}
	c = next[0];
	next++;

	if (next[0] == '\0' && readbytes < nbytes) {
		end = true;
	} else if (c == '\n') {
		line++;
		prevCol = collumn;
		collumn = 1;
	} else if (c == '\t') {
		collumn += 8;
	} else {
		collumn++;
	}

	return c;
}
//gibt pro Aufruf das naechst letzte Zeichen aus.
//gibt Null zurück wenn kein weiteres letztes Zeichen geladen werden kann.

char Buffer::unGetChar(){
	//if(endfile()){
//		next--;
	//	end=false;
//	}
	char c;
	if(counter==0){
		c='\0';//EOF
	}else{
		counter --;
		next --;
		if(next[0]=='\0'){ //Dateianfang
			//return NULL;
		}
		c = next[0];
	}
	
	if(&next[0]==&buf1[0]){
		next=&buf2[nbytes];
		buf1WasReload = true;
	}else if(&next[0]==&buf2[0]){
		next=&buf1[nbytes];
		buf2WasReload = true;
	}
	
	if(c=='\0'){
		end=true;
	} else if(c=='\n'){
		line--;
		collumn=prevCol;	
	} else {
		collumn--;
	}

	return c;
}
