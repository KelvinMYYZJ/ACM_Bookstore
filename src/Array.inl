#ifndef BOOKSTORE_SRC_ARRAY_INL
#define BOOKSTORE_SRC_ARRAY_INL

#include "Array.h"
template <class ValueType, class Compare, class Less>
Array<ValueType, Compare, Less>::Array() = default;
template <class ValueType, class Compare, class Less>
Array<ValueType, Compare, Less>::Array(
    const Array<ValueType, Compare, Less>& other)
    : now_size(other.now_size) {
  for (int i = 0; i < now_size; i++) val[i] = other.val[i];
  return;
}
template <class ValueType, class Compare, class Less>
void Array<ValueType, Compare, Less>::Insert(const ValueType& obj) {
  ValueType tmp_obj = obj;
  ValueType* tmp = std::lower_bound(val, val + now_size, obj, Less());
  int pos = tmp - val;
  for (int pos = tmp - val; pos <= now_size; pos++)
    std::swap(val[pos], tmp_obj);
	now_size++;
  return;
}
template <class ValueType, class Compare, class Less>
void Array<ValueType, Compare, Less>::Erease(const ValueType& obj) {
  int tmp_pos = Find(obj);
  if (tmp_pos == -1) {
    // throw??
  }
  for (; tmp_pos < now_size; tmp_pos++)
    std::swap(val[tmp_pos], val[tmp_pos + 1]);
	now_size--;
  return;
}
template <class ValueType, class Compare, class Less>
int Array<ValueType, Compare, Less>::LowerBound(const ValueType& obj) {
  ValueType* tmp = std::lower_bound(val, val + now_size, obj, Less());
  return tmp - val;
}
template <class ValueType, class Compare, class Less>
int Array<ValueType, Compare, Less>::Find(const ValueType& obj) {
  ValueType* tmp = std::lower_bound(val, val + now_size, obj, Less());
	ValueType tmp_obj = *tmp;
  if (Compare()(tmp_obj, obj)) return tmp - val;
  return -1;
}
template <class ValueType, class Compare, class Less>
const ValueType& Array<ValueType, Compare, Less>::GetFront() const {
  return val[0];
}
template <class ValueType, class Compare, class Less>
const ValueType& Array<ValueType, Compare, Less>::GetTail() const {
  return val[now_size - 1];
}
template <class ValueType, class Compare, class Less>
const int& Array<ValueType, Compare, Less>::GetNowSize() const {
  return now_size;
}
template <class ValueType, class Compare, class Less>
bool Array<ValueType, Compare, Less>::Empty() const {
  return now_size;
}

template <class ValueType, class Compare, class Less>
ValueType& Array<ValueType, Compare, Less>::operator[](const int& index) {
  return val[index];
}
template <class ValueType, class Compare, class Less>
const ValueType& Array<ValueType, Compare, Less>::operator[](
    const int& index) const {
  return val[index];
}
template <class ValueType, class Compare, class Less>
std::ostream& operator<<(std::ostream& os,
                         const Array<ValueType, Compare, Less>& obj) {
  for (int i = 0; i < obj.now_size; i++) os << obj.val[i] << ' ';
  return os;
}

#endif  // BOOKSTORE_SRC_ARRAY_INL