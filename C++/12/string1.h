#include <iostream>
#ifndef STRNGBAD_H_
#define STRNGBAD_H_
using std::ostream;
using std::istream;

class String
{
private:
	char * str;
	int len;
	static int num_strings;
	static const int CINLIM = 80;
public:
	String(const char * s);
	String();
	String(const String &);
	~String();
	int length() const { return len;}

	//over loaded oprator methods
	String & operator=(const String &);
	String & operator=(const char *);
	char & operator[](int i);
	const char & operator[] (int i) const;

	//overloaded opertor friends
	friend bool operator<(const String &st, const String &st2);
	friend bool operator>(const String &st1, const String &st2);
	friend bool operator==(const String &st, const String &st2);
	friend ostream & operator<<(ostream & os, const String & st);
	friend istream & operator>>(istream & is, String & st);

	// static function
	static int HowMany();
	// friend std::ostream & operator << (std::ostream & os,
	// 									const StringBad & st);
	// String(const StringBad & st);
	// String & operator=(const StringBad & st);


};
#endif