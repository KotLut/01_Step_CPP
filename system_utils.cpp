#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "game_core.h"
#include "system_utils.h"
#include "ui_elements.h"
#include "logo.h"


void clear_screen(bool auto_clear) {
    if (!auto_clear) return;
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_continue() {
    std::cout << Color::yellow << "\n\tВведите Enter, чтобы продолжить... " << Color::reset;
    std::string dummy;
    std::getline(std::cin, dummy);
}

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

int get_valid_int(int min_value, int max_value) {
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

        // Проверка минимального значения
        if (value < min_value) {
            std::cout << Color::yellow
                << "\tЗначение меньше минимального (" << min_value << "). "
                << "Автоприсваивание: " << min_value << "\n" << Color::reset;
            return min_value;
        }

        // Проверка максимального значения
        if (value > max_value) {
            std::cout << Color::yellow
                << "\tЗначение превышает допустимый максимум (" << max_value << "). "
                << "Автоприсваивание: " << max_value << "\n" << Color::reset;
            return max_value;
        }

        // Спецслучай: 101–1000 требует подтверждени
        if (value > 100) {
            std::cout << Color::yellow
                << "\tВы ввели большое количество уровней (" << value << "). "
                << "Это может занять много времени.\n"
                << "\tВы точно хотите продолжить? (y/n) >> " << Color::reset;
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y" || confirm == "Y") {
                return value;
            }
            else {
                std::cout << Color::yellow << "\tПожалуйста, введите новое значение.\n" << Color::reset;
                continue;
            }
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
            std::cout << Color::red << "\tОжидается \"0\" или \"1\". Попробуйте снова\t >> " << Color::reset;
        }
    }
}


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

void create_default_save(const std::string& filename) {
    GameState default_state;
    save_game(default_state, filename);
    std::cout << Color::green << "\n\tСоздано новое сохранение.\n" << Color::reset;
}

bool load_game(GameState& state, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << Color::yellow << "\n\tФайл сохранения не найден. Создаём новый...\n" << Color::reset;
        create_default_save(filename);
        std::cout << Color::green << "\n\tФайл сохранения \"" << filename << "\" успешно создан!\n" << Color::reset;

        // Загружаем только что созданный файл в state
        file.open(filename);
        if (!file.is_open()) {
            // Крайний случай: не удалось создать файл — сбрасываем в памяти
            state = GameState();
            return false;
        }
    }

    std::string line;
    std::vector<int> values;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            size_t pos;
            int val = std::stoi(line, &pos);
            if (pos == line.size()) {
                values.push_back(val);
            }
        }
        catch (...) {
            // Игнорируем некорректные строки
        }
    }
    file.close();

    if (values.size() < 25) {
        std::cout << Color::red << "\n\tОшибка: сохранение повреждено. " << Color::green << "Создаём новое.\n" << Color::reset;
        create_default_save(filename);

        // Загружаем новое сохранение
        std::ifstream new_file(filename);
        if (!new_file.is_open()) {
            state = GameState(); // обнуляем прогресс
            return false;
        }
        values.clear();
        while (std::getline(new_file, line)) {
            if (line.empty()) continue;
            try {
                size_t pos;
                int val = std::stoi(line, &pos);
                if (pos == line.size()) {
                    values.push_back(val);
                }
            }
            catch (...) {}
        }
        new_file.close();
        if (values.size() < 25) {
            state = GameState(); // последняя надежда
            return false;
        }
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

    state.achievements.assign(15, false);
    for (int i = 0; i < 15 && (10 + i) < static_cast<int>(values.size()); ++i) {
        if (values[10 + i] == 1) {
            state.achievements[i] = true;
        }
    }

    return true;
}

void autosave(const GameState state) {
    save_game(state, "save_data.txt");
}

void perform_exit(const GameState& state) {
    clear_screen(state.auto_clear);

    std::cout << Color::red
        << "\n\t|    ИНИЦИАЛИЗИРОВАН\t|"
        << "\n\t|  ВЫХОД ИЗ ПРОГРАММЫ!\t|"
        << "\n\tПРОГРАММА ЗАКРОЕТСЯ ЧЕРЕЗ:"
        << Color::reset;

    int delay = state.exit_delay_sec;
    for (int sec = delay; sec >= 1; --sec) {
        std::string word;
        if (sec == 1) {
            word = "секунду";
        }
        else if (sec >= 2 && sec <= 4) {
            word = "секунды";
        }
        else {
            word = "секунд";
        }
        std::cout << "\n\t     " << sec << "\t" << word;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\n\n\n\t";
    clear_screen(state.auto_clear);
    show_logo("thanks");
    std::cout << "\n\n\n\t";
}

void show_saves_menu(GameState& state) {
    // Достижение: заход в меню сохранений
    if (state.achievements.size() > 6) {
        state.achievements[6] = true;
    }

    bool in_saves = true;
    while (in_saves) {
        clear_screen(state.auto_clear);
        std::cout << Color::white
            << "\n\t---/===/    СОХРАНЕНИЯ    \\===\\---\n"
            << "\tВозможные действия:\n"
            << "\t+->\"1\" - Сохранить текущий прогресс\n"
            << "\t+->\"2\" - Загрузить прогресс из файла\n"
            << "\t+->\"3\" - Сбросить к значениям по умолчанию\n"
            << "\t-->\"0\" - Назад\n"
            << Color::yellow
            << "\n\tВыбор действия >> " << Color::reset;

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            if (save_game(state)) {
                std::cout << Color::green << "\n\tПрогресс успешно сохранён!\n" << Color::reset;
            }
            else {
                std::cout << Color::red << "\n\tОшибка при сохранении!\n" << Color::reset;
            }
            wait_continue();
        }
        else if (choice == "2") {
            if (load_game(state)) {
                std::cout << Color::green << "\n\tПрогресс успешно загружен!\n" << Color::reset;
            }
            else {
                std::cout << Color::yellow << "\n\tСоздано новое сохранение.\n" << Color::reset;
            }
            wait_continue();
        }
        else if (choice == "3") {
            std::cout << Color::yellow
                << "\n\tВнимание: все текущие настройки и статистика\n"
                << "\tбудут заменены значениями по умолчанию!\n"
                << "\tПродолжить? (y/n) >> " << Color::reset;
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y" || confirm == "Y") {
                create_default_save();
                // Перезагружаем состояние из нового файла
                load_game(state);
                std::cout << Color::green << "\n\tСохранение сброшено к значениям по умолчанию.\n" << Color::reset;
            }
            else {
                std::cout << Color::yellow << "\n\tОтмена операции.\n" << Color::reset;
            }
            wait_continue();
        }
        else if (choice == "0") {
            in_saves = false;
        }
        else {
            std::cout << Color::red << "\n\tНеизвестная команда. Попробуйте снова.\n" << Color::reset;
            wait_continue();
        }
    }
}