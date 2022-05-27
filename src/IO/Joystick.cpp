#include "Joystick.h"
#include <GLFW/glfw3.h>

Joystick::Joystick(int i)
{
    id = GetId(i);
    Update();
}

void Joystick::Update()
{
    present = glfwJoystickPresent(id);
    if (present)
    {
        name = glfwGetJoystickName(id);
        axes = glfwGetJoystickAxes(id, &axesCount);
        buttons = glfwGetJoystickButtons(id, &buttonCount);
    }
}

float Joystick::AxesState(int axis)
{
    return present ? axes[axis] : 0.0;
}

uint8_t Joystick::ButtonState(int button)
{
    return present ? buttons[button]: GLFW_RELEASE;
}

int Joystick::GetButtonCount()
{
    return buttonCount;
}

bool Joystick:: IsPresent()
{
    return present;
}

const char* Joystick::GetName()
{
    return name;
}

int Joystick::GetId(int i)
{
    return GLFW_JOYSTICK_1 + i;
}