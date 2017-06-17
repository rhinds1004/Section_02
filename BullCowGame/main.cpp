#pragma once
/*  This is the console executable, that makes use of the
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

FBullCowGame BCGame;  //instaiates a class used throughout the game.


int main()
{
	do
	{
		BCGame.Reset();
		PrintIntro();
		std::cout << "Max Amount of Guesses: " << BCGame.GetMaxTries() << std::endl;
		PlayGame();
	} while(AskToPlayAgain());
	return 0;
}


//Prints the introduction to the game
void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "Welcome to the Bull and Cow game" << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	return;
}


//Plays a single game to completion
void PlayGame()
{
	int32 maxTries = BCGame.GetMaxTries();
	FText pGuess = "";
	FBullCowCount BullCowCount;

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() < BCGame.GetMaxTries())
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
		std::cout << std::endl;
		std::cout << "You have " << BCGame.GetMaxTries() - BCGame.GetCurrentTry() << " guesses left" << std::endl;
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
	std::cout << std::endl;
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
		ErrorMsg = "Guess is not an isogram";
		break;
	case EWordStatus::Too_Short:
		ErrorMsg = "Guess is too short";
		break;
	case EWordStatus::Too_Long:
		ErrorMsg = "Guess is too long";
		break;
	case EWordStatus::Not_Letter:
		ErrorMsg = "Guess can not contain a non-letter";
		break;
	case EWordStatus::Not_Lowercase:
		ErrorMsg = "Guess can not contain an Uppercase letter";
		break;
	default:
		ErrorMsg = "Unknown error occurred on guess validation";
		break;
	}

	return ErrorMsg;
}

//Tells the player if they won or lost the game.
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
