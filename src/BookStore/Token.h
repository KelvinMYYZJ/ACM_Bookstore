#ifndef BOOKSTORE_SRC_BOOKSTORE_TOKEN_H
#define BOOKSTORE_SRC_BOOKSTORE_TOKEN_H
#include <vector>
using std::vector;
#include "MyString.h"
enum class CharsetType : unsigned int;
bool operator&(const CharsetType& lhs, const CharsetType& rhs);
CharsetType operator|(const CharsetType& lhs, const CharsetType& rhs);
bool IsIllegal(const char& ch, const CharsetType& charset);
int FindIllegal(const string& str, const CharsetType& charset);
void CheckCharset(const string& str, const CharsetType& charset);
class Operation : public MyString {
 public:
  enum OpType {
    oQuit,
    oSu,
    oLogout,
    oRegister,
    oPasswd,
    oUseradd,
    oDelete,
    oShow,
    oBuy,
    oSelect,
    oModify,
    oImport,
    /*
  oReport,
  oShow,
  oReport,
  oReport,
  oLog */
  };

 private:
  OpType Type;

 public:
  Operation();
  Operation(const string& other);
  OpType GetType() const;
  ~Operation();
};
class UserID : public MyString {
 public:
  UserID();
  UserID(const string& other);
  ~UserID();
};

class Password : public MyString {
 public:
  Password();
  Password(const string& other);
  ~Password();
};

class Username : public MyString {
 public:
  Username();
  Username(const string& other);
  ~Username();
};

class Priority : public MyString {
 public:
  Priority();
  Priority(const string& other);
  int ToInt() const;
  ~Priority();
};

class ISBN : public MyString {
 public:
  ISBN();
  ISBN(const string& other);
  ~ISBN();
};

class BookName : public MyString {
 public:
  BookName();
  BookName(const string& other);
  ~BookName();
};

class Author : public MyString {
 public:
  Author();
  Author(const string& other);
  ~Author();
};

class Keyword : public MyString {
 public:
  Keyword();
  Keyword(const string& other);
  ~Keyword();
};

class KeywordList : public MyString {
 public:
  KeywordList();
  KeywordList(const string& other);
  vector<Keyword> ToList() const;
  ~KeywordList();
};

class Quantity : public MyString {
 public:
  Quantity();
  Quantity(const string& other);
  long long ToInt() const;
  ~Quantity();
};

class MoneyQuantity : public MyString {
 public:
  MoneyQuantity();
  MoneyQuantity(const string& other);
  double ToDouble() const;
  ~MoneyQuantity();
};

#endif  // BOOKSTORE_SRC_BOOKSTORE_TOKEN_H