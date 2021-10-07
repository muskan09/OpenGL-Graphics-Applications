#include "WindowProperties.h"
#include "ShapeProperties.h"
#include "Button.h"
#include "objects.h"

int draw_mode = 0;

void drawOctants(Shape& c, int x, int y)
{
    int cent_x = c.Circle::P1.first, cent_y = c.Circle::P1.second;
    glBegin(GL_POINTS);
    glColor3d(c.default_color[0], c.default_color[1], c.default_color[2]);
    glVertex2i(cent_x + x, cent_y + y);
    glVertex2i(cent_x - x, cent_y + y);
    glVertex2i(cent_x + x, cent_y - y);
    glVertex2i(cent_x - x, cent_y - y);
    glVertex2i(cent_x + y, cent_y + x);
    glVertex2i(cent_x - y, cent_y + x);
    glVertex2i(cent_x + y, cent_y - x);
    glVertex2i(cent_x - y, cent_y - x);
    glEnd();
}
void bresenham_circle(Shape& c)
{
    glPointSize(1);

    int x = 0, y = c.radius;
    int d = 3 - 2 * c.radius;
    drawOctants(c, x, y);

    int i = 0;
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;

        if (i == c.default_style.length()) i = 0;
        if (c.default_style[i++] == '0') continue;
        drawOctants(c, x, y);
    }
    glFlush();
}
void draw_circle(Shape& c)
{
    if (c.default_thickness == 1) { bresenham_circle(c); return; }
    else
    {
        int i = c.default_thickness % 2 == 0 ? -c.default_thickness / 2 + 1 : -c.default_thickness / 2;

        for (; i <= c.default_thickness / 2; ++i)
        {
            Shape shape(c.Circle::P1.first, c.Circle::P1.second, c.radius + i, c.default_color[0], c.default_color[1], c.default_color[2], c.default_style);
            bresenham_circle(shape);
        }
    }
}


void bresenham_line(Shape& l)
{
    glPointSize(1);

    int X1 = l.Line::P1.first, Y1 = l.Line::P1.second, X2 = l.P2.first, Y2 = l.P2.second;

    int dx = X2 - X1;
    int dy = Y2 - Y1;

    bool neg_slope = false;
    if (dy * dx < 0)
    {
        neg_slope = true;
        Y1 = -Y1;
        Y2 = -Y2;

        dy = -dy;
    }

    if (dx > dy && X1 > X2)
    {
        std::swap(X1, X2);
        std::swap(Y1, Y2);

        dx = -dx;
        dy = -dy;
    }
    else if (dy > dx && Y1 > Y2)
    {
        std::swap(X1, X2);
        std::swap(Y1, Y2);

        dx = -dx;
        dy = -dy;
    }

    /*
    * P0 = 2dy - dx
    * Pk+1 = Pk + 2dy (Pk < 0), yk+1 = yk
    * Pk+1 = Pk + 2dy -2dx (Pk >= 0), yk+1 = yk + 1
    */

    int P;
    int i = 0;
    std::vector<std::pair<int, int>> pts;
    std::vector<short> plot;

    if (dx > dy)
    {
        P = 2 * dy - dx;

        for (int x = X1, y = Y1, p = P; x <= X2; ++i)
        {
            if (i > l.default_style.size() - 1) i = 0;
            if (l.default_style[i] == '1') plot.push_back(1);
            else plot.push_back(0);

            if (neg_slope) pts.push_back(std::make_pair(x, -y));
            else pts.push_back(std::make_pair(x, y));

            x += 1;

            if (p < 0)
            {
                p += 2 * dy;
            }
            else
            {
                p += 2 * dy - 2 * dx;
                y += 1;
            }
        }
    }
    else
    {
        P = 2 * dx - dy;

        for (int x = X1, y = Y1, p = P; y <= Y2; ++i)
        {
            if (i > l.default_style.size() - 1) i = 0;
            if (l.default_style[i] == '1') plot.push_back(1);
            else plot.push_back(0);

            if (neg_slope) pts.push_back(std::make_pair(x, -y));
            else pts.push_back(std::make_pair(x, y));

            y += 1;

            if (p < 0)
            {
                p += 2 * dx;
            }
            else
            {
                p += 2 * dx - 2 * dy;
                x += 1;
            }
        }
    }
    if (plot[plot.size() - 1] == 0)
    {
        for (int i = 0; i < plot.size() / 2; ++i)
            plot[plot.size() - i - 1] = plot[i];
    }
    for (int i = 0; i < pts.size(); ++i)
    {
        if (plot[i])
        {
            glBegin(GL_POINTS);
            glColor3d(l.default_color[0], l.default_color[1], l.default_color[2]);
            glVertex2i(pts[i].first, pts[i].second);
            glEnd();
        }
    }

    glFlush();
}
void draw_line(Shape& l)
{
    if (l.default_thickness == 1)
    {
        bresenham_line(l);
        return;
    }

    int i = l.default_thickness % 2 == 0 ? -l.default_thickness / 2 + 1 : -l.default_thickness / 2;

    float m = (l.P2.second - l.Line::P1.second) / (float)(l.P2.first - l.Line::P1.first);

    if (std::abs(m) <= 1)
    {
        for (; i <= l.default_thickness / 2; ++i)
        {
            Shape shape(l.Line::P1.first - i * m, l.Line::P1.second + i, l.P2.first - i * m, l.P2.second + i, l.default_color[0], l.default_color[1], l.default_color[2], l.default_style);
            bresenham_line(shape);
        }
    }
    else
    {
        for (; i <= l.default_thickness / 2; ++i)
        {
            Shape shape(l.Line::P1.first + i, l.Line::P1.second - i / m, l.P2.first + i, l.P2.second - i / m, l.default_color[0], l.default_color[1], l.default_color[2], l.default_style);
            bresenham_line(shape);
        }
    }
}
void showClicked()
{
    glBegin(GL_QUADS);
    glColor3d(0.976, 0.968, 0.862);
    glVertex2i(selected_tl.first, selected_tl.second);
    glVertex2i(selected_tl.first, selected_br.second);
    glVertex2i(selected_br.first, selected_br.second);
    glVertex2i(selected_br.first, selected_tl.second);
    glEnd();
}
void set_points(GLFWwindow* window, int pt)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int x = xpos - 250;
    int y = 290 - ypos;

    if (y <= colors[0].getTopLeft().second && y >= colors[0].getBtmRight().second)
    {
        int i = 0;
        for (auto& btn : colors)
        {
            if (x >= btn.getTopLeft().first && x <= btn.getBtmRight().first)
            {
                btn.clicked = !btn.clicked;
                if (btn.clicked)
                {
                    colors[col_idx].clicked = false;
                    col_idx = i;
                    selected_tl = { btn.getTopLeft().first + 5, btn.getTopLeft().second - 5 };
                    selected_br = { btn.getBtmRight().first - 5, btn.getBtmRight().second + 5 };
                    break;
                }
                else
                {
                    col_idx = colors.size() - 1;
                    selected_tl = { colors[colors.size() - 1].getTopLeft().first + 5,
                                    colors[colors.size() - 1].getTopLeft().second - 5 };
                    selected_br = { colors[colors.size() - 1].getBtmRight().first - 5,
                                    colors[colors.size() - 1].getBtmRight().second + 5 };
                    break;
                }
            }
            ++i;
        }
        return;
    }

    if (pt == 1)
    {
        if (draw_mode == 0)
        {
            shapes.push_back(Shape(0, ++shape_number));
            shapes[shape_number].Line::setPoint1(x, y);
        }
        else if (draw_mode == 1)
        {
            shapes.push_back(Shape(1, ++shape_number));
            shapes[shape_number].Circle::setPoint1(x, y);
        }
        std::vector<double> c = colors[col_idx].getColor();
        shapes[shape_number].changeColor(c[0], c[1], c[2]);
        shapes[shape_number].changeColorEP(c[0], c[1], c[2]);
    }
    else if (pt == 2)
    {
        if (draw_mode == 0)
            shapes[shape_number].Line::setPoint2(x, y);

        else if (draw_mode == 1)
            shapes[shape_number].Circle::setPoint2(x, y);
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (glfwGetWindowAttrib(window, GLFW_HOVERED))
    {
        // set point 1 on left click, or set the center
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            set_points(window, 1);

        // set point 2 on right click, or set a point on the circle boundary
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            set_points(window, 2);
    }
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        // start drawing circles
        draw_mode = 1;
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        // start drawing lines
        draw_mode = 0;
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        // adjust thickness
        if (shapes.empty()) return;
        
        t_pres = !t_pres;
        if (t_pres) std::cout << "\nEditing shape thickness. Scroll to adjust. Press 'T' to exit." << std::endl;
        else if (!t_pres) 
        {
            std::cout << "Thickness changed to: " << sc << std::endl; 
            sc = 0;
        }
    }
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (t_pres)
    {
        sc += yoffset;
        if (sc < 1)sc = 1;
        shapes[shape_number].changeThickness(sc);
    }
}
int main()
{
    shapes.reserve(300);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 540, "GRAPHICS", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) std::cout << "ERROR!" << std::endl;

    glViewport(0, 0, 500, 540);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250, 250, -250, 290, 0.0, 1.0);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSwapInterval(1);

    int start_x = -245, start_y = 285; // btns are 30 px tall and wide, 5 px spacing bw them.

    for (int i = 0; i < col_vals.size(); ++i)
    {
        colors.push_back(Button(start_x, start_y, start_x + 30, start_y - 30, col_vals[i][0], col_vals[i][1], col_vals[i][2]));
        start_x += 35;
    }
    col_idx = colors.size() - 1;
    selected_tl = { colors[colors.size() - 1].getTopLeft().first + 5,
                                    colors[colors.size() - 1].getTopLeft().second - 5 };
    selected_br = { colors[colors.size() - 1].getBtmRight().first - 5,
                    colors[colors.size() - 1].getBtmRight().second + 5 };
    
    std::cout << "\nPRESS 'C' TO START DRAWING CIRCLES" << std::endl;
    std::cout << "PRESS 'L' TO START DRAWING LINES (default)" << std::endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(w.bg_color[0], w.bg_color[1], w.bg_color[2], w.bg_color[3]);

        glPointSize(w.org_size);
        glBegin(GL_POINTS);
        glColor3d(w.org_color[0], w.org_color[1], w.org_color[2]);
        glVertex2d(0, 0);
        glEnd();

        glPointSize(w.ax_size);
        glBegin(GL_LINES);
        glColor3d(w.ax_color[0], w.ax_color[1], w.ax_color[2]);
        glVertex2d(-250, 0);
        glVertex2d(250, 0);
        glEnd();

        glPointSize(w.ax_size);
        glBegin(GL_LINES);
        glColor3d(w.ax_color[0], w.ax_color[1], w.ax_color[2]);
        glVertex2d(0, 250);
        glVertex2d(0, -250);
        glEnd();

        for (auto sh : shapes)
        {
            /*bool cont = false;
            for (int i : deleted)
                if (i == sh.number) cont = true;
            if (cont) continue;*/


            if (sh.type == 0)
            {
                sh.Line::drawEndPoints();
                if (sh.Line::pts_set) draw_line(sh);
            }
            else
            {
                sh.Circle::drawEndPoints();
                if (sh.Circle::pts_set) draw_circle(sh);
            }
        }

        glBegin(GL_QUADS);
        glColor3d(0.976, 0.968, 0.862);
        glVertex2i(-250, 290);
        glVertex2i(250, 290);
        glVertex2i(-250, 250);
        glVertex2i(250, 250);
        glEnd();

        for (auto& btn : colors)
            btn.drawButton();
        showClicked();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}