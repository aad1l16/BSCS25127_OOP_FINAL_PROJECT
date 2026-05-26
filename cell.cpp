#include "raylib.h"
#include "cell.h"

cell::cell(int _x, int _y, int pX, int pY, int cS, bool r, bool f) : x{ _x }, y{ _y }, pixelX{ pX }, pixelY{ pY }, cellSize{ cS }, revealed{ r }, flagged{ f } {}

cell::cell(const cell& c) : x{ c.x }, y{ c.y }, pixelX{ c.pixelX }, pixelY{ c.pixelY }, cellSize{ c.cellSize }, revealed{ c.revealed }, flagged{ c.flagged } {}

void cell::operator=(const cell& c) {
	this->x = c.x;
	this->y = c.y;
	this->pixelX = c.pixelX;
	this->pixelY = c.pixelY;
	this->cellSize = c.cellSize;
	this->revealed = c.revealed;
	this->flagged = c.flagged;
}

int cell::get_adjacent_mines() {
	return 0;
}

void cell::reveal() {
	if(!this->flagged) this->revealed = true;
}

void cell::toggle_flag() {
	if (!this->revealed) {
		if (!this->flagged) this->flagged = true;
		else this->flagged = false;
	}
}

bool cell::is_mouse_over() {
	Vector2 mousePos = GetMousePosition();
	if (mousePos.x >= this->pixelX && mousePos.x <= this->pixelX + this->cellSize) if (mousePos.y >= this->pixelY && mousePos.y <= this->pixelY + this->cellSize) return true;
	return false;
}

bool cell::is_revealed() {
	return this->revealed;
}

bool cell::is_flagged() {
	return this->flagged;
}

int cell::get_x() {
	return this->x;
}

int cell::get_y() {
	return this->y;
}