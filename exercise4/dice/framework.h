//
// Created by swaggan on 15.06.21.
//

#ifndef EXERCISE4_FRAMEWORK_H

#include <iostream>
#include <utility>
#include <vector>
#include <ctime>
#include <memory>

namespace Games {

    class Player {
    public:
        explicit Player(std::string name) {
            this->score = 0;
            this->name = std::move(name);
        }

        std::string name;

        void incrementScore(int by) {
            score += by;
        }

        void incrementScore() {
            incrementScore(1);
        }

        void printScore() const {
            std::cout << name << ": " << score << std::endl;
        }

    private:
        int score;
    };

    class Dice {
    public:
        explicit Dice() {
            min = 1;
            max = 6;
            std::srand(time(0));
        }

        explicit Dice(int minVal, int maxVal) {
            min = minVal;
            max = maxVal;
        }

        [[nodiscard]] int roll() const {
            return rand() % (max - min + 1) + min;
        }

    private:
        int min, max;
    };

    /**
     * Abstract super-class for n Player games with m dices.
     */
    class AbstractGame {
    public:
        /**
         * Play a single round of the game.
         */
        virtual void playRound() = 0;

        /**
         * Display the result of the game somehow.s
         */
        void displayResult() {
            for (const auto &player : players) {
                player->printScore();
            }
        }

        virtual void play(int rounds) {
            for (int i = 1; i <= rounds; i++) {
                playRound();
            }
        }

    protected:
        std::vector<std::unique_ptr<Player>> players;
        std::vector<Dice> dices;

        AbstractGame(std::vector<std::unique_ptr<Player>> players,
                     std::vector<Dice> dices) {
            this->dices = std::move(dices);
            this->players = std::move(players);
        }
    };

} // namespace Games






#define EXERCISE4_FRAMEWORK_H

#endif //EXERCISE4_FRAMEWORK_H
