#include "EditingMode.h"
#include <iostream>
#include <typeinfo>

class _Replace : public EditorMode
{
private:
        

public:
    _Replace() : EditorMode({ Command(VK_R) })
    {
            
    }

    void OnSwitch(size_t commandIndex) const override
    {
        // R
    }

    void OnUpdate(TextEditor& editor, INPUT_RECORD input) const override
    {

    }
} Replace;

class _Visual : public EditorMode
{
private:
public:
    _Visual() : EditorMode({ Command(VK_V), Command(VK_V, LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED), Command(VK_V, SHIFT_PRESSED) })
    {

    }

    void OnSwitch(size_t commandIndex) const override
    {
        switch (commandIndex)
        {
        case 0: // V
                
            break;
        case 1: // CTRL+V

            break;
        case 2: // SHIFT+V

            break;
        }
    }

    void OnUpdate(TextEditor& editor, INPUT_RECORD input) const override
    {

    }
} Visual;

class _Insert : public EditorMode
{
private:
public:
    _Insert() : EditorMode({ Command(VK_I), Command(VK_A), Command(VK_O) })
    {

    }

    void OnSwitch(size_t commandIndex) const override
    {
        switch (commandIndex)
        {
        case 0: // I

            break;
        case 1: // A

            break;
        case 2: // O

            break;
        }
    }

    void OnUpdate(TextEditor& editor, INPUT_RECORD input) const override
    {

    }
} Insert;

class _Normal : public EditorMode
{
private:
public:
    _Normal() : EditorMode({ EditorMode::Command(VK_ESCAPE), }, { &Insert, &Visual, &Replace })
    {
        
    }

    void OnSwitch(size_t commandIndex) const override
    {
        // ESC
    }

    void OnUpdate(TextEditor& editor, INPUT_RECORD input) const override
    {

    }
} Normal;

INPUT_RECORD SimulateInput(WORD virtualKeyCode, DWORD controlKeyState = 0xFFFF)
{
    INPUT_RECORD input;
    input.EventType = KEY_EVENT;
    input.Event.KeyEvent.bKeyDown = true;
    input.Event.KeyEvent.wVirtualKeyCode = virtualKeyCode;
    input.Event.KeyEvent.dwControlKeyState = controlKeyState;

    return input;
}

int main()
{
    
}
