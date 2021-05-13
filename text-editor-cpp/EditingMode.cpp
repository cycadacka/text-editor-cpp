#include "EditingMode.h"

const std::vector<EditorMode::Command>& EditorMode::get_commands() const
{
    return m_commands;
}

EditorMode::EditorMode(const EditorMode& other)
{
    // m_parent
    delete m_parent;
    m_parent = &(*other.m_parent);

    // m_children
    while (other.m_children.size() < m_children.size())
    {
        delete m_children[m_children.size() - 1];
        m_children.pop_back();
    }

    for (size_t i = 0; i < other.m_children.size(); i++)
    {
        if (i >= m_children.size())
        {
            m_children.push_back(&(*other.m_children[i]));
        }
        else
        {
            delete m_children[i];
            m_children[i] = &(*other.m_children[i]);
        }
    }

    // m_commands
    m_commands = other.m_commands;
}

EditorMode::EditorMode(std::vector<Command> commands, std::vector<EditorMode*> children) : m_commands(commands)
{
    m_parent = nullptr;

    for (size_t i = 0; i < children.size(); i++)
    {
        delete children[i]->m_parent;
        children[i]->m_parent = &(*this);
        m_children.push_back(&(*children[i]));
    }
}

EditorMode* EditorMode::Switch(INPUT_RECORD input)
{
    if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown)
    {
        if (m_parent)
        {
            for (size_t i = 0; i < m_parent->m_commands.size(); i++)
            {
                if ((m_parent->m_commands[i].controlKeyState & input.Event.KeyEvent.dwControlKeyState) != 0 && m_parent->m_commands[i].virtualKeyCode == input.Event.KeyEvent.wVirtualKeyCode)
                {
                    m_parent->OnSwitch(i);
                    return m_parent;
                }
            }
        }
        else
        {
            for (size_t j = 0; j < m_children.size(); j++)
            {
                for (size_t k = 0; k < m_children[j]->m_commands.size(); k++)
                {
                    if ((m_children[j]->m_commands[k].controlKeyState & input.Event.KeyEvent.dwControlKeyState) != 0 && m_children[j]->m_commands[k].virtualKeyCode == input.Event.KeyEvent.wVirtualKeyCode)
                    {
                        m_children[j]->OnSwitch(k);
                        return m_children[j];
                    }
                }
            }
        }
    }

    return this;
}

EditorMode::Command::Command(uint16_t vkc, uint32_t cks) : virtualKeyCode(vkc), controlKeyState(cks)
{

}
