#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <vector>
using namespace std;
class LifeGame;
class Cell 
{
private:
	LifeGame* life;//вектор?
	int x, y;
	bool state, newstate;

protected:
	int get_neighbour_count() const;
public:
	
	Cell() {
}
	Cell(LifeGame* life, int y, int x, bool state);
	void calc();
	void change();
	bool is_alive()const
	{
		return state;
	}
	void set_state(bool value) 
	{
		newstate = state = value;
	}
	

};
std::ostream& operator<<(std::ostream& out, const Cell& c);



#endif // CELL_H