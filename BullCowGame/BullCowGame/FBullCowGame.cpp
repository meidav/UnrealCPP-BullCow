/*
  FBullCowGame.cpp
  BullCowGame

  Created by Arbel Meidav on 2/2/19.
  Copyright © 2019 Arbel Industries. All rights reserved.

*/
#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32) MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "plane"; // this must be an isogram
    
    MyCurrentTry = 1;
    MyHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    
    return;
}

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16}, {7,25} };
    return WordLengthToMaxTries[(int32) MyHiddenWord.length()];
    
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    
    if (!IsIsogram(Guess)) {
        // if guess isn't an isogram
        return EGuessStatus::Not_Isogram;
    } else if (!IsLowercase(Guess)){
        // if guess isn't all lowercase
        return EGuessStatus::Not_Lowercase;
    } else if (Guess.length() != GetHiddenWordLength()) {
        // if guess length is wrong
        return EGuessStatus::Wrong_Length;
    } else {
        return EGuessStatus::OK;
    }
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = (int32) MyHiddenWord.length(); // assuming the hidden word has same length as a guess based on validation
    
    for (int32 i = 0; i < WordLength; i++) {
        for (int32 j = 0; j < WordLength; j++) {
            if (Guess[i] == MyHiddenWord[j]) {
                if (i == j) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    }
    
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }
    
    TMap<char, bool> LetterSeen;
    
    for (auto Letter : Word) {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    for (auto Letter : Word) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
}
