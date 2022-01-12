#ifndef BOOKSTORE_SRC_BOOKSTORE_ACCOUNTMANAGER_H
#define BOOKSTORE_SRC_BOOKSTORE_ACCOUNTMANAGER_H
#include "BPTree.h"
#include "Token.h"
#include "BookManager.h"

class Account {
 public:
  UserID user_id;
  Password password;
  int priority;
  Username username;
  Account();
  Account(const UserID& _user_id, const Password& _password, int _priority,
          const Username& _username);
  ~Account();
};

class AccountHash {
 public:
  UserID operator()(const Account& obj);
};

class AccountManager {
 private:
  FileMap<UserID, Account, UserID, AccountHash> account_list;
  vector<pair<UserID, BookIndex>> LoginStack;
  void LoginNoExcept(const UserID& user_id);
  Account FindAccount(const UserID& user_id);
  bool AccountExist(const UserID& user_id);
  void ChangePasswordNoExcept(const UserID& user_id,
                              const Password& new_password);
  void DeleteUserNoExcept(const UserID& user_id);

 public:
  AccountManager(const string& name);
  void LoginWithoutPassword(const UserID& user_id);
  void Login(const UserID& user_id, const Password& password);
  void Logout();
  void AddUser(const UserID& user_id, const Password& password,
               const Priority& priority, const Username& username);
  void ChangePassword(const UserID& user_id, const Password& old_password,
                      const Password& new_password);
  void ChangePasswordWithoutPassword(const UserID& user_id,
                                     const Password& new_password);
  void DeleteUser(const UserID& user_id);
  int GetPriority();
	void SelectBook(const BookIndex& book_index);
  BookIndex GetSelected();
};

#endif  // BOOKSTORE_SRC_BOOKSTORE_ACCOUNTMANAGER_H