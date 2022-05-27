#include "Keyboard.h"
#include "../Window.h"
#include <GLFW/glfw3.h>

bool Keyboard::keys[GLFW_KEY_LAST]= {0};

bool Keyboard::keysChanged[GLFW_KEY_LAST] = {0};

// callback
void Keyboard::KeyCallBack(Window& widnow, int key, int scan_code, int action,int mods)
{
    auto glfwHandle = (GLFWwindow*)widnow.GetBackEndWinddowHandle();
    if (action != GLFW_RELEASE)
    {
        if (!keys[key])
        {
            keys[key] = true;
        }
    }else {
          keys[key] = false;
    }
    keysChanged[key] = action != GLFW_REPEAT;

}

bool Keyboard::Key(int key)
{
    return keys[key];
}

bool Keyboard::KeyChanged(int key)
{
    bool ret = keys[key];
    keysChanged[key] = false;
    return ret;
}

bool Keyboard::KeyWentUp(int key)
{
    return !keys[key] && KeyChanged(key);
}

bool Keyboard::KeyWentDown(int key)
{
    return keys[key] && KeyChanged(key);
}