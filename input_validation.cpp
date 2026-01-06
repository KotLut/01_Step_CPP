#include "input_validation.h"
#include <iostream>
#include <string>
#include <cctype>
#include "color.h"

std::string trim(const std::string& str) {
    if (str.empty()) return str;
    size_t start = 0;
    size_t end = str.size() - 1;
    while (start <= end && std::isspace(static_cast<unsigned char>(str[start]))) {
        ++start;
    }
    while (end > start && std::isspace(static_cast<unsigned char>(str[end]))) {
        --end;
    }
    return str.substr(start, end - start + 1);
}

int get_valid_int(int min_value) {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        line = trim(line);
        if (line.empty()) {
            std::cout << Color::red << "\tПустой ввод. Попробуйте снова.\n" << Color::reset;
            continue;
        }

        bool is_number = true;
        for (size_t i = 0; i < line.size(); ++i) {
            if (i == 0 && line[i] == '-') {
                // Разрешаем минус только в начале
                if (line.size() == 1) {
                    is_number = false;
                    break;
                }
                continue;
            }
            if (!std::isdigit(static_cast<unsigned char>(line[i]))) {
                is_number = false;
                break;
            }
        }

        if (!is_number) {
            std::cout << Color::red << "\tНекорректный ввод. Ожидается число.\n" << Color::reset;
            continue;
        }

        int value = std::stoi(line);
        if (value < min_value) {
            std::cout << Color::yellow
                << "\tЗначение меньше минимального (" << min_value << "). "
                << "Автоприсваивание: " << min_value << "\n" << Color::reset;
            return min_value;
        }
        return value;
    }
}

bool get_valid_binary_choice() {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        line = trim(line);
        if (line == "0") {
            return false;
        }
        else if (line == "1") {
            return true;
        }
        else {
            std::cout << Color::red << "\tОжидается \"0\" или \"1\". Попробуйте снова.\n" << Color::reset;
        }
    }
}