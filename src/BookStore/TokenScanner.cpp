#ifndef BOOKSTORE_SRC_BOOKSTORE_TOKENSCANNER_CPP
#define BOOKSTORE_SRC_BOOKSTORE_TOKENSCANNER_CPP
#include "TokenScanner.h"

#include <iostream>

#include "Error.h"
void TokenScanner::RemoveLeadingZero() {
  if (buffer.empty()) return;
  buffer.erase(buffer.find_last_not_of(' ') + 1);
  return;
}
TokenScanner::TokenScanner(const string& str) : buffer(str) {
		throw (Error("line too long"));
  RemoveLeadingZero();
}
TokenScanner::TokenScanner(std::istream& os) {
  if (!getline(os, buffer)) throw(Error("Reached EOF"));
	if (buffer.size() > 1024)
		throw (Error("line too long"));
  RemoveLeadingZero();
  return;
}
bool TokenScanner::HasMoreToken() const { return !buffer.empty(); }
TokenScanner::TokenType TokenScanner::JudgeToken() {
  if (buffer.find_first_not_of(' ') == buffer.find_first_of('-'))
    return tKeyValue;
  return tValue;
}
string TokenScanner::GetNextToken() {
  if (!HasMoreToken()) throw(Error("Can't get token: No token left"));
  buffer.erase(0, buffer.find_first_not_of(' '));
  string tmp_token = buffer.substr(0, buffer.find_first_of(' '));
  buffer.erase(0, buffer.find_first_of(' '));
  return tmp_token;
}
pair<string, string> TokenScanner::GetNextToken(const TokenType& token_type) {
  string tmp = GetNextToken();
  pair<string, string> ans;
  if (tmp.find_first_of('=') == string::npos || tmp.front() != '-')
    throw(Error("Not a K-V type token"));
  tmp.erase(0, 1);
  ans.first = tmp.substr(0, tmp.find_first_of('='));
  ans.second = tmp.substr(tmp.find_first_of('=') + 1);
  if (token_type == tKeyValueWithQuotation) {
    if (ans.second.front() != '\"' || ans.second.back() != '\"' ||
        ans.second.size() < 2)
      throw(Error("Not a token with \" \""));
    ans.second.pop_back();
    ans.second.erase(0, 1);
  }
  if (token_type == tKeyValue && ans.second.front() == '\"' &&
      ans.second.back() == '\"' && ans.second.size() >= 2) {
    ans.second.pop_back();
    ans.second.erase(0, 1);
  }
  return ans;
}
#endif  // BOOKSTORE_SRC_BOOKSTORE_TOKENSCANNER_CPP