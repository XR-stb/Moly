#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <thread>

#include "Vector.hpp"
#include "GraphicsDevice.hpp"

using namespace Moly;

int main() {
	GraphicsDevice window(1000, 1000);
	window.drawMap();

	window.DrawLine(30, 100, 200, 250);
	window.DrawLine(30, 100, 150, 300);
	window.DrawLine(200, 250, 150, 300);

	setcolor(RED);
	window.drawTraingle({ 30, 100 }, { 150, 300 }, { 200, 250 });
	setcolor(GREEN);
	window.drawTraingle({ 200, 100 }, { 300, 100 }, { 300, 250 });
	setcolor(YELLOW);
	window.DrawRectangle({ 600, 100 }, { 400, 250 });

	window.DrawCircle({ 300, 400 }, 100, 6);
	window.DrawCircle({ 550, 400 }, 100, 12);
	window.DrawCircle({ 800, 400 }, 100, 64);
	return 0;
}