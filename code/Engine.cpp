#define NOMINMAX
#include "Engine.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <limits>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif


// ВСЁ состояние игры
GameSession::GameSession() : achievements_(15) {};

int GameSession::getLaunchCount() const { return launch_count_; }
int GameSession::getExitDelaySec() const { return exit_delay_sec_; }
int GameSession::getLevelCount() const { return level_count_; }
int GameSession::getHintFrequency() const { return hint_frequency_; }
int GameSession::getHealth() const { return health_; }
int GameSession::getIntroType() const { return intro_type_; }
bool GameSession::getAutoClear() const { return auto_clear_; }
int GameSession::getWinCount() const { return win_count_; }
int GameSession::getDrawCount() const { return draw_count_; }
int GameSession::getLossCount() const { return loss_count_; }
const CustomBoolArray& GameSession::getAchievements() const { return achievements_; }

void GameSession::incrementLaunchCount() { ++launch_count_; }
void GameSession::setLaunchCount(int count) {launch_count_ = count;}
void GameSession::setExitDelaySec(int sec) { exit_delay_sec_ = sec; }
void GameSession::setLevelCount(int count) { level_count_ = count; }
void GameSession::setHintFrequency(int freq) { hint_frequency_ = freq; }
void GameSession::setHealth(int h) { health_ = h; }
void GameSession::setIntroType(int type) { intro_type_ = type; }
void GameSession::setAutoClear(bool clear) { auto_clear_ = clear; }
void GameSession::setWinCount(int w) { win_count_ = w; }
void GameSession::setDrawCount(int d) { draw_count_ = d; }
void GameSession::setLossCount(int l) { loss_count_ = l; }
void GameSession::incrementWins() { ++win_count_; }
void GameSession::incrementDraws() { ++draw_count_; }
void GameSession::incrementLosses() { ++loss_count_; }

bool GameSession::hasAchievement(size_t id) const {
    return achievements_.get(id);
}

void GameSession::unlockAchievement(size_t id) {
    achievements_.set(id, true);
}

void GameSession::resetAllAchievements() {
    achievements_.resetAll();
}

void GameSession::setAchievements(const CustomBoolArray& ach) {
    if (ach.size() == achievements_.size()) {
        for (size_t i = 0; i < achievements_.size(); ++i) {
            achievements_.set(i, ach.get(i));
        }
    }
}

void GameSession::reset() {
    launch_count_ = 0;
    exit_delay_sec_ = 3;
    level_count_ = 10;
    hint_frequency_ = 4;
    health_ = 5;
    intro_type_ = 3;
    auto_clear_ = true;
    win_count_ = 0;
    draw_count_ = 0;
    loss_count_ = 0;
    achievements_.resetAll();
}

int GameSession::getScore() const {
    return score_;
}

void GameSession::setScore(int score) {
    score_ = score;
}

void GameSession::addScore(int points) {
    score_ += points;
    if (score_ < 0) score_ = 0;
}

int GameSession::getScoreMultiplier() const {
    return score_multiplier_;
}

void GameSession::setScoreMultiplier(int multiplier) {
    score_multiplier_ = multiplier;
}


// === Безопасный ввод ===
std::string InputValidator::trim(const std::string& str) {
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

int InputValidator::getInt(int min_value, int max_value) {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        line = trim(line);
        if (line.empty()) {
            std::cout << Color::red << "\tПустой ввод! " << Color::yellow << "Попробуйте снова >> " << Color::cyan;
            continue;
        }

        bool is_number = true;
        for (size_t i = 0; i < line.size(); ++i) {
            if (i == 0 && line[i] == '-') {
                if (line.size() == 1) { is_number = false; break; }
                continue;
            }
            if (!std::isdigit(static_cast<unsigned char>(line[i]))) {
                is_number = false; break;
            }
        }

        if (!is_number) {
            std::cout << Color::red << "\tНекорректный ввод! " << Color::yellow << "Ожидается число >> " << Color::cyan;
            continue;
        }

        // Защита от переполнения
        int value;
        try {
            std::size_t pos;
            long long temp = std::stoll(line, &pos);


            if (pos != line.size()) {
                throw std::invalid_argument("partial number");
            }

            // Проверяем, влезает ли в int
            if (temp < static_cast<long long>(std::numeric_limits<int>::min()) || temp > static_cast<long long>(std::numeric_limits<int>::max())) {
                throw std::out_of_range("number out of int range");
            }

            value = static_cast<int>(temp);
        }
        catch (const std::exception&) {
            std::cout << Color::red << "\tЧисло слишком большое или повреждено! " << Color::yellow << "Попробуйте снова >> " << Color::cyan;
            continue;
        }

        // Логика ограничений
        if (value < min_value) {
            std::cout << Color::yellow
                << "\tЗначение меньше минимального (" << min_value << "). "
                << "Автоприсваивание: " << Color::total_yellow << min_value << Color::reset << "\n";
            return min_value;
        }
        if (value > max_value) {
            std::cout << Color::yellow
                << "\tЗначение превышает допустимый максимум (" << max_value << "). "
                << "Автоприсваивание: " << Color::total_yellow << max_value << Color::reset << "\n";
            return max_value;
        }
        if (value > 25 && value < 1000) {
            std::cout << Color::yellow
                << "\tВы ввели очень большое число (" << Color::total_yellow << value << Color::reset << Color::yellow << "). "
                << "Это может занять много времени.\n"
                << "\tВы точно хотите продолжить? (" << Color::green << "y" << Color::yellow << "/" << Color::red << "n" << Color::yellow << ") >> " << Color::cyan;
            std::string confirm;
            std::getline(std::cin, confirm);
            if (confirm == "y" || confirm == "Y" || confirm == "д" || confirm == "Д") {
                return value;
            }
            else {
                std::cout << Color::yellow << "\tПожалуйста, введите новое значение >> " << Color::cyan;
                continue;
            }
        }
        return value;
    }
}

bool InputValidator::getBinaryChoice() {
#ifdef _WIN32
    while (true) {
        char key = _getch();
        if (key == 27) { // Esc
            throw GameExitRequested{};
        }
        if (key == '0' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9') {
            std::cout << Color::cyan << "0\n" << Color::reset;
            return false;
        }
        else if (key == '1') {
            std::cout << Color::cyan << "1\n" << Color::reset;
            return true;
        }
        else {
            std::cout << Color::red << "\a?" << Color::reset;
        }
    }
#else
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        line = trim(line);
        if (line.empty()) continue;
        if (line == "0") return false;
        if (line == "1") return true;
        if (line == "q" || line == "Q") {
            throw GameExitRequested{};
        }
        std::cout << Color::red << "\tОжидается \"0\" или \"1\" (или \"q\" для выхода). ...\n";
    }
#endif
}

// === Работа с консолью ===
void ConsoleUI::clearScreen(bool autoClear) {
    if (!autoClear) return;
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void ConsoleUI::waitUser() {
#ifdef _WIN32
    std::cout << Color::yellow << "\n\tНажмите любую клавишу, чтобы продолжить... " << Color::reset;
    _getch();
#else
    std::cout << Color::yellow << "\n\tНажмите Enter, чтобы продолжить... " << Color::reset;
    std::string dummy;
    std::getline(std::cin, dummy);
#endif
}

// === Работа с файлами ===
bool SaveManager::save(const GameSession& session, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << Color::total_red << "Ошибка:" << Color::red << " не удалось создать файл сохранения!\n" << Color::reset;
        return false;
    }

    file << session.getLaunchCount() << "\n";
    file << session.getExitDelaySec() << "\n";
    file << session.getLevelCount() << "\n";
    file << session.getHintFrequency() << "\n";
    file << session.getHealth() << "\n";
    file << session.getIntroType() << "\n";
    file << (session.getAutoClear() ? 1 : 0) << "\n";
    file << session.getScoreMultiplier() << "\n";


    file << session.getWinCount() << "\n";
    file << session.getDrawCount() << "\n";
    file << session.getLossCount() << "\n";
    file << session.getScore() << "\n";

    const auto& ach = session.getAchievements();
    for (size_t i = 0; i < ach.size(); ++i) {
        file << (ach.get(i) ? 1 : 0) << "\n";
    }
    return true;
}

void SaveManager::createDefault(const std::string& filename) {
    GameSession default_state;
    save(default_state, filename);
    std::cout << Color::green << "\n\t"<< Color::total_green << "|Создано новое сохранение|" << Color::reset << "\n" << Color::reset;
}

bool SaveManager::load(GameSession& session, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << Color::yellow << "\n\tФайл сохранения не найден. " << Color::green << "Создаём новый...\n" << Color::reset;
        createDefault(filename);
        file.open(filename);
        if (!file.is_open()) {
            session.reset();
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
            if (pos == line.size()) values.push_back(val);
        }
        catch (const std::exception&) {}
    }
    file.close();

    if (values.size() < 27) {
        std::cout << Color::total_red << "\n\tОшибка:" << Color::red << " сохранение повреждено! " << Color::green << "Создаём новое.\n" << Color::reset;
        createDefault(filename);
        // Перезагрузка...
        std::ifstream new_file(filename);
        values.clear();
        if (new_file.is_open()) {
            while (std::getline(new_file, line)) {
                if (line.empty()) continue;
                try {
                    size_t pos;
                    int val = std::stoi(line, &pos);
                    if (pos == line.size()) values.push_back(val);
                }
                catch (const std::exception&) {}
            }
            new_file.close();
        }
        if (values.size() < 25) {
            session.reset();
            return false;
        }
    }

    session.reset();
    session.setLaunchCount(values[0]);
    session.setExitDelaySec(values[1]);
    session.setLevelCount(values[2]);
    session.setHintFrequency(values[3]);
    session.setHealth(values[4]);
    session.setIntroType(values[5]);
    session.setAutoClear(values[6] == 1);
    session.setScoreMultiplier(values[7]);

    // Статистика
    session.setWinCount(values[8]);
    session.setDrawCount(values[9]);
    session.setLossCount(values[10]);

    session.setScore(values[11]);

    // Достижения
    session.resetAllAchievements();
    for (int i = 0; i < 15 && (12 + i) < static_cast<int>(values.size()); ++i) {
        if (values[12 + i] == 1) {
            session.unlockAchievement(i);
        }
    }
}

void SaveManager::autosave(const GameSession& session) {
    save(session);
}


// === Реализация методов CustomBoolArray ===
CustomBoolArray::CustomBoolArray(size_t size) : size_(size) {
    data_ = new bool[size_]();
}

CustomBoolArray::~CustomBoolArray() {
    delete[] data_;
}

bool CustomBoolArray::get(size_t index) const {
    if (index < size_) {
        return data_[index];
    }
    return false;
}

void CustomBoolArray::set(size_t index, bool value) {
    if (index < size_) {
        data_[index] = value;
    }
}

size_t CustomBoolArray::size() const {
    return size_;
}

void CustomBoolArray::resetAll() {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = false;
    }
}
