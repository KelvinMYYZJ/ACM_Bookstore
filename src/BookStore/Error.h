#ifndef BOOKSTORE_SRC_BOOKSTORE_ERROR_H
#define BOOKSTORE_SRC_BOOKSTORE_ERROR_H
#include <exception>
#include <string>
using std::string;
class Error : public std::exception {
 private:
  char* const msg_;
 public:
  Error(const string& msg);
  const char* what() const noexcept override;
	~Error();
};
#endif  // BOOKSTORE_SRC_BOOKSTORE_ERROR_H