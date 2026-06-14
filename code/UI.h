#pragma once

#include <string>
#include "Engine.h"
#include "logos.h"
#include "GameMode.h"


// === Индексы достижений ===
enum AchievementIndex {
    CUSTOMIZE_SETTINGS = 0,      // (1) Изменение настроек
    SAW_ALPHA_LOGO,              // (2) Альфа-логотип
    SAW_BIG_LOGO,                // (3) Большая заставка
    TOGGLED_AUTO_CLEAR,          // (4) Отключил очистку
    REVISITED_CLEAR_SETTING,     // (5) Вернул очистку
    VIEWED_CREDITS,              // (6) Прочитал "От автора"
    ENTERED_SAVES_MENU,          // (7) Заходил в сохранения
    FOUND_MICRO_EASTER_EGG,      // (8) Микро-пасхалка
    TRIGGERED_LOGO_TAB,           // (9) Tab автору
    OPENED_LOGO_LINK,            // (10) Открыл ссылку логотипа
    SAW_ALT_LOGO,                // (11) Альтернативный логотип
    FIXED_HELLO_WORLD,           // (12) Исправил hello_world (КОДЕР)
};


// === Класс пользовательского интерфейса ===
class UI {
public:
    static void setupConsole();
    // --- Основные экраны ---
    static void showSettingsMenu(GameSession& session);
    static void showHelp(GameSession& session);
    static void showStats(const GameSession& session);
    static void showAchievements(const GameSession& session);
    static void showCredits(GameSession& session);
    static void showLogo(const std::string& name);
    static void showLogoAuthor(GameSession& session);
    static void showSavesMenu(GameSession& session);
    static void performExit(const GameSession& session);

private:
    // --- Вспомогательные: для настроек ---
    static void editLevels(GameSession& session);
    static void editHintFrequency(GameSession& session);
    static void editHealth(GameSession& session);
    static void editExitDelay(GameSession& session);
    static void editIntroType(GameSession& session);
    static void editScoreMultiplier(GameSession& session);
    static void toggleAutoClear(GameSession& session);

    // --- Подразделы справки ---
    static void showHelpClassic();
    static void showHelpAllOrNothing();
    static void showHelpLives();
    static void showHelpHints();
    static void showHelpSettings();
    static void showHelpStats();
    static void showHelpAchievements();
    static void showHelpAuthor();
    static void showHelpExit();
    static void showHelpSaves();
    static void showHelpEvent();
};


// === Менеджер праздничных событий ===
class FestiveEventManager {
public:
    static void showChristmasTree();   // Новогодняя ёлка
    // static void showSummerEvent();  // Заготовки на будущее)
};


// === Главное меню игры ===
class MainMenu {
public:
    explicit MainMenu(GameSession& session) : session_(session) {}

    void run();

private:
    GameSession& session_;

    void showIntro();
    void showMenu();
    bool handleKeyPress(char key);
};