#include "FSA.cpp"
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
	return 0;
}