#include <glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

bool called = false;

double X1 = 0;
double Y1 = 0;
double X2 = 0;
double Y2 = 0;

bool selected = false;

void simple_dda(double X1, double Y1, double X2, double Y2)
{
    if (!::called) std::cout << "IMPLEMENTING SIMPLE DDA\n" << std::endl;

    int dx = X2 - X1;
    int dy = Y2 - Y1;
    int steps = std::max(std::abs(dx), std::abs(dy));

    double xinc = dx / (double)steps;
    double yinc = dy / (double)steps;

    if (!::called) std::cout << "steps: " << steps << ", xinc: " << xinc << ", yinc: " << yinc << std::endl;

    X1 += 0.500; Y1 += 0.500;
    if (!::called) std::cout << "( " << (int)X1 << ", " << (int)Y1 << " )" << std::endl;

    for (int i = 0; i < steps; ++i)
    {
        X1 += xinc;
        Y1 += yinc;
        // if (!::called_simp) std::cout << "( " << std::trunc(X1) << ", " << std::trunc(Y1) << " ) " << std::endl;
        if (!::called) std::cout << "( " << (int)(X1) << ", " << (int)(Y1) << " ) " << std::endl;

        glPointSize(1);
        glBegin(GL_POINTS);
        glColor3d(1.0, 0.5, 0.0);
        glVertex2i((int)(X1), (int)(Y1));
        glEnd();
    }

    glFlush();
    ::called = true;
}

void symmetric_dda(double X1, double Y1, double X2, double Y2)
{
    if (!::called) std::cout << "IMPLEMENTING SYMMETRIC DDA\n" << std::endl;
    int x2 = X2, y2 = Y2;

    int dx = X2 - X1;
    int dy = Y2 - Y1;

    double E = pow(2, -1*((int)log2((std::max(std::abs(dx), std::abs(dy)))) + 1));
    // 2^-(n) such that 2^(n-1) <= max(dx, dy) < 2^n

    double xinc = dx * E;
    double yinc = dy * E;

    if (!::called) std::cout << "E: " << E << ", xinc: " << xinc << ", yinc: " << yinc << std::endl;

    if (!::called) std::cout << "( " << X1 << ", " << Y1 << " )" << std::endl;

    while(true)
    {
        X1 += xinc;
        Y1 += yinc;
        if (!::called) std::cout << "( " << std::round(X1) << ", " << std::round(Y1) << " ) " << std::endl;

        glPointSize(1);
        glBegin(GL_POINTS);
        glColor3d(0.5, 0.0, 0.5);
        glVertex2d(std::round(X1), std::round(Y1));
        glEnd();

        if (std::round(X1) == x2 && std::round(Y1) == y2) break;
    }

    glFlush();
    ::called = true;
}

void bresenham(double X1, double Y1, double X2, double Y2)
{
    if (!::called) std::cout << "IMPLEMENTING BRESENHAM'S ALGORITHM\n" << std::endl;

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
    
    if (dx > dy)
    {
        P = 2 * dy - dx;

        for (int x = X1, y = Y1, p = P; x <= X2; )
        {
            glPointSize(1);
            glBegin(GL_POINTS);
            glColor3d(0.0, 1.0, 1.0);
            if(neg_slope) glVertex2i(x, -y);
            else glVertex2i(x, y);
            glEnd();

            if (!::called) std::cout << "( " << x << ", " << (neg_slope ? -y : y) << " ) " << std::endl;
           

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

        for (int x = X1, y = Y1, p = P; y <= Y2; )
        {
            glPointSize(1);
            glBegin(GL_POINTS);
            glColor3d(0.5, 0.5, 1.0);
            if (neg_slope) glVertex2i(x, -y);
            else glVertex2i(x, y);
            glEnd();

            if (!::called) std::cout << "( " << x << ", " << (neg_slope ? -y : y) << " ) " << std::endl;

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

    glFlush();
    ::called = true;
}

short point = 1;
void set_point(GLFWwindow* window)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (::point == 1)
    {
        X1 = xpos - 250;
        Y1 = 250 - ypos;
        std::cout << "P1: " << "( " << X1 << ", " << Y1 << " )" << std::endl;
        ::point = 2;
    }
    else if (::point == 2)
    {
        X2 = xpos - 250;
        Y2 = 250 - ypos;
        std::cout << "P2: " << "( " << X2 << ", " << Y2 << " )" << std::endl;
        ::point = 1;
        ::selected = true;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (selected) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        if (glfwGetWindowAttrib(window, GLFW_HOVERED))
            set_point(window);
                 
}


int main(void)
{
    int choice;

    std::cout << "CHOOSE A LINE DRAWING ALGORITHM:\n";
    std::cout << "1. Simple DDA\n2. Symmetric DDA\n3. Bresenham\n: ";
    std::cin >> choice;

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 500, "Line Drawing Algorithms", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-250, 250, -250, 250, 0.0, 1.0);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // std::cout << glGetString(GL_VERSION) << std::endl;

    std::cout << "\nSELECT SEGMENT END POINTS VIA MOUSE CLICKS\n";

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
       
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        glPointSize(4);
        glBegin(GL_POINTS);
        glColor3d(1.0, 0.0, 0.0);
        glVertex2d(X1, Y1);
        glEnd();

        glPointSize(4);
        glBegin(GL_POINTS);
        glColor3d(1.0, 0.0, 0.0);
        glVertex2d(X2, Y2);
        glEnd();

        glPointSize(4);
        glBegin(GL_POINTS);
        glColor3d(0.0, 0.0, 0.0);
        glVertex2d(0, 0);
        glEnd();

        glPointSize(1);
        glBegin(GL_LINES);
        glColor3d(0.0, 0.0, 0.0);
        glVertex2d(-250, 0);
        glVertex2d(250, 0);
        glEnd();

        glPointSize(1);
        glBegin(GL_LINES);
        glColor3d(0.0, 0.0, 0.0);
        glVertex2d(0, 250);
        glVertex2d(0, -250);
        glEnd();

        if (selected && choice == 1) simple_dda(X1, Y1, X2, Y2);
        if (selected && choice == 2) symmetric_dda(X1, Y1, X2, Y2);
        if (selected && choice == 3) bresenham(X1, Y1, X2, Y2);
        

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}