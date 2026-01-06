#pragma once

#include <vector>

// Хранилище состояния игры
// Содержит ВСЁ об игре: настройки, прогресс, достижения, статистику
struct GameState {
    // === Основные параметры ===
    int launch_count = 1;      // кол-во запусков
    int exit_delay_sec = 3;    // задержка перед выходом
    int level_count = 10;      // кол-во уровней
    int hint_frequency = 4;    // подсказка раз в N уровней
    int health = 5;            // жизни (для режима "ЖИЗНИ")
    int intro_type = 3;        // тип стартовой заставки
    bool auto_clear = true;    // Очищать ли экран?

    // === Статистика игрока ===
    int win_count = 0;         // победы
    int draw_count = 0;        // ничьи
    int loss_count = 0;        // поражения

    // === Достижения (15 штук) ===
    std::vector<bool> achievements;
    
    GameState() {
        achievements.resize(15, false);
    }
};