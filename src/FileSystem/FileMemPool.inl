#ifndef BOOKSTORE_SRC_FILESYSTEM_FILEMEMPOOL_INL
#define BOOKSTORE_SRC_FILESYSTEM_FILEMEMPOOL_INL
#include <fstream>
#include <string>
#include "MyString.h"
using std::fstream;
using std::string;
#include "FileMemPool.h"
bool fileop::File_Exist(MyString file_name) {
  fstream temp_file(file_name.ToString(), fstream::in | fstream::out | fstream::binary);
  if (!temp_file) return false;
  temp_file.close();
  return true;
}
void fileop::Create_File(MyString file_name) {
  fstream temp_file(file_name.ToString(), fstream::out | fstream::binary);
  temp_file.close();
  return;
}
FileMemPool::FileMemPool(string _file_name)
    : file_name(_file_name.append(".dat")) {
  if (!fileop::File_Exist(file_name)) fileop::Create_File(file_name);
}
FileMemPool::FileMemPool(const char* _file_name)
    : FileMemPool(string(_file_name)) {}
template <class ValueType>
FilePtr<ValueType> FileMemPool::fnew(const ValueType& obj, const int& num){
  fstream temp_file(file_name.ToString(), fstream::in | fstream::out | fstream::binary);
  temp_file.seekp(0, std::ios::end);
  FilePtr<ValueType> ans(temp_file.tellp());
  for (int i = 0; i < num; i++)
    temp_file.write(reinterpret_cast<const char*>(&obj), sizeof(ValueType));
  temp_file.close();
  return ans;
}

template <class ValueType>
ValueType FileMemPool::fread(const FilePtr<ValueType>& ptr) const{
  fstream temp_file(file_name.ToString(), fstream::in | fstream::out | fstream::binary);
  temp_file.seekg(ptr.Get_Pos());
  ValueType ans;
  temp_file.read(reinterpret_cast<char*>(&ans), sizeof(ValueType));
  temp_file.close();
  return ans;
}

template <class ValueType>
void FileMemPool::fread(const FilePtr<ValueType>& ptr,ValueType& ans) const{
  fstream temp_file(file_name.ToString(), fstream::in | fstream::out | fstream::binary);
  temp_file.seekg(ptr.Get_Pos());
  temp_file.read(reinterpret_cast<char*>(&ans), sizeof(ValueType));
  temp_file.close();
  return;
}

template <class ValueType>
void FileMemPool::modify(const FilePtr<ValueType>& ptr, const ValueType& obj){
  fstream temp_file(file_name.ToString(), fstream::in | fstream::out | fstream::binary);
  temp_file.seekp(ptr.Get_Pos());
  temp_file.write(reinterpret_cast<const char*>(&obj), sizeof(ValueType));
  temp_file.close();
  return;
}
bool FileMemPool::Empty() const{
	fstream temp_file(file_name.ToString(), fstream::in | fstream::out | fstream::binary);
  temp_file.seekp(0, std::ios::end);
	bool tmp_ans = temp_file.tellp();
	temp_file.close();
	return !tmp_ans;
}
FileMemPool::~FileMemPool() = default;

#endif  // BOOKSTORE_SRC_FILESYSTEM_FILEMEMPOOL_INL
