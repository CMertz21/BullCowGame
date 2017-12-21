
/* This is the console executable, that makes use of the BullCowClass
This acts as the vies in a MVC parrern, and is responsible for all user interaction. For gamelogic see the FBullCowGame class
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
//to make syntax Unreal friendly
using int32 = int;
using FText = std::string;

//function prototypes outside class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiiate a new game

//entry point for the application
int main()
{	
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
return 0; //exit the application	
}


//Print Intro
void PrintIntro() 
{
	//Introduce the Game

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "          }_{                ____ " << std::endl;
	std::cout << "         (o o)              (o  o) " << std::endl;
	std::cout << "  /-------\\ /                 \\ /-------\\" << std::endl;
	std::cout << " / | BULL |O                   O| COW  | \\ " << std::endl;
	std::cout << "*  |-,--- |                     |------|  * " << std::endl;
	std::cout << "   ^      ^                     ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of\n";
	std::cout << std::endl;
	return;
}

// PlayGame Loop - Plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	

	// loop  asking for guesses while the game is NOT won 
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
	//initialize Guess and set equal to GetGuess()
		FText Guess = GetValidGuess();

		//Submit Valid Guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print Number of Bulls / Cows
		std::cout << "Bulls= " << BullCowCount.Bulls;
		std::cout << ". Cows= " << BullCowCount.Cows << "\n\n";
		PrintGameSummary();
	}
	
	return;
}

//Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
	//calls GetCurrentTry from FBullCowGame.h
	int32 CurrentTry = BCGame.GetCurrentTry();

	//Get current try from the user
	std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
	
	std::getline(std::cin, Guess);
	//switch for validity
	 Status = BCGame.CheckGuessValidity(Guess);
	switch (Status)
		{
	case EGuessStatus::Wrong_Length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "Please enter an isogram (A word with no repeating letters. \n\n";
		break;
	case EGuessStatus::Not_lowercase:
		std::cout << "Please enter only lowercase letters. \n\n";
		break;
	case EGuessStatus::No_numbers:
		std::cout << "Please enter only lowercase letters. No numbers or special chars.  \n\n";
		break;
	default:
		//assume the guess is valid
		break;
		}
	

	} while (Status != EGuessStatus::OK); //keep looping until we get no errors. 
	return Guess;
}

//ask to play again
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
		
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else if (BCGame.GetCurrentTry() > BCGame.GetMaxTries())
	{
		std::cout << " OUT OF GUESSES - - Better luck next time! \n\n";
	}
	return;
}

