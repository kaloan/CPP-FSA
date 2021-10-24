#include "DFSA.h"

template<typename StateT, typename AlphaT>
StateT * DFSA<StateT, AlphaT>::findImage(const StateT &q, const AlphaT &a) const
{
	auto possible = transitions.find(std::make_pair(q, a));
	if (possible == transitions.end()) return nullptr;
	StateT* res = &(possible->second);
	return res;
}

template<typename StateT, typename AlphaT>
bool DFSA<StateT, AlphaT>::isFinal(const StateT &q) const
{
	return final.find(q) == final.end();
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
	alphabet.insert(a);
}

template<typename StateT, typename AlphaT>
StateT* DFSA<StateT, AlphaT>::step(const StateT & q, std::list<AlphaT>& word) const
{
	if (word.empty()) return nullptr;
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
	// If one of the lists in the list starts with a final state,
	// then it will be final in the minimized automata
	std::list<std::list<StateT>> currentEquivalentStates;
	
	std::list<StateT> nonFinal;
	std::list<StateT> finalEquiv;
	for (auto state& : states)
	{
		if (isFinal(state)) finalEquiv.push_front(state);
		else nonFinal.push_back(state);
	}
	currentEquivalentStates.push_back(finalEquiv);
	currentEquivalentStates.push_back(nonFinal);

	bool change = true;
	while (change)
	{
		change = false;

		for (int i = 1; i <= currentEquivalentStates.size(); ++i)
		{
			// At the start the only equivalent class emerging from 
			// the current one will be itself
			std::list<std::list<StateT>> newEquivalentClasses;
			newEquivalentClasses.push_back(currentEquivalentStates.front());

			// For each letter find the image of the states in one of the classes
			// Different images would mean the states should be in different classes
			for (auto const& a : alphabet)
			{
				std::list<std::list<StateT>> tempClasses;

				for (auto const& equivalentClass : newEquivalentClasses)
				{
					std::unordered_map<StateT*, std::list<StateT>> images;
					for (auto const& state : equivalentClass)
					{
						std::list<StateT>& toPush = images[findImage(state, a)];
						if (isFinal(state)) toPush.push_front(state);
						else toPush.push_back(state);
					}

					for (auto const& imageListPair : images)
					{
						tempClasses.push_back(imageListPair.second);
					}
				}

				newEquivalentClasses = std::move(tempClasses);
			}

			// If only one "new" equivalent class was created it is the old equivalent class 
			// and will be equivalent forever
			if (newEquivalentClasses.size() == 1) continue;
			
			change = true;

			currentEquivalentStates.insert(currentEquivalentStates.end(), 
				newEquivalentClasses.begin(), newEquivalentClasses.end());
			currentEquivalentStates.pop_front();
		}
	}

	// Construct the result - for each equivalent class we have a state
	// If the equivalent class starts with a final state, then it is final
	DFSA<size_t, AlphaT> res;

	// Map states of the old automata to states of the minimized automata
	std::unordered_map<StateT*, size_t> oldToNew;
	size_t newState = 1;
	oldToNew.insert(std::make_pair(nullptr, newState));
	for (auto const& equivalentClass : currentEquivalentStates)
	{
		for (auto const& oldState : equivalentClass)
		{
			oldToNew.insert(std::make_pair(&oldState, newState));
		}
		++newState;
	}

	// What if the pointers in oldToNew are not the same as in transition?
	for (auto const& a : alphabet)
	{
		for (auto const& equivalentClass : currentEquivalentStates)
		{
			auto const& oldStateRef = equivalentClass.front();
			auto const& newState = oldToNew.at(&oldStateRef);
			auto const& newImage = oldToNew.at(findImage(oldStateRef, a));
			if (isFinal(oldStateRef)) res.addFinal(newState);
			res.addTransition(newState, a, newImage);
		}
	}

	return res;
}
