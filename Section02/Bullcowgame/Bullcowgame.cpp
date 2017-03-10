/* This is the console executable, that makes use of the BullCows class.
This acts as the view in a MVC patter, and is responsible for all user interaction. For game logic see the FBullCowGame class. */
#include <iostream>
#include <string>
#include "Fbullcowgame.h"


Fbullcowgame BCGame; //instantiate a new game

//to make syntax Unreal friendly
using int32 = int;
using FText = std::string;

//function prototypes as outside a class
void PrintIntro(void);
void PlayGame(void);
void PrintGameSumary(void);
FText GetValidGuess(void);
bool AskToPlayAgain(void);

// The entry point for our application
int main(void) 
{
    do {
        PrintIntro();
        PlayGame();
        PrintGameSumary();
    }
    //While works when the condition (inside the "()") is true, so when the return value of the function Ask... = true we have a loop.Note: when we do the "while" and he calls the function ask everything inside Ask works so if we have a print inside we'll have a print here
    while(AskToPlayAgain());
return 0;    
}

void PrintIntro(void)
{
    std::cout << "Welcome to Bulls and Cows game! Are you ready?\n";
    std::cout << 
"         .=     ,        =." << std::endl <<
" _  _   /'/    )\\,/,/(_   \\ \\" << std::endl <<
"   `//-.|  (  ,\\)\\//\\)\\/_  ) |" << std::endl <<
"   //___\\   `\\\\/\\/\\/\\///'  /" << std::endl <<
",-\"~`-._ `\"--'_   `\"\"\"`  _ \\`'\"~-,_" << std::endl <<    
"\\       `-.  '_`.      .'_` \\ ,-\"~`/" << std::endl <<
" `.__.-'`/   (-\\       /-) |-.__,'"  << std::endl <<
"   ||   |     \\O)  /^\\ (O/  |"  << std::endl <<
"   `\\  |         /   `\\    /"  << std::endl <<
"     \\  \\       /      `\\ /"  << std::endl <<
"      `\\ `-.  /' .---.--.\\" << std::endl <<
"        `\\/`~(, '()      ()'" << std::endl <<
"         /(O) \\   _,.-.,_)" << std::endl <<
"        //  \\ `\'`      /" << std::endl <<
"       / |  ||   `\"\"\"\"~\"`" << std::endl <<
"     /'  |__||" << std::endl <<
"           `o" << std::endl;
    
    
    BCGame.Reset();
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n"; 
    return;
}

void PrintGameSumary(void)
{
    if (BCGame.IsGameWon() == true)
    {
        std::cout << "Congratulations, you won!!\n";
    }
    else
    {
        std::cout << "Game Over!!\n";
    }
    return;
}



//Function which loops though the player guess and gives him a feedback of what he typed on keyboard 

void PlayGame(void)
{ 
    //BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << "Your max number of tries is:\n" << MaxTries << std::endl;
    //Loops asking for guesses while the game is NOT won and there are still tries remaining
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        //submit valid guess to the game, and receive counts
        FText Guess = GetValidGuess(); 
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        //Print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bull << std::endl << "Cows = " << BullCowCount.Cow << std::endl;     
        std::cout << "**************************\n";
    }
    return;
}


//Function which will get the guess of the player and loop continually until the user gives a valid guess
FText GetValidGuess(void) 
{
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do {
        int32 GetCurrentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << GetCurrentTry << " of " << BCGame.GetMaxTries() << std::endl;
        std::cout << "Enter your guess stranger\n";
        std::getline (std::cin,Guess);
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) 
        {
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a isogram, remember that isogram means: a word without repeated letter\n";
                break;
            case EGuessStatus::Not_Correct:
                std::cout << "Please write your word only with lowercase letters\n";
                break;
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
                break;
            case EGuessStatus::Invalid_Status:
                std::cout << "Something weird happened: I found an Invalid Status\n";
                break;
            case EGuessStatus::OK:
                break;
            default:
                break;
        }
        std::cout << std::endl;
    } while (Status != EGuessStatus::OK); //keep looping until we get no errors
    return Guess;
}

bool AskToPlayAgain(void) {
    std::cout << "Do you want to play again?\nYes/No\n";
    FText Response = "";
    std::getline (std::cin,Response);
    return (Response[0] == 'y' || Response[0] == 'Y' || Response[0] == 's' || Response[0] == 'S');
}

