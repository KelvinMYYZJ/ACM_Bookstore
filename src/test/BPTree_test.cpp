#include <iostream>
#ifndef ONLINE_JUDGE
#ifndef BUG
#define DEBUG
#endif
#endif
// #include "Array.h"
#include <string>

#include "BPTree.h"
#include "FileMemPool.h"
#include "MyString.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

/* void FileMemPoolTest() {
  FileMemPool test("test");
  std::cout << "Testing FileMemPool and FilePtr" << std::endl;
  auto ptr1 = test.fnew(0, 5);
  for (int i = 0; i < 5; i++) test.modify(ptr1 + i, i);
  for (int i = 0; i < 5; i++) std::cout << test.fread(ptr1 + i) << ' ';
  std::cout << std::endl;
  std::cout << "Finished testing FileMemPool and FilePtr" << std::endl;
  return;
} */
/* void ArrayTest()
{

  std::cout << "Testing Array" << std::endl;
  int a[8] = {1, 9, 2, 6, 0, 8, 1, 7};
        Array<int> arr;
  for (int i =0;i<8;i++)
                arr.Insert(a[i]);
        std::cout<< "Now array is: "<< arr<<std::endl;
        for (int i=0;i<10;i++)
        {
                int tmp = arr.Find(i);
                if(tmp == -1)
                        std::cout<<"Can't find "<<i<<" in arr"<<std::endl;
                else
                        std::cout<<"Find "<<i<<"in arr, pos:"<<tmp<<std::endl;
        }
        arr.Erease(1);
        std::cout<< "Now array is: "<< arr<<std::endl;
  std::cout << "Finished testing Array" << std::endl;
        return;
} */

signed main() {
#ifndef ONLINE_JUDGE
  freopen("!input.txt", "r", stdin);
  // freopen("!output.txt","w",stdout);
#endif
  FileMap<MyString, int> test("test");
  FilePtr<int> a(1234);
  if (!a) return 0;
  int T;
  std::cin >> T;
  while (T--) {
    string op;
    try {
      cin >> op;
      if (op == "insert") {
        MyString key;
        int value;
        cin >> key >> value;
        test.Insert(key, value);
      }
      if (op == "find") {
        MyString key;
        cin >> key;
        auto tmp_out = test.Find(key);
        if (tmp_out.empty()) {
          cout << "null" << std::endl;
          continue;
        }
        for (int& now : tmp_out) cout << now << ' ';
        cout << std::endl;
      }
			if(op == "delete")
			{
        MyString key;
        int value;
        cin >> key >> value;
        test.Erase(key, value);
			}
			if (op == "print")
			{
			cout<<"begin print"<<endl;
				test.Print();
			cout<<"end print"<<endl<<endl<<endl;}
    }  catch (const char* t) {
       cout << T << " op=" << op << ", " << t << std::endl;
     }
    /* catch (long t) {
      cout << t << endl;
    } */
  }
  /* if (op=="delete")
  {
MyString key;
int value;
cin >> key >> value;
test.Erase(key, value);
  } */
  return 0;
}