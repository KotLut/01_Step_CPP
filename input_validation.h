#pragma once

#include <string>

// Проверяет ввод от пользователя
int get_valid_int(int min_value = 1);

bool get_valid_binary_choice();

// Удаляет пробелы в начале и конце строки
std::string trim(const std::string& str);