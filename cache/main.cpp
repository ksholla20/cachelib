#include <iostream>
#include "Cache.h"
using namespace std;
int main() {
	CachePtr RU_CACHE = Cache::getCache(LRU_CACHE, 4);
	RU_CACHE->put("1", "asd");
	RU_CACHE->put("2", "qwe");
	RU_CACHE->put("3", "fre");
	cout << RU_CACHE->get("2") << endl;
	RU_CACHE->put("4", "lkj");
	RU_CACHE->put("5", "def");
	RU_CACHE->put("3", "cvd");
	RU_CACHE->put("6", "hgf");
	RU_CACHE->deleteKey("3");
	RU_CACHE->put("7", "poi");

	cout << "______________" << endl;

	CachePtr FU_CACHE = Cache::getCache(LFU_CACHE, 4);
	FU_CACHE->put("1", "asd");
	FU_CACHE->put("2", "qwe");
	FU_CACHE->put("3", "fre");
	cout << FU_CACHE->get("2") << endl;
	FU_CACHE->put("4", "lkj");
	FU_CACHE->put("5", "def");
	FU_CACHE->put("3", "cvd");
	FU_CACHE->put("6", "hgf");
	FU_CACHE->deleteKey("3");
	FU_CACHE->put("7", "poi");

	return 0;
}