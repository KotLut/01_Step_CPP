#pragma once

#include <vector>
#include <cstdint>

// Хранилище состояния игры
// Содержит ВСЁ об игре: настройки, прогресс, достижения, статистику
struct GameState {
    // === Основные параметры ===
    int32_t launch_count = 1;      // кол-во запусков
    int32_t exit_delay_sec = 3;    // задержка перед выходом
    int32_t level_count = 10;      // кол-во уровней
    int32_t hint_frequency = 4;    // подсказка раз в N уровней
    int32_t health = 5;            // жизни (для режима "ЖИЗНИ")
    int32_t intro_type = 3;        // тип стартовой заставки
    bool auto_clear = true;        // Очищать ли экран?

    // === Статистика игрока ===
    int32_t win_count = 0;         // sum_win
    int32_t draw_count = 0;        // sum_nichego
    int32_t loss_count = 0;        // sum_lose

    // === Достижения (15 штук) ===
    // Используем вектор bool — проще, чем enum, на старте
    std::vector<bool> achievements = std::vector<bool>(15, false);
    // Достижения по порядку (соответствуют строкам 8–22 в save_data.txt):
    // [0] = customize_settings
    // [1] = saw_alpha_logo
    // [2] = saw_big_logo
    // [3] = toggled_auto_clear
    // [4] = revisited_clear_setting
    // [5] = viewed_credits
    // [6] = entered_saves_menu
    // [7] = found_micro_easter_egg
    // [8] = triggered_logo_10
    // [9] = opened_logo_link
    // [10] = saw_alt_logo
    // [11] = fixed_hello_world
    // ... остальные — пока не нужны

    // === Текущий режим (не обязательный сейчас, но для будущего) ===
    // int32_t current_mode = 0; // 0=classic, 1=all_or_nothing, и т.д.
};