#pragma once
#include "FBullCowGame.h"
#include <map>

// make syntax more Unreal friendly
#define TMap std::map 
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); } // default constructor


int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; //this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	
	if (!IsIsogram(Guess)) { // If guesss is not an isogram, return error
		return EGuessStatus::Not_Isogram;
	} 
	else if(!IsLowercase(Guess)){ 
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {	// else return okay
		return EGuessStatus::OK;
	}
}

//receives a valid guess and increments turn count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all the letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters of the guessed word against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if letters match
			if (Guess[GChar] == MyHiddenWord[MHWChar]) { // using [i] here for both Guss and MyhiddenWord will cause BullCowCount++ to run twice
				if (GChar == MHWChar) {
					BullCowCount.Bulls++;
				} 
				else {
					BullCowCount.Cows++;
				}
			}

		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) {
		return true;
	}
	TMap<char, bool> LetterSeen;//setup map
	for (auto Letter : Word) {//For all letters of the word
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; //we do not have an isogram
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;// for example in case cases where symbols or numbers are entered
}

bool FBullCowGame::IsLowercase(FString Word) const{
	for (auto Letter : Word) { 
		//If not a lowercase letter then return false
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
