#pragma once
#include <iostream>
#include <vector>
#include "ShapeProperties.h"

class Button
{
private:
	std::pair<int, int> top_left;
	std::pair<int, int> btm_right;

	std::vector<GLdouble> color;
public:
	bool clicked = false;

	//Constructors
	Button() :top_left({ 0, 0 }), btm_right({ 0,0 }), color({ 0.0, 0.0, 0.0 }) {}
	Button(int l1, int l2, int r1, int r2) : top_left({ l1, l2 }), btm_right({ r1, r2 }), color({ 0.0, 0.0, 0.0 }) {}
	Button(int l1, int l2, int r1, int r2, double r, double g, double b) : top_left({ l1, l2 }), btm_right({ r1, r2 }), color({ r, g, b }) {}

	// button rendering
	void drawButton();

	//setting methods
	void setColor(double r, double g, double b) { color[0] = r; color[1] = g; color[2] = b; }

	// getting methods
	std::pair<int, int> getTopLeft()
	{
		return top_left;
	}
	std::pair<int, int> getBtmRight()
	{
		return btm_right;
	}
	std::vector<double> getColor()
	{
		return color;
	}
};

void Button::drawButton()
{
	glBegin(GL_QUADS);
	glColor3d(color[0], color[1], color[2]);
	glVertex2i(top_left.first, top_left.second);
	glVertex2i(top_left.first, btm_right.second);
	glVertex2i(btm_right.first, btm_right.second);
	glVertex2i(btm_right.first, top_left.second);
	glEnd();

	glFlush();
}