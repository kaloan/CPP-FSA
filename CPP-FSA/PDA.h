#pragma once
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <utility>
#include <tuple>
#include "Hashes.h"


template<typename StateT, typename AlphaT, typename StackT>
class PDA {
private:
	StateT start;
	std::unordered_map<std::tuple<StateT, AlphaT, StackT>, std::pair<StateT, std::vector<StackT>>, hash_tuple<StateT, AlphaT, StackT>> transitions;
	std::unordered_set<StateT> final;
protected:

};