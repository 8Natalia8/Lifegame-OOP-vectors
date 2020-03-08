#include <iostream>
#include <vector>
#include "LifeGame.h"
using namespace std;
int main() {
	cout << "Game 'LIFE'. OOP variant." << endl;
	LifeGame g(10,9);
	g.start_func(1,2,true);
	g.start_func(1, 3, true);
	g.start_func(3, 4, true);
	g.start_func(3, 5, true);
	g.go();
	return 0;
}
