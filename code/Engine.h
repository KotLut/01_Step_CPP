#pragma once

#include <cstddef>
#include <string>
#include <iostream>


// === Цвета игры ===
namespace Color {
    inline const char* reset = "\033[0;38;5;255;40m";
    inline const char* underlined = "\033[4;38;5;255;40m";
    inline const char* red = "\033[0;31;40m";
    inline const char* green = "\033[0;32;40m";
    inline const char* yellow = "\033[0;33;40m";
    inline const char* blue = "\033[0;34;40m";
    inline const char* purple = "\033[0;35;40m";
    inline const char* cyan = "\033[0;36;40m";
    inline const char* white = "\033[0;37;40m";
    inline const char* brown = "\033[0;38;5;94m";
    inline const char* gray = "\033[0;38;5;244m";
    inline const char* pink = "\033[0;38;5;162;40m";
    
    inline const char* anti_reset = "\033[0;30;47m";
    inline const char* total_red = "\033[0;30;41m";
    inline const char* total_green = "\033[0;30;42m";
    inline const char* total_yellow = "\033[0;30;43m";
    inline const char* total_blue = "\033[0;30;44m";
    inline const char* total_purple = "\033[0;30;45m";
    inline const char* total_cyan = "\033[0;30;46m";
    inline const char* total_white = "\033[0;30;47m";
    inline const char* total_brown = "\033[0;30;48;5;94m";
    inline const char* total_gray = "\033[0;30;48;5;244m";
    inline const char* total_pink = "\033[0;30;48;5;162m";
}

// === Массив для достижений ===
class CustomBoolArray {
private:
    bool* data_;
    size_t size_;

public:
    explicit CustomBoolArray(size_t size);
    ~CustomBoolArray();
    CustomBoolArray(const CustomBoolArray&) = delete;
    CustomBoolArray& operator=(const CustomBoolArray&) = delete;
    bool get(size_t index) const;
    void set(size_t index, bool value);

    size_t size() const;
    void resetAll();
};

// ВСЁ состояние игры
class GameSession {
public:
    GameSession();

    int getLaunchCount() const;
    int getExitDelaySec() const;
    int getLevelCount() const;
    int getHintFrequency() const;
    int getHealth() const;
    int getIntroType() const;
    bool getAutoClear() const;
    int getWinCount() const;
    int getDrawCount() const;
    int getLossCount() const;
    int getScore() const;
    int getScoreMultiplier() const;
    const CustomBoolArray& getAchievements() const;

    void incrementLaunchCount();
    void setLaunchCount(int count);
    void setExitDelaySec(int sec);
    void setLevelCount(int count);
    void setHintFrequency(int freq);
    void setHealth(int h);
    void setIntroType(int type);
    void setAutoClear(bool clear);
    void setWinCount(int w);
    void setDrawCount(int d);
    void setLossCount(int l);
    void setScore(int score);
    void setScoreMultiplier(int multiplier);
    void setAchievements(const CustomBoolArray& ach);
    void incrementWins();
    void incrementDraws();
    void incrementLosses();
    bool hasAchievement(size_t id) const;
    void unlockAchievement(size_t id);
    void resetAllAchievements();

    void addScore(int points);
    void reset();

private:
    int launch_count_ = 0;
    int exit_delay_sec_ = 3;
    int level_count_ = 10;
    int hint_frequency_ = 4;
    int health_ = 5;
    int intro_type_ = 3;
    bool auto_clear_ = true;

    int win_count_ = 0;
    int draw_count_ = 0;
    int loss_count_ = 0;

    int score_ = 0;
    int score_multiplier_ = 1;
    CustomBoolArray achievements_;

    GameSession(const GameSession&) = delete;
    GameSession& operator=(const GameSession&) = delete;
};


// === Безопасный ввод ===
class InputValidator {
public:
    static std::string trim(const std::string& str);
    static int getInt(int min_value, int max_value = 1000);
    static bool getBinaryChoice();
};

// === Работа с консолью ===
class ConsoleUI {
public:
    static void clearScreen(bool autoClear = true);
    static void waitUser();
};

// === Работа с файлами ===
class SaveManager {
public:
    static bool save(const GameSession& session, const std::string& filename = "01_Step_Save.txt");
    static bool load(GameSession& session, const std::string& filename = "01_Step_Save.txt");
    static void createDefault(const std::string& filename = "01_Step_Save.txt");
    static void autosave(const GameSession& session);
};

// Исключение для выхода из игрового режима
struct GameExitRequested {};

