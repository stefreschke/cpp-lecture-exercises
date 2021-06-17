
#include <iostream>
#include "framework.h"

using namespace Games;

class MudGame : public AbstractGame {
public:
    explicit MudGame(std::vector<std::unique_ptr<Player>> players) :
            AbstractGame(std::move(players),
                         std::vector<Dice>{Dice(), Dice(), Dice(),
                                           Dice(), Dice()}) {
        // nothing else to do
    }

    /**
     * All players throw each round. If two or five thrown on any dice, no
     * points given. If no two or five thrown, sum of dices added to players
     * score.
     */
    void playRound() override {
        for (auto &player : players) {
            int sumOfDices = 0;
            bool twoOrFiveThrown = false;
            for (auto dice : dices) {
                int rolledNumber = dice.roll();
                sumOfDices += rolledNumber;
                if (rolledNumber == 2 || rolledNumber == 5) {
                    twoOrFiveThrown = true;
                    break;
                }
            }
            if (!twoOrFiveThrown) {
                player->incrementScore(sumOfDices);
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

    MudGame game{std::move(players)};
    game.play(numRounds);
    game.displayResult();
}
