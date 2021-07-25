#include "src/TextEditor.h"
#include "src/Application.h"

extern void ErrorExit(const char*);

int main()
{
    HANDLE consoleInput = GetStdHandle(STD_INPUT_HANDLE);
    if (consoleInput == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleOutput == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    static Application* application = new Application(consoleInput, consoleOutput);
    static TextEditor* textEditor = new TextEditor(application);

    application->Start();

    delete application, textEditor;
}
