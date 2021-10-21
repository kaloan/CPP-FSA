#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>

template<typename T>
class Set : public std::unordered_set<T> {

};
/*class Set : public std::unordered_map<T, bool> {
public:
	void add(T val) {
		insert({ val, true });
	}
	auto pick() {
		return this->begin();
	}
};*/

template<typename StateT, typename AlphaT>
class FSA 
{
private:
	StateT start;
	std::unordered_map<std::pair<StateT, AlphaT>, Set<StateT>> transitions;
	Set<StateT> final;
public:
	void setStart(const StateT&);
	void addFinal(const StateT&);
	void addTransition(const StateT& q, const AlphaT& a, const StateT& w);
	StateT* step(const StateT&, std::list<AlphaT>&) const;
	bool inLanguage(std::list<AlphaT>&) const;
};