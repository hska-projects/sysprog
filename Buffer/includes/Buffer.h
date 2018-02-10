/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/stat.h>
class Buffer {
public:
	char *next,*buf1,*buf2;
	int file_;
	int write_;
	int nbytes;
	int readbytes;
	int counter;
	bool end;
	int line;
	int collumn;
	int prevCol;
	bool wasEndOfFile;
	bool buf1WasReload;
	bool buf2WasReload;
	Buffer(const char *const fileName);
	~Buffer();

	void closeFile();
	int getLine();
	int getCollumn();
	bool endfile();
	int reload(char* buf);
	char getChar();
	char unGetChar();
};

#endif /* BUFFER_H_ */
