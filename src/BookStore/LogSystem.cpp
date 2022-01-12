#ifndef BOOKSTORE_SRC_BOOKSTORE_LOGSYSTEM_CPP
#define BOOKSTORE_SRC_BOOKSTORE_LOGSYSTEM_CPP
#include "LogSystem.h"

#include "Error.h"
LogSystem::LogSystem(const string& name_)
    : index_file_(name_ + "_index_file"),
      record_file_(name_ + "_record_file") {}

void LogSystem::Record(const double& money) {
  auto ptr = record_file_.fnew(money);
  index_file_.modify(FilePtr<FilePtr<double>>(0), ptr);
}

pair<double, double> LogSystem::Show() {
  pair<double, double> ans;
  if (index_file_.Empty()) return ans;
  FilePtr<double> tmp_ptr = index_file_.fread(FilePtr<FilePtr<double>>(0));
  while (tmp_ptr.Get_Pos()) {
    double tmp_price = record_file_.fread(tmp_ptr);
    if (tmp_price > 0)
      ans.first += tmp_price;
    else
      ans.second -= tmp_price;
    --tmp_ptr;
  }
  double tmp_price = record_file_.fread(tmp_ptr);
  if (tmp_price > 0)
    ans.first += tmp_price;
  else
    ans.second -= tmp_price;
  return ans;
}

pair<double, double> LogSystem::Show(const Quantity& quantity) {
  long long tmp_number = quantity.ToInt();
  pair<double, double> ans;
  if (index_file_.Empty()) throw(Error("not enough trade"));
  FilePtr<double> tmp_ptr = index_file_.fread(FilePtr<FilePtr<double>>(0));
  if (tmp_ptr.Get_Pos() / sizeof(double) + 1 < tmp_number)
    throw(Error("not enough trade"));
  while (tmp_number--) {
    double tmp_price = record_file_.fread(tmp_ptr);
    if (tmp_price > 0)
      ans.first += tmp_price;
    else
      ans.second -= tmp_price;
    --tmp_ptr;
  }
  return ans;
}

LogSystem::~LogSystem() = default;
#endif  // BOOKSTORE_SRC_BOOKSTORE_LOGSYSTEM_CPP