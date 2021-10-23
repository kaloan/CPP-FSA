#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>
#include "Hashes.h"

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
	StateT* step(const StateT&, std::list<AlphaT>&) const;
	bool inLanguage(std::list<AlphaT>&) const;
};