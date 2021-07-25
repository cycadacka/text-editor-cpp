#include "TextEditor.h"

void TextEditor::OnKey(keys_t downedKeys, keys_t releasedKeys)
{
    keys_t pressedKeys = m_application->get_pressedKeys();
    size_t pressedKeysSize = pressedKeys.size();

    for (size_t i = 0; i < pressedKeysSize; i++)
    {
        KEY_EVENT_RECORD& pressedKey = pressedKeys[i];

        switch (pressedKey.wVirtualKeyCode)
        {
        case VK_N:
            if ((pressedKey.dwControlKeyState & ANY_CTRL) != 0 && pressedKeysSize <= 1)
            {
                // TODO: New file.
                return;
            }
            break;
        case VK_O:
            if ((pressedKey.dwControlKeyState & ANY_CTRL) != 0 && pressedKeysSize <= 1)
            {
                // TODO: Open file.
                return;
            }
            break;
        case VK_S:
            if (pressedKeysSize <= 1)
            {
                if ((pressedKey.dwControlKeyState & ANY_CTRL) != 0)
                {
                    // TODO: Save file.
                    return;
                }
                else if ((pressedKey.dwControlKeyState & (ANY_CTRL | ANY_ALT)) != 0)
                {
                    // TODO: Save as file.
                    return;
                }
            }
            break;
        }
    }
}

void TextEditor::OnMouse(MOUSE_EVENT_RECORD mouseEvent)
{
    if ((mouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) != 0)
        m_application->Stop();
}

void TextEditor::OnWindowBufferSize(WINDOW_BUFFER_SIZE_RECORD windowBufferSize)
{
    m_windowBufferSize = windowBufferSize.dwSize;
}

TextEditor::TextEditor(Application* application): m_application(application)
{
    using namespace std::placeholders;

    application->Subscribe(static_cast<Application::KeyEvent_t>(std::bind(&TextEditor::OnKey, this, _1, _2)));
    application->Subscribe(static_cast<Application::MouseEvent_t>(std::bind(&TextEditor::OnMouse, this, _1)));
    application->Subscribe(static_cast<Application::WindowBufferSizeEvent_t>(std::bind(&TextEditor::OnWindowBufferSize, this, _1)));

    m_windowBufferSize = application->GetScreenBufferSize();
}

void TextEditor::LoadFile(const char* filename)
{
    std::ifstream ifs (filename);
    std::string line;

    m_text.clear();
    while (getline(ifs, line))
        m_text.push_back(line);

    ifs.close();
}

void TextEditor::SaveFile(const char* filename) const
{
    std::ofstream ofs (filename, std::ofstream::trunc);

    for (size_t i = 0; i < m_text.size(); i++)
        ofs << m_text[i] << '\n';

    ofs.close();
}
