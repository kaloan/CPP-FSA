#include "FSA.cpp"
#include "DFSA.cpp"
#include "PDA.cpp"
#include <iostream>

using namespace std;

int main() {
	FSA<unsigned int, char> automaton;
	automaton.setStart(1);
	automaton.addFinal(2);
	automaton.addTransition(1, 'a', 3);
	automaton.addTransition(3, 'b', 2);
	list<char> word = { 'a', 'b' };
	cout << automaton.inLanguage(word) << endl;

	DFSA<unsigned int, char> Dautomaton;
	Dautomaton.setStart(1);
	Dautomaton.addFinal(2);
	Dautomaton.addTransition(1, 'a', 3);
	Dautomaton.addTransition(3, 'b', 2);
	word = { 'a', 'b' };
	cout << Dautomaton.inLanguage(word) << endl;

	PDA<unsigned int, char, char> pushdown;
	return 0;
}