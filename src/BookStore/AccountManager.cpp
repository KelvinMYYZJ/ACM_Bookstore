#ifndef BOOKSTORE_SRC_BOOKSTORE_ACCOUNTMANAGER_CPP
#define BOOKSTORE_SRC_BOOKSTORE_ACCOUNTMANAGER_CPP
#include "AccountManager.h"

#include "Error.h"
using namespace std::string_literals;
#pragma region Account
Account::Account() = default;

Account::Account(const UserID& _user_id, const Password& _password,
                 int _priority, const Username& _username)
    : user_id(_user_id),
      password(_password),
      priority(_priority),
      username(_username) {}

Account::~Account() = default;
#pragma endregion Account

#pragma region AccountHash
UserID AccountHash::operator()(const Account& obj) { return obj.user_id; }
#pragma endregion AccountHash

#pragma region AccountManager
AccountManager::AccountManager(const string& name)
    : account_list(name + "_account_list") {
  if (account_list.Find("root"s).empty())
    AddUser("root"s, "sjtu"s, "7"s, "root"s);
  return;
}

void AccountManager::LoginNoExcept(const UserID& user_id) {
  LoginStack.push_back({std::make_pair(user_id, BookIndex())});
  return;
}

void AccountManager::ChangePasswordNoExcept(const UserID& user_id,
                                            const Password& new_password) {
  Account target_account = FindAccount(user_id);
  account_list.Erase(user_id, target_account);
  target_account.password = new_password;
  account_list.Insert(user_id, target_account);
  return;
}

void AccountManager::DeleteUserNoExcept(const UserID& user_id) {
  Account target_account = FindAccount(user_id);
  account_list.Erase(user_id, target_account);
  return;
}
Account AccountManager::FindAccount(const UserID& user_id) {
  vector<Account> target_account_list =
      account_list.Find(user_id);  // size must be 0 or 1
  if (target_account_list.empty())
    throw(Error("Non-existing UserID : "s + user_id.ToString()));
  if (target_account_list.size() > 1)
    throw(Error("Fatal Error : Repeated UserID"));
  return target_account_list[0];
}

bool AccountManager::AccountExist(const UserID& user_id) {
  vector<Account> target_account_list =
      account_list.Find(user_id);  // size must be 0 or 1
  if (target_account_list.size() > 1)
    throw(Error("Fatal Error : Repeated UserID"));
  return !target_account_list.empty();
}

void AccountManager::LoginWithoutPassword(const UserID& user_id) {
  Account target_account = FindAccount(user_id);
  if ((GetPriority() & target_account.priority) ^ target_account.priority)
    throw(Error("Need password! Account \""s + user_id.ToString() +
                "\" has priority " + std::to_string(target_account.priority)));
  LoginNoExcept(user_id);
  return;
}

void AccountManager::Login(const UserID& user_id, const Password& password) {
  Account target_account = FindAccount(user_id);
  if (target_account.password != password)
    throw(Error("Wrong password! Correct Password is \""s +
                target_account.password.ToString() + "\""));
  LoginNoExcept(user_id);
  return;
}

void AccountManager::Logout() {
  if (LoginStack.empty()) throw Error("No account is online");
  LoginStack.pop_back();
  return;
}
void AccountManager::AddUser(const UserID& user_id, const Password& password,
                             const Priority& priority,
                             const Username& username) {
  Account target_account(user_id, password, priority.ToInt(), username);
  if (AccountExist(user_id))
    throw Error("UserID Already exists : "s + user_id.ToString());
  account_list.Insert(user_id, target_account);
  return;
}

int AccountManager::GetPriority() {
  if (LoginStack.empty()) return 0;
  return FindAccount(LoginStack.back().first).priority;
}

void AccountManager::SelectBook(const BookIndex& book_index) {
  LoginStack.back().second = book_index;
  return;
}

BookIndex AccountManager::GetSelected() {
  if (LoginStack.empty())
    throw Error("No Account is online so no book is selected"s);
  if (LoginStack.back().second == BookIndex())
    throw Error("Current Account didn't selected any book"s);
  return LoginStack.back().second;
}

void AccountManager::ChangePassword(const UserID& user_id,
                                    const Password& old_password,
                                    const Password& new_password) {
  Account target_account = FindAccount(user_id);
  if (target_account.password != old_password)
    throw(Error("Wrong old password! Correct Password is \""s +
                target_account.password.ToString() + "\""));
  ChangePasswordNoExcept(user_id, new_password);
  return;
}

void AccountManager::ChangePasswordWithoutPassword(
    const UserID& user_id, const Password& new_password) {
  FindAccount(user_id);
  if (!(GetPriority() & 7))
    throw Error("Non-root changing password without old password");
  ChangePasswordNoExcept(user_id, new_password);
  return;
}

void AccountManager::DeleteUser(const UserID& user_id) {
  Account target_account = FindAccount(user_id);
  for (auto tmp_pair : LoginStack)
    if (tmp_pair.first == user_id)
      throw Error("Delete online account : "s + user_id.ToString());
  DeleteUserNoExcept(user_id);
  return;
}

#pragma endregion AccountManager
#endif  // BOOKSTORE_SRC_BOOKSTORE_ACCOUNTMANAGER_CPP