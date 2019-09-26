#pragma once
#include <map>
#include <memory>
#include "Cache.h"
#include "DoublyLinkedList.h"

struct CacheData {
	string key;
	string value;
	int ttl;
	CacheData(string k, string v, int t) : key(k), value(v), ttl(t){}
};
typedef shared_ptr<CacheData> CacheDataPtr;
class LRUCache :
	public Cache
{
private:
	int cacheSize;
	int curCnt = 0;
	shared_ptr<DoublyLinkedList<CacheDataPtr>> DLL;
	map<string, ListNode<CacheDataPtr>*> M;

	void deleteCacheEntry(ListNode<CacheDataPtr> * node);
	void print();

public:
	LRUCache(int size = MAX_CACHE_SIZE);
	string get(string key);
	void put(string key, string value, int ttl = -1);
	void deleteKey(string key);
	void clear();
	~LRUCache();
};

