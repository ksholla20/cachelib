#pragma once
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

template <class T, class Container = vector<T>,
	class Compare = less<typename Container::value_type> >
	class custom_priority_queue : public std::priority_queue<T, std::vector<T>, Compare>
{
public:

	bool remove(const T& value) {
		auto it = std::find(this->c.begin(), this->c.end(), value);
		if (it != this->c.end()) {
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
			return true;
		}
		else {
			return false;
		}
	}
};
