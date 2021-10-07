#include "ShapeProperties.h"
#include "WindowProperties.h"

void printColorPresets();

/* IMPLEMENTATION OF WINDOW PROPERTIES */
void Window::change_bgCol(GLdouble r, GLdouble g, GLdouble b, GLdouble a)
{
    bg_color[0] = r; bg_color[1] = g; bg_color[2] = b; bg_color[3] = a;
}
void Window::change_axCol(GLdouble r, GLdouble g, GLdouble b)
{
    ax_color[0] = r; ax_color[1] = g; ax_color[2] = b;
}
void Window::change_orgCol(GLdouble r, GLdouble g, GLdouble b)
{
    org_color[0] = r; org_color[1] = g; org_color[2] = b;
}
void Window::change_axsize(int s) { ax_size = s; }
void Window::change_orgsize(int s) { org_size = s; }
void Window::change_ColPresets(int i)
{
    // 0 bg, 1 ax, 2 org
    int choice;

    printColorPresets();

    std::cin >> choice;

    if (choice == 1)
    {
        if (i == 0) change_bgCol(0.0, 0.0, 1.0, 1.0);
        else if (i == 1) change_axCol(0.0, 0.0, 1.0);
        else change_orgCol(0.0, 0.0, 1.0);
    }
    else if (choice == 2)
    {
        if (i == 0) change_bgCol(0.0, 1.0, 0.0, 1.0);
        else if (i == 1) change_axCol(0.0, 1.0, 0.0);
        else change_orgCol(0.0, 1.0, 0.0);
    }
    else if (choice == 3)
    {
        if (i == 0) change_bgCol(1.0, 0.0, 0.0, 1.0);
        else if (i == 1) change_axCol(1.0, 0.0, 0.0);
        else change_orgCol(1.0, 0.0, 0.0);
    }
    else if (choice == 4)
    {
        if (i == 0) change_bgCol(0.0, 0.0, 0.0, 1.0);
        else if (i == 1) change_axCol(0.0, 0.0, 0.0);
        else change_orgCol(0.0, 0.0, 0.0);
    }
    else if (choice == 5)
    {
        if (i == 0) change_bgCol(1.0, 1.0, 0.0, 1.0);
        else if (i == 1) change_axCol(1.0, 1.0, 0.0);
        else change_orgCol(1.0, 1.0, 0.0);
    }
    else if (choice == 6)
    {
        if (i == 0) change_bgCol(1.0, 0.0, 0.5, 1.0);
        else if (i == 1) change_axCol(1.0, 0.0, 0.5);
        else change_orgCol(1.0, 0.0, 0.5);
    }
    else if (choice == 7)
    {
        if (i == 0) change_bgCol(1.0, 0.5, 0.0, 1.0);
        else if (i == 1) change_axCol(1.0, 0.5, 0.0);
        else change_orgCol(1.0, 0.5, 0.0);
    }
    else if (choice == 8)
    {
        if (i == 0) change_bgCol(0.0, 0.75, 1.0, 1.0);
        else if (i == 1) change_axCol(0.0, 0.75, 1.0);
        else change_orgCol(0.0, 0.75, 1.0);
    }
    else if (choice == 9)
    {
        if (i == 0) change_bgCol(0.5, 0.0, 1.0, 1.0);
        else if (i == 1) change_axCol(0.5, 0.0, 1.0);
        else change_orgCol(0.5, 0.0, 1.0);
    }
}

/* IMPLEMENTATION OF DEFAULT LINE PROPERTIES */
void DefaultLine::display_props(int t)
{
    std::cout << "\t\tColor (RGB): " << default_color[0] << " " << default_color[1] << " " << default_color[2] << std::endl;
    std::cout << "\t\tThickness: " << default_thickness << std::endl;
    std::cout << "\t\tStyle: " << default_style << std::endl;
    if (t == 0)
    {
        std::cout << "\t\tEndpoints Color (RGB): " << default_ep_color[0] << " " << default_ep_color[1] << " " << default_ep_color[2] << std::endl;
        std::cout << "\t\tEndpoints Size (px): " << default_ep_size << std::endl;
    }
    else
    {
        std::cout << "\t\tCenter Color (RGB): " << default_ep_color[0] << " " << default_ep_color[1] << " " << default_ep_color[2] << std::endl;
        std::cout << "\t\tCenter Size (px): " << default_ep_size << std::endl;
    }
}
void DefaultLine::changeColor(GLdouble r, GLdouble g, GLdouble b)
{
    default_color[0] = r;
    default_color[1] = g;
    default_color[2] = b;
}
void DefaultLine::changeColorPresets()
{
    int choice;

    printColorPresets();

    std::cin >> choice;

    if (choice == 1) changeColor(0.0, 0.0, 1.0);
    else if (choice == 2) changeColor(0.0, 1.0, 0.0);
    else if (choice == 3) changeColor(1.0, 0.0, 0.0);
    else if (choice == 4) changeColor(0.0, 0.0, 0.0);
    else if (choice == 5) changeColor(1.0, 1.0, 0.0);
    else if (choice == 6) changeColor(1.0, 0.0, 0.5);
    else if (choice == 7) changeColor(1.0, 0.5, 0.0);
    else if (choice == 8) changeColor(0.0, 0.75, 1.0);
    else if (choice == 9) changeColor(0.5, 0.0, 1.0);
}
void DefaultLine::changeThickness(int t)
{
    default_thickness = t;
}
void DefaultLine::changeStyle(std::string s)
{
    default_style = s;
}
void DefaultLine::changeStylePresets()
{
    int choice;

    std::cout << "\t\tSTYLE PRESETS:" << std::endl;
    std::cout << "\t\t1. . . . . . . . . . . (Plot 1, Skip 1)" << std::endl;
    std::cout << "\t\t2. .. .. .. .. .. .. ..(Plot 2, Skip 1)" << std::endl;
    std::cout << "\t\t3. ... ... ... ... ... (Plot 3, Skip 1)" << std::endl;
    std::cout << "\t\t4. .. . .. . .. . .. . ..  (Plot 2, Skip 1, Plot 1, Skip 1)" << std::endl;
    std::cout << "\t\t5. ..   ..   ..   ..   (Plot 2, Skip 3)" << std::endl;
    std::cout << "\t\t6. .... .... .... .... (Plot 4, Skip 1)" << std::endl;
    std::cout << "\t\t7. ....  ....  ....  ..(Plot 4, Skip 2)" << std::endl;
    std::cout << "\t\t8. ... .. ... .. ... .. ..(Plot 3, Skip 1, Plot 2, Skip 1)" << std::endl;
    std::cout << "\t\t9. ....    ....    ....(Plot 4, Skip 4)" << std::endl;
    std::cout << "\t\t: ";

    std::cin >> choice;

    if (choice == 1) changeStyle("10");
    else if (choice == 2) changeStyle("110");
    else if (choice == 3) changeStyle("1110");
    else if (choice == 4) changeStyle("11010");
    else if (choice == 5) changeStyle("11000");
    else if (choice == 6) changeStyle("11110");
    else if (choice == 7) changeStyle("111100");
    else if (choice == 8) changeStyle("1110110");
    else if (choice == 9) changeStyle("11110000");
}
void DefaultLine::changeColorEP(GLdouble r, GLdouble g, GLdouble b)
{
    default_ep_color[0] = r;
    default_ep_color[1] = g;
    default_ep_color[2] = b;
}
void DefaultLine::changeColorEPPresets()
{
    int choice;

    printColorPresets();

    std::cin >> choice;

    if (choice == 1) changeColorEP(0.0, 0.0, 1.0);
    else if (choice == 2) changeColorEP(0.0, 1.0, 0.0);
    else if (choice == 3) changeColorEP(1.0, 0.0, 0.0);
    else if (choice == 4) changeColorEP(0.0, 0.0, 0.0);
    else if (choice == 5) changeColorEP(1.0, 1.0, 0.0);
    else if (choice == 6) changeColorEP(1.0, 0.0, 0.5);
    else if (choice == 7) changeColorEP(1.0, 0.5, 0.0);
    else if (choice == 8) changeColorEP(0.0, 0.75, 1.0);
    else if (choice == 9) changeColorEP(0.5, 0.0, 1.0);
}
void DefaultLine::changeSizeEP(int s)
{
    default_ep_size = s;
}

/* IMPLEMENTATION OF LINE PROPERTIES */
void Line::setPoint1(int x1, int y1)
{
    P1.first = x1;
    P1.second = y1;
}
void Line::setPoint2(int x2, int y2)
{
    P2.first = x2;
    P2.second = y2;
    pts_set = true;
}
void Line::drawEndPoints()
{
    glPointSize(default_ep_size);
    glBegin(GL_POINTS);
    glColor3d(default_ep_color[0], default_ep_color[1], default_ep_color[2]);
    glVertex2i(P1.first, P1.second);
    glEnd();

    if (pts_set)
    {
        glPointSize(default_ep_size);
        glBegin(GL_POINTS);
        glColor3d(default_ep_color[0], default_ep_color[1], default_ep_color[2]);
        glVertex2i(P2.first, P2.second);
        glEnd();
    }
}
/* IMPLEMENTATION OF CIRCLE PROPERTIES */
void Circle::setPoint1(int x1, int y1)
{
    P1.first = x1;
    P1.second = y1;
}
void Circle::setPoint2(int x2, int y2)
{
    radius = sqrt(pow((P1.first - x2), 2) + pow((P1.second - y2), 2));
    pts_set = true;
}
void Circle::drawEndPoints()
{
    glPointSize(default_ep_size);
    glBegin(GL_POINTS);
    glColor3d(default_ep_color[0], default_ep_color[1], default_ep_color[2]);
    glVertex2i(P1.first, P1.second);
    glEnd();
}

/* IMPLEMENTATION OF SHAPE PROPERTIES */
void Shape::display_props()
{
    std::cout << "\t\tSHAPE NUMBER: " << number;
    type == 0 ? std::cout << ", is a LINE\n" << std::endl : std::cout << ", is a CIRCLE\n" << std::endl;
    DefaultLine::display_props(type);
}



void printColorPresets()
{
    std::cout << "\t\tCOLOR PRESETS:" << std::endl;
    std::cout << "\t\t1. Blue" << std::endl;
    std::cout << "\t\t2. Green" << std::endl;
    std::cout << "\t\t3. Red" << std::endl;
    std::cout << "\t\t4. Black" << std::endl;
    std::cout << "\t\t5. Yellow" << std::endl;
    std::cout << "\t\t6. Pink" << std::endl;
    std::cout << "\t\t7. Orange" << std::endl;
    std::cout << "\t\t8. Sky Blue" << std::endl;
    std::cout << "\t\t9. Purple" << std::endl;
    std::cout << "\t\t: ";
}