#pragma once

#include <string>
#include "game_core.h"

// ANSI-цвета для консольного интерфейса
namespace Color {
	inline const char* reset =  "\033[0m";
	inline const char* red =    "\033[31m";
	inline const char* green =  "\033[32m";
	inline const char* yellow = "\033[33m";
    inline const char* blue =   "\033[34m";
    inline const char* cyan =   "\033[36m";
	inline const char* white =  "\033[37m";
    inline const char* brown = "\033[38;5;94m";
}

// Индексы достижений (строки 8–22)
enum AchievementIndex {
    CUSTOMIZE_SETTINGS = 0,      // (1) Изменение настроек
    SAW_ALPHA_LOGO,              // (2) Альфа-логотип
    SAW_BIG_LOGO,                // (3) Большая заставка
    TOGGLED_AUTO_CLEAR,          // (4) Отключил очистку
    REVISITED_CLEAR_SETTING,     // (5) Вернул очистку
    VIEWED_CREDITS,              // (6) Прочитал "От автора"
    ENTERED_SAVES_MENU,          // (7) Заходил в сохранения
    FOUND_MICRO_EASTER_EGG,      // (8) Микро-пасхалка
    TRIGGERED_LOGO_10,           // (9) Ввёл "10" в меню
    OPENED_LOGO_LINK,            // (10) Открыл ссылку логотипа
    SAW_ALT_LOGO,                // (11) Альтернативный логотип
    FIXED_HELLO_WORLD,           // (12) Исправил hello_world (КОДЕР)
};

// Меню и экраны
void show_settings_menu(GameState& state);
void show_help(GameState& state);
void show_stats(const GameState& state);
void show_achievements_menu(const GameState& state);
void show_credits(GameState& state);
void show_logo_author(GameState& state);