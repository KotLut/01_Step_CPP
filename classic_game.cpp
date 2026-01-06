#include "classic_game.h"
#include <iostream>
#include <random>
#include "color.h"
#include "input_validation.h"
#include "game_results.h"

void run_classic_game(GameState& state) {
    std::cout << Color::white
        << "\n---/===/    ÊËÀÑÑÈ×ÅÑÊÀß ÈÃÐÀ    \\===\\---\n";

    std::cout << "\tÊîëè÷åñòâî óðîâíåé: " << state.level_count << "\n";
    std::cout << Color::yellow << "\n\t\tÏÎÅÕÀËÈ!\n" << Color::reset;

    int correct_answers = 0;
    int incorrect_answers = 0;

    // Ãåíåðàòîð ñëó÷àéíûõ ÷èñåë (0 èëè 1)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int level = 1; level <= state.level_count; ++level) {
        std::cout << Color::white
            << "\n+---\t-=/ ÓÐÎÂÅÍÜ " << level << " \\=-\t---+\n";

        std::cout << Color::yellow << "\tÂàøå ÷èñëî (0 èëè 1) >> " << Color::reset;
        bool player_choice = get_valid_binary_choice();

        int random_value = dis(gen);
        std::cout << "\tÐàíäîì = \t" << random_value << "\n";

        if ((player_choice && random_value == 1) || (!player_choice && random_value == 0)) {
            std::cout << "\tÂÅÐÍÎ!\t\t+  \n";
            ++correct_answers;
        }
        else {
            std::cout << "\tÍÅÂÅÐÍÎ.\t-  \n";
            ++incorrect_answers;
        }

        std::cout << "+---\t-=\\ ÓÐÎÂÅÍÜ " << level << " /=-\t---+\n";

        std::cout << Color::yellow << "\n\tÍàæìèòå Enter, ÷òîáû ïðîäîëæèòü... " << Color::reset;
        std::cin.get();
    }

    show_game_results(state, correct_answers, incorrect_answers);
}