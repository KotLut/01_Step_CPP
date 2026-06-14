[![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-0078D7.svg)](https://www.microsoft.com/windows)
![Terminal](https://img.shields.io/badge/Interface-Console-333333?logo=terminal&logoColor=white)
[![Release](https://img.shields.io/github/v/release/KotLut/01_Step_CPP?include_prereleases&color=green)](https://github.com/KotLut/01_Step_CPP/releases)
[![License: MIT](https://img.shields.io/badge/License-MIT-777777.svg)](LICENSE)
[![Contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg)](CONTRIBUTING.md)

# 🎮 0/1 Step — Игра на удачу и интуицию (RU)

> **«Угадай, что выбрал компьютер: 0 или 1?»**  
> Минималистичная, но глубокая текстовая игра с несколькими режимами, настройками, достижениями и пасхалками.  
> Написана на **C++** с использованием современных практик и без внешних зависимостей.

![game_alpha_logo](https://raw.githubusercontent.com/KotLut/01_Step_CPP/main/01_Step_alpha-logo.png)

---

## 📦 Версия
**2-beta** — вторая публичная бета-версия

---

## 🌟 Особенности

### 🎯 Игровые режимы
- **Классический** — угадывай 0/1 на каждом уровне.
- **«Всё или ничего»** — одно число на все уровни, результат в виде таблицы.
- **«ЖИЗНИ»** — ограниченное здоровье; ошибка = потеря жизни.
- **«С подсказками»** — раз в N уровней видишь правильный ответ заранее.

### ⚙️ Настройки
- Количество уровней (с защитой от слишком больших значений)
- Здоровье (для режима «ЖИЗНИ»)
- Частота подсказок
- Время выхода из программы (с обратным отсчётом)
- Тип заставки: Альфа / Большая / Базовая
- Автоочистка экрана (вкл/выкл)

### 🏆 Система прогресса
- **Статистика**: победы, ничьи, поражения, количество запусков
- **15 достижений**, разделённых на категории:
  - **Обычные**
  - **Нестандартные**
  - **Редкие**

### 🎁 Секреты и пасхалки
- Ввод `"10"` в главном меню → логотип автора + ссылка на игру
- Пустой ввод в меню → микро-пасхалка
- **Праздничный эвент** (пункт `12`) — анимированная ёлка с движущимися разноцветными шариками!

### 📚 Справка
Полноценная многоуровневая справка с описанием всех режимов, настроек, ошибок и сохранений.

---

## 🛠 Технические детали

- **Язык**: C++17
- **Случайность**: `std::mt19937` + `std::random_device`
- **Цвета**: ANSI-коды (`white`, `green`, `yellow`, `red`, `blue`, `cyan`, `brown`)
- **Безопасность**: валидация ввода, защита от некорректных значений
- **Архитектура**: модульная, каждый файл отвечает за отдельную подсистему
- **Поддержка UTF-8** в консоли Windows


---

## 🏗 Архитектура и ООП

Проект реализован с соблюдением принципов объектно-ориентированного программирования:

### 📦 Собственные структуры данных
- **`CustomBoolArray`** — динамический массив `bool`, реализованный вручную (вместо `std::vector<bool>`).
  - Управление памятью инкапсулировано в классе (конструктор/деструктор)
  - Инкапсуляция: приватный указатель `bool* data_`, публичные методы `get()`, `set()`
  - Запрет копирования через `= delete` для предотвращения утечек
  - Соответствует требованию задания: *"Реализация структур данных — собственная!"*

### 🧱 Модульная структура
| Файл | Ответственность |
|------|----------------|
| `main.cpp` | Точка входа в приложение |
| `Engine.h/.cpp` | Класс `GameSession`: состояние игры, сохранения, достижения |
| `UI.h/.cpp` | Консольный интерфейс, меню, подразделы меню |
| `GameMode.h/.cpp` | Базовый класс режимов + 4 режима (Классика, Всё/Ничего, Жизни, Подсказки) |
| `logos.h` | заставки и логотипы |

### ⚠ Обработка исключений
- Класс-исключение `GameExitRequested` для корректного прерывания игры
- Валидация ввода через `InputValidator::getInt()` с повторным запросом
- Защита от некорректных файлов сохранения (автосоздание обычного сохранения)

---


## ▶️ Как запустить

### 📥 Вариант 1: Скачать готовую игру (рекомендуется)

1. Перейдите в раздел **[Releases](https://github.com/KotLut/01_Step_CPP/releases)**.
2. Скачайте файл **`01_Step.exe`**
4. Запустите файл.

> 💡 При первом запуске автоматически создастся файл `save_data.txt` — в нём хранятся ваши настройки, статистика и достижения.

---
### 🔧 Вариант 2: Собрать из исходного кода

#### Требования
- ОС: **Windows**
- Компилятор, поддерживающий **C++17**
- (Опционально) Любая IDE или редактор кода

#### Инструкция
1. Склонируйте репозиторий:
   ```bash
   git clone https://github.com/KotLut/01_Step_CPP.git
   ```
2. Откройте файл **`01-Step.slnx`** в Visual Studio.
3. Вверху выберите конфигурацию:  
   **Platform: x64** → **Configuration: Release**
4. Нажмите **«Сборка → Собрать решение»** (или `Ctrl+Shift+B`).
5. После сборки запустите игру непосредственно в Visual Studio или из папки:  
   `01-Step\x64\Release\01-Step.exe`

> 💡 Исходный код полностью на русском языке и использует UTF-8. Все файлы сохранены с BOM для корректной работы в Visual Studio.

## 📜 Лицензия
Этот проект распространяется под лицензией [MIT](LICENSE).

## 🤝 Как внести вклад
Хотите помочь проекту? Ознакомьтесь с нашим [руководством по вкладу](CONTRIBUTING.md).

## 💬 Обсуждения
Есть идея, вопрос или просто хотите пообщаться?  
Присоединяйтесь к [Discussions](https://github.com/KotLut/01_Step_CPP/discussions)!

---

## 🚀 Дорожная карта

- [x] Основной игровой процесс
- [x] Система сохранения
- [x] Достижения
- [ ] Дополнительные игровые режимы
- [ ] Улучшения локализации
- [ ] Полная поддержка Linux

---

# 🎮 0/1 Step — A game of luck and intuition (EN)

> **"Guess what the computer chose: 0 or 1?"**  
> A minimalistic but deep text game with multiple modes, settings, achievements and Easter eggs.  
> Written in **C++** using modern practices and without external dependencies.

![game_alpha_logo](https://raw.githubusercontent.com/KotLut/01_Step_CPP/main/01_Step_alpha-logo.png)

---

## 📦 Version
**2-beta** — second public beta version

---

## 🌟 Features

### 🎯 Game modes
- **Classic** — Guess 0/1 on each level.
- **"All or nothing"** — one number for all levels, the result is in the form of a table.
- **"LIFE"** — limited health; error = loss of life.
- **"With hints"** — once in N levels you see the correct answer in advance.

### ⚙️ Settings
- Number of levels (with protection against too high values)
- Health (for the "LIFE" mode)
- Frequency of prompts
- Program exit time (with countdown)
- Splash screen type: Alpha / Large / Basic
- Auto screen cleaning (on/off)

### 🏆 Progress system
- **Statistics**: wins, draws, losses, number of runs
- **15 achievements**, divided into categories:
  - **Common**
  - **Unusual**
  - **Rare**

### 🎁 Secrets and Easter eggs
- Enter `"10"` in the main menu → author's logo + link to the game
- Empty menu entry → micro Easter egg
- **Festive event** (item `12`) — animated Christmas tree with moving colorful balls!

### 📚 Help
A full-fledged multi-level help with descriptions of all modes, settings, errors, and saves.

---

## 🛠 Technical Details

- **Language**: C++17
- **Randomness**: `std::mt19937` + `std::random_device`
- **Colors**: ANSI codes (`white`, `green`, `yellow`, `red`, `blue`, `cyan`, `brown`)
- **Security**: input validation, protection against incorrect values
- **Architecture**: modular, each file is responsible for a separate subsystem
- **UTF-8 support** in Windows console

---

# 🏗 Architecture and OOP

The project was implemented in compliance with the principles of object-oriented programming:

### 📦 Proprietary data structures
- CustomBoolArray is a manually implemented dynamic `bool` array
- Memory management via `new[]`/`delete[]` (RAII)
- Encapsulation: private pointer `bool* data_`, public methods `get()`, `set()`
- Prohibition of copying via `= delete` to prevent leaks
- Meets the requirement of the assignment: * "The implementation of data structures is proprietary!"*

### 🧱 Modular structure
| File | Responsibility |
|------|----------------|
| `main.cpp` | Application Entry point |
| `Engine.h/.cpp` | 'GameSession` class: game status, saves, achievements |
| `UI.h/.cpp` | Console interface, menus, menu subsections |
| `GameMode.h/.cpp ` | Basic class of modes + 4 modes (Classic, All/Nothing, Life, Hints) |
| `logos.h` | screensavers and logos |

### ⚠ Exception handling
-The `GameExitRequested` exception class for correctly interrupting the game
- Input validation via `InputValidator::getInt()` with a repeat request
- Protection against incorrect save files (auto-create normal save)

---


## ▶️ How to launch

## Option 1: Download the finished game (recommended)

1. Go to the **[Releases](https://github.com/KotLut/01_Step_CPP/releases)**.
2. Download the file **`01_Step.exe `**
4. Run the file.

> 💡 The file will be automatically created at the first launch `save_data.txt ` — It stores your settings, stats, and achievements.

---
### 🔧 Option 2: Build from source code

#### Requirements
- OS: **Windows**
- A compiler that supports **C++17**
- (Optional) Any IDE or code editor

#### Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/KotLut/01_Step_CPP.git
   ```
2. Open the **`01-Step.slnx`** file in Visual Studio.
3. At the top, select the configuration:
**Platform: x64** → **Configuration: Release**
4. Click **"Build → Assemble Solution"** (or `Ctrl+Shift+B`).
5. After the build, run the game directly in Visual Studio or from the folder:
`01-Step\x64\Release\01-Step.exe `

> 💡 The source code is entirely in Russian and uses UTF-8. All files are saved from the BOM to work correctly in Visual Studio.

## 📜 License
This project is distributed under the [MIT](LICENSE).

## 🤝 How to contribute
Do you want to help the project? Check out our [contribution guide](CONTRIBUTING.md).

## 💬 Discussions
Do you have an idea, a question, or just want to chat?  
Join the [Discussions](https://github.com/KotLut/01_Step_CPP/discussions)!

---

## 🚀 Roadmap

- [x] Core gameplay
- [x] Save system
- [x] Achievements
- [ ] Additional game modes
- [ ] Localization improvements
- [ ] Linux full support
