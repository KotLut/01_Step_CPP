#pragma once

#include "Engine.h"
#include "UI.h"



// Базовый класс для всех игровых режимов
class GameMode {
public:
    virtual ~GameMode() = default;
    virtual void play(GameSession& session) = 0;

protected:
    // Вспомогательный метод, общий для всех режимов
    void updateStats(GameSession& session, int correct, int incorrect);
};


// === Игровые режимы ===
class ClassicMode : public GameMode {
public:
    void play(GameSession& session) override;
};


class AllOrNothingMode : public GameMode {
public:
    void play(GameSession& session) override;
};


class LivesMode : public GameMode {
public:
    void play(GameSession& session) override;
};


class HintsMode : public GameMode {
public:
    void play(GameSession& session) override;
};