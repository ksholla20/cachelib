#include "LRUCache.h"
#include <iostream>
using namespace std;

LRUCache::LRUCache(int size):cacheSize(size) {
	cout << "LRU Cache of size " << size << " created." << endl;
}

void LRUCache::deleteNode(ListNode* node) {
	if (node->prev) node->prev->next = node->next;
	if (node->next) node->next->prev = node->prev;
	if (node == beg) beg = node->next;
	if (node == end) end = node->prev;
	delete node;
}

ListNode* LRUCache::addNode(string key, string value, int ttl) {
	ListNode * node = new ListNode(key, value, ttl);
	if (end) {
		end->next = node;
		node->prev = end;
		end = node;
	}
	else {
		beg = end = node;
	}
	return node;
}

void LRUCache::appendToEnd(ListNode * node) {
	if (node == end) return;
	if (node == beg) beg = beg->next;
	if(node->prev) node->prev->next = node->next;
	node->next->prev = node->prev;
	end->next = node;
	node->prev = end;
	node->next = NULL;
	end = node;
}

void LRUCache::deleteCacheEntry(ListNode * node) {
	M.erase(node->key);
	deleteNode(node);
}

void LRUCache::print() {
	ListNode * cur = beg;
	while (cur) {
		cout << cur->key << ":" << cur->value << " -> ";
		cur = cur->next;
	}
	cout << "NULL" << endl;
}

bool LRUCache::hasKey(string key) {
	return !(M.find(key) == M.end());
}

string LRUCache::get(string key){
	string value;
	auto itr = M.find(key);
	if (itr != M.end()) {
		value = itr->second->value;
		appendToEnd(itr->second);
	}
	print();
	return value;
}

void LRUCache::put(string key, string value, int ttl) {
	auto itr = M.find(key);
	if (itr == M.end()) {
		ListNode * node = addNode(key, value, ttl);
		M.insert(make_pair(key, node));
		curCnt++;
		if(curCnt > cacheSize){
			deleteCacheEntry(beg);
		}
	}
	else {
		ListNode * node = itr->second;
		node->value = value;
		node->ttl = ttl;
		appendToEnd(node);
	}
	print();
}

void LRUCache::deleteKey(string key) {
	auto itr = M.find(key);
	if (itr != M.end()) {
		deleteCacheEntry(itr->second);
	}
	print();
}

void LRUCache::clear() {
	M.clear();
	while (beg) {
		auto next = beg->next;
		delete beg;
		beg = next;
	}
	end = NULL;
}

LRUCache::~LRUCache() {
	clear();
}
