#ifndef BOOKSTORE_SRC_BOOKSTORE_ERROR_CPP
#define BOOKSTORE_SRC_BOOKSTORE_ERROR_CPP
#include "Error.h"

#include <cstring>
Error::Error(const string& msg) : msg_(new char[msg.length() + 1]) {
  strcpy(msg_, msg.c_str());
  return;
}
const char* Error::what() const noexcept { return msg_; }
Error::~Error() {
  delete[] msg_;
  return;
}
#endif  // BOOKSTORE_SRC_BOOKSTORE_ERROR_CPP