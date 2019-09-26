#include "LRUCache.h"
#include <iostream>
using namespace std;

LRUCache::LRUCache(int size):cacheSize(size) {
	cout << "LRU Cache of size " << size << " created." << endl;
	DLL = make_shared<DoublyLinkedList<CacheDataPtr>>();
}

void LRUCache::deleteCacheEntry(ListNode<CacheDataPtr> * node) {
	M.erase(node->val->key);
	DLL->deleteNode(node);
}

void LRUCache::print() {
	ListNode<CacheDataPtr> * cur = DLL->get_front();
	while (cur) {
		cout << cur->val->key << ":" << cur->val->value << " -> ";
		cur = cur->next;
	}
	cout << "NULL" << endl;
}

string LRUCache::get(string key){
	string value;
	auto itr = M.find(key);
	if (itr != M.end()) {
		value = itr->second->val->value;
		DLL->push_back(itr->second);
	}
	print();
	return value;
}

void LRUCache::put(string key, string value, int ttl) {
	auto itr = M.find(key);
	if (itr == M.end()) {
		auto node = DLL->addNode(make_shared<CacheData>(key, value, ttl));
		M.insert(make_pair(key, node));
		curCnt++;
		if(curCnt > cacheSize){
			deleteCacheEntry(DLL->get_front());
			curCnt--;
		}
	}
	else {
		auto node = itr->second;
		node->val->value = value;
		node->val->ttl = ttl;
		DLL->push_back(node);
	}
	print();
}

void LRUCache::deleteKey(string key) {
	auto itr = M.find(key);
	if (itr != M.end()) {
		deleteCacheEntry(itr->second);
	}
	curCnt--;
	print();
}

void LRUCache::clear() {
	M.clear();
	DLL->clear();
	curCnt = 0;
}

LRUCache::~LRUCache() {
	clear();
}
