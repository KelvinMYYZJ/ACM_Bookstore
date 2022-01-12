#ifndef BOOKSTORE_SRC_BOOKSTORE_BOOKMANAGER_CPP
#define BOOKSTORE_SRC_BOOKSTORE_BOOKMANAGER_CPP
#include "BookManager.h"

#include "Error.h"

#pragma region Book
Book::Book() = default;
Book::Book(const ISBN& isbn_) : isbn(isbn_) {}
#pragma endregion Book
#pragma region BookIndexHash
long BookIndexHash::operator()(const BookIndex& book_index) {
  return book_index.Get_Pos();
}
Book::Book(const Book&) = default;
bool operator<(const Book& lhs, const Book& rhs) { return lhs.isbn < rhs.isbn; }
#pragma endregion BookIndexHash

#pragma region BookManager

BookIndex BookManager::FindIndex(const ISBN& isbn) {
  auto index_list = map_isbn.Find(isbn);
  if (index_list.empty()) return BookIndex();
  if (index_list.size() > 1) throw(Error("Fatal Error : repeated ISBN in map"));
  return index_list.front();
}

BookIndex BookManager::CreatBookNoExcept(const ISBN& isbn) {
  return book_list.fnew(Book(isbn));
}

Book BookManager::ReadBook(const BookIndex& book_index) {
  return book_list.fread(book_index);
}
set<Book> BookManager::ReadBookList(const vector<BookIndex>& book_index_list) {
  set<Book> ans;
  for (const auto& book_index : book_index_list)
    ans.insert(ReadBook(book_index));
  return ans;
}

void BookManager::ModifyBook(const BookIndex& book_index, const Book& book) {
  book_list.modify(book_index, book);
  return;
}
BookManager::BookManager(const string& name)
    : name_(name),
      book_list(name + "_book_list"s),
      map_isbn(name + "_map_isbn"s),
      map_book_name(name + "_map_book_name"s),
      map_author(name + "_map_author"),
      map_keyword(name + "_map_keyword"s) {}

set<Book> BookManager::FindBook() { return ReadBookList(map_isbn.FindAll()); }

set<Book> BookManager::FindBook(const ISBN& isbn) {
  return ReadBookList(map_isbn.Find(isbn));
}
set<Book> BookManager::FindBook(const BookName& book_name) {
  return ReadBookList(map_book_name.Find(book_name));
}

set<Book> BookManager::FindBook(const Author& author) {
  return ReadBookList(map_author.Find(author));
}

set<Book> BookManager::FindBook(const Keyword& keyword) {
  return ReadBookList(map_keyword.Find(keyword));
}

double BookManager::BuyBook(const ISBN& isbn, const Quantity& quantity) {
  auto book_index = FindIndex(isbn);
  if (!book_index) throw(Error("Buying non-existing book"));
  Book tmp_book = ReadBook(book_index);
  long long number = quantity.ToInt();
  if (tmp_book.inventory < number) throw(Error("Not enough inventory"));
  tmp_book.inventory -= number;
  ModifyBook(book_index, tmp_book);
  return double(number) * tmp_book.price;
}

BookIndex BookManager::SelectBook(const ISBN& isbn) {
  BookIndex tmp_book_index = FindIndex(isbn);
  if (!tmp_book_index) {
    tmp_book_index = CreatBookNoExcept(isbn);
    map_isbn.Insert(isbn, tmp_book_index);
  }
  return tmp_book_index;
}
void BookManager::Modify(const BookIndex& book_index, const ISBN& isbn) {
  auto tmp_list = map_isbn.Find(isbn);
  if (!tmp_list.empty() && book_index.Get_Pos() != tmp_list.front().Get_Pos())
    throw(Error("Change ISBN to exsisting ISBN"));
  Book tmp_book = ReadBook(book_index);
  map_isbn.Erase(tmp_book.isbn, book_index);
  tmp_book.isbn = isbn;
  ModifyBook(book_index, tmp_book);
  map_isbn.Insert(isbn, book_index);
  // std::cerr<<map_isbn.FindAll().size()<<std::endl;
  return;
}
void BookManager::Modify(const BookIndex& book_index,
                         const BookName& book_name) {
  Book tmp_book = ReadBook(book_index);
  map_book_name.Erase(tmp_book.book_name, book_index);
  tmp_book.book_name = book_name;
  ModifyBook(book_index, tmp_book);
  map_book_name.Insert(book_name, book_index);
  return;
}
void BookManager::Modify(const BookIndex& book_index, const Author& author) {
  Book tmp_book = ReadBook(book_index);
  map_author.Erase(tmp_book.author, book_index);
  tmp_book.author = author;
  ModifyBook(book_index, tmp_book);
  map_author.Insert(author, book_index);
  return;
}
void BookManager::Modify(const BookIndex& book_index,
                         const KeywordList& keyword_list) {
  Book tmp_book = ReadBook(book_index);
  auto old_keyword_list = tmp_book.keyword_list.ToList();
  for (const auto& tmp_keyword : old_keyword_list)
    map_keyword.Erase(tmp_keyword, book_index);
  tmp_book.keyword_list = keyword_list;
  ModifyBook(book_index, tmp_book);
  auto new_keyword_list = keyword_list.ToList();
  for (const auto& tmp_keyword : new_keyword_list)
    map_keyword.Insert(tmp_keyword, book_index);
  return;
}
void BookManager::Modify(const BookIndex& book_index,
                         const MoneyQuantity& price) {
  Book tmp_book = ReadBook(book_index);
  tmp_book.price = price.ToDouble();
  ModifyBook(book_index, tmp_book);
  return;
}
void BookManager::Import(const BookIndex& book_index,
                         const Quantity& quantity) {
  long long number = quantity.ToInt();
  Book tmp_book = ReadBook(book_index);
  tmp_book.inventory += number;
  ModifyBook(book_index, tmp_book);
  return;
}
#pragma endregion BookManager

#endif  // BOOKSTORE_SRC_BOOKSTORE_BOOKMANAGER_CPP