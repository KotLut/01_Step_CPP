#include <iostream>
#include <string>
#include "clear.h"
#include "color.h"
#include "game_state.h"
#include "persistence.h"
#include "input_validation.h"
#include "settings.h"
#include "classic_game.h"


void wait_for_input() {
    std::cout << Color::yellow << "\tВведите что-нибудь, чтобы продолжить >> " << Color::reset;
    std::string dummy;
    std::getline(std::cin, dummy);
}

// Заглушки — будут заменены позже
void show_classic_game() { std::cout << "Classic game (stub)\n"; wait_for_input(); }
void show_all_or_nothing() { std::cout << "All or nothing (stub)\n"; wait_for_input(); }
void show_xp_game() { std::cout << "XP game (stub)\n"; wait_for_input(); }
void show_podskaz_game() { std::cout << "Podskaz game (stub)\n"; wait_for_input(); }
void show_help() { std::cout << "Help (stub)\n"; wait_for_input(); }
void show_settings() { std::cout << "Settings (stub)\n"; wait_for_input(); }
void show_stats() { std::cout << "Stats (stub)\n"; wait_for_input(); }
void show_achievements() { std::cout << "Achievements (stub)\n"; wait_for_input(); }
void show_about() { std::cout << "About (stub)\n"; wait_for_input(); }
void show_logo_author() { std::cout << "Logo author (stub)\n"; wait_for_input(); }
void show_saves_menu() { std::cout << "Saves menu (stub)\n"; wait_for_input(); }



void show_main_menu() {
    std::cout << Color::cyan << "\n\t\t=== 0/1 Step ===\n" << Color::reset;
    std::cout << Color::white
        << "\t---/===/  ГЛАВНОЕ МЕНЮ:  \\===\\---\t\n"
        << "\tВозможные действия:\n"
        << "\t+->\"1\" - Классическая игра\n"
        << "\t+->\"2\" - Режим \"Всё или ничего\"\n"
        << "\t+->\"3\" - Режим \"ЖИЗНИ\"\n"
        << "\t+->\"4\" - Режим игры \"С подсказками\"\n"
        << "\t+->\"5\" - Справка\n"
        << "\t+->\"6\" - Настройки\n"
        << "\t+->\"7\" - Статистика\n"
        << "\t+->\"8\" - Достижения\n"
        << "\t+=>\"9\" - \"От автора\"\n"
        << "\t-->\"0\" - Выход\n"
        << Color::yellow
        << "\n\t*Все остальные команды перезапускают Игру\n"
        << Color::reset;
}


int main() {
    system("chcp 65001");

    setlocale(LC_ALL, "Russian");
    GameState state;
    // Пытаемся загрузить сохранение
    if (!load_game(state, "save_data.txt")) {
        // Если не получилось — state уже в базовом состоянии
        // (конструктор GameState() задал значения по умолчанию)
    }

    bool game_running = true;
    clear_screen();
    std::cout << Color::cyan << "\n\t\t=== 0/1 Step ===\n" << Color::reset;
    std::cout << "\tИгра запущена впервые!\n\tНажмите \"5\" для Справки.\n";
    wait_for_input();

    while (game_running) {
        clear_screen();
        show_main_menu();

        std::cout << Color::yellow << "\n\t Выбор действия >> " << Color::reset;
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            clear_screen();
            run_classic_game(state);
        }
        else if (choice == "2") {
            clear_screen();
            show_all_or_nothing();
        }
        else if (choice == "3") {
            clear_screen();
            show_xp_game();
        }
        else if (choice == "4") {
            clear_screen();
            show_podskaz_game();
        }
        else if (choice == "5") {
            clear_screen();
            show_help();
        }
        else if (choice == "6") {
            clear_screen();
            show_settings_menu(state);
        }
        else if (choice == "7") {
            clear_screen();
            show_stats();
        }
        else if (choice == "8") {
            clear_screen();
            show_achievements();
        }
        else if (choice == "9") {
            clear_screen();
            show_about();
        }
        else if (choice == "10") {
            clear_screen();
            show_logo_author();
        }
        else if (choice == "11") {
            clear_screen();
            show_saves_menu();
        }
        else if (choice == "0") {
            clear_screen();
            std::cout << Color::red << "\n\tВыход из программы...\n" << Color::reset;
            game_running = false;
        }
        else {
            std::cout << Color::red << "\n\tНеизвестная команда. Возврат в меню...\n" << Color::reset;
            wait_for_input();
        }
    }

    // Сохраняем прогресс перед выходом
    save_game(state, "save_data.txt");
    return 0;
}