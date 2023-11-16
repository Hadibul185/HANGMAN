#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

vector<string> words = {"HELLO", "WORLD", "COMPUTER", "PROGRAMMING", "HANGMAN", "SCIENCE" , "ELEMENT" , "NEW", "OLD", "GOOD", "NICE" };
const int MAX_TRIES = 7;
const int MAX_LIVES = 5;

string getRandomWord() {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

bool isWordGuessed(const string& word, const string& guessedLetters) {
    for (char letter : word) {
        if (guessedLetters.find(letter) == string::npos) {
            return false;
        }
    }
    return true;
}

void displayWord(const string& word, const string& guessedLetters) {
    for (char letter : word) {
        if (guessedLetters.find(letter) != string::npos) {
            cout << letter << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

char giveHint(const string& word, const string& guessedLetters) {
    for (char letter : word) {
        if (guessedLetters.find(letter) == string::npos) {
            return letter;
        }
    }
    return '\0';
}

int main() {
    string wordToGuess = getRandomWord();
    string guessedLetters = "";
    int wrongTries = 0;
    int lives = MAX_LIVES;

    cout << "Welcome to Hangman!" << endl;

    while (lives > 0 && !isWordGuessed(wordToGuess, guessedLetters)) {
        cout << "Current Word: ";
        displayWord(wordToGuess, guessedLetters);

        cout << "Type 'hint' for a hint or guess a letter: ";
        string input;
        cin >> input;

        if (input == "hint") {
            char hintLetter = giveHint(wordToGuess, guessedLetters);
            if (hintLetter != '\0') {
                cout << "Hint: The word contains the letter '" << hintLetter << "'" << endl;
            } else {
                cout << "Sorry, no more hints available!" << endl;
            }
        } else if (input.length() == 1 && isalpha(input[0])) {
            char guess = toupper(input[0]);

            if (guessedLetters.find(guess) != string::npos) {
                cout << "You already guessed this letter." << endl;
            } else if (wordToGuess.find(guess) != string::npos) {
                cout << "Correct guess!" << endl;
                guessedLetters += guess;
            } else {
                cout << "Wrong guess!" << endl;
                guessedLetters += guess;
                wrongTries++;
                lives--;
                cout << "Lives left: " << lives << endl;
            }
        } else {
            cout << "Invalid input. Please enter a single letter or 'hint'." << endl;
        }
    }

    if (isWordGuessed(wordToGuess, guessedLetters)) {
        cout << "Congratulations! You guessed the word: " << wordToGuess << endl;
    } else {
        cout << "Sorry, you ran out of lives. The word was: " << wordToGuess << endl;
    }

    return 0;
}
