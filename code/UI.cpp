#include "UI.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <conio.h>
#endif


namespace Urls{
    constexpr const char* LOGO_URL = "https://raw.githubusercontent.com/KotLut/01_Step_CPP/refs/heads/main/01_Step_alpha-logo.png";
}

void UI::setupConsole() {
    system("chcp 65001");
    //setlocale(LC_ALL, "Russian");
}

// --- Вспомогательные функции: настройки ---
void UI::editLevels(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_green << "\n\t| (01) Выбор количества уровней |\n" << Color::reset;
    std::cout << "\tТекущее значение: " << session.getLevelCount() << "\n";

    std::cout << Color::yellow << "\tВведите новое количество уровней (минимум 1): " << Color::cyan;
    session.setLevelCount(InputValidator::getInt(1,1000));
    session.unlockAchievement(AchievementIndex::CUSTOMIZE_SETTINGS);
    std::cout << Color::green << "\n\tПринято! Теперь уровней: " << Color::total_green << session.getLevelCount() << Color::reset << "\n" << Color::reset;
    ConsoleUI::waitUser();
}

void UI::editHintFrequency(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_yellow
        << "\n\t| (02) Выбор частоты подсказок |" << Color::reset << "\n"
        << "\t// Подсказки появляются раз в N уровней.\n"
        << "\t// \"1\" — каждый уровень, чем больше — тем реже.\n";
    std::cout << "\tТекущее значение: " << Color::total_yellow << session.getHintFrequency() << Color::reset << "\n";

    std::cout << Color::yellow << "\tВведите частоту подсказок (минимум 1): " << Color::cyan;
    session.setHintFrequency(InputValidator::getInt(1,20));
    session.unlockAchievement(AchievementIndex::CUSTOMIZE_SETTINGS);
    std::cout << Color::green << "\n\tПринято! Теперь подсказка раз в " << Color::total_yellow << session.getHintFrequency() << Color::green << " уровней.\n" << Color::reset;
    ConsoleUI::waitUser();
}

void UI::editHealth(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_pink
        << "\n\t| (03) Выбор количества здоровья |" << Color::reset << "\n" 
        << "\t// Здоровье определяет длительность режима \"ЖИЗНИ\".\n";
    std::cout << "\tТекущее значение: " << Color::total_pink << session.getHealth() << Color::reset << "\n";

    std::cout << Color::pink << "\tВведите количество здоровья (минимум 1): " << Color::cyan;
    session.setHealth(InputValidator::getInt(1,10));
    session.unlockAchievement(AchievementIndex::CUSTOMIZE_SETTINGS);
    std::cout << Color::green << "\n\tПринято! " << Color::pink << "Теперь здоровья: " << Color::total_pink << session.getHealth() << Color::reset << "\n";
    ConsoleUI::waitUser();
}

void UI::editExitDelay(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_white
        << "\n\t| (04) Изменение времени выхода |" << Color::reset << "\n";
    std::cout << "\tТекущее значение: " << Color::total_white << session.getExitDelaySec() << Color::reset << " сек.\n";

    std::cout << Color::yellow << "\tВведите время выхода в секундах (минимум 1): " << Color::cyan;
    session.setExitDelaySec(InputValidator::getInt(1,60));
    session.unlockAchievement(AchievementIndex::CUSTOMIZE_SETTINGS);
    std::cout << Color::green << "\n\tПринято! Теперь выход через " << Color::total_white << session.getExitDelaySec() << Color::green << " сек.\n" << Color::reset;
    ConsoleUI::waitUser();
}

void UI::editIntroType(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_cyan
        << "\n\t| (05) Выбор варианта заставки |\n" << Color::reset
        << "\t+-> \"1\" - " << Color::green << "Альфа-версия заставки\n" << Color::reset
        << "\t+-> \"2\" - " << Color::yellow << "Большая заставка\n" << Color::reset
        << "\t--> \"3\" - " << Color::cyan << "Новая заставка (рекомендуется)\n" << Color::reset;
    std::cout << Color::yellow << "\n\tВыберите вариант (1-3): " << Color::cyan;

    while (true) {
        int choice = InputValidator::getInt(1, 3);
        if (choice >= 1 && choice <= 3) {
            session.setIntroType(choice);
            session.unlockAchievement(AchievementIndex::CUSTOMIZE_SETTINGS);
            std::cout << Color::green << "\n\tПринято! " << Color::cyan
                << "Выбрана заставка номер " << Color::total_cyan << choice
                << Color::reset << ".\n";
            break;
        }
        else {
            std::cout << Color::red << "\tДопустимы только значения от 1 до 3. "
                << Color::yellow << "Попробуйте снова >> " << Color::cyan;
        }
    }
    ConsoleUI::waitUser();
}

void UI::editScoreMultiplier(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_yellow << "\n\t| (06) Множитель очков |\n" << Color::reset;
    std::cout << "\tТекущее значение: " << session.getScoreMultiplier() << "\n";

    std::cout << Color::yellow << "\tВведите множитель (1-10): " << Color::cyan;
    session.setScoreMultiplier(InputValidator::getInt(1, 10));
    session.unlockAchievement(AchievementIndex::CUSTOMIZE_SETTINGS);
    std::cout << Color::green << "\n\tПринято! Множитель: " << Color::total_green << session.getScoreMultiplier() << Color::reset << "\n" << Color::reset;
    ConsoleUI::waitUser();
}

void UI::toggleAutoClear(GameSession& session) {
    session.setAutoClear(!session.getAutoClear());
    std::cout << (session.getAutoClear() ? Color::total_green : Color::total_red)
        << "\n\t| Автоочистка экрана "
        << (session.getAutoClear() ? "ВКЛЮЧЕНА |" : "ВЫКЛЮЧЕНА |")
        << "\n" << Color::reset;

    if (!session.getAutoClear()) {
        session.unlockAchievement(AchievementIndex::TOGGLED_AUTO_CLEAR);
    }
    else {
        if (session.hasAchievement(AchievementIndex::TOGGLED_AUTO_CLEAR)) {
            session.unlockAchievement(AchievementIndex::REVISITED_CLEAR_SETTING);
        }
    }
    ConsoleUI::waitUser();
}


// --- Основное меню настроек ---
void UI::showSettingsMenu(GameSession& session) {
    bool in_settings = true;
    while (in_settings) {
        ConsoleUI::clearScreen(session.getAutoClear());
        std::cout << Color::total_gray
            << "\n\t---/===/    НАСТРОЙКИ    \\===\\---" << Color::reset
            << Color::gray << "\n\tВозможно поменять:"
            << Color::gray << "\n\t╟─> " << Color::reset << "1 → Количество уровней"
            << Color::gray << "\n\t╟─> " << Color::reset << "2 → " << Color::yellow << "Частоту подсказок" << Color::reset
            << Color::gray << "\n\t╟─> " << Color::reset << "3 → " << Color::pink << "Здоровье (в режиме \"ЖИЗНИ\")" << Color::reset
            << Color::gray << "\n\t╟─> " << Color::reset << "4 → Время выхода"
            << Color::gray << "\n\t╟─> " << Color::reset << "5 → " << Color::cyan << "Заставку" << Color::reset
            << Color::gray << "\n\t╟─> " << Color::reset << "6 → " << Color::yellow << "Множитель очков" << Color::reset
            << Color::gray << "\n\t╟─> " << Color::reset << "9 → " << Color::green << "Вкл" << Color::reset << "/" << Color::red << "Выкл" << Color::reset << " автоочистку экрана"
            << Color::gray << "\n\t╙─> " << Color::reset << "0 → Назад"
            << Color::yellow<< "\n\n\tВыбор действия >> " << Color::reset;

#ifdef _WIN32
        char key = _getch();

        // Вывод нажатой клавиши
        if (key == 27) {
            std::cout << Color::cyan << "Esc\n" << Color::reset;
        }
        else if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '9') {
            std::cout << Color::cyan << key << "\n" << Color::reset;
        }
        else {
            std::cout << Color::red << "\a?" << Color::reset;
            continue;
        }

        switch (key) {
        case '1': editLevels(session); break;
        case '2': editHintFrequency(session); break;
        case '3': editHealth(session); break;
        case '4': editExitDelay(session); break;
        case '5': editIntroType(session); break;
        case '6': editScoreMultiplier(session); break;
        case '9': toggleAutoClear(session); break;
        case '0':
        case 27: // Esc
            in_settings = false;
            break;
        default:
            break;
        }
#else
        // Fallback для Linux/macOS
        std::string choice;
        std::getline(std::cin, choice);
        if (choice == "1") editLevels(session);
        else if (choice == "2") editHintFrequency(session);
        else if (choice == "3") editHealth(session);
        else if (choice == "4") editExitDelay(session);
        else if (choice == "5") editIntroType(session);
        else if (choice == "6") editScoreMultiplier(session);
        else if (choice == "9") toggleAutoClear(session);
        else if (choice == "0") in_settings = false;
        // остальное игнорируется
#endif
    }
}


// --- Подразделы справки ---
void UI::showHelpClassic() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_white
        << "\n\t\t| (1) Подробности о Классической игре |" << Color::reset
        << "\n\n\tЭто основной режим " << Color::cyan << "Игры" << Color::reset << ". Его геймплей заключается в следующем:"
        << "\n\tна каждом уровне вы выбираете цифру \"" << Color::yellow << "0" << Color::reset << "\" или \"" << Color::yellow << "1" << Color::reset << "\", и если ваш ответ"
        << "\n\tсовпадает с цифрой, которая случайно выбрана компьютером, то"
        << "\n\tуровень считается верным, то есть выигранным."
        << "\n\tЕсли ответ не совпадает с случайным числом, то уровень считается"
        << "\n\tпроигранным."

        << "\n\n\t" << Color::gray << "• Ограничение: " << Color::reset << "в Классической игре действует лимит на " << Color::cyan << "35 уровней" << Color::reset << "."
        << "\n\tДаже если в " << Color::gray << "Настройках" << Color::reset << " указано больше, игра автоматически"
        << "\n\tобрежет значение — чтобы сессия не затягивалась."

        << "\n\n\t" << Color::gray << "• Визуал: " << Color::reset << "заголовки уровней чередуются по цвету:"
        << "\n\t" << Color::cyan << "нечётные уровни" << Color::reset << " — " << Color::cyan << "циановые" << Color::reset << "," << Color::yellow << "чётные уровни" << Color::reset << " — " << Color::yellow << "жёлтые" << Color::reset << "."
        << "\n\tЭто помогает глазу ориентироваться в длинных сессиях."

        << "\n\n\t" << Color::gray << "• Прерывание игры: " << Color::reset << "если вы хотите выйти из партии досрочно,"
        << "\n\tнажмите " << Color::yellow << "Esc" << Color::reset << " (Windows) или введите \"" << Color::yellow << "q" << Color::reset << "\" (Linux)."
        << "\n\t Прогресс текущей игры не сохранится в " << Color::cyan << "Статистику" << Color::reset

        << "\n\n\tВ конце каждой игры выводятся итоги, которые, исходя из количества"
        << "\n\tверных и неверных ответов, засчитывают игроку:"
        << "\n\t- \"" << Color::green << "ПОБЕДУ" << Color::reset << "\" - если количество верных уровней больше, чем неверных;"
        << "\n\t- \"" << Color::yellow << "НИЧЬЮ" << Color::reset << "\" - если количество верных равно количеству неверных;"
        << "\n\t- \"" << Color::red << "ПОРАЖЕНИЕ" << Color::reset << "\" - если неверных уровней больше, чем верных."

        << "\n\n\t" << Color::cyan << "═══ Система очков ═══" << Color::reset
        << "\n\tЗа каждый исход начисляются очки по формулам:"
        << "\n\t" << Color::green << "• ПОБЕДА:    " << Color::reset << "(верных × 2 − неверных × 1) × множитель × бонус"
        << "\n\t" << Color::yellow << "• НИЧЬЯ:     " << Color::reset << "верных × 1 × множитель × бонус"
        << "\n\t" << Color::red << "• ПОРАЖЕНИЕ: " << Color::reset << "0 − (неверных × 1) × множитель"

        << "\n\n\t" << Color::gray << "Важно: " << Color::reset << "при поражении очки уходят в " << Color::red << "минус" << Color::reset << " —"
        << "\n\tкаждая ошибка буквально \"съедает\" ваш счёт. Играйте осторожно!"

        << "\n\n\t" << Color::gray << "• Множитель очков " << Color::reset << "— настраиваемый параметр (от 1 до 10),"
        << "\n\tкоторый можно изменить в разделе \"" << Color::gray << "Настройки" << Color::reset << "\" (пункт \"" << Color::green << "6" << Color::reset << "\")."

        << "\n\n\t" << Color::gray << "• Бонус за достижения " << Color::reset << "— даёт до " << Color::yellow << "+10%" << Color::reset << " к очкам за победу,"
        << "\n\tесли открыты " << Color::blue << "все достижения" << Color::reset << ". Промежуточные значения дают"
        << "\n\tпропорциональный бонус (например, половина открытых — " << Color::yellow << "+5%" << Color::reset << ")."

        << "\n\n\tЭти данные сохраняются и учитываются в блоках \"" << Color::cyan << "Статистика" << Color::reset << "\" и \"" << Color::blue << "Достижения" << Color::reset << "\"."
        << "\n\tКоличество уровней можно изменить в " << Color::gray << "Настройках" << Color::cyan << " Игры" << Color::reset << "."
        << "\n\tПодробнее об этом вы можете прочитать в соседних разделах " << Color::total_white << "Справки" << Color::reset << ":"
        << "\n\t" << Color::total_gray << "\"Подробности о Настройках\"" << Color::reset << ", " << Color::total_cyan << "\"Подробности о Статистике\"" << Color::reset << " и " << Color::total_blue << "\"Подробности о Достижениях\"" << Color::reset << ".\n";
    ConsoleUI::waitUser();
}

void UI::showHelpAllOrNothing() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_cyan
        << "\n\t\t| (2) Подробности о режиме \"Всё или ничего\" |" << Color::reset
        << "\n\n\tЭто режим " << Color::cyan << "Игры" << Color::reset << ", в котором вам предстоит выбрать одну цифру"
        << "\n\t\"" << Color::yellow << "0" << Color::reset << "\" или \"" << Color::yellow << "1" << Color::reset << "\", и она будет автоматически введена во все уровни."
        << "\n\tЕсли ваш ответ совпадает со случайным числом компьютера — уровень выигран."
        << "\n\tИначе — проигран."

        << "\n\n\t" << Color::gray << "• Особенность: " << Color::reset << "в отличие от Классической игры, здесь " << Color::cyan << "лимит = 1000" << Color::reset << " на количество"
        << "\n\tуровней. Вы можете установить число до " << Color::yellow << "1000" << Color::reset << " включительно — режим справится."
        << "\n\tЭто идеальный полигон для проверки теории вероятностей и удачи."

        << "\n\n\t" << Color::gray << "• Табличный вывод: " << Color::reset << "все уровни отображаются в виде единой таблицы:"
        << "\n\t- \"" << Color::white << "№ Ур." << Color::reset << "\" — номер уровня;"
        << "\n\t- \"" << Color::white << "Ваш.Ч." << Color::reset << "\" — ваше выбранное число (одно на всю игру);"
        << "\n\t- \"" << Color::white << "Сл.Ч." << Color::reset << "\" — число компьютера на данном уровне;"
        << "\n\t- \"" << Color::white << "√/X" << Color::reset << "\" — \"" << Color::green << "√" << Color::reset << "\" при совпадении, \"" << Color::red << "X" << Color::reset << "\" — при несовпадении."

        << "\n\n\t" << Color::gray << "• Адаптивная скорость: " << Color::reset << "чтобы таблица не мелькала слишком быстро,"
        << "\n\tигра автоматически подстраивает задержку между строками:"
        << "\n\t- до 100 уровней → " << Color::yellow << "50 мс" << Color::reset << " между строками;"
        << "\n\t- от 101 до 1000 → " << Color::yellow << "25 мс" << Color::reset << ";"
        << "\n\t- 1000 → " << Color::yellow << "12 мс" << Color::reset << " (режим \"пулемётной очереди\")."

        << "\n\n\t" << Color::gray << "• Прерывание игры: " << Color::reset << "нажмите " << Color::yellow << "Esc" << Color::reset << " (Windows) или введите \"" << Color::yellow << "q" << Color::reset << "\""
        << "\n\t(Linux) в момент запроса вашего числа — игра завершится досрочно."
        << "\n\tПрогресс текущей партии не попадёт в статистику."
        << "\n\n\tИтоги такие же, как в Классической игре:"
        << "\n\t- \"" << Color::green << "ПОБЕДА" << Color::reset << "\" - если верных уровней больше, чем неверных;"
        << "\n\t- \"" << Color::yellow << "НИЧЬЯ" << Color::reset << "\" - если поровну;"
        << "\n\t- \"" << Color::red << "ПОРАЖЕНИЕ" << Color::reset << "\" - если неверных больше."

        << "\n\n\t" << Color::cyan << "═══ Система очков ═══" << Color::reset
        << "\n\tРаботает по тем же формулам, что и в Классической игре:"
        << "\n\t" << Color::green << "• ПОБЕДА:    " << Color::reset << "(верных × 2 − неверных × 1) × множитель × бонус"
        << "\n\t" << Color::yellow << "• НИЧЬЯ:     " << Color::reset << "верных × 1 × множитель × бонус"
        << "\n\t" << Color::red << "• ПОРАЖЕНИЕ: " << Color::reset << "0 − (неверных × 1) × множитель"

        << "\n\n\t" << Color::gray << "Важно: " << Color::reset << "при поражении очки уходят в " << Color::red << "минус" << Color::reset << " —"
        << "\n\tкаждая ошибка буквально \"съедает\" ваш счёт. Играйте осторожно!"

        << "\n\n\tДанные сохраняются в " << Color::cyan << "\"Статистику\"" << Color::reset << " и " << Color::blue << "\"Достижения\"" << Color::reset << "."
        << "\n\tКоличество уровней можно изменить через " << Color::gray << "Настройки" << Color::reset << "."
        << "\n\tПодробнее — в соседних разделах " << Color::total_white << "Справки" << Color::reset << ":\n";
    ConsoleUI::waitUser();
}

void UI::showHelpLives() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_pink
        << "\n\t\t| (3) Подробности о режиме Игры \"ЖИЗНИ\" |" << Color::reset
        << "\n\n\tЭто режим, сходный с \"" << Color::cyan << "Классическим" << Color::reset << "\", но с ограничением по " << Color::pink << "здоровью" << Color::reset << "."
        << "\n\tПри верном ответе " << Color::pink << "здоровье" << Color::reset << " не меняется, при неверном — уменьшается на " << Color::red << "1" << Color::reset << "."
        << "\n\tИгра заканчивается, когда " << Color::pink << "здоровье" << Color::red << " = 0 " << Color::reset << "или " << Color::yellow << "достигнут лимит уровней." << Color::reset

        << "\n\n\t" << Color::gray << "• Ограничение по уровням: " << Color::reset << "в этом режиме действует лимит на " << Color::cyan << "35 уровней" << Color::reset << "."
        << "\n\tДаже если в " << Color::gray << "Настройках" << Color::reset << " указано больше, игра автоматически"
        << "\n\tобрежет значение до максимума — чтобы сессия не затягивалась."
        << "\n\n\t" << Color::gray << "• Здоровье: " << Color::reset << "изначально задаётся в " << Color::gray << "Настройках" << Color::reset << " (от " << Color::yellow << "1" << Color::reset << " до " << Color::yellow << "10" << Color::reset << ")."
        << "\n\tОтображается в виде " << Color::pink << "сердечек ♥" << Color::reset << " — текущие розовые, потерянные — серые " << Color::gray << "♥" << Color::reset << "."
        << "\n\tПример при " << Color::pink << "3/5" << Color::reset << ": " << Color::pink << "♥♥♥" << Color::gray << "♥♥" << Color::reset << " (" << Color::pink << "3/5" << Color::reset << ")."

        << "\n\n\t" << Color::gray << "• Визуал: " << Color::reset << "заголовки уровней чередуются по цвету:"
        << "\n\t" << Color::cyan << "нечётные уровни" << Color::reset << " — " << Color::cyan << "циановые" << Color::reset << ","  << Color::yellow << "чётные уровни" << Color::reset << " — " << Color::yellow << "жёлтые" << Color::reset << "."
        << "\n\tЭто помогает глазу ориентироваться в длинных сессиях."

        << "\n\n\t" << Color::gray << "• Прерывание игры: " << Color::reset << "нажмите " << Color::yellow << "Esc" << Color::reset << " (Windows) или введите \"" << Color::yellow << "q" << Color::reset << "\""
        << "\n\t(Linux) в момент запроса вашего числа — игра завершится досрочно."
        << "\n\tПрогресс текущей партии не попадёт в статистику."

        << "\n\n\tПравила — как в \"" << Color::cyan << "Классике" << Color::reset << "\":"
        << "\n\t- \"" << Color::green << "ПОБЕДА" << Color::reset << "\" - если верных уровней больше, чем неверных;"
        << "\n\t- \"" << Color::yellow << "НИЧЬЯ" << Color::reset << "\" - если поровну;"
        << "\n\t- \"" << Color::red << "ПОРАЖЕНИЕ" << Color::reset << "\" - если неверных больше."

        << "\n\n\t" << Color::pink << "═══ Варианты окончания ═══" << Color::reset
        << "\n\tВ отличие от других режимов, здесь возможны " << Color::yellow << "три" << Color::reset << " сценария завершения:"
        << "\n\t- " << Color::pink << "Здоровье исчерпано!" << Color::reset << " — вы потеряли все ♥ до окончания уровней."
        << "\n\t- " << Color::yellow << "Достигнут лимит уровней!" << Color::reset << " — вы прошли все уровни, сохранив здоровье."
        << "\n\t- " << Color::pink << "Здоровье исчерпано, " << Color::yellow << "да и уровни тоже!" << Color::reset << " — последний уровень"
        << "\n\tсовпал с потерей последней единицы здоровья. Драматичный финал!"

        << "\n\n\t" << Color::cyan << "═══ Система очков ═══" << Color::reset
        << "\n\tРаботает по тем же формулам, что и в Классической игре:"
        << "\n\t" << Color::green << "• ПОБЕДА:    " << Color::reset << "(верных × 2 − неверных × 1) × множитель × бонус"
        << "\n\t" << Color::yellow << "• НИЧЬЯ:     " << Color::reset << "верных × 1 × множитель × бонус"
        << "\n\t" << Color::red << "• ПОРАЖЕНИЕ: " << Color::reset << "0 − (неверных × 1) × множитель"

        << "\n\n\t" << Color::gray << "Важно: " << Color::reset << "при поражении очки уходят в " << Color::red << "минус" << Color::reset << " —"
        << "\n\tкаждая ошибка буквально \"съедает\" ваш счёт. Играйте осторожно!"

        << "\n\n\tДанные сохраняются в " << Color::cyan << "\"Статистику\"" << Color::reset << " и " << Color::blue << "\"Достижения\"" << Color::reset << "."
        << "\n\tКоличество здоровья и уровней можно изменить через " << Color::gray << "Настройки" << Color::reset << "."
        << "\n\tПодробнее — в соседних разделах " << Color::total_white << "Справки" << Color::reset << ":\n";
    ConsoleUI::waitUser();
}

void UI::showHelpHints() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_yellow
        << "\n\t\t| (4) Подробности о режиме Игры \"С подсказками\" |" << Color::reset
        << "\n\n\tЭтот режим похож на \"" << Color::cyan << "Классический" << Color::reset << "\", но раз в N уровней"
        << "\n\tпоказывается случайное число " << Color::yellow << "ДО" << Color::reset << " вашего ввода — это " << Color::yellow << "подсказка!" << Color::reset
        << "\n\tЧастота подсказок настраивается в " << Color::gray << "Настройках" << Color::reset << " Игры."

        << "\n\n\t" << Color::gray << "• Как работает подсказка: " << Color::reset << "на уровнях, номер которых кратен N,"
        << "\n\tчисло компьютера выводится " << Color::yellow << "заранее" << Color::reset << " — ещё до того, как вы сделаете выбор."
        << "\n\tВам остаётся только повторить его — и уровень гарантированно будет выигран."
        << "\n\tНа остальных уровнях число показывается " << Color::gray << "после" << Color::reset << " вашего ответа."

        << "\n\n\t" << Color::gray << "• Пример: " << Color::reset << "если частота подсказок равна " << Color::yellow << "4" << Color::reset << ","
        << "\n\tто подсказки будут на уровнях " << Color::yellow << "4, 8, 12, 16, 20, 24, 28, 32" << Color::reset << "..."
        << "\n\tЧем меньше N — тем чаще подсказки, тем легче играть."

        << "\n\n\t" << Color::gray << "• Диапазон частоты: " << Color::reset << "от " << Color::yellow << "1" << Color::reset << " (подсказка на каждом уровне — чит-режим)"
        << "\n\tдо " << Color::yellow << "20" << Color::reset << " (подсказка появляется крайне редко)."
        << "\n\tЗначение по умолчанию — " << Color::yellow << "4" << Color::reset << "."

        << "\n\n\t" << Color::gray << "• Стратегия: " << Color::reset << "на уровнях с подсказкой — просто повторяйте число."
        << "\n\tНа остальных — полагайтесь на удачу или свою \"серию\" (например,"
        << "\n\tвсегда выбирать \"1\" или чередовать). Помните: за каждую ошибку"
        << "\n\tочки уходят в " << Color::red << "минус" << Color::reset << "!"

        << "\n\n\t" << Color::gray << "• Ограничение: " << Color::reset << "в этом режиме действует лимит на " << Color::cyan << "35 уровней" << Color::reset << "."
        << "\n\tДаже если в " << Color::gray << "Настройках" << Color::reset << " указано больше, игра автоматически"
        << "\n\tобрежет значение до максимума — чтобы сессия не затягивалась."

        << "\n\n\t" << Color::gray << "• Визуал: " << Color::reset << "заголовки уровней чередуются по цвету:"
        << "\n\t" << Color::cyan << "нечётные уровни" << Color::reset << " — " << Color::cyan << "циановые" << Color::reset << ","  << Color::yellow << "чётные уровни" << Color::reset << " — " << Color::yellow << "жёлтые" << Color::reset << "."
        << "\n\tА сама подсказка всегда выводится " << Color::yellow << "жёлтым цветом" << Color::reset << " — её невозможно пропустить."

        << "\n\n\t" << Color::gray << "• Прерывание игры: " << Color::reset << "нажмите " << Color::yellow << "Esc" << Color::reset << " (Windows) или введите \"" << Color::yellow << "q" << Color::reset << "\""
        << "\n\t(Linux) в момент запроса вашего числа — игра завершится досрочно."
        << "\n\tПрогресс текущей партии не попадёт в статистику."

        << "\n\n\tОстальные правила — как в \"" << Color::cyan << "Классике" << Color::reset << "\":"
        << "\n\t- \"" << Color::green << "ПОБЕДА" << Color::reset << "\" - если верных уровней больше, чем неверных;"
        << "\n\t- \"" << Color::yellow << "НИЧЬЯ" << Color::reset << "\" - если поровну;"
        << "\n\t- \"" << Color::red << "ПОРАЖЕНИЕ" << Color::reset << "\" - если неверных больше."

        << "\n\n\t" << Color::cyan << "═══ Система очков ═══" << Color::reset
        << "\n\tРаботает по тем же формулам, что и в Классической игре:"
        << "\n\t" << Color::green << "• ПОБЕДА:    " << Color::reset << "(верных × 2 − неверных × 1) × множитель × бонус"
        << "\n\t" << Color::yellow << "• НИЧЬЯ:     " << Color::reset << "верных × 1 × множитель × бонус"
        << "\n\t" << Color::red << "• ПОРАЖЕНИЕ: " << Color::reset << "0 − (неверных × 1) × множитель"

        << "\n\n\t" << Color::gray << "Важно: " << Color::reset << "при поражении очки уходят в " << Color::red << "минус" << Color::reset << " —"
        << "\n\tкаждая ошибка буквально \"съедает\" ваш счёт. Играйте осторожно!"

        << "\n\n\tДанные сохраняются в " << Color::cyan << "\"Статистику\"" << Color::reset << " и " << Color::blue << "\"Достижения\"" << Color::reset << "."
        << "\n\tЧастоту подсказок и количество уровней можно изменить через " << Color::gray << "Настройки" << Color::reset << "."
        << "\n\tПодробнее — в соседних разделах " << Color::total_white << "Справки" << Color::reset << ":\n";
    ConsoleUI::waitUser();
}

void UI::showHelpStats() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_cyan
        << "\n\t\t| (5) Подробности о Статистике |" << Color::reset
        << "\n\n\tЗдесь отображаются суммарные данные по всем режимам " << Color::cyan << "Игры" << Color::reset << ":"
        << "\n\t- количество " << Color::green << "побед" << Color::reset << ","
        << "\n\t- " << Color::yellow << "ничьих" << Color::reset << ","
        << "\n\t- " << Color::red << "поражений" << Color::reset << ","
        << "\n\t- " << Color::yellow << "общие очки" << Color::reset << " (накапливаются между сессиями " << Color::cyan << "Игры" << Color::reset << "),"
        << "\n\t- число " << Color::cyan << "запусков программы" << Color::reset << "."
        << "\n\n\t" << Color::cyan << "Статистика" << Color::green << " автоматически " << Color::reset << "сохраняется и загружается"
        << "\n\tвместе с " << Color::yellow << "сохранениями" << Color::reset << ". Сбросить её можно через меню"
        << "\n\t\"" << Color::yellow << "Сохранения" << Color::reset << "\" → пункт \"" << Color::red << "3" << Color::reset << "\".\n";
    ConsoleUI::waitUser();
}

void UI::showHelpAchievements() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_blue
        << "\n\t\t| (6) Подробности о Достижениях |" << Color::reset
        << "\n\n\tДостижения " << Color::cyan << "Игры" << Color::reset << " разделены на три категории:"
        << "\n\t- " << Color::green << "ОБЫКНОВЕННЫЕ" << Color::reset << " — за победы, ничьи, запуски и просмотр заставок;"
        << "\n\t- " << Color::cyan << "НЕСТАНДАРТНЫЕ" << Color::reset << " — за взаимодействие с настройками и меню;"
        << "\n\t- " << Color::blue << "РЕДКИЕ" << Color::reset << " — связаны с пасхалками и секретными действиями."
        << "\n\n\t" << Color::yellow << "Бонус: " << Color::reset << "за каждое открытое достижение вы получаете"
        << "\n\tпроцентную надбавку к очкам. Открыв " << Color::blue << "все 12" << Color::reset << " — получите"
        << "\n\tмаксимальный бонус " << Color::yellow << "+10%" << Color::reset << " к каждому исходу игры.\n";
    ConsoleUI::waitUser();
}

void UI::showHelpExit() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_white
        << "\n\t\t| (7) Подробности о выходе из Игры |" << Color::reset
        << "\n\n\tПри нажатии " << Color::yellow << "Backspace" << Color::reset << " в главном меню запускается"
        << "\n\tпроцедура выхода:"
        << "\n\t- " << Color::green << "автосохранение" << Color::reset << " текущего прогресса;"
        << "\n\t- " << Color::red << "обратный отсчёт" << Color::reset << " (время настраивается в " << Color::gray << "Настройках" << Color::reset << ");"
        << "\n\t- показ прощального логотипа \"" << Color::cyan << "thanks" << Color::reset << "\"."
        << "\n\n\tПосле окончания отсчёта программа корректно завершает свою работу.\n";
    ConsoleUI::waitUser();
}

void UI::showHelpSettings() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_gray
        << "\n\t\t| (8) Подробности о Настройках Игры |" << Color::reset
        << "\n\n\tВ Настройках можно изменить:"
        << "\n\t- количество уровней,"
        << "\n\t- " << Color::yellow << "частоту подсказок" << Color::reset << ","
        << "\n\t- " << Color::pink << "здоровье" << Color::reset << " (для режима \"" << Color::pink << "ЖИЗНИ" << Color::reset << "\"),"
        << "\n\t- время выхода (в секундах),"
        << "\n\t- " << Color::cyan << "тип заставки" << Color::reset << " (1, 2, 3),"
        << "\n\t- " << Color::yellow << "множитель очков" << Color::reset << " (от 1 до 10),"
        << "\n\t- " << Color::green << "Вкл" << Color::reset << "/" << Color::red << "Выкл" << Color::reset << " автоочистку экрана."
        << "\n\n\tНевозможно ввести недопустимые значения — система защитит ввод.\n";
    ConsoleUI::waitUser();
}

void UI::showHelpAuthor() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_green
        << "\n\t\t| (9) Подробности о блоке \"От автора\" |" << Color::reset
        << "\n\n\tЗдесь — напутствие от " << Color::green << "автора" << Color::reset << " и скрытые " << Color::cyan << "пасхалки" << Color::reset << "."
        << "\n\n\t" << Color::gray << "• Логотип автора: " << Color::reset << "вызывается клавишей " << Color::yellow << "Tab" << Color::reset << " в главном меню."
        << "\n\tПри первом просмотре показывается " << Color::cyan << "author1" << Color::reset << ", при повторном — " << Color::cyan << "author2" << Color::reset << "."
        << "\n\n\t" << Color::gray << "• Секретная ссылка: " << Color::reset << "внутри блока логотипов автора есть подсказка —"
        << "\n\tнажмите " << Color::yellow << "Tab" << Color::reset << ", чтобы открыть дополнительную графику в браузере."
        << "\n\t(Требуется подключение к Сети.)"
        << "\n\n\tДальше — ищите сами " << Color::yellow << ":)\n" << Color::reset;
    ConsoleUI::waitUser();
}

void UI::showHelpSaves() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_yellow
        << "\n\t\t| (-) Подробности о сохранениях Игры |" << Color::reset
        << "\n\n\tВ блоке сохранений можно:"
        << "\n\t- \"" << Color::green << "1" << Color::reset << "\" — " << Color::green << "сохранить" << Color::reset << " текущий прогресс (мгновенно);"
        << "\n\t- \"" << Color::cyan << "2" << Color::reset << "\" — " << Color::cyan << "загрузить" << Color::reset << " прогресс из файла (если файла нет — появится новое сохранение);"
        << "\n\t- \"" << Color::red << "3" << Color::reset << "\" — " << Color::red << "сбросить" << Color::reset << " всё к значениям по умолчанию."
        << "\n\n\t" << Color::yellow << "Важно: " << Color::reset << "сброс удалит " << Color::red << "ВСЁ" << Color::reset << ": настройки, статистику,"
        << "\n\tочки и достижения. Перед сбросом " << Color::cyan << "Игра" << Color::reset << " запросит подтверждение"
        << "\n\t(" << Color::green << "y" << Color::reset << "/" << Color::red << "n" << Color::reset << ")."
        << "\n\n\tДоступ — через главное меню (клавиша \"" << Color::yellow << "-" << Color::reset << "\" или \"" << Color::yellow << "S" << Color::reset << "\").\n";
    ConsoleUI::waitUser();
}

void UI::showHelpEvent() {
    ConsoleUI::clearScreen();
    std::cout << Color::total_green
        << "\n\t\t| (+) Подробности о Праздничном эвенте |" << Color::reset
        << "\n\n\tВ этом специальном режиме вы увидите\n"
        << "\tпраздничную " << Color::green << "ёлочку" << Color::reset << ", созданную из символов ASCII."
        << "\n\tШарики на ней " << Color::yellow << "переливаются" << Color::reset << " четырьмя цветами и плавно двигаются."
        << "\n\n\t" << Color::gray << "• Управление: " << Color::reset << "нажмите " << Color::yellow << "Enter" << Color::reset << " или " << Color::yellow << "Esc" << Color::reset
        << "\n\tв любой момент, чтобы остановить анимацию."
        << "\n\n\t" << Color::gray << "• Вызов: " << Color::reset << "клавиши \"" << Color::yellow << "+" << Color::reset << "\", \"" << Color::yellow << "=" << Color::reset << "\" или \"" << Color::yellow << "E" << Color::reset << "\""
        << "\n\tв главном меню."
        << "\n\n\tЭто небольшой подарок от автора! " << Color::yellow << ";)\n" << Color::reset;
    ConsoleUI::waitUser();
}


// --- Главное меню справки ---
void UI::showHelp(GameSession& session) {
    bool in_help = true;
    while (in_help) {
        ConsoleUI::clearScreen(session.getAutoClear());
        std::cout << Color::total_green
            << "\n\t\t---/===/     СПРАВКА       \\===\\---\n" << Color::reset
            << "\n\tВас приветствует " << Color::green << "справка" << Color::reset
            << " по " << Color::cyan << "Игре \"0/1 Step\"" << Color::reset << "!\n\n"
            << Color::green << "\tПодробности о:\n"
            << Color::green << "\t╟─> " << Color::reset << "1 → Классической игре\n"
            << Color::green << "\t╟─> " << Color::reset << "2 → " << Color::cyan << "режиме \"Всё или ничего\"\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "3 → " << Color::pink << "режиме \"ЖИЗНИ\"\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "4 → " << Color::yellow << "режиме Игры \"С подсказками\"\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "5 → " << Color::cyan << "Статистике\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "6 → " << Color::blue << "Достижениях\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "7 → " << Color::white << "Выходе\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "8 → " << Color::gray << "Настройках\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "9 → " << Color::green << "блоке \"От автора\"\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "- → " << Color::yellow << "сохранениях Игры\n" << Color::reset
            << Color::green << "\t╟─> " << Color::reset << "+ → " << Color::green << "Праздничном эвенте\n" << Color::reset
            << Color::green << "\t╙─> " << Color::reset << "0 / Esc → Назад\n"
            << Color::yellow
            << "\n\t*Любая другая клавиша будет проинорирована.\n"
            << "\n\tВыберите раздел >> " << Color::reset;

#ifdef _WIN32
        char key = _getch();

        if (key == 27) {
            std::cout << "Esc\n" << Color::reset;
        }
        else if (key >= '0' && key <= '9') {
            std::cout << key << "\n" << Color::reset;
        }
        else if (key == '-' || key == '_' || key == '+' || key == '=') {
            std::cout << static_cast<char>(key) << "\n" << Color::reset;
        }
        else {
            std::cout << "?\n" << Color::reset;
            continue;
        }

        if (key == '1') showHelpClassic();
        else if (key == '2') showHelpAllOrNothing();
        else if (key == '3') showHelpLives();
        else if (key == '4') showHelpHints();
        else if (key == '5') showHelpStats();
        else if (key == '6') showHelpAchievements();
        else if (key == '7') showHelpExit();
        else if (key == '8') showHelpSettings();
        else if (key == '9') showHelpAuthor();
        else if (key == '-' || key == '_') showHelpSaves();
        else if (key == '+' || key == '=') showHelpEvent();
        else if (key == '0' || key == 27) {
            in_help = false;
        }

#else
        // Fallback для Linux/macOS
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") showHelpClassic();
        else if (choice == "2") showHelpAllOrNothing();
        else if (choice == "3") showHelpLives();
        else if (choice == "4") showHelpHints();
        else if (choice == "5") showHelpStats();
        else if (choice == "6") showHelpAchievements();
        else if (choice == "7") showHelpExit();
        else if (choice == "8") showHelpSettings();
        else if (choice == "9") showHelpAuthor();
        else if (choice == "-") showHelpSaves();
        else if (choice == "+") showHelpEvent();
        else if (choice == "0") in_help = false;
        // остальное игнорируется
#endif
    }
}


// --- Статистика ---
void UI::showStats(const GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_cyan
        << "\n\t---/===/ СТАТИСТИКА \\===\\---" << Color::reset
        << "\n\t\t ╟─────" << Color::green << "ПОБЕД: " << Color::total_green << session.getWinCount() << Color::reset
        << "\n\t\t ╟────" << Color::yellow << "ВНИЧЬЮ: " << Color::total_yellow << session.getDrawCount() << Color::reset
        << "\n\t\t ╟─" << Color::red << "ПОРАЖЕНИЙ: " << Color::total_red << session.getLossCount() << Color::reset
        << "\n\t\t ║"
        << "\n\t\t ╟──────" << Color::yellow << "ОЧКИ: " << Color::total_yellow << session.getScore() << Color::reset
        << "\n\t\t ║"
        << "\n\t\t ╚═" << Color::cyan << "ЗАПУСКОВ ПРОГРАММЫ:" << Color::total_cyan << session.getLaunchCount() << Color::reset << "\n";

    ConsoleUI::waitUser();
}


// --- Достижения ---
void UI::showAchievements(const GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    std::cout << Color::total_blue
        << "\n\t---/===/    ДОСТИЖЕНИЯ    \\===\\---" << Color::reset
        << "\n\n\tВ этом разделе вы можете увидеть свои " << Color::blue << "достижения" << Color::reset << ".\n"
        << "\tОни разделены на категории:\n";

    std::cout << Color::green << "\n\tОБЫКНОВЕННЫЕ:\n" << Color::reset;
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::CUSTOMIZE_SETTINGS) ? "[+]" : "[ ]")
        << " Изменение настроек\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::SAW_ALPHA_LOGO) ? "[+]" : "[ ]")
        << " Альфа-логотип\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::SAW_BIG_LOGO) ? "[+]" : "[ ]")
        << " Большая заставка\n";

    std::cout << Color::cyan << "\n\tНЕСТАНДАРТНЫЕ:\n" << Color::reset;
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::TOGGLED_AUTO_CLEAR) ? "[+]" : "[ ]")
        << " Отключил очистку\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::REVISITED_CLEAR_SETTING) ? "[+]" : "[ ]")
        << " Вернул очистку\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::VIEWED_CREDITS) ? "[+]" : "[ ]")
        << " Прочитал \"От автора\"\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::ENTERED_SAVES_MENU) ? "[+]" : "[ ]")
        << " Заходил в сохранения\n";

    std::cout << Color::blue << "\n\tРЕДКИЕ:\n" << Color::reset;
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::FOUND_MICRO_EASTER_EGG) ? "[+]" : "[ ]")
        << " Микро-пасхалка (\"\")\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::TRIGGERED_LOGO_TAB) ? "[+]" : "[ ]")
        << " Ввёл Tab автору\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::OPENED_LOGO_LINK) ? "[+]" : "[ ]")
        << " Открыл ссылку логотипа\n";
    std::cout << "\t  " << (session.hasAchievement(AchievementIndex::SAW_ALT_LOGO) ? "[+]" : "[ ]")
        << " Альтернативный логотип\n";

    ConsoleUI::waitUser();
}


// --- Блок "От автора" ---
void UI::showCredits(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());
    session.unlockAchievement(AchievementIndex::VIEWED_CREDITS);

    std::cout << Color::total_green
        << "\n\t\t---/===/ От автора \\===\\---" << Color::reset << "\n"
        << "\n\t\t     Здравствуй, игрок!\n\n"
        << "\tБлагодарю тебя за запуск " << Color::cyan << "0/1 Step" << Color::reset
        << " и блока " << Color::green << "\"От автора\"" << Color::reset << ".\n"
        << "\tВ этом окошке я в одностороннем порядке желаю тебе удачной игры.\n\n"
        << "\t" << Color::gray << "(PS: попробуй нажать " << Color::yellow << "Tab" << Color::gray
        << " в главном меню " << Color::yellow << ";Ъ" << Color::reset << "\n"
        << Color::yellow
        << "\n\t>> " << Color::cyan;

#ifdef _WIN32
    char key = _getch();

    if (key == 9) {
        std::cout << "Tab\n" << Color::reset;
        std::cout << Color::green << "\tДа не здесь! (^-^" << Color::cyan << "\"" << Color::green << ")" << Color::reset << "\n";
        session.unlockAchievement(AchievementIndex::TRIGGERED_LOGO_TAB);
        ConsoleUI::waitUser();
    }
    else {
        std::cout << "?\n" << Color::reset;
    }
#else
    std::string dummy;
    std::getline(std::cin, dummy);
#endif
}


// --- Логотипы  ---
void UI::showLogo(const std::string& name) {
    if (name == "base") {
        std::cout << Color::green << GameLogos::base << Color::reset;
    }
    else if (name == "alpha") {
        std::cout << Color::cyan << GameLogos::alpha << Color::reset;
    }
    else if (name == "big") {
        std::cout << Color::yellow << GameLogos::big << Color::reset;
    }
    else if (name == "author1") {
        std::cout << Color::green << GameLogos::author1 << Color::reset;
    }
    else if (name == "author2") {
        std::cout << Color::yellow << GameLogos::author2 << Color::reset;
    }
    else if (name == "extra1") {
        std::cout << Color::green << GameLogos::extra1 << Color::reset;
    }
    else if (name == "extra2") {
        std::cout << Color::red << GameLogos::extra2 << Color::reset;
    }
    else if (name == "thanks") {
        std::cout << Color::cyan << GameLogos::thanks << Color::reset;
    }
    else {
        std::cout << Color::red << "\t[Неизвестный логотип: " << name << "]\n" << Color::reset;
    }
}


// --- Логотип автора ---
void UI::showLogoAuthor(GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());

    std::cout << Color::green
        << "\n\n\tПожалуйста, открой окно " << Color::cyan << "Игры" << Color::green << " на весь экран,"
        << "\n\tтак ты увидишь то, что нужно " << Color::total_yellow << ";)" << Color::reset
        << "\n\n\tНажми любую клавишу, как будешь готов >> " << Color::reset;

#ifdef _WIN32
    _getch();
#else
    std::string dummy;
    std::getline(std::cin, dummy);
#endif

    ConsoleUI::clearScreen(session.getAutoClear());

    bool link_already_opened = session.hasAchievement(AchievementIndex::OPENED_LOGO_LINK);

    if (link_already_opened) {
        UI::showLogo("author2");
        session.unlockAchievement(AchievementIndex::SAW_ALT_LOGO);
    }
    else {
        UI::showLogo("author1");
        session.unlockAchievement(AchievementIndex::SAW_ALPHA_LOGO);
    }

    std::cout << Color::white
        << "\n\tЕсли хочешь увидеть ещё графику по\n"
        << "\t" << Color::cyan << "0/1 Step" << Color::reset << ", нажми " << Color::yellow << "Tab" << Color::reset << " :)\n"
        << "\t(Потребуется подключение к Сети)\n"
        << Color::yellow << "\n\tНажмите клавишу >> " << Color::cyan;

#ifdef _WIN32
    char key = _getch();

    if (key == 9) {
        std::cout << "Tab\n" << Color::reset;
#ifdef _WIN32
        std::string cmd = std::string("start ") + Urls::LOGO_URL;
        system(cmd.c_str());
#endif
        session.unlockAchievement(AchievementIndex::OPENED_LOGO_LINK);
        session.unlockAchievement(AchievementIndex::SAW_ALT_LOGO);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    else {
        std::cout << "?\n" << Color::reset;
    }
#else
    std::string dummy;
    std::getline(std::cin, dummy);
    if (dummy == "10") {
        std::cout << Color::green << "\tДа не здесь! (^-^" << Color::cyan << "\"" << Color::green << ")" << Color::reset << "\n";
        session.unlockAchievement(AchievementIndex::TRIGGERED_LOGO_TAB);
        ConsoleUI::waitUser();
    }
#endif
}

void UI::showSavesMenu(GameSession& session) {
    session.unlockAchievement(AchievementIndex::ENTERED_SAVES_MENU);

    bool in_saves = true;
    while (in_saves) {
        ConsoleUI::clearScreen(session.getAutoClear());
        std::cout << Color::total_yellow
            << "\n\t---/===/    СОХРАНЕНИЯ    \\===\\---\n" << Color::reset
            << Color::cyan << "\tВозможные действия:\n" << Color::reset
            << Color::cyan << "\t╟─>" << Color::reset << " 1 → " << Color::green << "Сохранить" << Color::reset << " текущий прогресс\n"
            << Color::cyan << "\t╟─>" << Color::reset << " 2 → " << Color::cyan << "Загрузить" << Color::reset << " прогресс из файла\n"
            << Color::cyan << "\t╟─>" << Color::reset << " 3 → " << Color::red << "Сбросить" << Color::reset << " к значениям по умолчанию\n"
            << Color::cyan << "\t╙─>" << Color::reset << " 0 → Назад\n"
            << Color::yellow
            << "\n\tВыбор действия >> " << Color::cyan;

#ifdef _WIN32
        char key = _getch();

        // Вывод нажатой клавиши
        if (key == 27) {
            std::cout << "Esc\n" << Color::reset;
        }
        else if (key >= '0' && key <= '3') {
            std::cout << key << "\n" << Color::reset;
        }
        else {
            std::cout << Color::red << "\a?" << Color::reset;
            continue;
        }

        // Обработка
        if (key == '1') {
            if (SaveManager::save(session)) {
                std::cout << Color::green << "\n\tПрогресс успешно сохранён!\n" << Color::reset;
            }
            else {
                std::cout << Color::red << "\n\tОшибка при сохранении!\n" << Color::reset;
            }
            ConsoleUI::waitUser();
        }
        else if (key == '2') {
            if (SaveManager::load(session)) {
                std::cout << Color::green << "\n\tПрогресс успешно загружен!\n" << Color::reset;
            }
            else {
                std::cout << Color::yellow << "\n\tСоздано новое сохранение.\n" << Color::reset;
            }
            ConsoleUI::waitUser();
        }
        else if (key == '3') {
            std::cout << Color::yellow
                << "\n\tВнимание: все текущие настройки и статистика\n"
                << "\tбудут заменены значениями по умолчанию!\n"
                << "\tПродолжить? (" << Color::green << "y" << Color::yellow << "/" << Color::red << "n" << Color::yellow << ") >> " << Color::reset;

            char confirm_key = _getch();
            bool confirmed = (confirm_key == 'y' || confirm_key == 'Y' || confirm_key == 'д' || confirm_key == 'Д');
            std::cout << (confirmed ? "y\n" : "n\n") << Color::reset;

            if (confirmed) {
                SaveManager::createDefault();
                SaveManager::load(session);
                std::cout << Color::green << "\n\tСохранение сброшено к значениям по умолчанию.\n" << Color::reset;
            }
            else {
                std::cout << Color::yellow << "\n\tОтмена операции.\n" << Color::reset;
            }
            ConsoleUI::waitUser();
        }
        else if (key == '0' || key == 27) {
            in_saves = false;
        }
        // остальное игнорируется (continue выше)

#else
        // Linux fallback
        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            if (SaveManager::save(session)) {
                std::cout << Color::green << "\n\tПрогресс успешно сохранён!\n" << Color::reset;
            }
            else {
                std::cout << Color::red << "\n\tОшибка при сохранении!\n" << Color::reset;
            }
            ConsoleUI::waitUser();
        }
        else if (choice == "2") {
            if (SaveManager::load(session)) {
                std::cout << Color::green << "\n\tПрогресс успешно загружен!\n" << Color::reset;
            }
            else {
                std::cout << Color::yellow << "\n\tСоздано новое сохранение.\n" << Color::reset;
            }
            ConsoleUI::waitUser();
        }
        else if (choice == "3") {
            std::cout << Color::yellow
                << "\n\tВнимание: все текущие настройки и статистика\n"
                << "\tбудут заменены значениями по умолчанию!\n"
                << "\tПродолжить? (" << Color::green << "y" << Color::yellow << "/" << Color::red << "n" << Color::yellow << ") >> " << Color::reset;

            std::string confirm;
            std::getline(std::cin, confirm);
            bool confirmed = (confirm == "y" || confirm == "Y" || confirm == "д" || confirm == "Д");
            if (confirmed) {
                SaveManager::createDefault();
                SaveManager::load(session);
                std::cout << Color::green << "\n\tСохранение сброшено к значениям по умолчанию.\n" << Color::reset;
            }
            else {
                std::cout << Color::yellow << "\n\tОтмена операции.\n" << Color::reset;
            }
            ConsoleUI::waitUser();
        }
        else if (choice == "0") {
            in_saves = false;
        }
        // остальное игнорируется
#endif
    }
}

void FestiveEventManager::showChristmasTree() {
    ConsoleUI::clearScreen(true);

    std::cout << Color::green << "\n\t---/===/    ПРАЗДНИЧНЫЙ ЭВЕНТ    \\===\\---\n" << Color::reset;
    ConsoleUI::waitUser();

    const int tree_height = 10;
    std::vector<std::vector<int>> ball_positions(tree_height);
    std::vector<std::string> ball_colors = { Color::red, Color::green, Color::blue, Color::yellow };

    // Инициализация шариков
    for (int row = 1; row < tree_height; ++row) {
        int stars = 2 * row + 1;
        int count = (row < 5) ? 2 : 3;
        for (int i = 0; i < count; ++i) {
            int pos = (stars * i) / count;
            ball_positions[row].push_back(pos);
        }
    }

    int frame = 0;
    bool running = true;

    while (running) {
        std::ostringstream frame_buffer;

        // Верхушка
        frame_buffer << Color::yellow << "\n\t        \\ /\n";
        frame_buffer << "\t       --@--\n";

        // Ёлка
        for (int row = 0; row < tree_height; ++row) {
            int stars = 2 * row + 1;
            int padding = tree_height - row - 1;
            frame_buffer << "\t" << std::string(padding, ' ');

            if (row > 0) {
                for (size_t i = 0; i < ball_positions[row].size(); ++i) {
                    ball_positions[row][i]++;
                    if (ball_positions[row][i] >= stars) {
                        ball_positions[row][i] = 0;
                    }
                }
            }

            for (int col = 0; col < stars; ++col) {
                bool is_ball = false;
                std::string ball_color = Color::reset;

                if (row > 0) {
                    for (size_t i = 0; i < ball_positions[row].size(); ++i) {
                        if (col == ball_positions[row][i]) {
                            is_ball = true;
                            int color_idx = (row + static_cast<int>(i) + frame) % static_cast<int>(ball_colors.size());
                            ball_color = ball_colors[color_idx];
                            break;
                        }
                    }
                }

                if (is_ball) {
                    frame_buffer << ball_color << "o" << Color::reset;
                }
                else {
                    frame_buffer << Color::green << "*" << Color::reset;
                }
            }
            frame_buffer << "\n";
        }

        // Ствол
        for (int i = 0; i < 3; ++i) {
            frame_buffer << "\t" << std::string(tree_height - 2, ' ') << Color::brown << "|||" << Color::reset << "\n";
        }

        frame_buffer << Color::yellow
            << "\n\tНажмите Enter, чтобы остановить.\n"
            << Color::reset;

        // Выводим весь кадр
        ConsoleUI::clearScreen(true);
        std::cout << frame_buffer.str() << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        frame++;

        // Windows-only non-blocking input
        if (_kbhit()) {
            char key = _getch();
            if (key == '\r' || key == 27) {
                running = false;
            }
        }
    }

    std::cout << Color::green << "\n\tЭвент завершён. Спасибо за просмотр!\n" << Color::reset;
    ConsoleUI::waitUser();
}

void UI::performExit(const GameSession& session) {
    ConsoleUI::clearScreen(session.getAutoClear());

    SaveManager::save(session);
    std::cout << "\n\t      " << Color::total_green << "ИГРА СОХРАНЕНА" << Color::reset << "\n\n";

    std::cout << Color::total_red
        << "\n\t|    ИНИЦИАЛИЗИРОВАН    |"
        << "\n\t|  ВЫХОД ИЗ ПРОГРАММЫ!  |" << Color::red
        << "\n\tПРОГРАММА ЗАКРОЕТСЯ ЧЕРЕЗ"
        << Color::reset;

    int delay = session.getExitDelaySec();
    for (int sec = delay; sec >= 1; --sec) {
        std::string word;
        int last_digit = sec % 10;
        if (last_digit == 1 && sec != 11) {
            word = "секунду";
        }
        else if (last_digit >= 2 && last_digit <= 4 && !(sec >= 12 && sec <= 14)) {
            word = "секунды";
        }
        else {
            word = "секунд";
        }
        std::cout << "\n\t     " << sec << "\t" << word;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    ConsoleUI::clearScreen(session.getAutoClear());
    UI::showLogo("thanks");
    std::cout << "\n\n\n" << Color::total_cyan;
}


// === Работа с главным меню Игры ===
void MainMenu::showIntro() {
    if (session_.getLaunchCount() == 0) {
        ConsoleUI::clearScreen(true);
        UI::showLogo("alpha");
        std::cout << Color::cyan << "\n\t\t=== 0/1 Step ===" << Color::reset;
        std::cout << "\n\t" << Color::cyan << "Игра" << Color::reset << " запущена впервые!\n\tМожете нажатием " << Color::green << "7" << Color::reset << " вызвать " << Color::green << "Справку" << Color::reset << ".\n";
        ConsoleUI::waitUser();
    }
}

void MainMenu::showMenu() {
    ConsoleUI::clearScreen(session_.getAutoClear());
    session_.incrementLaunchCount();
    SaveManager::autosave(session_);

    // Заставка
    int intro = session_.getIntroType();
    if (intro == 1) {
        UI::showLogo("alpha");
        session_.unlockAchievement(AchievementIndex::SAW_ALPHA_LOGO);
    }
    else if (intro == 2) {
        UI::showLogo("big");
        session_.unlockAchievement(AchievementIndex::SAW_BIG_LOGO);
    }
    else {
        UI::showLogo("base");
    }

    std::cout << Color::total_cyan << "\n\t\t===  0/1 Step  ===" << Color::reset;
    std::cout << Color::cyan
        << "\n\t---/===/   ГЛАВНОЕ МЕНЮ:  \\===\\---" << Color::reset << "\t\n"
        << Color::yellow << "\tВозможные действия:\n" << Color::reset 
        << Color::yellow << "\t╟─> " << Color::reset << "1 → Классическая игра\n"
        << Color::yellow << "\t╟─> " << Color::reset << "2 → " << Color::cyan << "Режим \"Всё или ничего\"" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "3 → " << Color::pink << "Режим \"ЖИЗНИ\"" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "4 → " << Color::yellow << "Режим игры \"С подсказками\"" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "5 / T → " << Color::cyan << "Статистика" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "6 / A → " << Color::blue << "Достижения" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "7 / H → " << Color::green << "Справка" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "8 / C / I → " << Color::gray << "Настройки" << Color::reset << "\n"
        << Color::yellow << "\t╠═> " << Color::reset << "9 → " << Color::green << "\"От автора\"" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "- / S → " << Color::yellow << "Сохранения" << Color::reset << "\n"
        << Color::yellow << "\t╟─> " << Color::reset << "+ / E → " << Color::green << "Праздничный эвент" << Color::reset << "\n"
        << Color::yellow << "\t╙─> " << Color::reset << "Backspace → " << Color::gray << "Выход" << Color::reset << "\n"
        << Color::yellow
        << "\n\t*Любая другая клавиша вызывает перезапуск Игры\n"
        << Color::reset;

    std::cout << Color::yellow << "\n\t Нажмите клавишу >> " << Color::cyan;
}

bool MainMenu::handleKeyPress(char key) {
    if (key == '1') {
        ClassicMode().play(session_);
    }
    else if (key == '2') {
        AllOrNothingMode().play(session_);
    }
    else if (key == '3') {
        LivesMode().play(session_);
    }
    else if (key == '4') {
        HintsMode().play(session_);
    }
    else if (key == '5' || key == 't' || key == 'T') {
        UI::showStats(session_);
    }
    else if (key == '6' || key == 'a' || key == 'A') {
        UI::showAchievements(session_);
    }
    else if (key == '7' || key == 'h' || key == 'H') {
        UI::showHelp(session_);
    }
    else if (key == '8' || key == 'c' || key == 'C' || key == 'i' || key == 'I') {
        UI::showSettingsMenu(session_);
    }
    else if (key == '9') {
        UI::showCredits(session_);
    }
    else if (key == 9 || key == 'l' || key == 'L') { // Tab или L/l
        UI::showLogoAuthor(session_);
    }
    else if (key == '-' || key == '_' || key == 's' || key == 'S') {
        UI::showSavesMenu(session_);
    }
    else if (key == '+' || key == '=' || key == 'e' || key == 'E') {
        FestiveEventManager::showChristmasTree();
    }
    else if (key == 8) { // Backspace
        UI::performExit(session_);
        return false;
    }
    else {
        // Любая другая клавиша открывает пасхалку
        session_.unlockAchievement(AchievementIndex::FOUND_MICRO_EASTER_EGG);
        std::cout << "?\n" << Color::reset;
        return true;
    }

    // === Вывод нажатой клавиши (только для известных действий) ===
    if (key == 8) {
        std::cout << "Backspace\n" << Color::reset;
    }
    else if (key == 9) {
        std::cout << "Tab\n" << Color::reset;
    }
    else if (key == '-' || key == '_' || key == '+' || key == '=') {
        std::cout << static_cast<char>(key) << "\n" << Color::reset;
    }
    else if ((key >= '0' && key <= '9') ||
        (key >= 'a' && key <= 'z') ||
        (key >= 'A' && key <= 'Z')) {
        std::cout << key << "\n" << Color::reset;
    }

    SaveManager::autosave(session_);
    return true;
}

void MainMenu::run() {
    showIntro();
    while (true) {
        showMenu();
#ifdef _WIN32
        char key = _getch();
        if (!handleKeyPress(key)) break;
#else
        std::string s;
        std::getline(std::cin, s);
        s = InputValidator::trim(s);
        if (!s.empty() && !handleKeyPress(s[0])) break;
#endif
    }
}