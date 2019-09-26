#pragma once
#include <map>
#include <queue>
#include "Cache.h"
#include "DoublyLinkedList.h"
class LFUCache :
	public Cache
{
private:
	int cacheSize;
	int curCnt = 0;
	map<string, string> M;
	map<string, int> freq;
	map<int, shared_ptr<DoublyLinkedList<string>>> counter;

	void insertCount(string key, int cnt);
	void deleteKeyInQueue(string key);

	void print();
public:
	LFUCache(int size = MAX_CACHE_SIZE);
	string get(string key);
	void put(string key, string value, int ttl = -1);
	void deleteKey(string key);
	void clear();
	~LFUCache();
};

