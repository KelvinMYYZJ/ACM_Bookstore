#ifndef BOOKSTORE_SRC_BOOKSTORE_TOKENSCANNER_H
#define BOOKSTORE_SRC_BOOKSTORE_TOKENSCANNER_H
#include <string>
using std::string;
#include <utility>
using std::pair;
class TokenScanner {
 private:
  string buffer;
  void RemoveLeadingZero();

 public:
  enum TokenType {
    tKeyValue,
    tKeyValueWithoutQuotation,
    tKeyValueWithQuotation,
		tValue,
  };
  // tKeyValue means : -Key=Value
  // tKeyValueWithQuotation means : -Key="Value"
  TokenScanner(const string& str);
  TokenScanner(std::istream& os);
  bool HasMoreToken() const;
  string GetNextToken();
  pair<string, string> GetNextToken(const TokenType&);
	TokenType JudgeToken();
};
#endif  // BOOKSTORE_SRC_BOOKSTORE_TOKENSCANNER_H