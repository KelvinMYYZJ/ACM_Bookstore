#ifndef BOOKSTORE_SRC_BOOKSTORE_LOGSYSTEM_H
#define BOOKSTORE_SRC_BOOKSTORE_LOGSYSTEM_H
#include <utility>
using std::pair;
#include "FileMemPool.h"
#include "Token.h"
class LogSystem {
 private:
  FileMemPool index_file_;
  FileMemPool record_file_;
  int lst;

 public:
  LogSystem(const string& name_);
  void Record(const double& money);
  pair<double, double> Show();
  pair<double, double> Show(const Quantity& times);
  ~LogSystem();
};
#endif  // BOOKSTORE_SRC_BOOKSTORE_LOGSYSTEM_H