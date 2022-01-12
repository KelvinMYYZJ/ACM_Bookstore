#ifndef BOOKSTORE_SRC_BOOKSTORE_BOOKMANAGER_H
#define BOOKSTORE_SRC_BOOKSTORE_BOOKMANAGER_H
#include <string>
using namespace std::string_literals;
#include <set>
using std::set;
#include "BPTree.h"
#include "FileMemPool.h"
#include "Token.h"
struct Book {
  ISBN isbn;
  BookName book_name = ""s;
  Author author = ""s;
  KeywordList keyword_list = ""s;
  double price = 0;
  long long inventory = 0;
  Book();
  Book(const ISBN& isbn);
  Book(const Book& other);
};
bool operator<(const Book& lhs, const Book& rhs);
typedef FilePtr<Book> BookIndex;

class BookIndexHash {
 public:
  long operator()(const BookIndex& book_index);
};

class BookManager {
 private:
  const string name_;
  FileMemPool book_list;
  FileMap<ISBN, BookIndex, long, BookIndexHash> map_isbn;
  FileMap<BookName, BookIndex, long, BookIndexHash> map_book_name;
  FileMap<Author, BookIndex, long, BookIndexHash> map_author;
  FileMap<Keyword, BookIndex, long, BookIndexHash> map_keyword;
  BookIndex FindIndex(const ISBN& isbn);
  BookIndex CreatBookNoExcept(const ISBN& isbn);
  Book ReadBook(const BookIndex& book_index);
  set<Book> ReadBookList(const vector<BookIndex>& book_index_list);
  void ModifyBook(const BookIndex& book_index, const Book& book);

 public:
  BookManager(const string& name);
  set<Book> FindBook();
  set<Book> FindBook(const ISBN& isbn);
  set<Book> FindBook(const BookName& book_name);
  set<Book> FindBook(const Author& author);
  set<Book> FindBook(const Keyword& keyword);
  double BuyBook(const ISBN& isbn, const Quantity& quantity);
  BookIndex SelectBook(const ISBN& isbn);
  void Modify(const BookIndex& book_index, const ISBN& isbn);
  void Modify(const BookIndex& book_index, const BookName& book_name);
  void Modify(const BookIndex& book_index, const Author& author);
  void Modify(const BookIndex& book_index, const KeywordList& keyword_list);
  void Modify(const BookIndex& book_index, const MoneyQuantity& price);
  void Import(const BookIndex& book_index, const Quantity& quantity);
};
#endif  // BOOKSTORE_SRC_BOOKSTORE_BOOKMANAGER_H