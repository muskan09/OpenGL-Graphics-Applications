#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    std::vector<GLdouble> bg_color = { 1.0, 1.0, 1.0,  1.0 };
    std::vector<GLdouble> ax_color = { 0.0, 0.0, 0.0 };
    std::vector<GLdouble> org_color = { 0.0, 0.0, 0.0 };

    int ax_size = 1;
    int org_size = 4;

    // setting methods
    void change_bgCol(GLdouble, GLdouble, GLdouble, GLdouble);
    void change_axCol(GLdouble, GLdouble, GLdouble);
    void change_orgCol(GLdouble, GLdouble, GLdouble);
    void change_axsize(int);
    void change_orgsize(int);
    void change_ColPresets(int);
};

