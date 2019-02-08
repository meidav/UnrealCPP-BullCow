/*
  FBullCowGame.hpp
  BullCowGame

  Created by Arbel Meidav on 2/2/19.
  Copyright © 2019 Arbel Industries. All rights reserved.

  Game logic. No view code or direct user interaction
*/
#pragma once
#include <string>
#include <map>

// making syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
    
};

class FBullCowGame
{
public:
    FBullCowGame(); // constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmitValidGuess(FString);
    
private:
    // initialized in constructor
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

