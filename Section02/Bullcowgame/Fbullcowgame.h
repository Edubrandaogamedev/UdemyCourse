/*The game logic (no view or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#include <iostream>
#pragma once


//To make the syntax unreal friendly
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
    int32 Bull = 0;
    int32 Cow = 0;
};

enum class EGuessStatus 
{
    Invalid_Status,
    Not_Isogram,
    Wrong_Length,
    Not_Correct,
    OK
};

class Fbullcowgame 
{
    public:
       // Fbullcowgame(); // constructor
        int32 GetHiddenWordLength(void) const; 
        int32 GetMaxTries(void) const;
        int32 GetCurrentTry(void) const;
        bool IsGameWon(void) const ;
        EGuessStatus CheckGuessValidity(FString) const;
        //A method for couting bulls and cows, and increasing turn number. Assuming valid guess
        FBullCowCount SubmitValidGuess(FString);
        void Reset(void);
    
    
    private:
        int32 MyCurrentTry;
        FString MyHiddenWord;
        FString GetHiddenWord(int32 userchoose) const;
        bool IsIsogram(FString Guess) const;
        bool IsCorrect(FString Guess) const;
        bool bGameIsWon;
        int32 GetUserLengthChoose() const;
       
    
        
};