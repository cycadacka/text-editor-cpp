#pragma once
#include "Application.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

constexpr WORD VK_ALPHA0 = 0x30;
constexpr WORD VK_ALPHA1 = 0x31;
constexpr WORD VK_ALPHA2 = 0x32;
constexpr WORD VK_ALPHA3 = 0x33;
constexpr WORD VK_ALPHA4 = 0x34;
constexpr WORD VK_ALPHA5 = 0x35;
constexpr WORD VK_ALPHA6 = 0x36;
constexpr WORD VK_ALPHA7 = 0x37;
constexpr WORD VK_ALPHA8 = 0x38;
constexpr WORD VK_ALPHA9 = 0x39;

constexpr WORD VK_A = 0x41;
constexpr WORD VK_B = 0x42;
constexpr WORD VK_C = 0x43;
constexpr WORD VK_D = 0x44;
constexpr WORD VK_E = 0x45;
constexpr WORD VK_F = 0x46;
constexpr WORD VK_G = 0x47;
constexpr WORD VK_H = 0x48;
constexpr WORD VK_I = 0x49;
constexpr WORD VK_J = 0x4A;
constexpr WORD VK_K = 0x4B;
constexpr WORD VK_L = 0x4C;
constexpr WORD VK_M = 0x4D;
constexpr WORD VK_N = 0x4E;
constexpr WORD VK_O = 0x4F;
constexpr WORD VK_P = 0x50;
constexpr WORD VK_Q = 0x51;
constexpr WORD VK_R = 0x52;
constexpr WORD VK_S = 0x53;
constexpr WORD VK_T = 0x54;
constexpr WORD VK_U = 0x55;
constexpr WORD VK_V = 0x56;
constexpr WORD VK_W = 0x57;
constexpr WORD VK_X = 0x58;
constexpr WORD VK_Y = 0x59;
constexpr WORD VK_Z = 0x5A;

constexpr DWORD ANY_ALT = LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED;
constexpr DWORD ANY_CTRL = LEFT_CTRL_PRESSED | RIGHT_CTRL_PRESSED;

class TextEditor
{
    std::unique_ptr<Application> m_application;
    std::vector<std::string> m_text;
    COORD m_windowBufferSize;

    void OnKey(keys_t, keys_t);
    void OnMouse(MOUSE_EVENT_RECORD);
    void OnWindowBufferSize(WINDOW_BUFFER_SIZE_RECORD);

public:
    TextEditor(Application* application);

    void LoadFile(const char* filename);
    void SaveFile(const char* filename) const;
};

