#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include "system_utils.h"
#include "ui_elements.h"


void run_classic_game(GameState& state) {
    clear_screen(state.auto_clear);
    std::cout << Color::white
        << "\n---/===/    КЛАССИЧЕСКАЯ ИГРА    \\===\\---\n";

    std::cout << "\tКоличество уровней: " << state.level_count << "\n";
    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    int correct_answers = 0;
    int incorrect_answers = 0;

    // Генератор случайных чисел (0 или 1)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int level = 1; level <= state.level_count; ++level) {
        std::cout << Color::white
            << "\n\t-=/ УРОВЕНЬ " << level << " \\=-\t\n";

        std::cout << Color::yellow << "\tВаше число (0 или 1) >> " << Color::reset;
        bool player_choice = get_valid_binary_choice();

        int random_value = dis(gen);
        std::cout << "\tРандом = \t" << random_value << "\n";

        if ((player_choice && random_value == 1) || (!player_choice && random_value == 0)) {
            std::cout << "\tВЕРНО!\t\t" << Color::green << "+" << Color::reset << "  \n";
            ++correct_answers;
        }
        else {
            std::cout << "\tНЕВЕРНО.\t" << Color::red << "-" << Color::reset << "  \n";
            ++incorrect_answers;
        }

        std::cout << "\t-=\\ УРОВЕНЬ " << level << " /=-\t\n";

        wait_continue();
    }

    show_game_results(state, correct_answers, incorrect_answers);
}


void run_all_or_nothing(GameState& state) {
    clear_screen(state.auto_clear);

    std::cout << Color::white
        << "\n---/===/  РЕЖИМ ИГРЫ: \""<<Color::cyan<<"ВСЁ ИЛИ НИЧЕГО" << Color::reset << "\"  \\===\\---\n"
        << "\n\tКоличество уровней\n";

    if (state.level_count == 10) {
        std::cout << "\t(установлено по умолчанию): " << state.level_count << "\n";
    }
    else {
        std::cout << "\tв соответствии с пользовательской настройкой: " << state.level_count << "\n";
    }

    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    // === ОДИН ВВОД ЧИСЛА НА ВСЕ УРОВНИ ===
    std::cout << "\n Ваше число >> ";
    bool player_choice = get_valid_binary_choice();
    int player_num = player_choice ? 1 : 0;

    int correct = 0;
    int incorrect = 0;

    // === Генератор случайных чисел ===
    std::random_device rd;
    std::mt19937 gen(rd());

    // === Верхняя рамка ===
    std::cout << "\n==================================================\n";
    std::cout << "||\t |№ Ур.\t| Ваш.Ч.| Сл.Ч.\t| +/-  |       ||\n";

    for (int level = 1; level <= state.level_count; ++level) {
        std::uniform_int_distribution<> dis(0, 1);
        int random_val = dis(gen);

        std::cout << "||\t | " << level << "\t| " << player_num << "\t| " << random_val << "\t| ";
        if (player_num == random_val) {
            std::cout << " " << Color::green << "+" << Color::reset << "   |       ||\n";
            ++correct;
        }
        else {
            std::cout << " " << Color::red << "-" << Color::reset << "   |       ||\n";
            ++incorrect;
        }

        if (state.level_count <= 100) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        else if (state.level_count <= 1000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(12));
        }
    }

    std::cout << "==================================================\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    // === Итоги ===
    show_game_results(state, correct, incorrect);
}


void run_lives_game(GameState& state) {
    clear_screen(state.auto_clear);

    std::cout << Color::white
        << "\n---/===/  РЕЖИМ ИГРЫ: \"" << Color::red << "ЖИЗНИ" << Color::reset << "\"  \\===\\---\n"
        << "\n\tНачальное здоровье: " << state.health << "\n"
        << "\tМакс. количество уровней: " << state.level_count << "\n";

    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    int current_health = state.health;
    int correct = 0;
    int incorrect = 0;
    int level = 0;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (current_health > 0 && level < state.level_count) {
        ++level;
        std::cout << Color::white
            << "\n\t-=/ УРОВЕНЬ " << level << " \\=-\t\n"
            << "\tЗдоровье: " << Color::red << current_health << Color::reset << "\n";

        std::cout << Color::yellow << "\tВаше число (0 или 1) >> " << Color::reset;
        bool player_choice = get_valid_binary_choice();
        int player_num = player_choice ? 1 : 0;

        std::uniform_int_distribution<> dis(0, 1);
        int random_val = dis(gen);

        std::cout << "\tСлучайное число = " << random_val << "\n";

        if (player_num == random_val) {
            std::cout << Color::green << "\tВЕРНО! Здоровье сохранено.\n" << Color::reset;
            ++correct;
        }
        else {
            std::cout << Color::red << "\tНЕВЕРНО! Здоровье -1.\n" << Color::reset;
            --current_health;
            ++incorrect;
        }

        std::cout << "\t-=\\ УРОВЕНЬ " << level << " /=-\t\n";

        wait_continue();
    }

    // === Итоги по "жизням"===
    std::cout << Color::white << "\n---/===/    ИТОГИ ИГРЫ    \\===\\---\n";
    if (current_health == 0) {
        std::cout << "\tИгра окончена: " << Color::red << "здоровье" << Color::reset << " исчерпано!\n";
    }
    else {
        std::cout << "\tДостигнут лимит уровней.\n";
    }

    show_game_results(state, correct, incorrect);
}


void run_hints_game(GameState& state) {
    clear_screen(state.auto_clear);

    constexpr int DEFAULT_LEVELS = 10;
    constexpr int DEFAULT_HINT_FREQ = 4;

    std::cout << Color::white
        << "\n---/===/\tРЕЖИМ ИГРЫ \"" << Color::yellow << "С ПОДСКАЗКАМИ" << Color::reset << "\"\t\\===\\---\n";


    std::cout << "\n\tПодсказки будут появляться раз в ";
    if (state.hint_frequency == DEFAULT_HINT_FREQ) {
        std::cout << "\n\t(установлено по умолчанию): " << state.hint_frequency << " ур.\n";
    }
    else {
        std::cout << "\n\t(в соответствии с пользовательской настройкой): " << state.hint_frequency << " ур.\n";
    }


    std::cout << "\n\tКоличество уровней\n";
    if (state.level_count == DEFAULT_LEVELS) {
        std::cout << "\t(установлено по умолчанию): " << state.level_count << "\n";
    }
    else {
        std::cout << "\t(в соответствии с пользовательской настройкой): " << state.level_count << "\n";
    }

    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    int correct = 0;
    int incorrect = 0;


    std::random_device rd;
    std::mt19937 gen(rd());

    for (int level = 1; level <= state.level_count; ++level) {
        std::uniform_int_distribution<> dis(0, 1);
        int random_val = dis(gen);

        clear_screen(state.auto_clear);

        std::cout << Color::white
            << "\n\t---/===/    УРОВЕНЬ " << level << "    \\===\\---\n";

        bool is_hint_level = (level % state.hint_frequency == 0);

        // Сама подсказка
        if (is_hint_level) {
            std::cout << "\t" << Color::yellow << "РАНДОМ = \t" << random_val << Color::reset << "\n";
            std::cout << Color::yellow << "\tВаше число !! >> " << Color::reset;
        }
        else {
            std::cout << Color::yellow << "\tВаше число >> " << Color::reset;
        }

        bool player_choice = get_valid_binary_choice();
        int player_num = player_choice ? 1 : 0;

        // Если НЕ подсказка
        if (!is_hint_level) {
            std::cout << "\tРандом = " << random_val << "\n";
        }

        if (player_num == random_val) {
            std::cout << Color::green << "\tВЕРНО! +\n" << Color::reset;
            ++correct;
        }
        else {
            std::cout << Color::red << "\tНЕВЕРНО. -\n" << Color::reset;
            ++incorrect;
        }

        wait_continue();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    show_game_results(state, correct, incorrect);
}


void show_game_results(GameState& state, int correct, int incorrect) {
    std::cout << Color::white << "\n\t---===/ ИТОГИ ИГРЫ \\===---\n";
    std::cout << "\n\t    " << Color::green << "ВЕРНЫХ ОТВЕТОВ: " << correct;
    std::cout << "\n\t  " << Color::red << "НЕВЕРНЫХ ОТВЕТОВ: " << incorrect;
    std::cout << "\n\n\t  " << Color::reset << "ПОТОМУ --> ";

    if (correct == incorrect) {
        std::cout << Color::yellow << "НИЧЬЯ\t:|\n" << Color::reset;
        state.draw_count += 1;
    }
    else if (correct > incorrect) {
        std::cout << Color::green << "ПОБЕДА!\t:)\n" << Color::reset;
        state.win_count += 1;
    }
    else {
        std::cout << Color::red << "ПОРАЖЕНИЕ\t:(\n" << Color::reset;
        state.loss_count += 1;
    }

    wait_continue();
}