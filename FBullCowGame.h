/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind
*/
#pragma once
#include <string>

//make syntax Unreal friendly
using FString = std::string;
using int32 = int;


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
	Not_Lowercase
};



class FBullCowGame{
	public:
		FBullCowGame(); // This is the constructor
		int32 GetMaxTries() const;
		int32 GetCurrentTry() const;
		int32 GetHiddenWordLength() const;
		bool IsGameWon() const;
		EGuessStatus CheckGuessValidity(FString) const; 


		void Reset(); //TODO, make a more rich return value.

		// counts bulls and cows, and increases the try number assuming valid guess
		FBullCowCount SubmitValidGuess(FString);


	private:
		//See FBullCowGame.h for initialization 
		int32 MyCurrentTry;
		FString MyHiddenWord;
		bool bGameIsWon;
		bool IsIsogram(FString) const;
		bool IsLowercase(FString) const;
};