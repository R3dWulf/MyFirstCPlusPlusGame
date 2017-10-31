#pragma once
/*
	This is the console executible that makes use of the BUllCow Class
	This acts as the view in a MVC pattern, and is responsible for all
	use interaction. For game logic see the FBullCowGame class.
*/
#include <iostream> //copies and paste the iostream code library here
#include <string> //includes th FText library
#include "FBullCowGame.h" //include the header file. Unreal requries F before file name


//using namespace std; //allows std:: to be removed from code 

using FText = std::string; //better for cross play between 32-bit and 64-bit os???

using int32 = int;

//Prototypes to call the functions at the top to prevent compiling error
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game and looks for the constructor in the header


//Entry point for application
int main() {
	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return	0;
}



void PrintIntro() {
	//constexpr === const in ES2015???
	//std::cout === character output
	//cin === character input
	//FText xxxx = ""; a variable that will be a FText


	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n"; //<< std::endlline === \n
	std::cout << std::endl;
	std::cout << "              } {        ___" << std::endl;
	std::cout << "             (o o)      (o o) " << std::endl;
	std::cout << "   /----------\\ /        \\ /----------\\ " << std::endl;
	std::cout << "  /|   BULL   |o          o|    COW   |\\ " << std::endl;
	std::cout << " * |----,-----|            |----------| * " << std::endl;
	std::cout << "   |          |            |          | " << std::endl;
	std::cout << "   ^          ^            ^          ^ " << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";

	std::cout << std::endl;

	return; //returning nothing
}

void PlayGame(){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for number of turns asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText Guess = GetValidGuess();

		// Submit valid guess and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until user enters a valid guess
FText GetValidGuess() { //TODO change to GetValidGuess

	FText Guess = "";

	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		//get guess from user
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done, you won!\n\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}