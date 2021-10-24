#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>
#include "Hashes.h"


template<typename StateT, typename AlphaT>
class DFSA
{
private:
	StateT start;
	std::unordered_set<AlphaT> alphabet;
	std::unordered_set<StateT> states;
	std::unordered_set<StateT> final;
	std::unordered_map<std::pair<StateT, AlphaT>, StateT, hash_pair<StateT, AlphaT>> transitions;
	


	const StateT* findImage(const StateT&, const AlphaT&) const;
	bool isFinal(const StateT&) const;

public:
	void setStart(const StateT&);
	void addFinal(const StateT&);
	void addTransition(const StateT& q, const AlphaT& a, const StateT& w);
	
	const StateT* step(const StateT&, std::list<AlphaT>&) const;
	bool inLanguage(std::list<AlphaT>&) const;
	
	DFSA<size_t, AlphaT> minimize() const;
};