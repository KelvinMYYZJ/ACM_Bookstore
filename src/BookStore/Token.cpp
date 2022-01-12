#ifndef BOOKSTORE_SRC_BOOKSTORE_TOKEN_CPP
#define BOOKSTORE_SRC_BOOKSTORE_TOKEN_CPP
#include "Token.h"

#include <set>
using std::set;
#include <string>
using namespace std::string_literals;
using std::string;
#include <cctype>
#include <functional>

#include "Error.h"
#pragma region StringCheck
enum class CharsetType : unsigned int {
  cDigit = 1,
  cAlpha = 2,
  cUnderLine = 4,
  cPrintable = 8,
  cPrintableWithoutQuotation = 16,
  cDot = 32
};
bool operator&(const CharsetType& lhs, const CharsetType& rhs) {
  return (unsigned int)(lhs) & (unsigned int)(rhs);
}
CharsetType operator|(const CharsetType& lhs, const CharsetType& rhs) {
  return CharsetType((unsigned int)(lhs) | (unsigned int)(rhs));
}

bool IsIllegal(const char& ch, const CharsetType& charset) {
  if (charset & CharsetType::cDigit)
    if (std::isdigit(ch)) return false;
  if (charset & CharsetType::cAlpha)
    if (std::isalpha(ch)) return false;
  if (charset & CharsetType::cUnderLine)
    if (ch == '_') return false;
  if (charset & CharsetType::cPrintable)
    if (std::isprint(ch)) return false;
  if (charset & CharsetType::cPrintableWithoutQuotation)
    if (std::isprint(ch) && ch != '\"') return false;
  if (charset & CharsetType::cDot)
    if (ch == '.') return false;
  return true;
}

int FindIllegal(const string& str, const CharsetType& charset) {
  auto illegal_iter =
      std::find_if(str.begin(), str.end(),
                   std::bind(IsIllegal, std::placeholders::_1, charset));
  return std::distance(str.begin(), illegal_iter);
}
#pragma endregion StringCheck

#pragma region Operation
Operation::Operation() : MyString() {}
Operation::Operation(const string& other) : MyString(other) {
  if (Length() > 10) throw(Error(string("Operation too long : ") + ToString()));
  if (other == "quit" || other == "exit") {
    Type = OpType::oQuit;
    return;
  }
  if (other == "su") {
    Type = OpType::oSu;
    return;
  }
  if (other == "logout") {
    Type = OpType::oLogout;
    return;
  }
  if (other == "register") {
    Type = OpType::oRegister;
    return;
  }
  if (other == "passwd") {
    Type = OpType::oPasswd;
    return;
  }
  if (other == "useradd") {
    Type = OpType::oUseradd;
    return;
  }
  if (other == "delete") {
    Type = OpType::oDelete;
    return;
  }
  if (other == "show") {
    Type = OpType::oShow;
    return;
  }
  if (other == "buy") {
    Type = OpType::oBuy;
    return;
  }
  if (other == "select") {
    Type = OpType::oSelect;
    return;
  }
  if (other == "modify") {
    Type = OpType::oModify;
    return;
  }
  if (other == "import") {
    Type = OpType::oImport;
    return;
  }
  throw(Error("Invaild operation name"s + other));
  return;
}

Operation::OpType Operation::GetType() const { return Type; }

Operation::~Operation() = default;
#pragma endregion Operation

#pragma region UserID
UserID::UserID() : MyString() {}
UserID::UserID(const string& other) : MyString(other) {
  if (Length() > 30) throw(Error(string("UserID too long : ") + ToString()));
  int first_illegal_pos =
      FindIllegal(other, CharsetType::cDigit | CharsetType::cAlpha |
                             CharsetType::cUnderLine);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in UserID, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

UserID::~UserID() = default;
#pragma endregion UserID

#pragma region Password
Password::Password() : MyString() {}
Password::Password(const string& other) : MyString(other) {
  if (Length() > 30) throw(Error(string("Password too long : ") + ToString()));
  int first_illegal_pos =
      FindIllegal(other, CharsetType::cDigit | CharsetType::cAlpha |
                             CharsetType::cUnderLine);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in Password, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

Password::~Password() = default;
#pragma endregion Password

#pragma region Username
Username::Username() : MyString() {}
Username::Username(const string& other) : MyString(other) {
  if (Length() > 30) throw(Error(string("Username too long : ") + ToString()));
  int first_illegal_pos = FindIllegal(other, CharsetType::cPrintable);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in Username, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

Username::~Username() = default;
#pragma endregion Username

#pragma region Priority
Priority::Priority() : MyString() {}
Priority::Priority(const string& other) : MyString(other) {
  if (Length() > 1) throw(Error(string("Priority too long : ") + ToString()));
  int first_illegal_pos = FindIllegal(other, CharsetType::cDigit);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in Priority, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

int Priority::ToInt() const { return (*this)[0] - '0'; }

Priority::~Priority() = default;
#pragma endregion Priority

#pragma region ISBN
ISBN::ISBN() : MyString() {}

ISBN::ISBN(const string& other) : MyString(other) {
  if (Length() > 20) throw(Error(string("ISBN too long : ") + ToString()));
  int first_illegal_pos = FindIllegal(other, CharsetType::cPrintable);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in ISBN, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

ISBN::~ISBN() = default;
#pragma endregion ISBN

#pragma region BookName
BookName::BookName() : MyString() {}

BookName::BookName(const string& other) : MyString(other) {
  if (Length() > 60) throw(Error(string("BookName too long : ") + ToString()));
  int first_illegal_pos =
      FindIllegal(other, CharsetType::cPrintableWithoutQuotation);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in BookName, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

BookName::~BookName() = default;
#pragma endregion BookName

#pragma region Author
Author::Author() : MyString() {}

Author::Author(const string& other) : MyString(other) {
  if (Length() > 60) throw(Error(string("Author too long : ") + ToString()));
  int first_illegal_pos =
      FindIllegal(other, CharsetType::cPrintableWithoutQuotation);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in Author, postion : ") +
                std::to_string(first_illegal_pos)));
  return;
}

Author::~Author() = default;
#pragma endregion Author

#pragma region KeywordList
KeywordList::KeywordList() : MyString() {}

KeywordList::KeywordList(const string& other) : MyString(other) {
  if (Length() > 60)
    throw(Error(string("KeywordList too long : ") + ToString()));
  int first_illegal_pos = FindIllegal(other, CharsetType::cPrintable);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in KeywordList, postion : ") +
                std::to_string(first_illegal_pos)));
  // check repeated keywords
  set<Keyword> ans;
  string tmp_string = ToString();
  while (!tmp_string.empty()) {
    int a = tmp_string.find_first_of('|');
    if (a) {
      int lst_size = ans.size();
      ans.insert(tmp_string.substr(0, a));
      if (lst_size == ans.size())
        throw(Error("Repeated keyword : "s + tmp_string.substr(0, a)));
    }
    tmp_string.erase(0, a);
    if (!tmp_string.empty()) tmp_string.erase(0, 1);
  }
  return;
}

vector<Keyword> KeywordList::ToList() const {
  vector<Keyword> ans;
  string tmp_string = ToString();
  while (!tmp_string.empty()) {
    int a = tmp_string.find_first_of('|');
    if (a) ans.push_back(tmp_string.substr(0, a));
    tmp_string.erase(0, a);
    if (!tmp_string.empty()) tmp_string.erase(0, 1);
  }
  return ans;
}

KeywordList::~KeywordList() = default;
#pragma endregion KeywordList

#pragma region Keyword
Keyword::Keyword() : MyString() {}

Keyword::Keyword(const string& other) : MyString(other) {
  if (Length() > 60)
    throw(Error(string("Keyword too long : ") + ToString()));
  int first_illegal_pos = FindIllegal(other, CharsetType::cPrintable);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in Keyword, postion : ") +
                std::to_string(first_illegal_pos)));
	if (other.find_first_of('|') != string::npos)
		throw("Multiple keywords in keyword");
}

Keyword::~Keyword() = default;
#pragma endregion Keyword

#pragma region Quantity
Quantity::Quantity() : MyString() {}

Quantity::Quantity(const string& other) : MyString(other) {
  if (Length() > 10) throw(Error(string("Quantity too long : ") + ToString()));
  int first_illegal_pos = FindIllegal(other, CharsetType::cDigit);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in Quantity, postion : ") +
                std::to_string(first_illegal_pos)));
  if (Length() == 10 && "2147483647"s < other) throw("Quantity too large");
  return;
}

long long Quantity::ToInt() const {
  long long ans = 0;
  string tmp = ToString();
  for (int i = 0; i < Length(); i++) ans = ans * 10 + tmp[i] - '0';
  return ans;
}

Quantity::~Quantity() = default;
#pragma endregion Quantity

#pragma region MoneyQuantity
MoneyQuantity::MoneyQuantity() : MyString() {}

MoneyQuantity::MoneyQuantity(const string& other) : MyString(other) {
  if (Length() > 13)
    throw(Error(string("MoneyQuantity too long : ") + ToString()));
  int first_illegal_pos =
      FindIllegal(other, CharsetType::cDigit | CharsetType::cDot);
  if (first_illegal_pos < Length())
    throw(Error(string("Invaild charactor in MoneyQuantity, postion : ") +
                std::to_string(first_illegal_pos)));
  if (other.find_first_of('.') != other.find_last_of('.'))
    throw(Error("Too much . in MoneyQuantity"));
  return;
}

double MoneyQuantity::ToDouble() const { return stod(ToString()); }

MoneyQuantity::~MoneyQuantity() = default;
#pragma endregion MoneyQuantity

#endif  // BOOKSTORE_SRC_BOOKSTORE_TOKEN_CPP