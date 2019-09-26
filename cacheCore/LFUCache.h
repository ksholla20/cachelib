#pragma once
#include <map>
#include <queue>
#include "Cache.h"
#include "DoublyLinkedList.h"
#include "custom_priority_queue.h"

class LFUCache :
	public Cache
{
private:
	int cacheSize;
	int curCnt = 0;
	map<string, CacheDataPtr> M;
	map<string, int> freq;
	map<int, shared_ptr<DoublyLinkedList<string>>> counter;
	custom_priority_queue<CacheDataPtr, vector<CacheDataPtr>, comparator> P;

	void insertCount(string key, int cnt);
	void deleteKeyInQueue(string key);
	void removeExpiredEntry();

	void print();
public:
	LFUCache(int size = MAX_CACHE_SIZE);
	string get(string key);
	void put(string key, string value, int ttl = -1);
	void deleteKey(string key);
	void clear();
	~LFUCache();
};

