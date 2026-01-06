#include "persistence.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "color.h"

bool save_game(const GameState& state, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << Color::red << "Ошибка: не удалось создать файл сохранения!\n" << Color::reset;
        return false;
    }

    // Порядок должен быть точным
    file << state.launch_count << "\n";
    file << state.exit_delay_sec << "\n";
    file << state.level_count << "\n";
    file << state.hint_frequency << "\n";
    file << state.health << "\n";
    file << state.intro_type << "\n";
    file << (state.auto_clear ? 1 : 0) << "\n"; // bool

    file << state.win_count << "\n";
    file << state.draw_count << "\n";
    file << state.loss_count << "\n";

    // Достижения (15 штук)
    for (size_t i = 0; i < state.achievements.size(); ++i) {
        file << (state.achievements[i] ? 1 : 0) << "\n";
    }

    file.close();
    return true;
}

bool load_game(GameState& state, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << Color::yellow << "Файл сохранения не найден. Создаём новый...\n" << Color::reset;
        create_default_save(filename);
        std::cout << Color::yellow << "Файл сохранения с именем \"" << filename << "\" Успешно создан!\n" << Color::reset;
        return false;
    }

    std::string line;
    std::vector<int> values;

    while (std::getline(file, line)) {
        // Пропускаем пустые строки
        if (line.empty()) continue;
        try {
            size_t pos;
            int val = std::stoi(line, &pos);
            // Убедимся, что преобразовали всю строку
            if (pos == line.size()) {
                values.push_back(val);
            }
        }
        catch (...) {
            // Игнорируем некорректные строки
        }
    }
    file.close();

    // Должно быть ровно 25 значений
    if (values.size() < 25) {
        std::cout << Color::red << "Ошибка: сохранение повреждено. Создаём новое.\n" << Color::reset;
        create_default_save(filename);
        return false;
    }

    // Заполняем GameState
    state.launch_count = values[0];
    state.exit_delay_sec = values[1];
    state.level_count = values[2];
    state.hint_frequency = values[3];
    state.health = values[4];
    state.intro_type = values[5];
    state.auto_clear = (values[6] == 1);

    state.win_count = values[7];
    state.draw_count = values[8];
    state.loss_count = values[9];

    state.achievements.resize(15, false);
    for (int i = 0; i < 15; ++i) {
        if (values[10 + i] == 1) {
            state.achievements[i] = true;
        }
    }

    return true;
}

void create_default_save(const std::string& filename) {
    GameState default_state;
    save_game(default_state, filename);
    std::cout << Color::green << "Создано новое сохранение.\n" << Color::reset;
}