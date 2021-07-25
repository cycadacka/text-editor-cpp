#pragma once
#include <functional>
#include <algorithm>
#include <Windows.h>
#include <vector>

typedef std::vector<KEY_EVENT_RECORD> keys_t;

class Application
{
public:
    typedef std::function<void(keys_t downedKeys, keys_t releasedKeys)> KeyEvent_t;
    typedef std::function<void(MOUSE_EVENT_RECORD)> MouseEvent_t;
    typedef std::function<void(WINDOW_BUFFER_SIZE_RECORD)> WindowBufferSizeEvent_t;

private:
    HANDLE m_consoleInput = nullptr;
    HANDLE m_consoleOutput = nullptr;

    mutable std::vector<KeyEvent_t> m_keySubscribers;
    mutable std::vector<MouseEvent_t> m_mouseSubscribers;
    mutable std::vector<WindowBufferSizeEvent_t> m_windowBufferSizeSubscribers;

    keys_t m_pressedKeys;
    bool m_requestStop = false;
    bool m_running = false;

    // TODO: Show (YES/NO) dialog.
    void Update();
    bool TryFindPressedKey(KEY_EVENT_RECORD key, size_t& index);

public:
    Application(HANDLE consoleInput, HANDLE consoleOutput);

    const keys_t& get_pressedKeys() const;

    const bool IsRunning() const;
    const COORD GetScreenBufferSize() const;

    void Start();
    void Stop();
    void Subscribe(KeyEvent_t) const;
    void Subscribe(MouseEvent_t) const;
    void Subscribe(WindowBufferSizeEvent_t) const;
};

