// The game logic (no view code or direct user interaction
// The game is a simple guess the word game based on Mastermind
#pragma once
#include <string>	
//Make Unreal Friendly
using int32 = int;
using FString = std::string;
//all initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status, 
	OK,
	Not_Isogram, 
	Wrong_Length, 
	Not_lowercase,
	No_numbers,
	No_special_chars,

};

class FBullCowGame
{
public: 
	FBullCowGame(); //constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	
	// Assuming valid guess counting bulls and cows and increasing try# number
	FBullCowCount SubmitValidGuess(FString);


// please try to ignore this and focus on the interface above 
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};