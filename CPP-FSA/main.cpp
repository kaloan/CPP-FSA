#include "FSA.h"
#include <iostream>

using namespace std;

int main() {
	FSA<unsigned int, char> automaton;
	automaton.addTransition(1, 'a', 3);
	automaton.addTransition(3, 'b', 2);
	list<char> word = { 'a', 'b' };
	cout << automaton.inLanguage(word) << endl;
	return 0;
}