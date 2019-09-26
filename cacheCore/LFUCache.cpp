#include <iostream>
#include "LFUCache.h"
#include <chrono>


LFUCache::LFUCache(int size): cacheSize(size) {
}

void LFUCache::insertCount(string key, int cnt) {
	if (counter.find(cnt) == counter.end())
		counter.insert(make_pair(cnt, make_shared<DoublyLinkedList<string>>()));
	counter[cnt]->addNode(key);
}

void LFUCache::deleteKeyInQueue(string key) {
	//freq[key] will get the current frequency
	//counter[freq[key]] will get the queue which has all keys with current frequency
	//from here, we extract node with current key
	//we then add it to next frequency queue
	auto countQueue = counter[freq[key]];
	auto node = countQueue->get_front();
	while (node->val != key) node = node->next;
	countQueue->deleteNode(node);
}

void LFUCache::removeExpiredEntry() {
	if (P.size() == 0) return;
	int time = (int)chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
	while (P.size() && (P.top()->ttl < time)) {
		string key = P.top()->key;
		P.pop();
		deleteKey(key);
	}
}

void LFUCache::print() {
	for (auto itr = M.begin(); itr != M.end(); itr++) {
		cout << itr->first << ":" << itr->second->value << " ";
	}
	cout << endl;
}

string LFUCache::get(string key) {
	removeExpiredEntry();
	string value;
	auto itr = M.find(key);
	if (itr != M.end()) {
		value = itr->second->value;
		deleteKeyInQueue(key);
		freq[key]++;
		insertCount(key, freq[key]);
	}
	print();
	return value;
}

void LFUCache::put(string key, string value, int ttl) {
	removeExpiredEntry();
	if (ttl < 0) {
		ttl = INT_MAX;
	}
	else {
		ttl += (int)chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
	}
	if (M.find(key) != M.end()) {
		M[key]->value = value;
		get(key);
		P.remove(M[key]);
		P.push(M[key]);
		print();
		return;
	}
	curCnt++;
	if (curCnt > cacheSize) {
		string removeKey = counter.begin()->second->get_front()->val;
		counter.begin()->second->pop_front();
		if (!counter.begin()->second->hasNode()) {
			counter.erase(counter.begin()->first);
		}
		P.remove(M[removeKey]);
		freq.erase(removeKey);
		M.erase(removeKey);
		curCnt--;
	}
	M.insert(make_pair(key, make_shared<CacheData>(key, value, ttl)));
	freq.insert(make_pair(key, 1));
	insertCount(key, 1);
	P.push(M[key]);
	print();
}

void LFUCache::deleteKey(string key) {
	auto itr = M.find(key);
	if (itr != M.end()) {
		deleteKeyInQueue(key);
		freq.erase(key);
		P.remove(M[key]);
		M.erase(key);
	}
	curCnt--;
	print();
}
void LFUCache::clear() {
	for (auto itr = counter.begin(); itr != counter.end(); itr++) {
		itr->second->clear();
	}
	counter.clear();
	freq.clear();
	M.clear();
	curCnt = 0;
}

LFUCache::~LFUCache() {
}
