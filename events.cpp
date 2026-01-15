#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>
#include <conio.h>
#include "events.h"
#include "system_utils.h"
#include "ui_elements.h"

void show_event() {
    clear_screen();

    std::cout << Color::green
        << "\n\t---/===/    ПРАЗДНИЧНЫЙ ЭВЕНТ    \\===\\---\n"
        << Color::yellow
        << "\n\tНажмите Enter, чтобы начать анимацию...\n"
        << Color::reset;
    wait_continue();

    const int tree_height = 10;
    // Для каждой строки — вектор позиций шариков
    std::vector<std::vector<int>> ball_positions(tree_height);
    std::vector<std::string> ball_colors = { Color::red, Color::green, Color::blue, Color::yellow };

    // Инициализация: сколько шариков на строке
    for (int row = 1; row < tree_height; ++row) {
        int stars = 2 * row + 1;
        int count = (row < 5) ? 2 : 3; // короткие — 2, длинные — 3
        for (int i = 0; i < count; ++i) {
            // Равномерно распределяем стартовые позиции
            int pos = (stars * i) / count;
            ball_positions[row].push_back(pos);
        }
    }

    int frame = 0;
    bool running = true;

    while (running) {
        clear_screen();

        // Верхушка
        std::cout << Color::yellow << "\n\t        \\ /\n";
        std::cout << "\t       --@--\n";

        // Ёлка
        for (int row = 0; row < tree_height; ++row) {
            int stars = 2 * row + 1;
            int padding = tree_height - row - 1;
            std::cout << "\t" << std::string(padding, ' ');

            // Двигаем шарики (кроме первой строки)
            if (row > 0) {
                for (size_t i = 0; i < ball_positions[row].size(); ++i) {
                    ball_positions[row][i]++;
                    if (ball_positions[row][i] >= stars) {
                        ball_positions[row][i] = 0;
                    }
                }
            }

            // Вывод строки
            for (int col = 0; col < stars; ++col) {
                bool is_ball = false;
                std::string ball_color = Color::reset;

                if (row > 0) {
                    for (size_t i = 0; i < ball_positions[row].size(); ++i) {
                        if (col == ball_positions[row][i]) {
                            is_ball = true;
                            int color_idx = (row + static_cast<int>(i) + frame) % static_cast<int>(ball_colors.size());
                            ball_color = ball_colors[color_idx];
                            break;
                        }
                    }
                }

                if (is_ball) {
                    std::cout << ball_color << "o" << Color::reset;
                }
                else {
                    std::cout << Color::green << "*" << Color::reset;
                }
            }
            std::cout << "\n";
        }

        // Ствол
        for (int i = 0; i < 3; ++i) {
            std::cout << "\t" << std::string(tree_height - 2, ' ') << Color::brown << "|||" << Color::reset << "\n";
        }

        std::cout << Color::yellow
            << "\n\tНажмите Enter, чтобы остановить.\n"
            << Color::reset;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        frame++;

        if (_kbhit()) {
            char key = _getch();
            if (key == '\r' || key == 27) {
                running = false;
            }
        }
    }

    std::cout << Color::green << "\n\tЭвент завершён. Спасибо за просмотр!\n" << Color::reset;
    wait_continue();
}