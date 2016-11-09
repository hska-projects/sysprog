#include "../includes/myString.h"

myString::myString() {
	size = 0;
	str = new char[1];
	str[0] = '\0';
}

myString::myString(char c) {
	size = 1;
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
}

myString::myString(const char *s) {
	// TODO
	int c = 0;
	while (s[c] != '\0')
		c++;
	size = c;
	//size = strlen(s);
	str = new char[size + 1];
	for (int i = 0; i < size; i++)
		str[i] = s[i];
	str[size] = '\0';
}

myString::myString(const myString& s) {
	// TODO
	size = s.size;
	str = new char[size + 1];
	for (int i = 0; i < size; i++)
		str[i] = s.str[i];

	if (str[size] != '\0')
		str[size] = '\0';
}

myString::~myString() {
	delete[] str;
}

int myString::compare(myString& s) {
	const char* s1 = str;
	const char* s2 = s.str;

	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

char& myString::operator[](int index) {
	// TODO
	return str[index - 1];
}

char* myString::getStr() {
	// TODO
	return str;
}

int myString::getLen() {
	// TODO
	return size;
}

myString& myString::operator=(myString& s) {
	// TODO
	size = s.size;
	str = new char[size + 1];
	for (int i = 0; i < size; i++)
		str[i] = s.str[i];
	str[size] = '\0';
	return *this;
}

myString& myString::operator+=(myString& s) {
	// TODO
	int newSize = size + s.size;
	char* temp = str;
	str = new char[newSize + 1];
	for (int i = 0; i < size; i++)
		str[i] = temp[i];

	for (int k = size, j = 0; k < newSize; k++, j++)
		str[k] = s.str[j];

	if (str[newSize] != '\0')
		str[newSize] = '\0';
	size = newSize;
	delete[] temp;
	return *this;
}
