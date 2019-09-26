#include "LRUCache.h"
#include <iostream>
#include <chrono>
using namespace std;

LRUCache::LRUCache(int size):cacheSize(size) {
	cout << "LRU Cache of size " << size << " created." << endl;
	DLL = make_shared<DoublyLinkedList<CacheDataPtr>>();
}

void LRUCache::deleteCacheEntry(ListNode<CacheDataPtr> * node) {
	P.remove(node->val);
	M.erase(node->val->key);
	DLL->deleteNode(node);
}

void LRUCache::removeExpiredEntry() {
	if (P.size() == 0) return;
	int time = (int)chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
	while (P.size() && (P.top()->ttl < time)) {
		string key = P.top()->key;
		P.pop();
		deleteKey(key);
	}
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
	removeExpiredEntry();
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
	removeExpiredEntry();
	auto itr = M.find(key);
	if (ttl < 0) {
		ttl = INT_MAX;
	}
	else {
		ttl += (int)chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
	}
	if (itr == M.end()) {
		auto node = DLL->addNode(make_shared<CacheData>(key, value, ttl));
		M.insert(make_pair(key, node));
		curCnt++;
		if(curCnt > cacheSize){
			deleteCacheEntry(DLL->get_front());
			curCnt--;
		}
		P.push(node->val);
	}
	else {
		auto node = itr->second;
		node->val->value = value;
		node->val->ttl = ttl;
		DLL->push_back(node);
		P.remove(node->val);
		P.push(node->val);
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
