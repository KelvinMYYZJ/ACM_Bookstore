#ifndef BOOKSTORE_SRC_BOOKSTORE_BOOKSTORE_H
#define BOOKSTORE_SRC_BOOKSTORE_BOOKSTORE_H
#include <string>

#include "AccountManager.h"
#include "BookManager.h"
#include "LogSystem.h"
#include "TokenScanner.h"
using std::string;
class BookStore {
 private:
  static void (BookStore::*func_list[])(TokenScanner&);
  static const int priority_need[];
  const string name_;
  AccountManager account_manager_;
  BookManager book_manager_;
  LogSystem log_system_;

  void CheckTokenEmpty(TokenScanner& left_line);
  void CheckPriority(Operation::OpType op_type);

  void QuitCheck(TokenScanner& left_line);
  void Su(TokenScanner& left_line);
  void Logout(TokenScanner& left_line);
  void Register(TokenScanner& left_line);
  void Passwd(TokenScanner& left_line);
  void Useradd(TokenScanner& left_line);
  void Delete(TokenScanner& left_line);
  void Show(TokenScanner& left_line);
  void Buy(TokenScanner& left_line);
  void Sselect(TokenScanner& left_line);
  void Modify(TokenScanner& left_line);
  void Import(TokenScanner& left_line);

 public:
  BookStore(const string& name);
  void work();
  ~BookStore();
};

#endif  // BOOKSTORE_SRC_BOOKSTORE_BOOKSTORE_H