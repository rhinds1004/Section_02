#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;
using TCHAR = char;



void FBullCowGame::Reset()
{
	constexpr int32 START_CURRENT_TRY = 0;
	const FString HIDDEN_WORD = "plan";

	this->MyCurrentTry = START_CURRENT_TRY;
	this->MyHiddenWord = HIDDEN_WORD;
	this->bWonGame = false;
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

bool FBullCowGame::GetWonGame()const { return this->bWonGame; }


int32 FBullCowGame::GetHiddenWordLength() const
{
	return this->MyHiddenWord.length()/sizeof(TCHAR);
}


bool FBullCowGame::IsGameWon() const 
{
	return this->GetWonGame();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,7}, {6,8} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

EWordStatus FBullCowGame::IsIsogram(FString Guess) const
{
	EWordStatus result = EWordStatus::OK;
	TMap<char, bool> LetterSeen;
	//treat 0 or 1 guess as isograms
	if(Guess.length()/sizeof(TCHAR) <= 1){ return result; }

	for(auto Letter : Guess) 
	{
		Letter = tolower(Letter);
		if(!isalpha(Letter))
		{
			result = EWordStatus::Not_Letter;
			break;
		}
		if(LetterSeen[Letter] == true)
		{
			result = EWordStatus::Not_Isogram;
			break;
		}
		else
		{
			LetterSeen[Letter] = true;
		}

	}
	return result;
}

// if a letter in the guess is not lower case, function returns false
// returns true otherwise.
bool FBullCowGame::IsLowerCase(FString Guess) const
{

	for(auto Letter : Guess)
	{
		if(islower(Letter) == false)
		{
			return false;
		}
	}
	return true;
}



EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	int32 guessLength = Guess.length() / sizeof(TCHAR);
	int32 hiddenWordLength = GetHiddenWordLength();
	EWordStatus result = EWordStatus::Unknown_Error;

	result = IsIsogram(Guess);
	if(result == EWordStatus::OK)
	{
		if(guessLength != hiddenWordLength)
		{
			if(guessLength < hiddenWordLength)
			{
				result = EWordStatus::Too_Short;
			}
			else
			{
				result = EWordStatus::Too_Long;
			}
		}
		else if(IsLowerCase(Guess) == false)
		{
			result = EWordStatus::Not_Lowercase;
		}
		else
		{
			result = EWordStatus::OK;
		}
	}
	return result;
}

//recieves a valid guess and increments turn, and returns count of Bulls and Cows
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 counter = 0, i = 0;
	while(counter < (int32)(Guess.length()/sizeof(TCHAR)))
	{
		// compare letters against the hidden word
		// if guess's letter and guess's letter position within the word
		// is the same as hidden word's letter and letter
		// position. It's a bull.
		if(tolower(Guess[counter]) == MyHiddenWord[counter])
		{
			BullCowCount.BullCount++;
		}
		else
		{
			// Checks if the guess's letter is anywhere with the hidden word
			// if the letter is found. It's a cow
			for(i = 0; i < GetHiddenWordLength(); i++)
			{
				if(tolower(Guess[counter]) == MyHiddenWord[i])
				{
					BullCowCount.CowCount++;
				}
			}
		}
		counter++;
	}
	if(BullCowCount.BullCount == GetHiddenWordLength())
	{
		this->bWonGame = true;
	}
	return BullCowCount;
}


