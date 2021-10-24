#include "FSA.cpp"
#include "DFSA.cpp"
#include "PDA.cpp"
#include <iostream>

using namespace std;

int main() {
	/*FSA<unsigned int, char> automaton;
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

	auto minimizedDA = Dautomaton.minimize();
	word = { 'a', 'b' };
	cout << minimizedDA.inLanguage(word) << endl;*/

	//Test it https://www.youtube.com/watch?v=0XaGAkY09Wc
	DFSA<char, unsigned int> Tautomaton;
	Tautomaton.setStart('A');
	Tautomaton.addFinal('E');
	Tautomaton.addTransition('A', 0, 'B');
	Tautomaton.addTransition('A', 1, 'C');
	Tautomaton.addTransition('B', 0, 'B');
	Tautomaton.addTransition('B', 1, 'D');
	Tautomaton.addTransition('C', 0, 'B');
	Tautomaton.addTransition('C', 1, 'C');
	Tautomaton.addTransition('D', 0, 'B');
	Tautomaton.addTransition('D', 1, 'E');
	Tautomaton.addTransition('E', 0, 'B');
	Tautomaton.addTransition('E', 1, 'C');

	auto minimizedDAT = Tautomaton.minimize();
	list<unsigned int> wordT = { 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1 };
	cout << minimizedDAT.inLanguage(wordT) << endl;

	PDA<unsigned int, char, char> pushdown;
	return 0;
}