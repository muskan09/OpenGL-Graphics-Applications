#pragma once
#include "ShapeProperties.h"
#include "WindowProperties.h"
#include "Button.h"

DefaultLine def_line;
Window w;

std::vector<Shape> shapes;
// std::vector<std::vector<int>> board;
std::vector<int> deleted;
int shape_number = -1;

std::vector<Button> colors;
std::vector<std::vector<double>> col_vals = {
        {1,0,0},{0, 1, 0},{0,0,1} , {0, 0.980, 0.772},
        {0.976, 0.031, 0.992},{0.984, 0.882, 0.196 }, { 0.984, 0.556, 0.196 },
        {0.627, 0.196, 0.984}, {0.196, 0.6, 0.984}, {0.5, 0, 0.5},
        {0, 0.5, 0.5}, {0.5, 0.5, 0}, {0.549, 0.549, 0.549},
        {0,0,0}
};

std::pair<int, int> selected_tl = { 0,0 };
std::pair<int, int> selected_br = { 0,0 };
bool col_selected = false;
int col_idx;

bool t_pres = false;
int sc = 0;