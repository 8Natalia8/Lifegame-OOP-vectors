#include <iostream>
#include <string>
#include "LifeGame.h"
#include <vector>
using namespace std;

LifeGame::LifeGame(int rows, int cols) : rows(rows), cols(cols)
{
	//делаем двумерный вектор, далее в цикле от i,j вызываем конструктор
	vector<vector<Cell>>board(rows,vector<Cell>(cols));
	//board = new Cell **[rows];
	for (int i = 0; i < rows; i++)
	{
		//board[i] = new Cell * [cols];
		for (int j = 0; j < cols; j++)
			//board[i][j] = new Cell(this, i, j, false);
			board[i][j]=Cell(this, i, j, false);
	}
}

LifeGame::~LifeGame()
{
}

Cell* LifeGame::get_cell(int y, int x) {
	return board[y][x];
}
void LifeGame::print()const
{

	cout << " " << string(cols, '#') << endl;
	for (int i = 0; i < rows; i++) {
		cout << "#";
		for (int j = 0; j < cols; j++)
			cout << *(board[i][j]);
		cout << "#"<<endl;
	}
	cout << " " << string(cols, '#') << endl;
}
void LifeGame::step()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			board[i][j]->calc();
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			board[i][j]->change();
}

Cell* LifeGame::start_func(int y, int x, bool state) {
	 board[y][x]->set_state(state);
	 return board[y][x];
}
bool LifeGame::boardEmptyness() {
	bool flag=true;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (board[i][j]->is_alive())//нужн0 осмотреть если хоть одна жива
			{
				flag = false; //поле не пусто
				return flag;
			}
	return flag;
}
void LifeGame::go() {
	print();
	bool res; 
	while (1) {
		res= boardEmptyness();
		if (res == false) {
			print();
			step();
			
			
		}
		else {
			print();
			step();
			return;
		}
	}

}