#pragma once
#include <map>
#include "Cache.h"

struct ListNode {
	ListNode* prev;
	ListNode* next;
	string key, value;
	int ttl;
	ListNode(string k, string v, int t): key(k), value(v), ttl(t), prev(NULL), next(NULL){}
};
class LRUCache :
	public Cache
{
private:
	int cacheSize;
	int curCnt = 0;
	ListNode* beg = NULL;
	ListNode* end = NULL;
	map<string, ListNode*> M;

	void deleteNode(ListNode* node);
	ListNode* addNode(string key, string value, int ttl);
	void appendToEnd(ListNode * node);

	void deleteCacheEntry(ListNode * node);
	bool hasKey(string key);
	void print();

public:
	LRUCache(int size = MAX_CACHE_SIZE);
	string get(string key);
	void put(string key, string value, int ttl = -1);
	void deleteKey(string key);
	void clear();
	~LRUCache();
};

