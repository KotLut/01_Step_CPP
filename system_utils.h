#pragma once

#include <string>
#include "game_core.h"

// Экран
void clear_screen(bool auto_clear = true);
void wait_continue();

// Ввод
std::string trim(const std::string& str);
int get_valid_int(int min_value, int max_value = 1000);
bool get_valid_binary_choice();

// Файлы
bool save_game(const GameState& state, const std::string& filename = "save_data.txt");
void create_default_save(const std::string& filename = "save_data.txt");
bool load_game(GameState& state, const std::string& filename = "save_data.txt");
void autosave(const GameState state);

// Выход
void perform_exit(const GameState& state);

// Меню управления сохранениями
void show_saves_menu(GameState& state);