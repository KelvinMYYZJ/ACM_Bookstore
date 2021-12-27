#include <ctime>
#include <iostream>

#include "Array.h"
// #include "FileMemPool.h"
// #include "ull.h"

int main() {
  // ! Notice
  // If you are using dynamic-link library, the DLL
  // file (filename extension is `.so` in Linux and
  // `.dll` in Windows) must be in a location that
  // the executable file can directly access(that is,
  // under the same folder or under system PATH),
  // otherwise it cannot run.
  // But if you are using the statically-linked library
  // (filename extension is `.a` in Linux and `.lib`
  // in Windows), the executable file can run without
  // any other file.

  // Initialize ULL with file name
  // Ull testUll("test.dat"); ) std::cout << item << std::endl;
	FileMemPool a("a");
	Array<int> tmp;
	tmp.Insert(1);
	tmp.Insert(1);
	tmp.Insert(4);
	tmp.Insert(5);
	tmp.Insert(1);
	tmp.Insert(4);
	auto x = a.fnew(tmp);
	std::cout<<a.fread(x)<<std::endl;
  return 0;
}
