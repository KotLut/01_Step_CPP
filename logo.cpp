#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "system_utils.h"
#include "logo.h"
#include "ui_elements.h"


void show_logo(const std::string& name) {
    const char* art = nullptr;

    if (name == "base") {
        art = GameLogos::base;
        std::cout << Color::cyan << art << Color::reset;
    }
    else if (name == "alpha") {
        art = GameLogos::alpha;
        std::cout << Color::green << art << Color::reset;
    }
    else if (name == "big") {
        art = GameLogos::big;
        std::cout << Color::yellow << art << Color::reset;
    }
    else if (name == "author1") {
        art = GameLogos::author1;
        std::cout << Color::green << art << Color::reset;
    }
    else if (name == "author2") {
        art = GameLogos::author2;
        std::cout << Color::yellow << art << Color::reset;
    }
    else if (name == "extra1") {
        art = GameLogos::extra1;
        std::cout << Color::green << art << Color::reset;
    }
    else if (name == "extra2") {
        art = GameLogos::extra2;
        std::cout << Color::green << art << Color::reset;
    }
    else if (name == "thanks") {
        art = GameLogos::thanks;
        std::cout << Color::green << art << Color::reset;
    }
    else {
        std::cout << Color::red << "\t[Неизвестный логотип: " << name << "]\n" << Color::reset;
        return;
    }
}

void show_logo_author(GameState& state) {
    clear_screen(state.auto_clear);

    std::cout << Color::white
        << "\n\n\tПожалуйста, открой окно Игры на весь экран,"
        << "\n\tтак ты увидишь то, что нужно ;)"
        << Color::yellow
        << "\n\n\tВведи что-нибудь, как будешь готов >> " << Color::reset;

    std::string dummy;
    std::getline(std::cin, dummy);

    clear_screen(state.auto_clear);
    show_logo("author1");

    // Достижение: увидел логотип
    if (state.achievements.size() > 1) {
        state.achievements[1] = true;
    }

    std::cout << Color::white
        << "\n\tЕсли хочешь увидеть ещё графику по\n"
        << "\t0/1 Step, то введи \"10\" ниже :)\n"
        << "\t(Потребуется подключение к Сети)\n";

    // Проверка: уже открывал ссылку?
    bool link_already_opened = (state.achievements.size() > 9 && state.achievements[9]);
    if (link_already_opened) {
        // Достижение "повторный просмотр"
        if (state.achievements.size() > 10) {
            state.achievements[10] = true;
        }
        std::cout << "\t\t(Логотип уже был открыт ранее)\n";
        show_logo("author2");
    }
    else {
        std::cout << "\t\t(Потом можешь вызвать логотип автора ещё раз ;)\n";
    }

    std::cout << Color::yellow << "\n\t>> " << Color::reset;
    std::string input;
    std::getline(std::cin, input);

    if (input == "10") {
#ifdef _WIN32
        system("start https://raw.githubusercontent.com/KotLut/01_Step_CPP/refs/heads/main/01_Step_alpha-logo.png");
#endif

        // Обновляем достижения
        if (state.achievements.size() > 9) {
            state.achievements[9] = true;
        }
        if (state.achievements.size() > 10) {
            state.achievements[10] = true;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}