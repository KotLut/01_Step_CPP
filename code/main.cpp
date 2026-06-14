#include <iostream>
#include "Engine.h"
#include "UI.h"

int main() {
    UI::setupConsole();
    GameSession session;
    SaveManager::load(session);

    MainMenu menu(session);
    menu.run();                 // Ctrl+ЛКМ по "run" для перехода к меню)

    return 0; 
}