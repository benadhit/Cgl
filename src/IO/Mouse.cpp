#include "Mouse.h"
#include "../Window.h"
#include <GLFW/glfw3.h>

double Mouse::x_ =0 ;
double Mouse::y_ =0 ;
double Mouse::last_x_ =0;
double Mouse::last_y_ =0 ;
double Mouse::dx_ =0;
double Mouse::dy_ =0;
double Mouse::scrollDx_ = 0;
double Mouse::scrollDy_ = 0;
bool Mouse::firstMouse_ = true;
bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = {0};
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] ={0};

bool Mouse::Button(int button)
{
    return buttons[button];
}

bool Mouse::ButtonChanged(int button)
{
    bool ret = buttonsChanged[button];
    buttonsChanged[button] = false;
    return ret;
}

bool Mouse::ButtonWentUp(int button)
{
    return !buttons[button] && ButtonChanged(button);
}

bool Mouse::ButtonWentDown(int button)
{
    return buttons[button] && ButtonChanged(button);
}

void Mouse::GetMousePos(double& x, double& y)
{
    x = x_;
    y = y_;
}

void Mouse::GetMouseAcce(double& dx, double& dy)
{
    dx = dx_;
    dy_ = dy_;
}

void Mouse::GetMouseScrollAcce(double& dx, double& dy)
{
    dx = scrollDx_;
    dy_ = scrollDy_;
}

void Mouse::CursorPosCallback(Window& window, double x, double y)
{
    x_ = x;
    y_ = y;
    if (firstMouse_)
    {
        last_x_ = x;
        last_y_ = y;
        firstMouse_ = false;
    }
    dx_ = x- last_x_;
    dy_ = last_y_ - y;
    last_x_ = x;
    last_y_ = y;
}

void Mouse::MouseWheelCallback(Window& window,double dx, double dy)
{
    scrollDx_ = dx;
    scrollDy_ = dy;
}

void Mouse::MouseButtonCallback(Window& window, int button, int action, int mods)
{
    if (action != GLFW_RELEASE)
    {
       if (!buttons[button])
       {
           buttons[button] = true;
       } else {
           buttons[button] = false;
       }    
    }
    buttonsChanged[button] = action != GLFW_REPEAT;
}
    