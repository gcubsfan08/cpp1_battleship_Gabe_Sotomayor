#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"
#include <iostream>
#include <list>
using namespace std;

class BaseGame {
protected:
    Board* board;
    virtual int solve() = 0;
public:
    BaseGame();
    ~BaseGame();
    int run();
};


class ControlGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (this->board->guess(i, j) == ResponseType::HIT)
                {
                    hits += 1;
                }
            }
        }
        return hits;
    }
};

class AssignmentGame : public BaseGame {
protected:
    //Guess Struct
    struct Guess
    {
        int x;
        int y;
    };
    //Different lists for keeping track of guesses
    list<Guess> guesses;
    list<Guess> rightGuesses;
    list<Guess> wrongGuesses;
    int solve() override
    {
        //IMPLEMENT YOUR SEARCH ALGRORITHM HERE
        int hits = 0;
        while (hits <= SHIP_COUNT)
        {
            //Initializing a random guess
            int randomGuessX = 1 + (rand() % 100);
            int randomGuessY = 1 + (rand() % 100);

            //ResponseType randomResponse = ;
            Guess randomGuess;
            randomGuess.x = randomGuessX;
            randomGuess.y = randomGuessY;

            //Evaluating the random guess
            if (this->board->guess(randomGuessX, randomGuessY) == ResponseType::HIT)
            {
                rightGuesses.push_back(randomGuess);
                hits += 1;
            }
            else if (this->board->guess(randomGuessX, randomGuessY) == ResponseType::NEARMISS)
            {

                if (TestLogicalGuess(randomGuessX + 1, randomGuessY) && AnotherGuess(randomGuessX + 1, randomGuessY))
                {
                    Guess guessCurrent;
                    guessCurrent.x = randomGuessX + 1;
                    guessCurrent.y = randomGuessY;
                    rightGuesses.push_back(guessCurrent);
                    hits += 1;
                }
                else if (TestLogicalGuess(randomGuessX - 1, randomGuessY) && AnotherGuess(randomGuessX - 1, randomGuessY))
                {
                    Guess guessCurrent;
                    guessCurrent.x = randomGuessX - 1;
                    guessCurrent.y = randomGuessY;
                    rightGuesses.push_back(guessCurrent);
                    hits += 1;
                }
                else if (TestLogicalGuess(randomGuessX, randomGuessY + 1) && AnotherGuess(randomGuessX, randomGuessY + 1))
                {
                    Guess guessCurrent;
                    guessCurrent.x = randomGuessX;
                    guessCurrent.y = randomGuessY + 1;
                    rightGuesses.push_back(guessCurrent);
                    hits += 1;
                }
                else if (TestLogicalGuess(randomGuessX, randomGuessY - 1) && AnotherGuess(randomGuessX, randomGuessY - 1))
                {
                    Guess guessCurrent;
                    guessCurrent.x = randomGuessX;
                    guessCurrent.y = randomGuessY - 1;
                    rightGuesses.push_back(guessCurrent);
                    hits += 1;
                }
            }
            else if (this->board->guess(randomGuessX, randomGuessY) == ResponseType::MISS)
            {
                wrongGuesses.push_back(randomGuess);
            }
        }
        //Test for solve method to return SHIP_COUNT
        return SHIP_COUNT;
    }
    bool TestPreviouslyGuessed(int x, int y)
    {
        bool success = true;
        for (Guess g : rightGuesses)
        {
            if (g.x == x && g.y == y)
            {
                success = false;
            }
        }
        for (Guess g : wrongGuesses)
        {
            if (g.x == x && g.y == y)
            {
                success = false;
            }
        }
        return success;
    }
    bool AnotherGuess(int x, int y)
    {
        bool success = false;
        if (this->board->guess(x, y) == ResponseType::HIT)
        {
            success = true;
        }
        return success;
    }
    bool TestLogicalGuess(int x, int y)
    {
        bool success = false;
        if (x <= WIDTH && y <= HEIGHT)
        {
            success = true;
        }
        return success;
    }
};


#endif /* GAME_H */
