#pragma once
#include <string>
#include <memory>
constexpr auto MAX_CACHE_SIZE = 4096;
using namespace std;

enum CacheType {
	LRU_CACHE,
	LFU_CACHE
};
class Cache;
typedef shared_ptr<Cache> CachePtr;
class Cache
{
public:
	Cache(int size = MAX_CACHE_SIZE);
	virtual string get(string key) = 0;
	virtual void put(string key, string value, int ttl = -1) = 0;
	virtual void deleteKey(string key) = 0;
	virtual void clear() = 0;
	static CachePtr getCache(CacheType c, int size = MAX_CACHE_SIZE);
	~Cache();
};

