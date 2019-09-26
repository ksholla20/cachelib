#include "Cache.h"
#include "LRUCache.h"
#include "LFUCache.h"

Cache::Cache(int size)
{
}

CachePtr Cache::getCache(CacheType c, int size) {
	if (c == LRU_CACHE)
		return make_shared<LRUCache>(size);
	else
		return make_shared<LFUCache>(size);
}

Cache::~Cache()
{
}
