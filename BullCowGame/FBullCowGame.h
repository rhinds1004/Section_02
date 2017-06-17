#pragma once
/* The game logic (no view code or direct user interaction)
   The game is a simple guess the word game based on Mastermind
*/

#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

// all values initilized to zero
struct FBullCowCount
{
	int32 BullCount = 0;
	int32 CowCount = 0;
};

enum class EWordStatus
{
	OK,
	Not_Isogram,
	Too_Short,
	Too_Long,
	Not_Letter,
	Not_Lowercase,
	Unknown_Error	
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32  GetMaxTries() const;
	int32  GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool GetWonGame() const;
	EWordStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;	
	
	void Reset();
	FBullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bWonGame;
	EWordStatus IsIsogram(FString Guess) const;
	bool IsLowerCase(FString Guess) const;
};