#include <ctime>
#include <iostream>

#include "BookStore.h"
int main() {
	freopen("stdin.txt","r",stdin);
	freopen("stdout.txt","w",stdout);
	freopen("stderr.txt","w",stderr);
	BookStore("SJTU").work();
  return 0;
}
