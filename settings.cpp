#include "settings.h"
#include <iostream>
#include "color.h"
#include "input_validation.h"

void edit_levels(GameState& state) {
    std::cout << Color::white
        << "\n\t| (01) Выбор количества уровней |\n";
    std::cout << "\tТекущее значение: " << state.level_count << "\n";
    std::cout << Color::yellow
        << "\tВведите новое количество уровней (минимум 1): " << Color::reset;
    state.level_count = get_valid_int(1);
    // Достижение: изменение настроек
    if (state.achievements.size() > 0) {
        state.achievements[0] = true; // customize_set
    }
    std::cout << Color::green << "\n\tПринято! Теперь уровней: " << state.level_count << "\n" << Color::reset;
}

void edit_hint_frequency(GameState& state) {
    std::cout << Color::white
        << "\n\t| (02) Выбор частоты подсказок |\n"
        << "\t// Подсказки появляются раз в N уровней.\n"
        << "\t// \"1\" — каждый уровень, чем больше — тем реже.\n";
    std::cout << "\tТекущее значение: " << state.hint_frequency << "\n";
    std::cout << Color::yellow
        << "\tВведите частоту подсказок (минимум 1): " << Color::reset;
    state.hint_frequency = get_valid_int(1);
    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь подсказка раз в " << state.hint_frequency << " уровней.\n" << Color::reset;
}

void edit_health(GameState& state) {
    std::cout << Color::white
        << "\n\t| (03) Выбор количества здоровья |\n"
        << "\t// Здоровье определяет длительность режима \"ЖИЗНИ\".\n";
    std::cout << "\tТекущее значение: " << state.health << "\n";
    std::cout << Color::yellow
        << "\tВведите количество здоровья (минимум 1): " << Color::reset;
    state.health = get_valid_int(1);
    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь здоровья: " << state.health << "\n" << Color::reset;
}

void edit_exit_delay(GameState& state) {
    std::cout << Color::white
        << "\n\t| (04) Изменение времени выхода |\n";
    std::cout << "\tТекущее значение: " << state.exit_delay_sec << " сек.\n";
    std::cout << Color::yellow
        << "\tВведите время выхода в секундах (минимум 1): " << Color::reset;
    state.exit_delay_sec = get_valid_int(1);
    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь выход через " << state.exit_delay_sec << " сек.\n" << Color::reset;
}

void edit_intro_type(GameState& state) {
    std::cout << Color::white
        << "\n\t| (05) Выбор варианта заставки |\n"
        << "\t+-> \"1\" - Альфа-версия заставки\n"
        << "\t+-> \"2\" - Большая заставка\n"
        << "\t--> \"3\" - Новая заставка (рекомендуется)\n";
    std::cout << Color::yellow << "\n\tВыберите вариант (1-3): " << Color::reset;

    while (true) {
        int choice = get_valid_int(1);
        if (choice >= 1 && choice <= 3) {
            state.intro_type = choice;
            if (state.achievements.size() > 0) {
                state.achievements[0] = true;
            }
            std::cout << Color::green << "\n\tПринято! Выбрана заставка №" << state.intro_type << ".\n" << Color::reset;
            break;
        }
        else {
            std::cout << Color::red << "\tДопустимы только значения от 1 до 3. Попробуйте снова.\n" << Color::reset;
        }
    }
}

void toggle_auto_clear(GameState& state) {
    state.auto_clear = !state.auto_clear;
    std::cout << Color::green
        << "\n\tАвтоочистка экрана " << (state.auto_clear ? "ВКЛЮЧЕНА" : "ВЫКЛЮЧЕНА") << ".\n"
        << Color::reset;

    // Достижения: ochistka и ochistka2
    if (!state.auto_clear && state.achievements.size() > 3) {
        state.achievements[3] = true;
    }
    if (state.auto_clear && state.achievements.size() > 4) {
        if (state.achievements[3]) {
            state.achievements[4] = true;
        }
    }
}

void show_settings_menu(GameState& state) {
    bool in_settings = true;
    while (in_settings) {
        std::cout << Color::white
                  << "\n\t---/===/    НАСТРОЙКИ    \\===\\---\n"
                  << "\tВозможные действия:\n"
                  << "\t╠>\"1\" - Количество уровней\n"
                  << "\t╠>\"2\" - Частота подсказок\n"
                  << "\t╠>\"3\" - Здоровье (режим \"ЖИЗНИ\")\n"
                  << "\t╠>\"4\" - Время выхода\n"
                  << "\t╠>\"5\" - Заставка\n"
                  << "\t╠>\"0\" - Вкл/Выкл автоочистку экрана\n"
                  << "\t╚>\"9\" - Назад\n"
                  << Color::yellow
                  << "\n\tВыбор действия >> " << Color::reset;

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            edit_levels(state);
        }
        else if (choice == "2") {
            edit_hint_frequency(state);
        }
        else if (choice == "3") {
            edit_health(state);
        }
        else if (choice == "4") {
            edit_exit_delay(state);
        }
        else if (choice == "5") {
            edit_intro_type(state);
        }
        else if (choice == "0") {
            toggle_auto_clear(state);
        }
        else if (choice == "9") {
            in_settings = false;
        }
        else {
            std::cout << Color::red << "\n\tНеизвестная команда. Возврат в меню настроек...\n" << Color::reset;
        }
    }
}