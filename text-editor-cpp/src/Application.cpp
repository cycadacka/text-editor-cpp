#include "Application.h"

extern void ErrorExit(const char*);

void Application::Update()
{
    // Read events.
    DWORD numberOfEvents, numberOfEventsRead;
    INPUT_RECORD* inputBuffer = nullptr;

    if (!GetNumberOfConsoleInputEvents(m_consoleInput, &numberOfEvents))
        ErrorExit("GetNumberOfConsoleInputEvents");

    inputBuffer = new INPUT_RECORD[numberOfEvents];
    if (!ReadConsoleInput(m_consoleInput, inputBuffer, numberOfEvents, &numberOfEventsRead))
        ErrorExit("ReadConsoleInput");

    // Loop through read events.
    size_t pressedKeyIndex = 0;
    keys_t downedKeys = keys_t();
    keys_t releasedKeys = keys_t();
    for (DWORD i = 0; i < numberOfEventsRead; i++)
    {
        switch (inputBuffer[i].EventType)
        {
        case KEY_EVENT:
        {
            const KEY_EVENT_RECORD& keyEvent = inputBuffer[i].Event.KeyEvent;
            if (keyEvent.bKeyDown)
            {
                downedKeys.push_back(keyEvent);
                if (!TryFindPressedKey(keyEvent, pressedKeyIndex))
                    m_pressedKeys.push_back(keyEvent);
            }
            else
            {
                releasedKeys.push_back(keyEvent);
                if (TryFindPressedKey(keyEvent, pressedKeyIndex))
                    m_pressedKeys.erase(m_pressedKeys.begin() + pressedKeyIndex);        
            }
        }
            break;
        case MOUSE_EVENT:
            for (size_t i = 0; i < m_mouseSubscribers.size(); i++)
                m_mouseSubscribers[i](inputBuffer[i].Event.MouseEvent);
            break;
        case WINDOW_BUFFER_SIZE_EVENT:
            for (size_t i = 0; i < m_windowBufferSizeSubscribers.size(); i++)
                m_windowBufferSizeSubscribers[i](inputBuffer[i].Event.WindowBufferSizeEvent);
            break;
        case FOCUS_EVENT:
        case MENU_EVENT:
            break;
        default:
            ErrorExit("Unknown event type");
            break;
        }
    }

    if (downedKeys.size() > 0 || releasedKeys.size() > 0)
        for (size_t i = 0; i < m_keySubscribers.size(); i++)
            m_keySubscribers[i](downedKeys, releasedKeys);

    // Destruction of variables.
    delete[] inputBuffer;
}

bool Application::TryFindPressedKey(KEY_EVENT_RECORD key, size_t& index)
{
    for (size_t i = 0; i < m_pressedKeys.size(); i++)
    {
        if (m_pressedKeys[i].wVirtualKeyCode == key.wVirtualKeyCode)
        {
            index = i;
            return true;
        }
    }

    return false;
}

Application::Application(HANDLE consoleInput, HANDLE consoleOutput)
{
    m_consoleInput = consoleInput;
    m_consoleOutput = consoleOutput;
}

const keys_t& Application::get_pressedKeys() const
{
    return m_pressedKeys;
}

const bool Application::IsRunning() const
{
    return m_running && !m_requestStop;
}

const COORD Application::GetScreenBufferSize() const
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(m_consoleOutput, &csbi))
        ErrorExit("GetConsoleScreenBufferInfo");

    return csbi.dwSize;
}

void Application::Start()
{
    if (m_running) // Do not start when already running.
        return;
    else
        m_running = true;

    DWORD consoleMode;
    if (!GetConsoleMode(m_consoleInput, &consoleMode))
        ErrorExit("GetConsoleMode");

    consoleMode = (consoleMode & ENABLE_EXTENDED_FLAGS) | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(m_consoleInput, consoleMode))
        ErrorExit("SetConsoleMode");

    while (true) {
        if (m_requestStop) {
            m_running = false;
            m_requestStop = false; // Fullfilled request
            break;
        }

        Update();
    }
}

void Application::Stop()
{
    m_requestStop = true;
}

void Application::Subscribe(KeyEvent_t subscriber) const
{
    m_keySubscribers.push_back(subscriber);
}

void Application::Subscribe(MouseEvent_t subscriber) const
{
    m_mouseSubscribers.push_back(subscriber);
}

void Application::Subscribe(WindowBufferSizeEvent_t subscriber) const
{
    m_windowBufferSizeSubscribers.push_back(subscriber);
}
