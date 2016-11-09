#ifndef SYMBOLTABLE_SRC_MYSTRING_H_
#define SYMBOLTABLE_SRC_MYSTRING_H_

class myString {
private:
	// 'myString' is represented internally as a plain C-style myString.
	int size;
	char* str;

public:
	myString();
	myString(char c);
	myString(const char *);
	myString(const myString&);
	~myString();

	int compare(myString&);
	char* getStr();
	int getLen();

	char& operator[](int index);
	myString& operator=(myString&);
	myString& operator+=(myString&);
};

#endif
