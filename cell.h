#pragma once
#include "raylib.h"

class cell {
protected:
	int x;
	int y;
	int pixelX;
	int pixelY;
	int cellSize;
	bool revealed;
	bool flagged;
public:
	cell(int, int, int, int, int, bool, bool);
	cell(const cell&);
	void operator=(const cell&);
	virtual void Draw() = 0;
	virtual bool is_mine() = 0;
	virtual int get_adjacent_mines();
	void reveal();
	void toggle_flag();
	bool is_mouse_over();
	bool is_revealed();
	bool is_flagged();
	int get_x();
	int get_y();
};