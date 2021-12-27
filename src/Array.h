#ifndef BOOKSTORE_SRC_ARRAY_H
#define BOOKSTORE_SRC_ARRAY_H
#include "Comp.h"
#include "DefaultConst.cpp"
#include "FileMemPool.h"
extern const int block_size;
template <class ValueType, class Compare, class Less>
class Array;
template <class ValueType, class Compare, class Less>
std::ostream& operator<<(std::ostream& os,
                         const Array<ValueType, Compare, Less>& obj);

template <class ValueType, class Compare = Comp::SingleComp<ValueType>,
          class Less = Comp::CompToLess<Compare, ValueType>>
class Array {
 private:
  const static int size = block_size;
  ValueType val[size];
  int now_size = 0;

 public:
  Array();
  Array(const Array<ValueType, Compare, Less>& other);
  void Insert(const ValueType& obj);
  void Erease(const ValueType& obj);
  int LowerBound(const ValueType& obj);
  int Find(const ValueType& obj);
  const ValueType& GetFront() const;
  const ValueType& GetTail() const;
  const int& GetNowSize() const;
  bool Empty() const;
  ValueType& operator[](const int& index);
  const ValueType& operator[](const int& index) const;
  // template<class ValueType1,class Compare1>
  friend std::ostream& operator<<<ValueType, Compare, Less>(
      std::ostream& os, const Array<ValueType, Compare, Less>& obj);
};
#include "Array.inl"
#endif  // BOOKSTORE_SRC_ARRAY_H