#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;
using TCHAR = char;



void FBullCowGame::Reset()
{
	constexpr int32 START_CURRENT_TRY = 1;
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	this->MyCurrentTry = START_CURRENT_TRY;
	this->MyMaxTries = MAX_TRIES;
	this->MyHiddenWord = HIDDEN_WORD;
	this->bWonGame = false;
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

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

EWordStatus FBullCowGame::IsIsogram(FString Guess) const
{
	int32 guessLength = Guess.length() / sizeof(TCHAR);
	EWordStatus result = EWordStatus::OK;
	TCHAR guessChar = NULL;
	int32 counter = 0, i = 0;
	do
	{
		guessChar = Guess[counter];
		if(!isalpha(guessChar))
		{
			result = EWordStatus::Not_Letter;
		}
		else
		{
			for(i = 0; i < guessLength; i++)
			{
				if(Guess[i] == guessChar && i != counter)
				{
					result = EWordStatus::Not_Isogram;
					break;
				}
			}
		}
		counter++;
	} while(result == EWordStatus::OK && counter < guessLength);
	return result;
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
		if(Guess[counter] == MyHiddenWord[counter])
		{
			BullCowCount.BullCount++;
		}
		else
		{
			// Checks if the guess's letter is anywhere with the hidden word
			// if the letter is found. It's a cow
			for(i = 0; i < GetHiddenWordLength(); i++)
			{
				if(Guess[counter] == MyHiddenWord[i])
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

int32 FBullCowGame::SetMaxTries(int32 maxTries)
{
	MyMaxTries = maxTries;
	return 0;
}
