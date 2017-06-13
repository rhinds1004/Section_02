/* THis is the console executable, that makes use of the
	BullCow class. THis acts as the view in a MVC pattern, and is
	responsible for all user interaction. For game logc see the FBullCowGame Class

*/
#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// Function Prototypes
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText);
bool AskToPlayAgain();
FText FindErrorMsg(EWordStatus);
void PrintGameSummary();

FBullCowGame BCGame;
//entry point for applications
int main()
{
	do
	{
		BCGame.Reset();
		std::cout << "Max Guesses: " << BCGame.GetMaxTries() << std::endl;
		PrintIntro();
		PlayGame();
	} while(AskToPlayAgain());
	return 0;
}


//Prints the introduction to the game
void PrintIntro()
{
	std::cout << "Welcome to the Bull and Cow game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	return;
}


//Play the game
void PlayGame()
{
	int32 maxTries = BCGame.GetMaxTries();
	FText pGuess = "";
	FBullCowCount BullCowCount;

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		pGuess = GetValidGuess();
		BullCowCount = BCGame.SubmitValidGuess(pGuess);
		std::cout << "The number of bulls: " << BullCowCount.BullCount << std::endl;
		std::cout << "The number of cows: " << BullCowCount.CowCount << std::endl;
		PrintGuess(pGuess);
	}
	PrintGameSummary();
	return;
}


//Gets the players guess and loops until player input is valid
FText GetValidGuess()
{
	EWordStatus result;
	FText PlayerGuess = "";
	do
	{
		std::cout << "How many tries: " << BCGame.GetCurrentTry() << std::endl;
		std::cout << "Please enter your guess: ";
		std::getline(std::cin, PlayerGuess);
		result = BCGame.CheckGuessValidity(PlayerGuess);
		if(result != EWordStatus::OK)
		{
			std::cout << FindErrorMsg(result) << std::endl;
		}
	} while(result != EWordStatus::OK);

	return PlayerGuess;
}


//repeat the player's guess back to them
void PrintGuess(FText Guess)
{
	std::cout << "Your guess was: " << Guess << std::endl;
	return;
}


//Ask the player if they want to play the game again
//default return is false
bool AskToPlayAgain()
{
	bool bResult = false;
	std::cout << "Do you want to play again using the same hidden word?(y/n): ";
	FText response = "";
	std::getline(std::cin, response);
	if(tolower(response[0]) == 'y')
	{
		bResult = true;
	}
	return bResult;
}

//Finds error message for the error code
FText FindErrorMsg(EWordStatus Error) 
{
	FText ErrorMsg = "";
	switch(Error)
	{
	case EWordStatus::Not_Isogram:
		ErrorMsg = "Guess not an isogram";
		break;
	case EWordStatus::Too_Short:
		ErrorMsg = "Guess is too short";
		break;
	case EWordStatus::Too_Long:
		ErrorMsg = "Guess is too long";
		break;
	case EWordStatus::Not_Letter:
		ErrorMsg = "Guess contains a non-letter";
		break;
	default:
		ErrorMsg = "Unknown error occurred on guess validation";
		break;
	}
	return ErrorMsg;
}

void PrintGameSummary()
{
	if(BCGame.IsGameWon())
	{
		std::cout << "Winner!" << std::endl;
	}
	else
	{
		std::cout << "You didn't win this time, but try again. You got this!" << std::endl;
	}
}