#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>

/*template<typename T>
class Set : public std::unordered_set<T> {

};*/
/*class Set : public std::unordered_map<T, bool> {
public:
	void add(T val) {
		insert({ val, true });
	}
	auto pick() {
		return this->begin();
	}
};*/
template<typename T> void hash_combine(size_t & seed, T const& v) {
	seed ^= stdext::hash_value(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T, typename U>
struct hash_pair {
	size_t operator()(const std::pair<T, U> &rhs) const noexcept 
	{
		size_t retval = stdext::hash_value<T>(rhs.first);
		hash_combine(retval, rhs.second);
		return retval;
	}
};

/*template<typename T, typename U>
size_t hash_pair(const std::pair<T, U> &rhs) {
	size_t retval = stdext::hash_value<T>(rhs.first);
	hash_combine(retval, rhs.second);
	return retval;
}*/

template<typename T, typename U>
size_t (*hashPtr)(const std::pair<T, U>&) { &hash_pair<T,U>};

template<typename StateT, typename AlphaT>
class FSA 
{
private:
	StateT start;
	std::unordered_map<std::pair<StateT, AlphaT>, std::unordered_set<StateT>, hash_pair<StateT, AlphaT>> transitions;
	std::unordered_set<StateT> final;
public:
	void setStart(const StateT&);
	void addFinal(const StateT&);
	void addTransition(const StateT& q, const AlphaT& a, const StateT& w);
	StateT* step(const StateT&, std::list<AlphaT>&);
	bool inLanguage(std::list<AlphaT>&);
};