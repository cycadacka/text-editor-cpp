#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "EditingMode.h"

class TextEditor
{
private:
    std::unique_ptr<EditorMode> m_editorMode;
    std::vector<std::string> m_text;

    void Update();

public:
    TextEditor(EditorMode mode);
    void Start();
};

