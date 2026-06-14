#include "GameMode.h"
#include <iostream>
#include <random>
#include <thread>
#include <chrono>


// Вспомогательный метод, общий для всех режимов
void GameMode::updateStats(GameSession& session, int correct, int incorrect) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << Color::white << "\n\t" << Color::total_white << "---===/ ИТОГИ ИГРЫ \\===---" << Color::white << "\n";
    std::cout << "\n\t    " << Color::green << "ВЕРНЫХ ОТВЕТОВ: " << correct;
    std::cout << "\n\t  " << Color::red << "НЕВЕРНЫХ ОТВЕТОВ: " << incorrect;
    std::cout << "\n\n\t  " << Color::reset << "ПОТОМУ --> ";

    int base_points = 0;
    int multiplier = session.getScoreMultiplier();

    const auto& achievements = session.getAchievements();
    int unlocked_count = 0;
    int total_count = static_cast<int>(achievements.size());
    for (size_t i = 0; i < achievements.size(); ++i) {
        if (achievements.get(i)) ++unlocked_count;
    }
    double achievement_bonus = 1.0 + (static_cast<double>(unlocked_count) / total_count) * 0.1;

    if (correct == incorrect) {
        std::cout << Color::total_yellow << "НИЧЬЯ" << Color::yellow << " :|" << Color::reset << "\n";
        session.incrementDraws();
        base_points = correct * 1;
    }
    else if (correct > incorrect) {
        std::cout << Color::total_green << "ПОБЕДА!" << Color::green << " :)" << Color::reset << "\n";
        session.incrementWins();
        base_points = correct * 2 - incorrect * 1;
    }
    else {
        std::cout << Color::total_red << "ПОРАЖЕНИЕ" << Color::red << " :(" << Color::reset << "\n";
        session.incrementLosses();
        base_points = 0 - incorrect * 1;
    }

    int points;
    if (base_points >= 0) {
        points = static_cast<int>(base_points * multiplier * achievement_bonus);
    }
    else {
        points = static_cast<int>(base_points * multiplier);
    }
    session.addScore(points);

    std::cout << Color::yellow << "\n\tБазовые очки: " << Color::reset;
    if (base_points > 0) {
        std::cout << Color::total_green << "+" << base_points << Color::reset << "\n";
    }
    else if (base_points < 0) {
        std::cout << Color::total_red << base_points << Color::reset << "\n";
    }
    else {
        std::cout << Color::total_gray << "0" << Color::reset << "\n";
    }

    if (multiplier > 1) {
        std::cout << Color::green << "\tМножитель: x" << multiplier << Color::reset << "\n";
    }
    if (achievement_bonus > 1.0 && correct > incorrect) {
        std::cout << Color::blue << "\tБонус за достижения: x" << std::fixed << std::setprecision(2)
            << achievement_bonus << Color::reset << "\n";
    }

    std::cout << Color::yellow << "\tИзменение очков: ";
    if (points > 0) {
        std::cout << Color::total_green << "+" << points << Color::reset << "\n";
    }
    else if (points < 0) {
        std::cout << Color::total_red << points << Color::reset << "\n";
    }
    else {
        std::cout << Color::total_gray << "0" << Color::reset << "\n";
    }

    std::cout << Color::yellow << "\n\tОбщий баланс: " << Color::total_yellow << session.getScore() << Color::reset << "\n";

    if (correct > incorrect) {
        UI::showLogo("extra1");
    }
    else if (correct < incorrect) {
        UI::showLogo("extra2");
    }

    SaveManager::autosave(session);
    ConsoleUI::waitUser();
}

// === КЛАССИЧЕСКАЯ ИГРА ===
void ClassicMode::play(GameSession& session) {
    const int MAX_LEVELS = 35;
    int levels = std::min(session.getLevelCount(), MAX_LEVELS);

    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::white
        << "\n---/===/    КЛАССИЧЕСКАЯ ИГРА    \\===\\---\n";
    std::cout << "\tКоличество уровней: " << levels << " (макс. " << MAX_LEVELS << ")\n";
    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    int correct = 0, incorrect = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int level = 1; level <= levels; ++level) {
        std::cout << (level % 2 == 0 ? Color::yellow : Color::cyan)
            << "\n\n\t-=/    УРОВЕНЬ " << level << "    \\=-\t\n" << Color::reset;
        std::cout << Color::yellow << "\tВаше число (0 или 1) >> " << Color::cyan;
        bool player_choice;
        try {
            player_choice = InputValidator::getBinaryChoice();
        }
        catch (const GameExitRequested&) {
            std::cout << Color::total_yellow << "\n\t|Игра прервана пользователем|\n" << Color::reset;
            ConsoleUI::waitUser();
            return;
        }
        int random_val = dis(gen);
        std::cout << "\tРандом = \t\t" << random_val << "\n";

        if ((player_choice && random_val == 1) || (!player_choice && random_val == 0)) {
            std::cout << Color::green << "\tВЕРНО\t\t\t" << Color::total_green << "√" << Color::reset;
            ++correct;
        }
        else {
            std::cout << Color::red << "\tНЕВЕРНО\t\t\t" << Color::total_red << "X" << Color::reset;
            ++incorrect;
        }
        std::cout << (level % 2 == 0 ? Color::yellow : Color::cyan)
            << "\n\t-=\\    УРОВЕНЬ " << level << "    /=-\t\n" << Color::reset;
        //ConsoleUI::waitUser();
    }

    updateStats(session, correct, incorrect);
}


// === ВСЁ ИЛИ НИЧЕГО ===
void AllOrNothingMode::play(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::white
        << "\n---/===/  РЕЖИМ ИГРЫ: \"" << Color::cyan << "ВСЁ ИЛИ НИЧЕГО" << Color::reset << "\"  \\===\\---\n";

    int levels = session.getLevelCount();
    if (levels == 10) {
        std::cout << "\t(установлено по умолчанию): " << levels << "\n";
    }
    else {
        std::cout << "\tв соответствии с пользовательской настройкой: " << levels << "\n";
    }
    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    std::cout << "\n Ваше число >> " << Color::cyan;
    bool player_choice;
    try {
        player_choice = InputValidator::getBinaryChoice();
    }
    catch (const GameExitRequested&) {
        std::cout << Color::total_yellow << "\n\t|Игра прервана пользователем|\n" << Color::reset;
        ConsoleUI::waitUser();
        return;
    }
    int player_num = player_choice ? 1 : 0;

    int correct = 0, incorrect = 0;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "\n╔════════╤══════╤═══════╤═══════╤══════╤═══════╗\n"
        << "║        " << Color::underlined << "│№ Ур. │ Ваш.Ч.│ Сл.Ч. │ √/X  │" << Color::reset << "       ║\n";

    for (int level = 1; level <= levels; ++level) {
        std::uniform_int_distribution<> dis(0, 1);
        int random_val = dis(gen);

        std::cout << "║\t | " << level << "\t| " << player_num << "\t| " << random_val << "\t| ";
        if (player_num == random_val) {
            std::cout << " " << Color::total_green << "√" << Color::reset << "   |       ║\n";
            ++correct;
        }
        else {
            std::cout << " " << Color::total_red << "X" << Color::reset << "   |       ║\n";
            ++incorrect;
        }

        int delay = (levels <= 100) ? 50 : (levels < 1000 ? 25 : 12);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }

    std::cout << "╚════════╧══════╧═══════╧═══════╧══════╧═══════╝\n";

    updateStats(session, correct, incorrect);
}


// === РЕЖИМ ИГРЫ: ЖИЗНИ ===
void LivesMode::play(GameSession& session) {
    const int MAX_LEVELS = 35;
    int levels = std::min(session.getLevelCount(), MAX_LEVELS);

    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::white
        << "\n---/===/  РЕЖИМ ИГРЫ: \"" << Color::red << "ЖИЗНИ" << Color::reset << "\"  \\===\\---\n";
    std::cout << "\tНачальное здоровье: " << session.getHealth() << "\n";
    std::cout << "\tКоличество уровней: " << levels;
    if (levels < session.getLevelCount()) {
        std::cout << " (макс. " << MAX_LEVELS << ")\n";
    }
    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    int max_health = session.getHealth();
    int current_health = session.getHealth();
    int correct = 0, incorrect = 0;
    int level = 0;
    std::random_device rd;
    std::mt19937 gen(rd());

    while (current_health > 0 && level < levels) {
        ++level;
        std::cout << (level % 2 == 0 ? Color::yellow : Color::cyan)
            << "\n\n\t-=/    УРОВЕНЬ " << level << "    \\=-\t\n" << Color::pink
            << "\tЗдоровье: " << Color::pink;

        for (int i = 0; i < current_health; ++i) {
            std::cout << "♥";
        }
        for (int i = current_health; i < max_health; ++i) {
            std::cout << Color::gray << "♥" << Color::pink;
        }

        std::cout << " (" << current_health << "/" << max_health << ")" << Color::reset << "\n";

        std::cout << Color::yellow << "\tВаше число (0 или 1) >> " << Color::cyan;
        bool player_choice;
        try {
            player_choice = InputValidator::getBinaryChoice();
        }
        catch (const GameExitRequested&) {
            std::cout << Color::total_yellow << "\n\t|Игра прервана пользователем|\n" << Color::reset;
            ConsoleUI::waitUser();
            return;
        }
        int player_num = player_choice ? 1 : 0;

        std::uniform_int_distribution<> dis(0, 1);
        int random_val = dis(gen);
        std::cout << "\tСлучайное число = " << random_val << "\n";

        if (player_num == random_val) {
            std::cout << Color::green << "\t" << Color::total_green << "√" << Color::green << " ВЕРНО! Здоровье сохранено.\n" << Color::reset;
            ++correct;
        }
        else {
            std::cout << Color::red << "\t" << Color::total_red << "X" << Color::red << " НЕВЕРНО! Здоровье -1.\n" << Color::reset;
            --current_health;
            ++incorrect;
        }
        std::cout << (level % 2 == 0 ? Color::yellow : Color::cyan)
            << "\n\t-=\\    УРОВЕНЬ " << level << "    /=-\t\n" << Color::reset;
        //ConsoleUI::waitUser();
    }

    std::cout << Color::pink << "\n\tИТОГО Здоровья: " << Color::pink;

    for (int i = 0; i < current_health; ++i) {
        std::cout << "♥";
    }
    for (int i = current_health; i < max_health; ++i) {
        std::cout << Color::gray << "♥" << Color::pink;
    }
    if (current_health == 0) {
        std::cout << Color::gray << " (" << current_health << "/" << max_health << ")" << Color::reset;
    }
    else {
        std::cout << " (" << current_health << "/" << max_health << ")" << Color::reset;
    }
    std::cout << Color::white << "\n   " << Color::total_pink << "---/===/    ИГРА ОКОНЧЕНА    \\===\\---"<< Color::white << "\n";

    if (current_health == 0 && level >= levels) {
        std::cout << Color::pink << "\tЗдоровье " << Color::red << "исчерпано"
            << Color::yellow << ", да и уровни " << Color::red << "тоже" << Color::yellow << "!\n" << Color::reset;
    }
    else if (current_health == 0) {
        std::cout << Color::pink << "\tЗдоровье" << Color::red << " исчерпано!\n" << Color::reset;
    }
    else {
        std::cout << Color::yellow << "\tДостигнут лимит уровней!\n" << Color::reset;
    }
    updateStats(session, correct, incorrect);
}


// === РЕЖИМ ИГРЫ: С ПОДСКАЗКАМИ ===
void HintsMode::play(GameSession& session) {
    const int MAX_LEVELS = 35;
    int levels = std::min(session.getLevelCount(), MAX_LEVELS);
    int freq = session.getHintFrequency();

    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::white
        << "\n---/===/\tРЕЖИМ ИГРЫ \"" << Color::yellow << "С ПОДСКАЗКАМИ" << Color::reset << "\"\t\\===\\---\n";

    std::cout << "\tПодсказка раз в " << freq << " ур.\n";
    std::cout << "\tКоличество уровней: " << levels;
    if (levels < session.getLevelCount()) {
        std::cout << " (макс. " << MAX_LEVELS << ")";
    }
    std::cout << "\n";
    std::cout << Color::yellow << "\n\t\tПОЕХАЛИ!\n" << Color::reset;

    int correct = 0, incorrect = 0;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int level = 1; level <= levels; ++level) {
        std::uniform_int_distribution<> dis(0, 1);
        int random_val = dis(gen);

        std::cout << (level % 2 == 0 ? Color::yellow : Color::cyan)
            << "\n\n\t-=/    УРОВЕНЬ " << level << "    \\=-\t\n" << Color::reset;

        bool is_hint = (level % freq == 0);
        if (is_hint) {
            std::cout << "\t" << Color::total_yellow << "РАНДОМ =        " << random_val << Color::reset << "\n";
            std::cout << Color::yellow << "\tВаше число   >> " << Color::cyan;
        }
        else {
            std::cout << Color::yellow << "\tВаше число   >> " << Color::cyan;
        }

        bool player_choice;
        try {
            player_choice = InputValidator::getBinaryChoice();
        }
        catch (const GameExitRequested&) {
            std::cout << Color::total_yellow << "\n\t|Игра прервана пользователем|\n" << Color::reset;
            ConsoleUI::waitUser();
            return;
        }
        int player_num = player_choice ? 1 : 0;

        if (!is_hint) {
            std::cout << "\tРандом =        " << random_val << "\n";
        }

        if (player_num == random_val) {
            std::cout << Color::green << "\tВЕРНО " << Color::total_green << "√" << Color::reset;
            ++correct;
        }
        else {
            std::cout << Color::red << "\tНЕВЕРНО " << Color::total_red << "X" << Color::reset;
            ++incorrect;
        }
        std::cout << (level % 2 == 0 ? Color::yellow : Color::cyan)
            << "\n\t-=\\    УРОВЕНЬ " << level << "    /=-\t\n" << Color::reset;
        //ConsoleUI::waitUser();
    }


    updateStats(session, correct, incorrect);
}