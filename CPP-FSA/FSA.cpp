#include "FSA.h"

template<typename StateT, typename AlphaT>
void FSA<StateT, AlphaT>::setStart(const StateT &start)
{
	this->start = start;
}

template<typename StateT, typename AlphaT>
void FSA<StateT, AlphaT>::addFinal(const StateT &q)
{
	final.insert(q);
}

template <typename StateT, typename AlphaT>
void FSA<StateT, AlphaT>::addTransition(const StateT& q, const AlphaT& a, const StateT& w) {
	//transitions[std::make_pair(q, a)].insert({ w, true });
	transitions[std::make_pair(q, a)].insert(w);
}

template<typename StateT, typename AlphaT>
StateT* FSA<StateT, AlphaT>::step(const StateT & q, std::list<AlphaT>& word)
{
	if (word.empty()) return NULL;
	std::unordered_set<StateT> possible = transitions[std::make_pair(q, word.front())];
	if (possible.empty()) return NULL;
	word.pop_front();
	//StateT* res = new StateT(*((StateT*)*(possible.begin())));
	StateT* res = new StateT(*(possible.begin()));
	return res;
	//return ((StateT*)*(possible.begin()));
}

template<typename StateT, typename AlphaT>
bool FSA<StateT, AlphaT>::inLanguage(std::list<AlphaT>& word)
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
