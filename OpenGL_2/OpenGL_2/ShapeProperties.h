#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// DefaultLine class
class DefaultLine
{
protected:

    std::vector<GLdouble> default_color = { 0.0, 0.0, 1.0 }; // r = 0.0, g = 0.0, b = 1.0;

    int default_thickness = 1; // default 1 px

    std::string default_style = "1"; // plot all

    std::vector<GLdouble> default_ep_color = { 1.0, 0.0, 0.0 }; // endpoints color
    int default_ep_size = 4; //endpoints size

public:
    void display_props(int);

    // set methods
    void changeColor(GLdouble, GLdouble, GLdouble);
    void changeColorPresets();
    void changeThickness(int);
    void changeStyle(std::string);
    void changeStylePresets();
    void changeColorEP(GLdouble, GLdouble, GLdouble);
    void changeColorEPPresets();
    void changeSizeEP(int);
};

class Line : virtual public DefaultLine
{
protected:
    std::pair<int, int> P1; // X1, Y1
    std::pair<int, int> P2; // X2, Y2

public:
    bool pts_set = false;

    // constructors
    Line() {}
    Line(int x1, int y1, int x2, int y2, GLdouble r, GLdouble g, GLdouble b, std::string s) : P1(x1, y1), P2(x2, y2) { default_color = { r, g, b }; default_style = s; }

    // set methods
    void setPoint1(int, int);
    void setPoint2(int, int);

    // end point drawing algo
    void drawEndPoints();
};

class Circle : virtual public DefaultLine
{
protected:
    std::pair<int, int> P1; // X1, Y1: center coords
    int radius = 0;

public:
    bool pts_set = false;

    // constructors
    Circle() {}
    Circle(int x1, int y1, int x2, int y2, GLdouble r, GLdouble g, GLdouble b, std::string s) : P1(x1, y1)
    {
        radius = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
        default_color = { r, g, b };
        default_style = s;
    }

    // set points
    void setPoint1(int x1, int y1);
    void setPoint2(int x2, int y2);

    // end point drawing algo
    void drawEndPoints();
};
class Shape :public Line, public Circle
{
public:
    int type; // 0: line, 1: circle
    int number;

    // constructors
    Shape() { type = 0; number = -1; }
    Shape(int t, int n) :type(t), number(n) {};
    Shape(int x1, int y1, int x2, int y2, GLdouble r, GLdouble g, GLdouble b, std::string s)
    {
        type = 0;
        Line::P1 = std::make_pair(x1, y1);
        Line::P2 = std::make_pair(x2, y2);
        default_color = { r, g, b };
        default_style = s;
    }
    Shape(int x1, int y1, int rad, GLdouble r, GLdouble g, GLdouble b, std::string s)
    {
        type = 1;
        Circle::P1 = std::make_pair(x1, y1);
        radius = rad;
        default_color = { r, g, b };
        default_style = s;
    }

    // methods
    void display_props();

    // friend functions
    friend void bresenham_circle(Shape&);
    friend void drawOctants(Shape&, int, int);
    friend void draw_circle(Shape&);
    friend void bresenham_line(Shape&);
    friend void draw_line(Shape&);
};
