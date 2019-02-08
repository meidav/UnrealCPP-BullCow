/*
  main.cpp
  BullCowGame

  Created by Arbel Meidav on 2/1/19.
  Copyright © 2019 Arbel Industries. All rights reserved.

*/
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// making syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText UserGuess);
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// entry point for application
int main()
{
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        PrintGameSummary();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    return 0;
}

void PrintIntro()
{
    std::cout << "\n\n";
    std::cout << "        db         db  \n";
    std::cout << "      d88           88  \n";
    std::cout << "     888            888  \n";
    std::cout << "    d88             888b  \n";
    std::cout << "    888             d88P  \n";
    std::cout << "    Y888b  /``````\\8888  \n";
    std::cout << "  ,----Y888        Y88P`````\\  \n";
    std::cout << "  |        ,'`\\_/``\\ |,,    |  \n";
    std::cout << "  \\,,,,-| | o | o / |```,,,/'  \n";
    std::cout << "        |  ''''''''' |  \n";
    std::cout << "       /             \\  \n";
    std::cout << "      |               \\  \n";
    std::cout << "      |  ,,,,----'''```|  \n";
    std::cout << "      |``   @    @     |  \n";
    std::cout << "      \\,,    ___    ,,/  \n";
    std::cout << "         \\__|   |__/  \n";
    std::cout << "            | | |  \n";
    std::cout << "            \\_|_/  \n\n";
    std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n\n";
    std::cout << "A Bull means you got the right letter in the right place.\n";
    std::cout << "A Cow means you got the right letter but it is in the wrong place.\n\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << "\nNote: An isogram is a word with no repeating letters, e.g. dog, cat, plant, etc. \n";
    std::cout << std::endl;
    return;
}

// plays a single game to completion
void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // loop while game is not won and there are Tries remaining
    
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
        
    }
    return;
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon()) {
        std::cout << "You won!! You must be one smart cookie.\n\n";
    } else {
        std::cout << "You have run out of guesses. Better luck next time.\n\n";
    }
    return;
}

// get a guess from the player, looping until the player provides a valid guess
FText GetValidGuess()
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid;
    do
    {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please make sure you only enter lower case letters.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Uh oh, you repeated a letter - that's not an Isogram. Please enter a word without repeating letters.\n\n";
                break;
            default:
                // assume guess is valid
                break;
        }
        
    } while (Status != EGuessStatus::OK);
    
    return Guess;
}

// repeat the guess back to them
void PrintGuess(FText UserGuess)
{
    std::cout << "You guessed: " << UserGuess << std::endl;
    return;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}
