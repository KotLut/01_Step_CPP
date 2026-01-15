#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
#include "game_core.h"
#include "system_utils.h"
#include "ui_elements.h"
#include "logo.h"
#include "events.h"


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
    clear_screen(state.auto_clear);

    show_logo("alpha");

    std::cout << Color::cyan << "\n\t\t=== 0/1 Step ===\n" << Color::reset;
    std::cout << "\tИгра запущена впервые!\n\tМожете нажатием \"5\" вызвать Справку.\n";
    wait_continue();

    // Основной цикл игры
    while (game_running) {

        // Дебажить тут

        clear_screen(state.auto_clear);
        state.launch_count++;
        autosave(state);

        if (state.intro_type == 1) {
            show_logo("alpha");
            if (state.achievements.size() > 1) {
                state.achievements[1] = true;
            }
        }
        else if (state.intro_type == 2) {
            show_logo("big");
            if (state.achievements.size() > 2) {
                state.achievements[2] = true; 
            }
        }
        else {
            show_logo("base");
        }

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
            << "\t+->\"9\" - \"От автора\"\n"
            << "\t+->\"11\" - Сохранения\n"
            << "\t+->\"12\" - Праздничный эвент\n"
            << "\t-->\"0\" - Выход\n"
            << Color::yellow
            << "\n\t*Все остальные команды перезапускают Игру\n"
            << Color::reset;

        std::cout << Color::yellow << "\n\t Выбор действия >> " << Color::reset;
        std::string choice;
        std::getline(std::cin, choice);

        if (choice.empty()) {
            // Микро-пасхалка: просто нажал Enter
            if (state.achievements.size() > 7) {
                state.achievements[7] = true;
            }
            continue;
        }
        else if (choice == "1") {
            clear_screen(state.auto_clear);
            run_classic_game(state);
            autosave(state);
        }
        else if (choice == "2") {
            clear_screen(state.auto_clear);
            run_all_or_nothing(state);
            autosave(state);
        }
        else if (choice == "3") {
            clear_screen(state.auto_clear);
            run_lives_game(state);
            autosave(state);
        }
        else if (choice == "4") {
            clear_screen(state.auto_clear);
            run_hints_game(state);
            autosave(state);
        }
        else if (choice == "5") {
            clear_screen(state.auto_clear);
            show_help(state);
            autosave(state);
        }
        else if (choice == "6") {
            clear_screen(state.auto_clear);
            show_settings_menu(state);
            autosave(state);
        }
        else if (choice == "7") {
            clear_screen(state.auto_clear);
            show_stats(state);
            autosave(state);
        }
        else if (choice == "8") {
            clear_screen(state.auto_clear);
            show_achievements_menu(state);
            autosave(state);
        }
        else if (choice == "9") {
            clear_screen(state.auto_clear);
            show_credits(state);
            autosave(state);
        }
        else if (choice == "10") {
            clear_screen(state.auto_clear);
            show_logo_author(state);
            autosave(state);
        }
        else if (choice == "11") {
            clear_screen(state.auto_clear);
            show_saves_menu(state);
            autosave(state);
        }
		else if (choice == "12") {
			clear_screen();
			show_event();
		}
        else if (choice == "0") {
            clear_screen(state.auto_clear);
            autosave(state);
            perform_exit(state);
            game_running = false;
        }
        else {
            std::cout << Color::red << "\n\tНеизвестная команда. " << Color::yellow << "Возврат в меню...\n" << Color::reset;
            wait_continue();
        }
    }

    // Сохраняем прогресс перед выходом
    save_game(state, "save_data.txt");
    return 0;
}