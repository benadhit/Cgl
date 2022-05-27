#pragma once

class Window;

class Keyboard{
public:
    // callback
    static void KeyCallBack(Window& widnow, int key, int scan_code, int action,int mods);

    static bool Key(int key);

    static bool KeyChanged(int key);

    static bool KeyWentUp(int key);

    static bool KeyWentDown(int key);
private:
    static bool keys[];
    static bool keysChanged[];
};