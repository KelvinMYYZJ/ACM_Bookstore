#ifndef BOOKSTORE_SRC_MYSTRING_H
#define BOOKSTORE_SRC_MYSTRING_H
#include <cstring>
#include <string>
#include "DefaultConst.cpp"
using std::string;
class MyString;
class MyString {
 private:
  char str[string_size];

 public:
  MyString();
  MyString(const char* other);
  MyString(string other);
  int Length()const;
	MyString& operator=(const MyString& other);
	friend bool operator<(const MyString& lhs,const MyString& rhs);
	friend bool operator>(const MyString& lhs,const MyString& rhs);
	friend bool operator<=(const MyString& lhs,const MyString& rhs);
	friend bool operator>=(const MyString& lhs,const MyString& rhs);
	friend bool operator==(const MyString& lhs,const MyString& rhs);
	friend bool operator!=(const MyString& lhs,const MyString& rhs);
	friend std::istream& operator>>(std::istream& lhs,MyString& rhs);
	friend std::ostream& operator<<(std::ostream& lhs,const MyString& rhs);
	string ToString()const;
	operator string();
	char& operator[](int index);
	char operator[](int index)const;
};
#endif  // BOOKSTORE_SRC_MYSTRING_H