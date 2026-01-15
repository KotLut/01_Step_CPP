# 🎮 0/1 Step — Игра на удачу и интуицию (RU)

> **«Угадай, что выбрал компьютер: 0 или 1?»**  
> Минималистичная, но глубокая текстовая игра с несколькими режимами, настройками, достижениями и пасхалками.  
> Написана на **C++** с использованием современных практик и без внешних зависимостей.

![game_alpha_logo](https://raw.githubusercontent.com/KotLut/01_Step_CPP/refs/heads/main/01_Step_alpha-logo.png)

---

## 📦 Версия
**0.1-beta** — первая публичная бета-версия

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
  - **Обычные** — за игру и победы
  - **Нестандартные** — за взаимодействие с настройками
  - **Редкие** — за пасхалки и секреты

### 🎁 Секреты и пасхалки
- Ввод `"10"` в главном меню → логотип автора + ссылка на игру
- Пустой ввод в меню → микро-пасхалка
- **Праздничный эвент** (пункт `12`) — анимированная ёлка с движущимися разноцветными шариками!

### 📚 Справка
Полноценная многоуровневая справка с описанием всех режимов, настроек, ошибок и сохранений.

---

## 🛠 Технические детали

- **Язык**: C++17
- **Случайность**: `std::mt19937` + `std::random_device` (высокое качество)
- **Цвета**: ANSI-коды (`white`, `green`, `yellow`, `red`, `blue`, `cyan`, `brown`)
- **Безопасность**: валидация ввода, защита от некорректных значений
- **Архитектура**: модульная, «пельменный код» — каждый файл решает одну задачу
- **Поддержка UTF-8** в консоли Windows


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
- IDE: **Visual Studio Community 2022** (или новее)

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

---

# 🎮 0/1 Step — A game of luck and intuition (EN)

> **"Guess what the computer chose: 0 or 1?"**  
> A minimalistic but deep text game with multiple modes, settings, achievements and Easter eggs.  
> Written in **C++** using modern practices and without external dependencies.

![game_alpha_logo](https://raw.githubusercontent.com/KotLut/01_Step_CPP/refs/heads/main/01_Step_alpha-logo.png)

---

## 📦 Version
**0.1-beta** — the first public beta version

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
  - **Ordinary** — for playing and winning
- **Non—standard** - for interacting with settings
— **Rare** - for Easter eggs and secrets

### 🎁 Secrets and Easter eggs
- Enter `"10"` in the main menu → author's logo + link to the game
- Empty menu entry → micro Easter egg
- **Festive event** (item `12`) — animated Christmas tree with moving colorful balls!

### 📚 Help
A full-fledged multi-level help with descriptions of all modes, settings, errors, and saves.

---

## 🛠 Technical Details

- **Language**: C++17
- **Randomness**: `std::mt19937` + `std::random_device` (high quality)
- **Colors**: ANSI codes (`white`, `green`, `yellow`, `red`, `blue`, `cyan`, `brown`)
- **Security**: input validation, protection against incorrect values
- **Architecture**: modular, "dumpling code" — each file solves one task
- **UTF-8 support** in Windows console


---


## ▶️ How to launch

## Option 1: Download the finished game (recommended)

1. Go to the **[Releases] section(https://github.com/KotLut/01_Step_CPP/releases )**.
2. Download the file **`01_Step.exe `**
4. Run the file.

> 💡 The file will be automatically created at the first launch `save_data.txt ` — It stores your settings, stats, and achievements.

---
### 🔧 Option 2: Build from source code

#### Requirements
- OS: **Windows**
- IDE: **Visual Studio Community 2022** (or later)

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

 The source code is entirely in Russian and uses UTF-8. All files are saved from the BOM to work correctly in Visual Studio.
