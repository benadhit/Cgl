#pragma once


class Window;
class Mouse {
public:
    static bool Button(int button);
    static bool ButtonChanged(int button);
    static bool ButtonWentUp(int button);
    static bool ButtonWentDown(int button);
    static void GetMousePos(double& x, double& y);
    static void GetMouseAcce(double& dx, double& dy);
    static void GetMouseScrollAcce(double& dx, double& dy);
    static void CursorPosCallback(Window& window, double x, double y);
    static void MouseWheelCallback(Window& window,double dx, double dy);
    static void MouseButtonCallback(Window& window, int button, int action, int mods);
    
private:
    static double x_;
    static double y_;
    static double last_x_;
    static double last_y_;
    static double dx_;
    static double dy_;
    static double scrollDx_;
    static double scrollDy_;
    static bool firstMouse_;
    static bool buttons[];
    static bool buttonsChanged[];

};