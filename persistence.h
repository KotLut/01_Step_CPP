#pragma once

#include <string>
#include "game_state.h"

// Сохраняет
bool save_game(const GameState& state, const std::string& filename = "save_data.txt");

// Загружает
bool load_game(GameState& state, const std::string& filename = "save_data.txt");

// Создаёт файл сохранения с базовыми значениями
void create_default_save(const std::string& filename = "save_data.txt");