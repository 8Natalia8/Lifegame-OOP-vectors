#ifndef LIFEGAME_H
#define LIFEGAME_H
#include <vector>
#include "Cell.h"
using namespace std;
class LifeGame
{
private:
	//трехмерный??вектор или указатель на двумерныйвектор
	//Cell*** board;
	vector<vector<Cell*>> board;
	int rows, cols;
public:
	LifeGame(int rows = 60, int cols = 60);
	~LifeGame();
	void print()const;
	void step();
	Cell* get_cell(int y, int x);
	int get_cols()const
	{
		return cols;
	}
	int get_rows()const
	{
		return rows;
	}
	Cell* start_func(int y, int x, bool state);
	bool boardEmptyness();
	void go();
	
};
#endif // LIFEGAME_H