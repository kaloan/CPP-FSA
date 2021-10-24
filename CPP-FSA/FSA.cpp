#include "FSA.h"

template<typename StateT, typename AlphaT>
const StateT * FSA<StateT, AlphaT>::findImage(const StateT &q, const AlphaT &a) const
{
	auto possible = transitions.find(std::make_pair(q, a));
	if (possible == transitions.end()) return nullptr;
	const StateT* res = &(*((possible->second).begin()));
	return res;
}

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
const StateT* FSA<StateT, AlphaT>::step(const StateT & q, std::list<AlphaT>& word) const
{
	if (word.empty()) return nullptr;
	const StateT* res = findImage(q, word.front());
	word.pop_front();
	return res;
	/*try
	{

		std::unordered_set<StateT> possible = transitions.at(std::make_pair(q, word.front()));
		res = new StateT(*(possible.begin()));
	}
	catch (const std::exception&)
	{
		return nullptr;
	}*/
	/*auto possibleIter = transitions.find(std::make_pair(q, word.front()));
	if (possibleIter == transitions.end()) return NULL;
	std::unordered_set<StateT> possible = possibleIter->second;
	
	//if (possible.empty()) return NULL;
	word.pop_front();
	StateT* res = &(*(possible.begin()));*/
}

template<typename StateT, typename AlphaT>
bool FSA<StateT, AlphaT>::inLanguage(std::list<AlphaT>& word) const
{
	StateT current;
	const StateT* next = &start;
	do {
		current = *next;
		if (word.empty() && final.find(current) != final.end()) return true;
		next = step(current, word);
	} while (next);

	return false;
}
