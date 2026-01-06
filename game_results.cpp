#include "game_results.h"
#include <iostream>
#include "color.h"

void show_game_results(GameState& state, int correct, int incorrect) {
    std::cout << Color::white << "\n\t---===/ ÈÒÎÃÈ ÈÃĞÛ \\===---\n";
    std::cout << "\n\t    ÂÅĞÍÛÕ ÎÒÂÅÒÎÂ: " << correct << "\n";
    std::cout << "\t  ÍÅÂÅĞÍÛÕ ÎÒÂÅÒÎÂ: " << incorrect << "\n";
    std::cout << "\n\t  ÏÎÒÎÌÓ" << Color::reset;

    if (correct == incorrect) {
        std::cout << Color::yellow << " --> ÍÈ×Üß\t:|\n" << Color::reset;
        state.draw_count += 1;
    }
    else if (correct > incorrect) {
        std::cout << Color::green << " --> ÏÎÁÅÄÀ!\t:)\n" << Color::reset;
        state.win_count += 1;
    }
    else {
        std::cout << Color::red << " --> ÏÎĞÀÆÅÍÈÅ\t:(\n" << Color::reset;
        state.loss_count += 1;
    }

    std::cout << Color::yellow << "\n\tÍàæìèòå Enter, ÷òîáû ïğîäîëæèòü... " << Color::reset;
    std::cin.get();
}