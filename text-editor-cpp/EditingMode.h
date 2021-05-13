#pragma once
#include <Windows.h>
#include <vector>
#include <memory>

#define VK_ALPHA0 0x30
#define VK_ALPHA1 0x31
#define VK_ALPHA2 0x32
#define VK_ALPHA3 0x33
#define VK_ALPHA4 0x34
#define VK_ALPHA5 0x35
#define VK_ALPHA6 0x36
#define VK_ALPHA7 0x37
#define VK_ALPHA8 0x38
#define VK_ALPHA9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

class TextEditor;

class EditorMode
{
public:
    struct Command
    {
        /*
          Virtual-key code that identifies the given key in a device-independent manner.
        */
        uint16_t virtualKeyCode;
        /* 
          State of the control keys. One or more of the following values:
          CAPSLOCK_ON         0x0080	The CAPS LOCK light is on.
          ENHANCED_KEY        0x0100	The key is enhanced.
          LEFT_ALT_PRESSED    0x0002	The left ALT key is pressed.
          LEFT_CTRL_PRESSED   0x0008	The left CTRL key is pressed.
          NUMLOCK_ON          0x0020	The NUM LOCK light is on.
          RIGHT_ALT_PRESSED   0x0001	The right ALT key is pressed.
          RIGHT_CTRL_PRESSED  0x0004	The right CTRL key is pressed.
          SCROLLLOCK_ON       0x0040	The SCROLL LOCK light is on.
          SHIFT_PRESSED       0x0010	The SHIFT key is pressed.
        */
        uint32_t controlKeyState;

        Command(uint16_t virtualKeyCode, uint32_t controlKeyState=0xFFFF);
    };

private:
    EditorMode* m_parent;
    std::vector<EditorMode*> m_children;
    std::vector<Command> m_commands;

protected:
    const std::vector<Command>& get_commands() const;

public:
    EditorMode(const EditorMode&);
    EditorMode(std::vector<Command> commands, std::vector<EditorMode*> children = {});

    virtual void OnSwitch(size_t commandIndex) const = 0;
    virtual void OnUpdate(TextEditor& editor, INPUT_RECORD input) const = 0;

    EditorMode* Switch(INPUT_RECORD input);
};
