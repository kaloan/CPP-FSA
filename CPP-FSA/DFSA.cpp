#include "DFSA.h"

template<typename StateT, typename AlphaT>
StateT * DFSA<StateT, AlphaT>::findImage(const StateT &q, const AlphaT &a)
{
	auto possible = transitions.find(std::make_pair(q, a));
	if (possible == transitions.end()) return NULL;
	StateT* res = &(possible->second);
	return res;
}

template<typename StateT, typename AlphaT>
void DFSA<StateT, AlphaT>::setStart(const StateT &start)
{
	this->start = start;
}

template<typename StateT, typename AlphaT>
void DFSA<StateT, AlphaT>::addFinal(const StateT &q)
{
	states.insert(q);
	final.insert(q);
}

template <typename StateT, typename AlphaT>
void DFSA<StateT, AlphaT>::addTransition(const StateT& q, const AlphaT& a, const StateT& w) {
	transitions[std::make_pair(q, a)] = w;
	states.insert(q);
}

template<typename StateT, typename AlphaT>
StateT* DFSA<StateT, AlphaT>::step(const StateT & q, std::list<AlphaT>& word) const
{
	if (word.empty()) return NULL;
	StateT* res = findImage(q, word.front());
	word.pop_front();
	return res;
}

template<typename StateT, typename AlphaT>
bool DFSA<StateT, AlphaT>::inLanguage(std::list<AlphaT>& word) const
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

template<typename StateT, typename AlphaT>
DFSA<int, AlphaT> DFSA<StateT, AlphaT>::minimize()
{
	std::list<std::pair<std::unordered_set<StateT>, bool>> currentEquivalentStates;
	std::unordered_set<StateT> nonFinal;
	for (auto state& : states)
	{
		if (final.find(state) == final.end()) nonFinal.insert(state);
	}
	currentEquivalentStates.push_back(std::make_pair(final, true));
	currentEquivalentStates.push_back(std::make_pair(nonFinal, false));
	bool change = true;
	while (change)
	{
		for (int i = 1; i <= list.size(); ++i)
		{
			eqivalentClass = currentEquivalentStates.front();
			currentEquivalentStates.pop_front();
			std::list<std::pair<std::unordered_set<StateT>, bool>> newEquivalentClasses;

			currentEquivalentStates.insert(currentEquivalentStates.end(), 
				myvector.begin(), myvector.end());
		}

		change = false;
	}
	return DFSA<int, AlphaT>();
}
