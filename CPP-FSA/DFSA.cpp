#include "DFSA.h"

template<typename StateT, typename AlphaT>
void DFSA<StateT, AlphaT>::setStart(const StateT &start)
{
	this->start = start;
}

template<typename StateT, typename AlphaT>
void DFSA<StateT, AlphaT>::addFinal(const StateT &q)
{
	final.insert(q);
}

template <typename StateT, typename AlphaT>
void DFSA<StateT, AlphaT>::addTransition(const StateT& q, const AlphaT& a, const StateT& w) {
	transitions[std::make_pair(q, a)] = w;
}

template<typename StateT, typename AlphaT>
StateT* DFSA<StateT, AlphaT>::step(const StateT & q, std::list<AlphaT>& word)
{
	if (word.empty()) return NULL;
	auto possible = transitions.find(std::make_pair(q, word.front()));
	if (possible == transitions.end()) return NULL;
	word.pop_front();
	StateT* res = new StateT((*(possible)).second);
	return res;
}

template<typename StateT, typename AlphaT>
bool DFSA<StateT, AlphaT>::inLanguage(std::list<AlphaT>& word)
{
	StateT current;
	StateT* next = &start;
	do {
		current = *next;
		if (word.empty() && final.find(current) != final.end()) return true;
		next = step(current, word);
	} while (next);

	return false;
}