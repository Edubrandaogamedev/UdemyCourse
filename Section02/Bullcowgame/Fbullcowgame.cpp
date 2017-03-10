#include <iostream>
#include "Fbullcowgame.h"
#include <map>
//To make syntax Unreal friendly
#define TMap std::map 




/*Fbullcowgame::Fbullcowgame()
{
    Reset();
    
}*/


int32 Fbullcowgame::GetUserLengthChoose() const
{
    FString Response = "";
    int Value;
    /*We're converting the first letter of the user input to asc so if the user write a different character between 3(51)-8(56) we ask him to put his choose again */  
    do 
    {
        std::cout<<"Please, choose the word length (3-8 letters)\n";
        std::getline (std::cin,Response);
        try // Start error handling
        {
            Value = std::stoi(Response);
        }
        catch (std::invalid_argument) // trap if user didn't enter a number
        {
            Value = 0; // Force Value set = 0
        }
    } while (Value > 8 || Value < 3); 
    return Value;
}

/* After the user choose his word length we convert his input to the hidden word. Remember we're using asc (3 = 51, 4 = 52,...8=56)*/
FString Fbullcowgame::GetHiddenWord(int32 userchoose) const
{
    TMap<int32,FString> WordLengthToHiddenWord { {3,"ant"},{4,"dark"},{5,"plant"},{6,"planet"},                   {7,"planets"},{8,"runescap"} }; // THESE WORDS MUST!!! BE AN ISOGRAM"
    return WordLengthToHiddenWord[userchoose];
}

void Fbullcowgame::Reset(void)
{
    int32 UserLengthChoose = GetUserLengthChoose();
    MyCurrentTry = 1;
    MyHiddenWord =GetHiddenWord(UserLengthChoose);
    bGameIsWon = false;
    return;
}

int32 Fbullcowgame::GetMaxTries(void) const
{
    TMap<int32, int32> WordLengthToMaxTries{ {3,3}, {4,4},{5,10},{6,15},{7,20},{8,30} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 Fbullcowgame::GetCurrentTry(void) const
{
    return MyCurrentTry;
}

int32 Fbullcowgame::GetHiddenWordLength(void) const
{
    return MyHiddenWord.length();
}

bool Fbullcowgame::IsGameWon(void) const
{
    
    return bGameIsWon;
}

EGuessStatus Fbullcowgame::CheckGuessValidity(FString Guess) const
{
    //if the length is wrong
    if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    //if the guess is not an isogram
    else if  (IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    //if the guess has capital letter, special character or numbers
    else if(!IsCorrect(Guess))
    {
        return EGuessStatus::Not_Correct;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

FBullCowCount Fbullcowgame::SubmitValidGuess(FString Guess)
{ 
    //setup a return variable
    FBullCowCount BullCowCount;
    
    int32 WordLength = MyHiddenWord.length();
    MyCurrentTry = MyCurrentTry +1;
    // loop through all letters in the guess and increase the bulls/cows count    
    for (int32 i = 0; i < WordLength; i = i +1)    
    {
         // compare letters against the hidden word
        for (int32 j = 0; j < WordLength; j = j+1)
        {
            // if i is different to j and the letter matchs, incriment cows 
            if ((i != j) && (Guess[i] == MyHiddenWord[j]))
            {
                BullCowCount.Cow = BullCowCount.Cow + 1;
               
            }
            /* However if the first condition of the "if" is not attempted we know that i must be equal to j and if the             letters matchs we incriment bulls */  
            else if     (Guess[i] == MyHiddenWord[j])
            {
                BullCowCount.Bull = BullCowCount.Bull + 1;
            }
            
        }
    }
    if (BullCowCount.Bull == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
           
    return BullCowCount;
}


//Function which check if the word is an isogram or not
bool Fbullcowgame::IsIsogram(FString Guess) const
{
    int32 WordLength = Guess.length();
    
    //loop through all letters of the user guess and check if has a letter repeated
    for (int32 i = 0; i < WordLength; i = i +1)
    {
        for (int32 j = 0; j < WordLength; j = j+1)
        {
            if ((i != j) && (Guess[i] == Guess[j]))
            {
                return true;
            }
    
        }
    }
    return false;
}


// Function which check if the word is correct, that's means if the asc code is only lowercase characters (no capital letters, numbers or special characters) 
bool Fbullcowgame::IsCorrect(FString Guess) const
{
    int32 WordLength = Guess.length();
    //Loop through the word
    for (int32 i = 0; i < WordLength; i = i + 1) 
    {
        if (((int)Guess[i] < 97) || ((int)Guess[i] > 122))
        {
            return false;
        }
    }
    return true;
}