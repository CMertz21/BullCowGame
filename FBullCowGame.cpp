#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;
using FString = std::string;

//constructor
FBullCowGame::FBullCowGame(){Reset();} //default constructor
//Getters

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const{return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, { 4, 7 }, { 5, 10}, { 6, 15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() 
{
	constexpr int32 MAX_TRIES = 3;
	const FString HIDDEN_WORD = "planet"; // This MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}
//recieves a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{

	//increment the turn number
	MyCurrentTry++;
	//setup a return value
	FBullCowCount BullCowCount;
	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{

			// if they match then 
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; //increment bulls
				}
				// if not in the same place
				else 
				{
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}
	//before returning BullCowCount check if Bulls = Wordlength to win
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word)  //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed cases
		if (LetterSeen[Letter]) {
			return false;}//we do NOT have an isogram
		else{
			LetterSeen[Letter] = true;
			}
			
	}
	return true; //for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//if not a lowercase letter 
		{
			return false;
		
			return true;
		}	
	}
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess))//if the guess isn't an isogram 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase 
	{
		return EGuessStatus::Not_lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())//if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	} 
	else
	{
		return EGuessStatus::OK;
	}
		
	//otherwise
		//return ok
}

