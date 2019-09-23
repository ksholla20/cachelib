#include <iostream>
#include "Cache.h"
using namespace std;
int main() {
	CachePtr C = Cache::getCache(LRU_CACHE, 4);
	C->put("1", "asd");
	C->put("2", "qwe");
	C->put("3", "fre");
	cout << C->get("2");
	C->put("4", "lkj");
	C->put("5", "def");
	C->put("3", "cvd");

	return 0;
}