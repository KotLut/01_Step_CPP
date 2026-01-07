#pragma once

#include <vector>
#include <string>

// Хранилище состояния игры
// Содержит ВСЁ об игре: настройки, статистику, достижения
struct GameState {
    // === Основные параметры ===
    int launch_count = 0;           // кол-во запусков
    int exit_delay_sec = 3;         // задержка перед выходом
    int level_count = 10;           // кол-во уровней
    int hint_frequency = 4;         // подсказка раз в N уровней
    int health = 5;                 // жизни (для режима "ЖИЗНИ")
    int intro_type = 3;             // тип стартовой заставки
    bool auto_clear = true;         // Очищать ли экран?

    // === Статистика игрока ===
    int win_count = 0;              // победы
    int draw_count = 0;             // ничьи
    int loss_count = 0;             // поражения

    // === Достижения (15 штук) ===
    std::vector<bool> achievements;

    GameState() {
        achievements.resize(15, false);
    }
};

void run_classic_game(GameState& state);
void run_all_or_nothing(GameState& state);
void run_hints_game(GameState& state);
void run_lives_game(GameState& state);
void show_game_results(GameState& state, int correct, int incorrect);