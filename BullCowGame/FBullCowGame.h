#pragma once
#include <string>


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
	EWordStatus CheckGuessValidity(FString) const; //TODO make a more rich return value
	bool IsGameWon() const;
	EWordStatus IsIsogram(FString Guess) const;

	
	void Reset();

	FBullCowCount SubmitValidGuess(FString);
	int32  SetMaxTries(int32 maxTries);

private:
	//init by constructor
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bWonGame;
};