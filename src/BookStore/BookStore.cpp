#ifndef BOOKSTORE_SRC_BOOKSTORE_BOOKSTORE_CPP
#define BOOKSTORE_SRC_BOOKSTORE_BOOKSTORE_CPP
#include <iomanip>
#include <string>
using std::string;
using namespace std::string_literals;
#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
#include "BookStore.h"
#include "Error.h"
void (BookStore::*BookStore::func_list[])(TokenScanner&) = {
    &BookStore::QuitCheck, &BookStore::Su,     &BookStore::Logout,
    &BookStore::Register,  &BookStore::Passwd, &BookStore::Useradd,
    &BookStore::Delete,    &BookStore::Show,   &BookStore::Buy,
    &BookStore::Select,    &BookStore::Modify, &BookStore::Import,

};
const int BookStore::priority_need[] = {
    0, 0, 1, 0, 1, 2, 4, 1, 1, 2, 2, 2,
};
void BookStore::CheckTokenEmpty(TokenScanner& left_line) {
  if (left_line.HasMoreToken()) throw(Error("Too much tokens"));
}
void BookStore::CheckPriority(Operation::OpType op_type) {
  if (priority_need[op_type] &&
      !(priority_need[op_type] & account_manager_.GetPriority()))
    throw(Error("Priority not allowed, current priority is "s +
                std::to_string(account_manager_.GetPriority())));
  return;
}
BookStore::BookStore(const string& name)
    : name_(name),
      account_manager_(name + "_Account"),
      book_manager_(name + "_Book"),
      log_system_(name + "_Log") {}
void BookStore::work() {
  try {
    while (true) {
      TokenScanner tmp_token_scanner(std::cin);
      if (!tmp_token_scanner.HasMoreToken()) continue;
      try {
        Operation::OpType op_type =
            Operation(tmp_token_scanner.GetNextToken()).GetType();
        if (op_type == Operation::oQuit) {
          QuitCheck(tmp_token_scanner);
          break;
        }
        CheckPriority(op_type);
        (this->*func_list[op_type])(tmp_token_scanner);
        cerr << "Succeed!" << endl;
      } catch (Error& error) {
        cout << "Invalid" << endl;
        cerr << error.what() << endl;
        continue;
      }
    }
  } catch (Error& error) {
    if (strcmp(error.what(), "Reached EOF"))
      std::cerr << "Fatal Unexpected Error:" << error.what() << endl;
    return;
  }
  return;
}

void BookStore::QuitCheck(TokenScanner& left_line) {
  if (left_line.HasMoreToken()) throw(Error("Not Plain after quit operation"));
  return;
}

void BookStore::Su(TokenScanner& left_line) {
  UserID user_id = left_line.GetNextToken();
  if (left_line.HasMoreToken()) {  // normal login
    Password password = left_line.GetNextToken();
    CheckTokenEmpty(left_line);
    account_manager_.Login(user_id, password);
  } else {  // admin login
    CheckTokenEmpty(left_line);
    account_manager_.LoginWithoutPassword(user_id);
  }
  return;
}
void BookStore::Logout(TokenScanner& left_line) {
  account_manager_.Logout();
  return;
}
void BookStore::Register(TokenScanner& left_line) {
  UserID user_id = left_line.GetNextToken();
  Password password = left_line.GetNextToken();
  Username username = left_line.GetNextToken();
  CheckTokenEmpty(left_line);
  account_manager_.AddUser(user_id, password, "1"s, username);
  return;
}
void BookStore::Passwd(TokenScanner& left_line) {
  UserID user_id = left_line.GetNextToken();
  Password password_input1 = left_line.GetNextToken();
  if (left_line.HasMoreToken()) {  // normal
    Password password_input2 = left_line.GetNextToken();
    CheckTokenEmpty(left_line);
    account_manager_.ChangePassword(user_id, password_input1, password_input2);
  } else {
    CheckTokenEmpty(left_line);
    account_manager_.ChangePasswordWithoutPassword(user_id, password_input1);
  }
  return;
}
void BookStore::Useradd(TokenScanner& left_line) {
  UserID user_id = left_line.GetNextToken();
  Password password = left_line.GetNextToken();
  Priority priority = left_line.GetNextToken();
  Username username = left_line.GetNextToken();
  if ((priority.ToInt() & account_manager_.GetPriority()) ==
      account_manager_.GetPriority())  // priority>=current_priority
    throw(Error("Adding a not less-priority account"));
  CheckTokenEmpty(left_line);
  account_manager_.AddUser(user_id, password, priority, username);
  return;
}
void BookStore::Delete(TokenScanner& left_line) {
  UserID user_id = left_line.GetNextToken();
  CheckTokenEmpty(left_line);
  account_manager_.DeleteUser(user_id);
  return;
}

void BookStore::Show(TokenScanner& left_line) {
  if (left_line.HasMoreToken() &&
      left_line.JudgeToken() == TokenScanner::tValue) {
    string tmp = left_line.GetNextToken();
    if (tmp != "finance") throw(Error("show what?"));
    if (!(account_manager_.GetPriority() & 4))
      throw(Error("you cant show finance"));
    pair<double, double> result;
    if (left_line.HasMoreToken()) {
      Quantity number = left_line.GetNextToken();
      CheckTokenEmpty(left_line);
      if (!number.ToInt()) {
        cout << endl;
        return;
      }
      result = log_system_.Show(number);
    } else {
      result = log_system_.Show();
    }
    cout << "+ " << setiosflags(std::ios::fixed) << std::setprecision(2)
         << result.first << " - " << setiosflags(std::ios::fixed)
         << std::setprecision(2) << result.second << "\n";
    return;
  }
  set<Book> tmp_show_list;
  ISBN isbn;
  BookName book_name;
  Author author;
  Keyword keyword;
  while (left_line.HasMoreToken()) {
    auto tmp_token_pair =
        left_line.GetNextToken(TokenScanner::tKeyValueWithoutQuotation);
    if (tmp_token_pair.first == "ISBN") {
      if (isbn != ""s) throw(Error("Repeated index : isbn"s));
      isbn = ISBN(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.second.front() != '\"' ||
        tmp_token_pair.second.back() != '\"' ||
        tmp_token_pair.second.size() < 2)
      throw(Error("Not a token with \" \""s));
    tmp_token_pair.second.pop_back();
    tmp_token_pair.second.erase(0, 1);
    if (tmp_token_pair.first == "name") {
      if (book_name != ""s) throw(Error("Repeated index : book_name"s));
      book_name = BookName(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.first == "author") {
      if (author != ""s) throw(Error("Repeated index : author"s));
      author = Author(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.first == "keyword") {
      if (keyword != ""s) throw(Error("Repeated index : keyword"s));
      keyword = Keyword(tmp_token_pair.second);
      continue;
    }
    throw(Error("unkown index type : "s + tmp_token_pair.first));
  }
  if (keyword != Keyword())
    tmp_show_list = book_manager_.FindBook(keyword);
  else if (isbn != ""s)
    tmp_show_list = book_manager_.FindBook(isbn);
  else if (book_name != ""s)
    tmp_show_list = book_manager_.FindBook(book_name);
  else if (author != ""s)
    tmp_show_list = book_manager_.FindBook(author);
  else
    tmp_show_list = book_manager_.FindBook();
  set<Book> show_list;
  for (const auto& tmp_book : tmp_show_list) {
    if (isbn != ""s && tmp_book.isbn != isbn) continue;
    if (book_name != ""s && tmp_book.book_name != book_name) continue;
    if (author != ""s && tmp_book.author != author) continue;
    show_list.insert(tmp_book);
  }
  if (show_list.empty()) cout << endl;
  cout << setiosflags(std::ios::fixed);
  for (const auto& tmp_book : show_list) {
    cout << tmp_book.isbn << '\t' << tmp_book.book_name << '\t'
         << tmp_book.author << '\t' << tmp_book.keyword_list << '\t'
         << setiosflags(std::ios::fixed) << std::setprecision(2)
         << tmp_book.price << '\t' << tmp_book.inventory << '\n';
  }
  return;
}

void BookStore::Buy(TokenScanner& left_line) {
  ISBN isbn = left_line.GetNextToken();
  Quantity quantity = left_line.GetNextToken();
  CheckTokenEmpty(left_line);
  double income = book_manager_.BuyBook(isbn, quantity);
  cout << setiosflags(std::ios::fixed);
  cout << std::setprecision(2) << income << endl;
  log_system_.Record(income);
  return;
}

void BookStore::Select(TokenScanner& left_line) {
  ISBN isbn = left_line.GetNextToken();
  CheckTokenEmpty(left_line);
  account_manager_.SelectBook(book_manager_.SelectBook(isbn));
  return;
}

void BookStore::Modify(TokenScanner& left_line) {
  BookIndex book_index = account_manager_.GetSelected();
  ISBN isbn;
  BookName book_name;
  Author author;
  KeywordList keyword_list;
  MoneyQuantity price;
  if (!left_line.HasMoreToken()) throw(Error("Not modified"));
  while (left_line.HasMoreToken()) {
    auto tmp_token_pair =
        left_line.GetNextToken(TokenScanner::tKeyValueWithoutQuotation);
    if (tmp_token_pair.first == "ISBN") {
      if (isbn != ""s) throw(Error("Repeated index : isbn"s));
      isbn = ISBN(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.first == "price") {
      if (price != ""s) throw(Error("Repeated index : price"s));
      price = MoneyQuantity(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.second.front() != '\"' ||
        tmp_token_pair.second.back() != '\"' ||
        tmp_token_pair.second.size() < 2)
      throw(Error("Not a token with \" \""s));
    tmp_token_pair.second.pop_back();
    tmp_token_pair.second.erase(0, 1);
    if (tmp_token_pair.first == "name") {
      if (book_name != ""s) throw(Error("Repeated index : book_name"s));
      book_name = BookName(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.first == "author") {
      if (author != ""s) throw(Error("Repeated index : author"s));
      author = Author(tmp_token_pair.second);
      continue;
    }
    if (tmp_token_pair.first == "keyword") {
      if (keyword_list != ""s) throw(Error("Repeated index : keyword"s));
      keyword_list = KeywordList(tmp_token_pair.second);
      continue;
    }
    throw(Error("unkown index type : "s + tmp_token_pair.first));
  }
  if (isbn != ""s) book_manager_.Modify(book_index, isbn);
  if (book_name != ""s) book_manager_.Modify(book_index, book_name);
  if (author != ""s) book_manager_.Modify(book_index, author);
  if (keyword_list != ""s) book_manager_.Modify(book_index, keyword_list);
  if (price != ""s) book_manager_.Modify(book_index, price);
  return;
}

void BookStore::Import(TokenScanner& left_line) {
  Quantity quantity = left_line.GetNextToken();
  MoneyQuantity cost = left_line.GetNextToken();
  CheckTokenEmpty(left_line);
  book_manager_.Import(account_manager_.GetSelected(), quantity);
  log_system_.Record(-cost.ToDouble());
  return;
}

BookStore::~BookStore() = default;
#endif  // BOOKSTORE_SRC_BOOKSTORE_BOOKSTORE_CPP