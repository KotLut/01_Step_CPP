#include <iostream>
#include <fstream>
#include <string>
#include "game_core.h"
#include "system_utils.h"
#include "ui_elements.h"


void edit_levels(GameState& state) {
    std::cout << Color::green
        << "\n\t| (01) Выбор количества уровней |\n" << Color::reset;
    std::cout << "\tТекущее значение: " << state.level_count << "\n";
    std::cout << Color::yellow
        << "\tВведите новое количество уровней (минимум 1): " << Color::reset;
    state.level_count = get_valid_int(1);
    // Достижение: изменение настроек
    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь уровней: " << state.level_count << "\n" << Color::reset;
}

void edit_hint_frequency(GameState& state) {
    std::cout << Color::yellow
        << "\n\t| (02) Выбор частоты подсказок |\n" << Color::reset
        << "\t// Подсказки появляются раз в N уровней.\n"
        << "\t// \"1\" — каждый уровень, чем больше — тем реже.\n";
    std::cout << "\tТекущее значение: " << state.hint_frequency << "\n";
    std::cout << Color::yellow
        << "\tВведите частоту подсказок (минимум 1): " << Color::reset;
    state.hint_frequency = get_valid_int(1);

    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь подсказка раз в " << state.hint_frequency << " уровней.\n" << Color::reset;
}

void edit_health(GameState& state) {
    std::cout << Color::red
        << "\n\t| (03) Выбор количества здоровья |\n" << Color::reset
        << "\t// Здоровье определяет длительность режима \"ЖИЗНИ\".\n";
    std::cout << "\tТекущее значение: " << state.health << "\n";
    std::cout << Color::yellow
        << "\tВведите количество здоровья (минимум 1): " << Color::reset;
    state.health = get_valid_int(1);

    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь здоровья: " << state.health << "\n" << Color::reset;
}

void edit_exit_delay(GameState& state) {
    std::cout << Color::white
        << "\n\t| (04) Изменение времени выхода |\n";
    std::cout << "\tТекущее значение: " << state.exit_delay_sec << " сек.\n";
    std::cout << Color::yellow
        << "\tВведите время выхода в секундах (минимум 1): " << Color::reset;
    state.exit_delay_sec = get_valid_int(1);
    if (state.achievements.size() > 0) {
        state.achievements[0] = true;
    }
    std::cout << Color::green << "\n\tПринято! Теперь выход через " << state.exit_delay_sec << " сек.\n" << Color::reset;
}

void edit_intro_type(GameState& state) {
    std::cout << Color::cyan
        << "\n\t| (05) Выбор варианта заставки |\n" << Color::reset
        << "\t+-> \"1\" - Альфа-версия заставки\n"
        << "\t+-> \"2\" - Большая заставка\n"
        << "\t--> \"3\" - Новая заставка (рекомендуется)\n";
    std::cout << Color::yellow << "\n\tВыберите вариант (1-3): " << Color::reset;

    while (true) {
        int choice = get_valid_int(1);
        if (choice >= 1 && choice <= 3) {
            state.intro_type = choice;
            if (state.achievements.size() > 0) {
                state.achievements[0] = true;
            }
            std::cout << Color::green << "\n\tПринято! Выбрана заставка №" << state.intro_type << ".\n" << Color::reset;
            break;
        }
        else {
            std::cout << Color::red << "\tДопустимы только значения от 1 до 3. Попробуйте снова.\n" << Color::reset;
        }
    }
}

void toggle_auto_clear(GameState& state) {
    state.auto_clear = !state.auto_clear;
    std::cout << Color::green
        << "\n\tАвтоочистка экрана " << (state.auto_clear ? "ВКЛЮЧЕНА" : "ВЫКЛЮЧЕНА") << ".\n"
        << Color::reset;

    // Достижения: ochistka и ochistka2
    if (!state.auto_clear && state.achievements.size() > 3) {
        state.achievements[3] = true;
    }
    if (state.auto_clear && state.achievements.size() > 4) {
        if (state.achievements[3]) {
            state.achievements[4] = true;
        }
    }
}

void show_settings_menu(GameState& state) {
    bool in_settings = true;
    while (in_settings) {
        clear_screen(state.auto_clear);
        std::cout << Color::green
            << "\n\t---/===/    НАСТРОЙКИ    \\===\\---\n" << Color::reset
            << "\tВозможные действия:\n"
            << "\t+->\"1\" - Количество уровней\n"
            << "\t+->\"2\" - Частота " << Color::yellow << "подсказок" << Color::reset << "\n"
            << "\t+->\"3\" - " << Color::red << "Здоровье" << Color::reset << " (режим \"" << Color::red << "ЖИЗНИ" << Color::reset << "\")\n"
            << "\t+->\"4\" - Время выхода\n"
            << "\t+->\"5\" - " << Color::cyan << "Заставка" << Color::reset << "\n"
            << "\t+->\"0\" - " << Color::green << "Вкл" << Color::reset << "/" << Color::red << "Выкл" << Color::reset << " автоочистку экрана\n"
            << "\t-->\"9\" - Назад\n"
            << Color::yellow
            << "\n\tВыбор действия >> " << Color::reset;

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            clear_screen(state.auto_clear);
            edit_levels(state);
        }
        else if (choice == "2") {
            clear_screen(state.auto_clear);
            edit_hint_frequency(state);
        }
        else if (choice == "3") {
            clear_screen(state.auto_clear);
            edit_health(state);
        }
        else if (choice == "4") {
            clear_screen(state.auto_clear);
            edit_exit_delay(state);
        }
        else if (choice == "5") {
            clear_screen(state.auto_clear);
            edit_intro_type(state);
        }
        else if (choice == "0") {
            clear_screen(state.auto_clear);
            toggle_auto_clear(state);
        }
        else if (choice == "9") {
            in_settings = false;
        }
        else {
            std::cout << Color::red << "\n\tНеизвестная команда." << Color::yellow << "\n\tВозврат в меню настроек...\n" << Color::reset;
        }
    }
}

void show_help_classic() {
    std::cout << Color::white
        << "\n\t\t| (1) Подробности о Классической игре |\n\n"
        << "\t\tЭто основной режим Игры. Его геймплей заключается в следующем:\n"
        << "\t\tна каждом уровне вы выбираете цифру \"0\" или \"1\", и если ваш ответ\n"
        << "\t\tсовпадает с цифрой, которая случайно выбрана компьютером, то\n"
        << "\t\tуровень считается верным, то есть выигранным.\n"
        << "\t\tЕсли ответ не совпадает с случайным числом, то уровень считается\n"
        << "\t\tпроигранным.\n\n"
        << "\t\tВ конце каждой игры выводятся итоги игры, которые, исходя из количества\n"
        << "\t\tверных и неверных ответов, засчитывают игроку:\n"
        << "\t\t- \"ПОБЕДУ\" - если количество верных уровней больше, чем неверных;\n"
        << "\t\t- \"НИЧЬЮ\" - если количество верных равно количеству неверных;\n"
        << "\t\t- \"ПОРАЖЕНИЕ\" - если неверных уровней больше, чем верных.\n\n"
        << "\t\tЭти данные сохраняются и учитываются в блоках \"Статистика\" и \"Достижения\".\n"
        << "\t\tКоличество уровней можно изменить в Настройках Игры.\n"
        << "\t\tПодробнее об этом вы можете прочитать в соседних разделах Справки:\n"
        << "\t\t\"Подробности о Настройках\", \"Подробности о Статистике\" и \"Подробности о Достижениях\".\n";
    wait_continue();
}

void show_help_all_or_nothing() {
    std::cout << Color::white
        << "\n\t\t| (2) Подробности о режиме \"" << Color::cyan << "Всё или ничего\"" << Color::reset << " |\n\n"
        << "\t\tЭто режим Игры, в котором вам предстоит выбрать одну цифру\n"
        << "\t\t\"0\" или \"1\", и она будет автоматически введена во все уровни.\n"
        << "\t\tЕсли ваш ответ совпадает со случайным числом компьютера — уровень выигран.\n"
        << "\t\tИначе — проигран.\n\n"
        << "\t\tВсе уровни отображаются таблицей:\n"
        << "\t\t- \"№ Ур.\" — номер уровня;\n"
        << "\t\t- \"Ваш.Ч.\" — ваше число;\n"
        << "\t\t- \"Сл.Ч.\" — число компьютера;\n"
        << "\t\t- \"+/-\" — \"+\" при совпадении, \"-\" — при несовпадении.\n\n"
        << "\t\tИтоги такие же, как в Классике.\n"
        << "\t\tДанные сохраняются в \"Статистику\" и \"Достижения\".\n"
        << "\t\tКоличество уровней — в Настройках.\n";
    wait_continue();
}

void show_help_lives() {
    std::cout << Color::white
        << "\n\t\t| (3) Подробности о режиме Игры \"" << Color::red << "ЖИЗНИ" << Color::reset << "\" |\n\n"
        << "\t\tЭто режим, сходный с \"Классическим\", но с ограничением по здоровью.\n"
        << "\t\tПри верном ответе здоровье не меняется, при неверном — уменьшается на 1.\n"
        << "\t\tИгра заканчивается, когда здоровье = 0 или достигнут лимит уровней.\n\n"
        << "\t\tПравила — как в \"Классике\".\n"
        << "\t\tКоличество здоровья — в Настройках.\n";
    wait_continue();
}

void show_help_hints() {
    std::cout << Color::white
        << "\n\t\t| (4) Подробности о режиме Игры \"" << Color::yellow << "С подсказками" << Color::reset << "\" |\n\n"
        << "\t\tЭтот режим похож на \"Классический\", но раз в N уровней\n"
        << "\t\tпоказывается случайное число ДО вашего ввода — это подсказка!\n"
        << "\t\tЧастота подсказок настраивается в Настройках Игры.\n\n"
        << "\t\tОстальные правила — как в \"Классике\".\n";
    wait_continue();
}

void show_help_errors() {
    std::cout << Color::white
        << "\n\t\t| (5) Подробности " << Color::red << "об ошибках" << Color::reset << " при запуске Игры |\n\n"
        << "\t\tСообщения \"ФАЙЛ СОХРАНЕНИЙ НЕ ОБНАРУЖЕН!\" означают,\n"
        << "\t\tчто файл \"save_data.txt\" отсутствует в папке с программой.\n\n"
        << "\t\tРешение:\n"
        << "\t\t1) Убедитесь, что папка с игрой распакована полностью.\n"
        << "\t\t2) Проверьте наличие файла \"save_data.txt\" рядом с .exe.\n";
    wait_continue();
}

void show_help_settings() {
    std::cout << Color::white
        << "\n\t\t| (6) Подробности о Настройках Игры |\n\n"
        << "\t\tВ Настройках можно изменить:\n"
        << "\t\t- количество уровней,\n"
        << "\t\t- частоту подсказок,\n"
        << "\t\t- здоровье (для режима \"ЖИЗНИ\"),\n"
        << "\t\t- время выхода (в секундах),\n"
        << "\t\t- тип заставки (1, 2, 3),\n"
        << "\t\t- автоочистку экрана (вкл/выкл).\n\n"
        << "\t\tТакже доступен блок работы с сохранениями.\n"
        << "\t\tНевозможно ввести недопустимые значения — система защитит вас.\n";
    wait_continue();
}

void show_help_stats() {
    std::cout << Color::white
        << "\n\t\t| (7) Подробности о Статистике |\n\n"
        << "\t\tЗдесь отображаются:\n"
        << "\t\t- количество побед,\n"
        << "\t\t- поражений,\n"
        << "\t\t- ничьих.\n\n"
        << "\t\tСтатистика учитывает все режимы и сохраняется между сессиями.\n";
    wait_continue();
}

void show_help_achievements() {
    std::cout << Color::white
        << "\n\t\t| (8) Подробности о " << Color::blue << "Достижениях" << Color::reset << " |\n\n"
        << "\t\tДостижения разделены на типы:\n"
        << "\t\t- \"ОБЫКНОВЕННЫЕ\": за победы, ничьи, запуски.\n"
        << "\t\t- \"НЕСТАНДАРТНЫЕ\": за взаимодействие с настройками.\n"
        << "\t\t- \"РЕДКИЕ\": связаны с пасхалками.\n\n"
        << "\t\tОтдельное достижение \"КОДЕР\" — для тех, кто найдёт\n"
        << "\t\tи исправит \"hello_world\" в коде игры.\n";
    wait_continue();
}

void show_help_author() {
    std::cout << Color::white
        << "\n\t\t| (9) Подробности о блоке \"От автора\" |\n\n"
        << "\t\tЗдесь — напутствие от автора и скрытые пасхалки.\n"
        << "\t\tДальше — ищите сами :)\n";
    wait_continue();
}

void show_help_exit() {
    std::cout << Color::white
        << "\n\t\t| (0) Подробности о выходе из Игры |\n\n"
        << "\t\tПри выборе \"0\" в главном меню запускается\n"
        << "\t\tобратный отсчёт (время настраивается в Настройках).\n"
        << "\t\tПрограмма закроется автоматически.\n";
    wait_continue();
}

void show_help_saves() {
    std::cout << Color::white
        << "\n\t\t| (11) Подробности о сохранениях Игры |\n\n"
        << "\t\tВ блоке сохранений можно:\n"
        << "\t\t- \"1\": сохранить текущий прогресс,\n"
        << "\t\t- \"2\": загрузить прогресс,\n"
        << "\t\t- \"3\": сбросить сохранение к значениям по умолчанию.\n\n"
        << "\t\tДоступ — через главное меню (\"11\") или Настройки.\n";
    wait_continue();
}

// --- Главное меню справки ---
void show_help(GameState& state) {
    clear_screen(state.auto_clear);
    std::cout << Color::green
        << "\n\t\t---/===/\tСПРАВКА  \t\\===\\---\n" << Color::reset
        << "\n\tВас приветствует справка по Игре \"0/1 Step\"!\n\n"
        << "\tПодробности о:\n"
        << "\t+->\"1\" - \"Классической игре\"\n"
        << "\t+->\"2\" - режиме \"Всё или ничего\"\n"
        << "\t+->\"3\" - режиме \"ЖИЗНИ\"\n"
        << "\t+->\"4\" - режиме Игры \"С подсказками\"\n"
        << "\t+->\"5\" - ошибках при запуске Игры\n"
        << "\t+->\"6\" - Настройках\n"
        << "\t+->\"7\" - Статистике\n"
        << "\t+->\"8\" - Достижениях\n"
        << "\t+=>\"9\" - блоке \"От автора\"\n"
        << "\t+->\"0\" - выходе из Игры\n"
        << "\t-->\"11\" - сохранениях Игры\n"
        << Color::yellow
        << "\n\t*Все остальные команды возвращают в Главное меню\n"
        << "\n\tО каком разделе вы хотите узнать подробности? >> " << Color::reset;

    std::string choice;
    std::getline(std::cin, choice);
    clear_screen(state.auto_clear);
    if (choice == "1") show_help_classic() ;
    else if (choice == "2") show_help_all_or_nothing();
    else if (choice == "3") show_help_lives();
    else if (choice == "4") show_help_hints();
    else if (choice == "5") show_help_errors();
    else if (choice == "6") show_help_settings();
    else if (choice == "7") show_help_stats();
    else if (choice == "8") show_help_achievements();
    else if (choice == "9") show_help_author();
    else if (choice == "0") show_help_exit();
    else if (choice == "11") show_help_saves();
    else {
        // Возврат в главное меню (просто выход из функции)
        return;
    }

    // После просмотра подраздела — возвращаемся в главное меню справки
    show_help(state);
}

void show_stats(const GameState& state) {
    std::cout << Color::white
        << "\n\t---/===/ СТАТИСТИКА \\===\\---\n" << Color::green
        << "\t\t |ПОБЕД:" << state.win_count << "\n" << Color::yellow
        << "\t\t |ВНИЧЬЮ:" << state.draw_count << "\n" << Color::red
        << "\t\t |ПОРАЖЕНИЙ:" << state.loss_count << "\n" << Color::reset
        << "\t\t |\n"
        << "\t\t 'ЗАПУСКОВ ПРОГРАММЫ:" << state.launch_count << "\n"
        << Color::yellow
        << "\n\tНажмите Enter, чтобы продолжить... " << Color::reset;
    std::cin.get();
}

void show_achievements_menu(const GameState& state) {
    std::cout << Color::white
        << "\n\t---/===/    " << Color::blue << "ДОСТИЖЕНИЯ" << Color::reset << "    \\===\\---\n"
        << "\n\tВ этом разделе вы можете увидеть свои достижения.\n"
        << "\tОни разделены на категории:\n";

    std::cout << Color::cyan << "\n\tОБЫКНОВЕННЫЕ:\n" << Color::reset;
    std::cout << "\t  " << (state.achievements.size() > 0 && state.achievements[0] ? "[+]" : "[ ]")
        << " Изменение настроек\n";
    std::cout << "\t  " << (state.achievements.size() > 1 && state.achievements[1] ? "[+]" : "[ ]")
        << " Альфа-логотип\n";
    std::cout << "\t  " << (state.achievements.size() > 2 && state.achievements[2] ? "[+]" : "[ ]")
        << " Большая заставка\n";

    std::cout << Color::green << "\n\tНЕСТАНДАРТНЫЕ:\n" << Color::reset;
    std::cout << "\t  " << (state.achievements.size() > 3 && state.achievements[3] ? "[+]" : "[ ]")
        << " Отключил очистку\n";
    std::cout << "\t  " << (state.achievements.size() > 4 && state.achievements[4] ? "[+]" : "[ ]")
        << " Вернул очистку\n";
    std::cout << "\t  " << (state.achievements.size() > 5 && state.achievements[5] ? "[+]" : "[ ]")
        << " Прочитал \"От автора\"\n";
    std::cout << "\t  " << (state.achievements.size() > 6 && state.achievements[6] ? "[+]" : "[ ]")
        << " Заходил в сохранения\n";

    std::cout << Color::blue << "\n\tРЕДКИЕ:\n" << Color::reset;
    std::cout << "\t  " << (state.achievements.size() > 7 && state.achievements[7] ? "[+]" : "[ ]")
        << " Микро-пасхалка ("")\n";
    std::cout << "\t  " << (state.achievements.size() > 8 && state.achievements[8] ? "[+]" : "[ ]")
        << " Ввёл \"10\" в меню\n";
    std::cout << "\t  " << (state.achievements.size() > 9 && state.achievements[9] ? "[+]" : "[ ]")
        << " Открыл ссылку логотипа\n";
    std::cout << "\t  " << (state.achievements.size() > 10 && state.achievements[10] ? "[+]" : "[ ]")
        << " Альтернативный логотип\n";

    wait_continue();
}

void show_credits(GameState& state) {
    clear_screen(state.auto_clear);

    // Разблокируем достижение "Прочитал От автора"
    if (state.achievements.size() > 5) {
        state.achievements[5] = true;
    }

    std::cout << Color::white
        << "\n\t\t---/===/ От автора \\===\\---\n"
        << "\n\t\t     Здравствуй, игрок!\n\n"
        << "\tБлагодарю тебя за запуск 0/1 Step и блока \"От автора\".\n"
        << "\tВ этом окошке я в одностороннем порядке желаю тебе удачной игры.\n\n"
        << "\t(PS: попробуй ввести \"10\" в главном меню ;)\n"
        << Color::yellow
        << "\n\t>> " << Color::reset;

    std::string input;
    std::getline(std::cin, input);

    // Пасхалка: если ввели "10" здесь
    if (input == "10") {
        std::cout << Color::green << "\tДа не здесь! (^-^" << Color::cyan << "\"" << Color::green << ")" << Color::reset << "\n";
        // Разблокируем достижение "Ввёл 10 в меню От автора"
        if (state.achievements.size() > 8) {
            state.achievements[8] = true;
        }
        wait_continue();
    }
}
