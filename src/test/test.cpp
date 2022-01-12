#include <bits/stdc++.h>

#include "Error.h"
#include "Token.h"
#ifndef ONLINE_JUDGE
#ifndef BUG
#define DEBUG
#endif
#endif
using namespace std;

signed main() {
#ifndef ONLINE_JUDGE
  // freopen("!input.txt","r",stdin);
  // freopen("!output.txt","w",stdout);
#endif
  string a;
  cin >> a;
  try {
  KeywordList tmp(a);
    auto tvec = tmp.ToList();
    for (auto& t : tvec) cout << t.ToString() << endl;
  } catch (Error& t) {
    cout << t.what()<<endl;
  }
  return 0;
}