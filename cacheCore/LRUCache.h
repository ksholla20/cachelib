#pragma once
#include <map>
#include <memory>
#include "Cache.h"
#include "DoublyLinkedList.h"
#include "custom_priority_queue.h"

class LRUCache :
	public Cache
{
private:
	int cacheSize;
	int curCnt = 0;
	shared_ptr<DoublyLinkedList<CacheDataPtr>> DLL;
	map<string, ListNode<CacheDataPtr>*> M;
	custom_priority_queue<CacheDataPtr, vector<CacheDataPtr>, comparator> P;

	void deleteCacheEntry(ListNode<CacheDataPtr> * node);
	void removeExpiredEntry();

	void print();

public:
	LRUCache(int size = MAX_CACHE_SIZE);
	string get(string key);
	void put(string key, string value, int ttl = -1);
	void deleteKey(string key);
	void clear();
	~LRUCache();
};

