
#include <iostream>
#include "framework.h"

using namespace Games;

class SevensGame : public AbstractGame {
public:
    explicit SevensGame(std::vector<std::unique_ptr<Player>> players) :
            AbstractGame(std::move(players),
                         std::vector<Dice>{Dice(), Dice()}) {
        // nothing else to do
    }

    /**
     * All players throw each round. If result is 7, score is incremented.
     */
    void playRound() override {
        for (auto &player : players) {
            int sum = 0;
            for (auto dice : dices) {
                sum += dice.roll();
            }
            if (sum == 7) {
                player->incrementScore();
            }
        }
    }
};

int main(int argc, char *argv[]) {
    const auto printUsage = [argv] {
        std::cout << "usage: " << argv[0] << " <num players> <num rounds>"
                  << std::endl;
    };
    if (argc != 3) {
        printUsage();
        return EXIT_FAILURE;
    }

    auto numPlayers = 0;
    auto numRounds = 0;
    try {
        numPlayers = std::stoul(argv[1]);
        numRounds = std::stoul(argv[2]);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        printUsage();
        return EXIT_FAILURE;
    }

    // own code

    std::vector<std::unique_ptr<Player>> players;
    for (int i = 1; i <= numPlayers; i++) {
        players.emplace_back(std::make_unique<Player>(std::to_string(i)));
    }
    SevensGame game{std::move(players)};
    game.play(numRounds);
    game.displayResult();
}
